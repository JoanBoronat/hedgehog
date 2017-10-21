const express = require('express');
const socket = require('socket.io');
const app = express();
const server = app.listen(80);
const io = socket(server);

app.use(express.static('public'));

app.get('/', function (req, res) {
  res.sendFile(__dirname + '/index.html');
});

io.on('connection', function (socket) {

    setInterval(() => {
        socket.emit('temperature', Math.random() * 100 % 100);
        socket.emit('humidity', Math.random() * 100 % 100);
        socket.emit('luminosity', Math.random() * 100 % 100);
    }, 1000)
    
  
  

});