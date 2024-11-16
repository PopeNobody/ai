---
stage: Create
group: Code Review
info: To determine the technical writer assigned to the Stage/Group associated with this page, see https://about.gitlab.com/handbook/product/ux/technical-writing/#assignments
---

<!--
This documentation is auto generated by a script.
Please do not edit this file directly. Run `make gen-docs` instead.
-->

# `glab ci trigger`

Trigger a manual CI/CD job.

```plaintext
glab ci trigger <job-id> [flags]
```

## Examples

```plaintext
$ glab ci trigger
# Interactively select a job to trigger

$ glab ci trigger 224356863
# Trigger manual job with id 224356863

$ glab ci trigger lint
# Trigger manual job with name lint

```

## Options

```plaintext
  -b, --branch string     The branch to search for the job. Default: current branch.
  -p, --pipeline-id int   The pipeline ID to search for the job.
```

## Options inherited from parent commands

```plaintext
      --help              Show help for this command.
  -R, --repo OWNER/REPO   Select another repository. Can use either OWNER/REPO or `GROUP/NAMESPACE/REPO` format. Also accepts full URL or Git URL.
```