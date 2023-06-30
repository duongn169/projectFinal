// $(document).ready(function() {


// 	// Bar Chart

// 	var barChartData = {
// 		labels: ['Jan', 'Feb', 'Mar', 'Apr', 'May', 'Jun'],
// 		datasets: [{
// 			label: 'Dataset 1',
// 			backgroundColor: 'rgba(0, 158, 251, 0.5)',
// 			borderColor: 'rgba(0, 158, 251, 1)',
// 			borderWidth: 1,
// 			data: [35, 59, 80, 81, 56, 55, 40]
// 		}, {
// 			label: 'Dataset 2',
// 			backgroundColor: 'rgba(255, 188, 53, 0.5)',
// 			borderColor: 'rgba(255, 188, 53, 1)',
// 			borderWidth: 1,
// 			data: [28, 48, 40, 19, 86, 27, 90]
// 		}]
// 	};

// 	var ctx = document.getElementById('bargraph').getContext('2d');
// 	window.myBar = new Chart(ctx, {
// 		type: 'bar',
// 		data: barChartData,
// 		options: {
// 			responsive: true,
// 			legend: {
// 				display: false,
// 			}
// 		}
// 	});

// 	// Line Chart

// 	var lineChartData = {
// 		labels: ["Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"],
// 		datasets: [{
// 			label: "My First dataset",
// 			backgroundColor: "rgba(0, 158, 251, 0.5)",
// 			data: [100, 70, 20, 100, 120, 50, 70, 50, 50, 100, 50, 90]
// 		}, {
// 		label: "My Second dataset",
// 		backgroundColor: "rgba(255, 188, 53, 0.5)",
// 		fill: true,
// 		data: [28, 48, 40, 19, 86, 27, 20, 90, 50, 20, 90, 20]
// 		}]
// 	};

// 	var linectx = document.getElementById('linegraph').getContext('2d');
// 	window.myLine = new Chart(linectx, {
// 		type: 'line',
// 		data: lineChartData,
// 		options: {
// 			responsive: true,
// 			legend: {
// 				display: false,
// 			},
// 			tooltips: {
// 				mode: 'index',
// 				intersect: false,
// 			}
// 		}
// 	});

// 	// Bar Chart 2

//     barChart();

//     $(window).resize(function(){
//         barChart();
//     });

//     function barChart(){
//         $('.bar-chart').find('.item-progress').each(function(){
//             var itemProgress = $(this),
//             itemProgressWidth = $(this).parent().width() * ($(this).data('percent') / 100);
//             itemProgress.css('width', itemProgressWidth);
//         });
//     };
// });

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
	document.getElementById('myChart'),
	config
);

// load data tu database
$(document).ready(function () {
	updateChart();
});
setInterval(updateChart, 2000);

function updateChart() {
	// gui request xuong database de lay data
	$.post('readData.php', function (data) {
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
		data: bpm,
		fill: false,
    
	},
	{
		label: 'spo2',
		backgroundColor: 'rgb(99, 255, 132)',
		borderColor: 'rgb(99, 255, 132)',
		data: spo2,
		fill: false,
    
	},


	]
};
const config1 = {
	type: 'line',
	data: chartdata1,
	
};
var myChart1 = new Chart(
	document.getElementById('mybar'),
	config1
);

// load data tu database
$(document).ready(function () {
	updateChart1();
});
setInterval(updateChart1, 2000);

function updateChart1() {
	// gui request xuong database de lay data
	$.post('readData.php', function (data) {
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
