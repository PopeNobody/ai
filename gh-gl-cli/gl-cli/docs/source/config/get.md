---
stage: Create
group: Code Review
info: To determine the technical writer assigned to the Stage/Group associated with this page, see https://about.gitlab.com/handbook/product/ux/technical-writing/#assignments
---

<!--
This documentation is auto generated by a script.
Please do not edit this file directly. Run `make gen-docs` instead.
-->

# `glab config get`

Prints the value of a given configuration key.

```plaintext
glab config get <key> [flags]
```

## Examples

```plaintext

  $ glab config get editor
  vim
  $ glab config get glamour_style
  notty

```

## Options

```plaintext
  -g, --global        Read from global config file (~/.config/glab-cli/config.yml). Default: checks 'Environment variables → Local → Global'.
  -h, --host string   Get per-host setting.
```

## Options inherited from parent commands

```plaintext
      --help   Show help for this command.
```