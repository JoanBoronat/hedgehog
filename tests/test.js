const express = require('express');
const app = express();
const server = app.listen(80, () => console.log("Server listening on port 80"));

const SerialPort = require('serialport');
const parsers = SerialPort.parsers;

// Use a `\r\n` as a line terminator
const parser = new parsers.Readline({
  delimiter: '\r\n'
});

const port = new SerialPort('COM3', {
  baudRate: 9600
});

port.pipe(parser);

port.on('open', () => console.log('Port open'));

let i= 0
parser.on('data', (data) => {
    i++;
    console.log(i, 'Data received: ', data)
});
