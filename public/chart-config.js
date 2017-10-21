const MAX_VALUES = 20;


function config(label, color, min, max, limMin, limMax){
    Chart.defaults.global.defaultFontColor = "#fff";
    Chart.defaults.global.defaultColor = '#fff'
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
                borderWidth: 0.8,
                data: Array(MAX_VALUES).fill(limMax),
                fill: false,
            }
            ]
        },
        options: {
            legend: {
                display: false
            },
            scaleFontColor: "#FFFFFF",
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
                        display: true,
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
    config.data.labels.push(config.counter);

    config.data.datasets[0].data.push(value);
    config.data.datasets[0].data.splice(0,1);

    config.data.datasets[1].data.push(config.limMin);
    config.data.datasets[1].data.splice(0,1);

    config.data.datasets[2].data.push(config.limMax);
    config.data.datasets[2].data.splice(0,1);
    
    config.counter++
    chart.update();

};
