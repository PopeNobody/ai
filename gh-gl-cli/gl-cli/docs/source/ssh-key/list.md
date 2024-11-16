---
stage: Create
group: Code Review
info: To determine the technical writer assigned to the Stage/Group associated with this page, see https://about.gitlab.com/handbook/product/ux/technical-writing/#assignments
---

<!--
This documentation is auto generated by a script.
Please do not edit this file directly. Run `make gen-docs` instead.
-->

# `glab ssh-key list`

Get a list of SSH keys for the currently authenticated user.

```plaintext
glab ssh-key list [flags]
```

## Examples

```plaintext
glab ssh-key list

```

## Options

```plaintext
  -p, --page int       Page number. (default 1)
  -P, --per-page int   Number of items to list per page. (default 30)
      --show-id        Shows IDs of SSH keys.
```

## Options inherited from parent commands

```plaintext
      --help              Show help for this command.
  -R, --repo OWNER/REPO   Select another repository. Can use either OWNER/REPO or `GROUP/NAMESPACE/REPO` format. Also accepts full URL or Git URL.
```