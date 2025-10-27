// starter was this very helpful post from @lpinca
// https://github.com/websockets/ws/issues/2052#issuecomment-1142529734

// installation: npm install ws

const WebSocketServer = require("ws");
const http = require('http');

const PORT = process.env.PORT || 8084;

const server = http.createServer((req, res) => {
  if (req.method === 'GET') {
    res.setHeader('Content-Type', 'text/html');
    res.end(data); } });

const wss = new WebSocketServer.Server({ server });

wss.on('connection', function (ws){
  console.log('qualcuno si è connesso');

  ws.on('error', console.error);

  ws.on('message', function message(data, is_binary) {
    console.log('server received: %s', data);
    if (data == "miao"){
      console.log('a miao rispondo bau');
      ws.send('bau'); }
    else {
      console.log('specchio riflesso ' + data + '##');
      ws.send(data,  { binary: is_binary }); }}); });

const data = `<!DOCTYPE html>
<html>
  <head> <meta charset="utf-8"> </head>
  <body>
    apri la console con F12
    <script>      
      var ws = new WebSocket('ws://localhost:${PORT}');
      ws.onopen = function () {
        console.log("websocket aperto. invia messaggi con\\nws.send('il tuo messaggio');"); }
      ws.onmessage = function (msg) {
        console.log('il server risponde:', msg.data); }
    </script>
  </body>
</html>`;

server.listen(PORT, () => {
    console.log(`Server in esecuzione su la porta ${PORT}`);
});
