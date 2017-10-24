const SerialPort = require('serialport');
const portName = 'COM12'

let receivedData = "";

serialPort = new SerialPort(portName, {
    baudRate: 9600,
    dataBits: 8, 
    parity: 'none', 
    stopBits: 1, 
    flowControl: false 
});

serialPort.on("open", function () {

    console.log('Open serial communication');

    serialPort.on('data', function(data) { 
        if (data != '\n') {
            console.log(receivedData);
            receivedData = '';
            serialPort.write('Hi, nice to meet you\n')
        } else {
            receivedData += data.toString();
        }
    });
}); 