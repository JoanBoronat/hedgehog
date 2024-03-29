const socket = io.connect('http://localhost');

const ctxT = document.getElementById("temperature-chart").getContext("2d");
const cfgT = config('Temperature (Celcius)', '#2377d1', 0, 50, 5, 45);
const Tchart = new Chart(ctxT, cfgT);

const ctxH = document.getElementById("humidity-chart").getContext("2d");
const cfgH = config('Humidity (RH)', '#34ad3c', 0, 100, 10, 88);
const Hchart = new Chart(ctxH, cfgH);

const ctxL = document.getElementById("luminosity-chart").getContext("2d");
const cfgL = config('Luminosity (lux)', '#339aad', 0, 1200, 0, 1200);
const Lchart = new Chart(ctxL, cfgL);

let errorCounter = 0;

socket.on('temperature', function (data) {
    updateValue('#temperature', data, '°C', Tchart);
    addData(Tchart, data)
});

socket.on('humidity', function (data) {
    updateValue('#humidity', data, '%RH', Hchart);
    addData(Hchart, data) 
});

socket.on('luminosity', function (data) {
    updateValue('#luminosity', data, 'lux', Lchart);
    addData(Lchart, data)    
});

socket.on('sensorError', function(data) {
    const {sensor, error, value} = data
    addError(sensor, error, value)
});

$( function() {
    createSlider(Tchart, '#slider-temperature');
    createSlider(Hchart, '#slider-humidity');
    createSlider(Lchart, '#slider-luminosity');

    $('#stop').click(() => power('off'))    
    $('#start').click(() => power('on'))

});

