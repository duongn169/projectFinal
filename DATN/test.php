<!DOCTYPE html>
<html>
<head>
    <title>Auto-Update Body Temperature</title>
    <script src="https://code.jquery.com/jquery-3.6.0.min.js"></script>
</head>
<body>
    <h1>Body Temperature: <span id="bodyTemp"></span></h1>

    <script>
        function updateBodyTemperature() {
            $.ajax({
                url: 'get_body_temperature.php',
                method: 'GET',
                dataType: 'text',
                success: function (response) {
                    $('#bodyTemp').text(response);
                },
                error: function (xhr, status, error) {
                    console.log('Error:', error);
                }
            });
        }

        // Call the updateBodyTemperature function initially
        updateBodyTemperature();

        // Call the updateBodyTemperature function every 1 second
        setInterval(updateBodyTemperature, 1000);
    </script>
</body>
</html>
