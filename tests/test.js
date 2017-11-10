const express = require('express');
const app = express();
const server = app.listen(80, () => console.log("Server listening on port 80"));

const SerialPort = require('serialport')

var sp = new SerialPort('COM3', {
    baudRate: 9600,
}, function (err) {
    if (err) {
      return console.log('Error: ', err.message);
    }
});

sp.on('open', onPortOpen);
sp.on('data', onData);
sp.on('error', onError);

function onPortOpen(){
    console.log("ARDUINO PORT OPENED");
}

function onData(d){
    console.log("Data: ");
}

function onError(error){
    console.log("ERROR: ", error);
}