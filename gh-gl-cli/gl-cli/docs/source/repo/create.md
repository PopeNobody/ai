---
stage: Create
group: Code Review
info: To determine the technical writer assigned to the Stage/Group associated with this page, see https://about.gitlab.com/handbook/product/ux/technical-writing/#assignments
---

<!--
This documentation is auto generated by a script.
Please do not edit this file directly. Run `make gen-docs` instead.
-->

# `glab repo create`

Create a new GitLab project/repository.

```plaintext
glab repo create [path] [flags]
```

## Examples

```plaintext
# Create a repository under your account using the current directory name.
$ glab repo create

# Create a repository under a group using the current directory name.
$ glab repo create --group glab-cli

# Create a repository with a specific name.
$ glab repo create my-project

# Create a repository for a group.
$ glab repo create glab-cli/my-project

```

## Options

```plaintext
      --defaultBranch master   Default branch of the project. Defaults to master if not provided.
  -d, --description string     Description of the new project.
  -g, --group string           Namespace or group for the new project. Defaults to the current user's namespace.
      --internal               Make project internal: visible to any authenticated user. Default.
  -n, --name string            Name of the new project.
  -p, --private                Make project private: visible only to project members.
  -P, --public                 Make project public: visible without any authentication.
      --readme README.md       Initialize project with README.md.
      --remoteName origin      Remote name for the Git repository you're in. Defaults to origin if not provided. (default "origin")
  -t, --tag stringArray        The list of tags for the project.
```

## Options inherited from parent commands

```plaintext
      --help   Show help for this command.
```