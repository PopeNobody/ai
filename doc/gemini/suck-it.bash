 Create a directory for the documentation
mkdir -p gemini-api-docs

# Download the English version of the main documentation page, preserving MIME
# types, adjusting extensions, and removing special characters from filenames

wget -r -np -nH --cut-dirs=3 -E -P gemini-api-docs  \
--restrict-file-names=windows  \
https://ai.google.dev/gemini-api/docs/

# Download the English version of the API reference
#wget -r -np -nH --cut-dirs=3 -E -P gemini-api-docs --restrict-file-names=windows https://ai.google.dev/gemini-api/reference/en/

# Download the English version of the cookbook
#wget -r -np -nH --cut-dirs=3 -E -P gemini-api-docs --restrict-file-names=windows https://ai.google.dev/gemini-api/cookbook/en/



