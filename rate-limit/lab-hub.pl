#!/usr/bin/env perl
use strict;
use warnings;
use LWP::UserAgent;
use JSON;
use YAML::Tiny;
use File::Path qw(make_path);
use File::Spec;
use Cwd;

# GitLab API configuration
my $config_path = File::Spec->catfile($ENV{HOME}, '.config', 'gitlab-cli', 'config.yml');
my $rate_limit_delay = 1; # Delay in seconds
my $base_url = "https://gitlab.com/api/v4";

# Load the API token from the YAML configuration
my $personal_access_token = load_api_token($config_path);
if (!$personal_access_token) {
    die "Error: Could not find a valid API token in $config_path\n";
}

# Set up HTTP client
my $ua = LWP::UserAgent->new;
$ua->default_header('PRIVATE-TOKEN' => $personal_access_token);

# Main logic
if (is_git_repo()) {
    print "Detected Git repository.\n";

    my $gitlab_metadata = get_or_create_gitlab_metadata();
    if ($gitlab_metadata) {
        print "GitLab Metadata:\n", to_json($gitlab_metadata, { pretty => 1 }), "\n";
        # Further logic can use this metadata
    }
} else {
    print "No Git repository detected. Exiting.\n";
    exit 1;
}

# Functions

# Load API token from YAML config
sub load_api_token {
    my $path = shift;

    if (-e $path) {
        my $yaml = YAML::Tiny->read($path);
        if ($yaml) {
            my $token = $yaml->[0]->{core}->{token};
            return $token if $token;
        }
    }
    return undef;
}

# Check if we are in a Git repository
sub is_git_repo {
    return -d File::Spec->catdir(getcwd(), '.git');
}

# Get or create GitLab metadata
sub get_or_create_gitlab_metadata {
    my $metadata_file = File::Spec->catfile(getcwd(), '.gitlab.json');

    # Use existing metadata if available
    if (-e $metadata_file) {
        print "Using cached metadata from $metadata_file\n";
        open my $fh, '<', $metadata_file or die "Could not open $metadata_file: $!";
        local $/;
        my $content = <$fh>;
        close $fh;
        return decode_json($content);
    }

    # Fetch metadata if not cached
    my $project_path = get_project_path();
    if (!$project_path) {
        die "Error: Could not determine the project path from the Git remote.\n";
    }

    print "Fetching project metadata for $project_path from GitLab...\n";
    my $project_data = api_call('GET', "/projects/" . uri_escape($project_path));
    if ($project_data) {
        # Save metadata to file
        open my $fh, '>', $metadata_file or die "Could not write to $metadata_file: $!";
        print $fh to_json($project_data, { pretty => 1 });
        close $fh;

        # Commit the metadata file
        system("git add $metadata_file && git commit -m 'Add GitLab metadata cache file'") == 0
            or warn "Could not commit $metadata_file: $!";

        return $project_data;
    }
    return undef;
}

# Parse the Git remote URL to extract the project path
sub get_project_path {
    my $remote_info = `git remote --verbose`;
    my ($remote_url) = $remote_info =~ m{origin\s+(\S+)\s+\(fetch\)};
    return undef unless $remote_url;

    if ($remote_url =~ m{gitlab\.com[:/]([^:/.]+/[^:/.]+)}) {
        return $1; # Extracted path: e.g., "nobody-does-ai/ai"
    }
    return undef;
}

# Helper function to make an API call
sub api_call {
    my ($method, $endpoint, $data) = @_;
    my $url = "$base_url$endpoint";

    print "API call: $url\n";
    my $response = $method eq 'GET'
        ? $ua->get($url)
        : $ua->post($url, Content => encode_json($data || {}), 'Content-Type' => 'application/json');

    if ($response->is_success) {
        return decode_json($response->decoded_content);
    } else {
        warn "API call failed: " . $response->status_line;
        return undef;
    }
}

# Escape URI components (e.g., "user/project" -> "user%2Fproject")
sub uri_escape {
    my $uri = shift;
    $uri =~ s{([^A-Za-z0-9\-._~])}{sprintf "%%%02X", ord($1)}eg;
    return $uri;
}
