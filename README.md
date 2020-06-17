# Qt-Server-Sent-Events-Demo

A Qt5 Server Sent Events (SSE) demo.

## Build instructions

- `cmake CMakeLists.txt`
- `make`
- `./qt-sse-demo <URL>`

## Demo

**Setup SSE server**

This repo includes a simple SSE server demo in the `server` directory.
To run it, you need NodeJS and Yarn installed:

- `cd server`
- `yarn install`
- `yarn start`

The demo server runs on port `3000` and publishes events on `/events`.

**Demo time!**

Start the Qt SSE demo with our SSE demo server as URL:

`./qt-sse-demo http://localhost:3000/events`

```
[dylan@desktop Qt-Server-Sent-Events-Demo]$ ./qt-sse-demo http://localhost:3000/events
Qt Server Sent Events demo, written by Dylan Van Assche.
Creating new Network::Manager
GET resource: QUrl("http://localhost:3000/events")
Received event from stream
"{\"timestamp\":\"Wed Jun 17 2020 19:09:17 GMT+0200 (Central European Summer Time)\",\"message\":\"Hello World!\"}"
-----------------------------------------------------
Received event from stream
"{\"timestamp\":\"Wed Jun 17 2020 19:09:21 GMT+0200 (Central European Summer Time)\",\"message\":\"Hello World!\"}"
-----------------------------------------------------
Received event from stream
"{\"timestamp\":\"Wed Jun 17 2020 19:09:26 GMT+0200 (Central European Summer Time)\",\"message\":\"Hello World!\"}"
-----------------------------------------------------
```
