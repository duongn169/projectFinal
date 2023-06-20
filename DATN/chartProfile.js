

const label = [];
const humidity = [];
const temperature = [];

const chartdata = {
    labels: label,
    datasets: [{
        label: 'Humidity',
        backgroundColor: 'rgb(255, 99, 132)',
        borderColor: 'rgb(255, 99, 132)',
        data: humidity
    },
    {
        label: 'Temperature',
        backgroundColor: 'rgb(99, 255, 132)',
        borderColor: 'rgb(99, 255, 132)',
        data: temperature
    },


    ]
};
const config = {
    type: 'line',
    data: chartdata,
    options: {
        animation: false
    }
};
var myChart = new Chart(
    document.getElementById('myChart1'),
    config
);

// load data tu database
$(document).ready(function () {
    updateChart();
});
setInterval(updateChart, 2000);

function updateChart() {
    // gui request xuong database de lay data
    $.post('readDataProfile.php', function (data) {
        var label = [];
        var humidity = [];
        var temperature = [];
        for (var i in data) {
            label.push(data[i].id);
            humidity.push(data[i].humidity);
            temperature.push(data[i].temperature);
        }
        // console.log(humidity);
        myChart.data.labels = label;
        myChart.data.datasets[0].data = humidity;
        myChart.data.datasets[1].data = temperature;
        myChart.update();


    })
}

const label1 = [];
const bpm = [];
const spo2 = [];

const chartdata1 = {
    labels: label1,
    datasets: [{
        label: 'bpm',
        backgroundColor: 'rgb(255, 99, 132)',
        borderColor: 'rgb(255, 99, 132)',
        data: bpm
    },
    {
        label: 'spo2',
        backgroundColor: 'rgb(99, 255, 132)',
        borderColor: 'rgb(99, 255, 132)',
        data: spo2
    },


    ]
};
const config1 = {
    type: 'bar',
    data: chartdata1,
    options: {
        scales: {
            y: {
                beginAtZero: true
            }
        }
    }
};
var myChart1 = new Chart(
    document.getElementById('mybar1'),
    config1
);

// load data tu database
$(document).ready(function () {
    updateChart1();
});
setInterval(updateChart1, 2000);

function updateChart1() {
    // gui request xuong database de lay data
    $.post('readDataProfile.php', function (data) {
        var label1 = [];
        var bpm = [];
        var spo2 = [];
        for (var i in data) {
            label1.push(data[i].id);
            bpm.push(data[i].bpm);
            spo2.push(data[i].spo2);
        }
        // console.log(humidity);
        myChart1.data.labels = label1;
        myChart1.data.datasets[0].data = bpm;
        myChart1.data.datasets[1].data = spo2;
        myChart1.update();


    })
}
