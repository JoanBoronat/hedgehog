var SerialPort= require('serial-node'), serial = new SerialPort();
serial.use('COM3');
serial.open();
var read = serial.read();
console.log(read);