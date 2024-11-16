
const express = require('express');
const crypto = require('crypto');
const fs = require('fs');
const path = require('path');

const app = express();
app.use(express.json());
app.use(express.text());

const baseDir = process.env.CHROOT_DIR || '/home/$LLM';
const port = process.env.PORT || 8080;

// Utility to compute MD5 hash of a file
const computeMD5 = (filePath) => {
    return new Promise((resolve, reject) => {
        const hash = crypto.createHash('md5');
        const stream = fs.createReadStream(filePath);
        stream.on('data', (data) => hash.update(data));
        stream.on('end', () => resolve(hash.digest('hex')));
        stream.on('error', (err) => reject(err));
    });
};

// Middleware to enforce chroot-like restriction
app.use((req, res, next) => {
    const fullPath = path.join(baseDir, req.path);
    if (!fullPath.startsWith(baseDir)) {
        return res.status(403).send("Access denied");
    }
    req.fullPath = fullPath;
    next();
});

// HASH method
app.all('*', async (req, res, next) => {
    if (req.headers.method === 'HASH') {
        const filePath = req.fullPath;
        if (!fs.existsSync(filePath)) {
            return res.status(404).send("File not found");
        }
        try {
            const hash = await computeMD5(filePath);
            return res.status(200).send(hash);
        } catch (err) {
            return res.status(500).send("Error computing hash");
        }
    }
    next();
});

// GET method
app.get('*', (req, res) => {
    const filePath = req.fullPath;
    if (fs.existsSync(filePath) && fs.statSync(filePath).isFile()) {
        res.sendFile(filePath);
    } else {
        res.status(404).send("File not found");
    }
});

// POST method with redispatch
app.post('*', (req, res) => {
    const method = req.headers.method;
    if (!method) {
        return res.status(400).send("Missing 'method' header");
    }

    switch (method.toUpperCase()) {
        case 'PUT':
            const dir = path.dirname(req.fullPath);
            if (!fs.existsSync(dir)) fs.mkdirSync(dir, { recursive: true });
            fs.writeFileSync(req.fullPath, req.body);
            res.status(201).send("File created");
            break;
        case 'DELETE':
            if (fs.existsSync(req.fullPath)) {
                fs.unlinkSync(req.fullPath);
                res.status(200).send("File deleted");
            } else {
                res.status(404).send("File not found");
            }
            break;
        default:
            res.status(400).send(`Unsupported method: ${method}`);
    }
});

// Start server
app.listen(port, () => {
    console.log(`WebDAV LLM server running on port ${port}`);
});
