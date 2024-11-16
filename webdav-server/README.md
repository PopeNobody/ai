
# WebDAV LLM Server

This Node.js application implements a WebDAV server with custom functionality:
- **HASH Method**: Computes and returns an MD5 hash of a file at the specified URL.
- **Redispatched Methods**: Allows methods like PUT and DELETE through a POST request with a custom "method" header.

## Features
- File access restricted to a chroot-like directory.
- Dynamic method support for interacting with files.

## Deployment
1. Install dependencies: `npm install express crypto`
2. Set environment variables:
   - `CHROOT_DIR`: Base directory for file operations (default: `/home/$LLM`).
   - `PORT`: Port to run the server (default: `8080`).
3. Run the server: `node server.js`

## Example Usage
- GET: Retrieve a file's content.
- POST with `method: HASH`: Get MD5 hash of a file.
- POST with `method: PUT`: Create or overwrite a file.
- POST with `method: DELETE`: Delete a file.

