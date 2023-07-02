<?php
session_start();

$user_id = $_SESSION['userId'];
require 'configView.php';


$query1 = "SELECT bodyTemp FROM IOT_project WHERE user_id='$user_id' ORDER BY id DESC LIMIT 1";
$query_run1 = mysqli_query($conn1, $query1);

if ($query_run1) {
    // Check if any rows were returned
    if (mysqli_num_rows($query_run1) > 0) {
        // Fetch the body temperature from the first row
        $row = mysqli_fetch_assoc($query_run1);
        $bodyTemp =  rand(53, 120); //$row['bodyTemp'];

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
