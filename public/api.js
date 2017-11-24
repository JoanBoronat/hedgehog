const MAX_VALUES = 15;


function config(label, color, min, max, limMin, limMax){
    Chart.defaults.global.defaultFontColor = "#bcc0c6";
    Chart.defaults.global.defaultColor = '#bcc0c6'
    Chart.defaults.global.animation.duration = 500;
    Chart.defaults.global.animation.easing = 'linear';
    Chart.defaults.global.elements.line.tension = 0.2;

    return {
        type: 'line',
        counter: 0,
        min: min,
        max: max,
        limMin: limMin,
        limMax: limMax,        
        data: {
            labels: Array(MAX_VALUES).fill(''),
            datasets: [{
                label: "Value",
                backgroundColor: color,
                borderColor: color,
                borderWidth: 1.2,
                data: Array(MAX_VALUES  ).fill(min),
                fill: false,
            },
            {
                label: "Limit inferior",
                backgroundColor: '#bf283e',
                borderColor: '#bf283e',
                pointRadius: 0,
                borderWidth: 0.8,
                data: Array(MAX_VALUES).fill(limMin),
                fill: false,
            },
            {
                label: "Limit superior",
                backgroundColor: '#bf283e',
                borderColor: '#bf283e',
                pointRadius: 0,
                borderWidth: 1,
                data: Array(MAX_VALUES).fill(limMax),
                fill: false,
            }
            ]
        },
        options: {
            legend: {
                display: false
            },
            responsive: true,
            tooltips: {
                mode: 'index',
                intersect: false,
            },
            hover: {
                mode: 'point',
                intersect: true
            },
            scales: {
                xAxes: [{
                    color: '#4f4e4e',
                    display: true,
                    gridLines: {
                        color: "#4f4e4e"
                      },
                }],
                yAxes: [{
                    color: '#4f4e4e',
                    display: true,
                    ticks: {
                        min: min,
                        max: max
                    },
                    scaleLabel: {
                        display: false,
                        labelString: label
                    },
                    gridLines: {
                        color: "#4f4e4e"
                      },
                }]
            }
        },
    };
}

function addData(chart, value) {

    let {config} = chart

    config.data.labels.splice(0,1);

    config.data.labels.push('');

    config.data.datasets[0].data.push(value);   
    config.data.datasets[0].data.splice(0,1);

    config.data.datasets[1].data.push(config.limMin);
    config.data.datasets[1].data.splice(0,1);

    config.data.datasets[2].data.push(config.limMax);
    config.data.datasets[2].data.splice(0,1);
    
    config.counter++
    chart.update();

};

function addError(sensor, error, value) {
    const tr = $(`<tr>
        <th scope='row'>${errorCounter++}</th>
        <td>${(new Date).toLocaleString()}</td>
        <td>${sensor}</td>
        <td>${error}</td>
        <td>${value}</td>
    </tr>`)

    $('#table-log').prepend(tr)
}

function createSlider(chart, id, sensor) {
    $( id ).slider({
        range: true,
        min: chart.config.min,
        max: chart.config.max,
        values: [ chart.config.limMin , chart.config.limMax ],
        slide: function( event, ui ) {
            $(id + "-display").text(ui.values[0] + ' - ' + ui.values[1])
            $(id + "-display").fadeIn()
        },
        change: function( event, ui ) {
          chart.config.limMin = ui.values[0];
          chart.config.limMax = ui.values[1];
          $(id + "-display").fadeOut()
          socket.emit('setLimit', {sensor: id.split('-')[1], values: ui.values})
        }
    });
}


function updateValue(id, value, unit, chart) {
    const {limMin, limMax} = chart.config
    const alertMin = limMin + limMin * 0.1;
    const alertMax = limMax * 0.9;

    $(id).text(value + ' ' + unit)
    if (value > limMax || value < limMin) $( id ).animate({color: "#bf283e"}, 500);
    else if (value > alertMax || value < alertMin) $( id ).animate({color: "#edd23b"}, 500);
    else $( id ).animate({color: "#34ad3c"}, 200);
}

function power(state) {
    switch (state) {
        case 'on':
            $('#start').hide();
            $('#stop').show();
            socket.emit('power', 'on')
        break;
        case 'off':
            $('#stop').hide();
            $('#start').show();
            socket.emit('power', 'off')
        break;
    }
}