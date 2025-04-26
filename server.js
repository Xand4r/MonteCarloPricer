const express = require('express');
const { execFile } = require('child_process');
const os = require('os');
const path = require('path');
const app = express();
const port = 3000;

// Middleware
app.use(express.json());
const publicPath = path.join(__dirname, 'public');
console.log('Serving static files from:', publicPath);
app.use(express.static(publicPath));

// GET / zeigt index.html
app.get('/', (req, res) => {
    res.sendFile(path.join(publicPath, 'index.html'));
});

// POST /calculate
app.post('/calculate', (req, res) => {
    const { day, month, year, weekday, strike, symbol, type, pricing, accuracy, dataKey, yieldKey } = req.body;

    let binary;
    if (os.platform() === 'win32') {
        binary = path.join(__dirname, 'bin', 'option_pricer.exe');
    } else if (os.platform() === 'darwin') {
        binary = path.join(__dirname, 'bin', 'option_pricer');
    } else {
        return res.status(500).send('Unsupported OS');
    }

    execFile(binary, [day, month, year, weekday, strike, symbol, type, pricing, accuracy, dataKey, yieldKey], (error, stdout, stderr) => {
        if (error) {
            console.error('Error executing C++ program:', error);
            return res.status(500).send('Error executing C++ code');
        }
        if (stderr) {
            console.error('stderr:', stderr);
            return res.status(500).send(stderr);
        }

        res.json({ price: parseFloat(stdout.trim()) });
    });
});

// Server starten
app.listen(port, () => {
    console.log(`Server running at http://localhost:${port}`);
});
