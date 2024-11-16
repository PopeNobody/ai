---
stage: Create
group: Code Review
info: To determine the technical writer assigned to the Stage/Group associated with this page, see https://about.gitlab.com/handbook/product/ux/technical-writing/#assignments
---

<!--
This documentation is auto generated by a script.
Please do not edit this file directly. Run `make gen-docs` instead.
-->

# `glab variable list`

List variables for a project or group.

```plaintext
glab variable list [flags]
```

## Aliases

```plaintext
ls
```

## Examples

```plaintext
glab variable list

```

## Options

```plaintext
  -g, --group string      Select a group or subgroup. Ignored if a repository argument is set.
  -F, --output string     Format output as: text, json. (default "text")
  -R, --repo OWNER/REPO   Select another repository. Can use either OWNER/REPO or `GROUP/NAMESPACE/REPO` format. Also accepts full URL or Git URL.
```

## Options inherited from parent commands

```plaintext
      --help   Show help for this command.
```