var label = [];
var humidity = [];
var temperature = [];

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
    document.getElementById('myChart'),
    config
);

// load data tu database
$(document).ready(function() {
    updateChart();
});
setInterval(updateChart, 2000);

function updateChart() {
    // gui request xuong database de lay data
    $.post('readData.php', function(data) {
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