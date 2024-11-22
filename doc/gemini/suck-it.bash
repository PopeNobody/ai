#!/bin/bash

# Create a directory for the documentation
mkdir -p gemini-api-docs

# Download the main documentation page, preserving MIME types and adjusting extensions
wget -r -np -nH --cut-dirs=3 -E -P gemini-api-docs https://ai.google.dev/gemini-api/docs

# Download the API reference
wget -r -np -nH --cut-dirs=3 -E -P gemini-api-docs https://ai.google.dev/gemini-api/reference

# Download the cookbook
wget -r -np -nH --cut-dirs=3 -E -P gemini-api-docs https://ai.google.dev/gemini-api/cookbook