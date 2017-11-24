const express = require('express');
const socket = require('socket.io');
const app = express();
const server = app.listen(80, () => console.log("Server listening on port 80"));
const io = socket(server);

let pwr = true;

const SerialPort = require('serialport');
const parsers = SerialPort.parsers;

// Use a `\r\n` as a line terminator
const parser = new parsers.Readline({
  delimiter: '\r\n'
});

const port = new SerialPort('COM4', {
  baudRate: 9600
});

port.pipe(parser);

app.use(express.static('public'));

app.get('/', function (req, res) {
  res.sendFile(__dirname + '/index.html');
});

io.on('connection', function (socket) {

    let sensor, value
    parser.on('data', (data) => {
        
        console.log(data)
        /*[sensor, value] = data.split(' ')
        switch(sensor) {
            case 'temperature':
                socket.emit('temperature', value)
                break;
            case 'humidity':
                socket.emit('humidity', value)
                break;
            case 'luminosity':
                socket.emit('luminosity', value)
                break;

        }*/
    
    });

    socket.on('setLimit', function(data) {
        port.write("Hello world")
    });

    socket.on('power', function(data) {
        pwr = data == 'on' ? true : false;
        console.log('   power' + data);
    });

});