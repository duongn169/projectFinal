<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <title>Chart</title>
    <link rel="stylesheet" href="https://cdn.jsdelivr.net/npm/bootstrap@5.0.0-beta3/dist/css/bootstrap.min.css">
    <style>
        body {
            font: 14px sans-serif;
        }

        .wrapper {
            float: left;
            width: 80%;
            padding: 20px;
            margin: 20px;
        }

        .box {
            margin: auto;
            width: 90%;
        }
    </style>
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.5.1/jquery.min.js"></script>
    <script src="https://cdnjs.cloudflare.com/ajax/libs/Chart.js/3.2.0/chart.min.js"> </script>
</head>

<body>


</body>


<body>
    <div class="wrapper border border-3 rounded border-primary">
        <canvas id="myChart"></canvas>
    </div>
    <script>
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
    </script>


</body>

</html>