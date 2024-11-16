---
stage: Create
group: Code Review
info: To determine the technical writer assigned to the Stage/Group associated with this page, see https://about.gitlab.com/handbook/product/ux/technical-writing/#assignments
---

<!--
This documentation is auto generated by a script.
Please do not edit this file directly. Run `make gen-docs` instead.
-->

# `glab mr close`

Close a merge request.

```plaintext
glab mr close [<id> | <branch>] [flags]
```

## Examples

```plaintext
$ glab mr close 1

# Close multiple merge requests at once
$ glab mr close 1 2 3 4

# Use the checked-out branch
$ glab mr close

$ glab mr close branch
$ glab mr close username:branch
$ glab mr close branch -R another/repo

```

## Options inherited from parent commands

```plaintext
      --help              Show help for this command.
  -R, --repo OWNER/REPO   Select another repository. Can use either OWNER/REPO or `GROUP/NAMESPACE/REPO` format. Also accepts full URL or Git URL.
```