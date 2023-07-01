<?php
// Connect to database
$server = "192.168.203.44";
$user = "pi";
$pass = "27122001";
$dbname = "healthData";

$conn = mysqli_connect($server, $user, $pass, $dbname);

// Check connection
if ($conn === false) {
    die("ERROR: Could not connect. " . mysqli_connect_error());
}
