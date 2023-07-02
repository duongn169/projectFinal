<?php 
 $server1 = "192.168.1.214";
 $user1 = "pi";
 $pass1 = "27122001";
 $dbname1 = "healthData";
 
 $conn1 = mysqli_connect($server1, $user1, $pass1, $dbname1);
 
 // Check connection
 if ($conn1 === false) {
     die("ERROR: Could not connect. " . mysqli_connect_error());
 }
