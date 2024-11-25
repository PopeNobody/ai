const { v2: webdav } = require('webdav-server'); // Import the v2 namespace
const path = require('path');
const server = new webdav.WebDAVServer(); // Correctly using v2 namespace
const rootDir = path.join(__dirname, 'webdav_root');
const fsManager = new webdav.PhysicalFileSystem(rootDir); // Access from v2 namespace

// Attach the filesystem to the root path
server.setFileSystem('/', fsManager, (success) => {
    if (success) {
        console.log('File system set up successfully!');
    } else {
        console.error('Failed to set up the file system!');
    }
});

// Add Basic Authentication
server.beforeRequest((ctx, next) => {
    const authHeader = ctx.request.headers['authorization'];
    if (!authHeader) {
        ctx.setCode(401);
        ctx.response.setHeader('WWW-Authenticate', 'Basic realm="WebDAV Server"');
        return;
    }

    const base64Credentials = authHeader.split(' ')[1];
    const credentials = Buffer.from(base64Credentials, 'base64').toString('utf8');
    const [username, password] = credentials.split(':');

    // Replace with your desired credentials
    if (username !== 'admin' || password !== 'password') {
        ctx.setCode(403);
        return;
    }

    next();
});

// Start the server
const port = 8080;
const host = "localhost";
server.start(port, host, () => {
    console.log(`WebDAV server is running at http://localhost:${port}`);
});
