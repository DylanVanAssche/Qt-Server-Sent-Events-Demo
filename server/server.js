/*
 * SSE server demo
 * (c) Dylan Van Assche (2020)
 * Released under the GPLv3 license
 * Based on: https://alligator.io/nodejs/server-sent-events-build-realtime-app/
 */
const express = require('express');
const cors = require('cors');
const app = express();
const PORT = 3000;
const INTERVAL = 5000;

// SSE headers
const headers = {
    'Content-Type': 'text/event-stream',
    'Connection': 'keep-alive',
    'Cache-Control': 'no-cache'
};

// Client management 
let clientIdCounter = 0
let clients = [];

// Handles new client connections
function eventsHandler(req, res) {
    res.writeHead(200, headers);
    let data = {
        'timestamp': `${new Date()}`,
        'message': 'Hello World!'
    }
    res.write(`data: ${JSON.stringify(data)}\n\n`);

    let clientId = clientIdCounter;
    const client = {
        id: clientId,
        res
    };
    clients.push(client);
    clientIdCounter++;

    // Remove client from list if connection is closed
    req.on('close', () => {
        console.log(`${clientId} Connection closed`);
        clients = clients.filter(c => c.id !== clientId);
    });
}

// Send events to all clients using SSE
function sendEvents() {
    console.info('Sending events to all clients');
    let data = {
        'timestamp': `${new Date()}`,
        'message': 'Hello World!'
    }
    clients.forEach(c => c.res.write(`data: ${JSON.stringify(data)}\n\n`))
}

// Setup resources
app.use(cors());
app.get('/events', eventsHandler);

// Push to clients every $INTERVAL ms 
setInterval(sendEvents, INTERVAL);

// Start server
app.listen(PORT, () => console.log(`SSE server demo listening on port ${PORT}`));
