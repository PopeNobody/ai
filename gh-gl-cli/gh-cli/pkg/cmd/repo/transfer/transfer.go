package transfer

import (
	"errors"
	"fmt"
	"net/http"
	"strings"

	"github.com/cli/cli/v2/api"
	"github.com/cli/cli/v2/internal/ghrepo"
	"github.com/cli/cli/v2/pkg/cmdutil"
	"github.com/cli/cli/v2/pkg/iostreams"
	ghAuth "github.com/cli/go-gh/v2/pkg/auth"
	"github.com/spf13/cobra"
)

type iprompter interface {
	ConfirmDeletion(string) error
}

type TransferOptions struct {
	HttpClient func() (*http.Client, error)
	BaseRepo   func() (ghrepo.Interface, error)
	Prompter   iprompter
	IO         *iostreams.IOStreams
	RepoArg    string
	Confirmed  bool
}

func NewCmdTransfer(f *cmdutil.Factory, runF func(*TransferOptions) error) *cobra.Command {
	opts := &TransferOptions{
		IO:         f.IOStreams,
		HttpClient: f.HttpClient,
		BaseRepo:   f.BaseRepo,
		Prompter:   f.Prompter,
	}

	cmd := &cobra.Command{
		Use:   "transfer [<repository>]",
		Short: "Transfer a repository",
		Long: `Transfer a GitHub repository.

With no argument, transfers the current repository. Otherwise, transfers the specified repository.

Deletion requires authorization with the "transfer_repo" scope. 
To authorize, run "gh auth refresh -s transfer_repo"`,
		Args: cobra.MaximumNArgs(1),
		RunE: func(cmd *cobra.Command, args []string) error {
			if len(args) > 0 {
				opts.RepoArg = args[0]
			}

			if !opts.IO.CanPrompt() && !opts.Confirmed {
				return cmdutil.FlagErrorf("--yes required when not running interactively")
			}

			if runF != nil {
				return runF(opts)
			}

			return transferRun(opts)
		},
	}

	cmd.Flags().BoolVar(&opts.Confirmed, "confirm", false, "confirm deletion without prompting")
	_ = cmd.Flags().MarkDeprecated("confirm", "use `--yes` instead")
	cmd.Flags().BoolVar(&opts.Confirmed, "yes", false, "confirm deletion without prompting")
	return cmd
}

func transferRun(opts *TransferOptions) error {
	httpClient, err := opts.HttpClient()
	if err != nil {
		return err
	}
	apiClient := api.NewClientFromHTTP(httpClient)

	var toTransfer ghrepo.Interface

	if opts.RepoArg == "" {
		toTransfer, err = opts.BaseRepo()
		if err != nil {
			return err
		}
	} else {
		repoSelector := opts.RepoArg
		if !strings.Contains(repoSelector, "/") {
			defaultHost, _ := ghAuth.DefaultHost()
			currentUser, err := api.CurrentLoginName(apiClient, defaultHost)
			if err != nil {
				return err
			}
			repoSelector = currentUser + "/" + repoSelector
		}
		toTransfer, err = ghrepo.FromFullName(repoSelector)
		if err != nil {
			return fmt.Errorf("argument error: %w", err)
		}
	}
	fullName := ghrepo.FullName(toTransfer)

	if !opts.Confirmed {
		if err := opts.Prompter.ConfirmDeletion(fullName); err != nil {
			return err
		}
	}

	err = transferRepo(httpClient, toTransfer)
	if err != nil {
		var httpErr api.HTTPError
		if errors.As(err, &httpErr) {
			statusCode := httpErr.HTTPError.StatusCode
			if statusCode == http.StatusMovedPermanently ||
				statusCode == http.StatusTemporaryRedirect ||
				statusCode == http.StatusPermanentRedirect {
				cs := opts.IO.ColorScheme()
				fmt.Fprintf(opts.IO.ErrOut, "%s Failed to transfer repository: %s has changed name or transferred ownership\n", cs.FailureIcon(), fullName)
				return cmdutil.SilentError
			}
		}
		return err
	}

	if opts.IO.IsStdoutTTY() {
		cs := opts.IO.ColorScheme()
		fmt.Fprintf(opts.IO.Out,
			"%s Transferd repository %s\n",
			cs.SuccessIcon(),
			fullName)
	}

	return nil
}
