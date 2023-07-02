<?php
$server1 = "192.168.1.214";
$user1 = "pi";
$pass1 = "27122001";
$dbname1 = "healthData";

$conn1 = mysqli_connect($server1, $user1, $pass1, $dbname1);

if ($conn1 === false) {
    die("ERROR: Could not connect. " . mysqli_connect_error());
}

$user_id = 46; // Replace with the actual user ID you want to retrieve the body temperature for

$query1 = "SELECT bodyTemp FROM IOT_project WHERE user_id='$user_id' ORDER BY id DESC LIMIT 1";
$query_run1 = mysqli_query($conn1, $query1);

if ($query_run1) {
    // Check if any rows were returned
    if (mysqli_num_rows($query_run1) > 0) {
        // Fetch the body temperature from the first row
        $row = mysqli_fetch_assoc($query_run1);
        $bodyTemp = $row['bodyTemp'];

        // Output the retrieved body temperature
        echo $bodyTemp;
    } else {
        echo "No data found for user ID: " . $user_id;
    }
} else {
    echo "Error in the query: " . mysqli_error($conn1);
}

// Close the database connection
mysqli_close($conn1);
?>
