const socket = io.connect('http://localhost');

const ctxT = document.getElementById("temperature-chart").getContext("2d");
const cfgT = config('Temperature (Celcius)', '#2377d1', 0, 100, 10, 90);
const Tchart = new Chart(ctxT, cfgT);

const ctxH = document.getElementById("humidity-chart").getContext("2d");
const cfgH = config('Humidity', '#34ad3c', 0, 100, 5, 70);
const Hchart = new Chart(ctxH, cfgH);

const ctxL = document.getElementById("luminosity-chart").getContext("2d");
const cfgL = config('Luminosity (lux)', '#339aad', 0, 100, 10, 100);
const Lchart = new Chart(ctxL, cfgL);


socket.on('temperature', function (data) {
    $('#temperature').text(data)
    addData(Tchart, data)
});

socket.on('humidity', function (data) {
    $('#humidity').text(data)
    addData(Hchart, data)
});

socket.on('luminosity', function (data) {
    $('#luminosity').text(data)
    addData(Lchart, data)    
});

$( function() {
    $( "#slider-range" ).slider({
      range: true,
      min: Tchart.config.min,
      max: Tchart.config.max,
      values: [ Tchart.config.limMin , Tchart.config.limMax ],
      slide: function( event, ui ) {
        console.log(ui.values)
      },
      change: function( event, ui ) {
        console.log(ui.values)
        Tchart.config.limMin = ui.values[0];
        Tchart.config.limMax = ui.values[1];
      }
    });
    
  } );