<?php

$con = mysqli_connect("192.168.1.214", "pi", "27122001", "doctorapp");

if (!$con) {
    die('Connection Failed' . mysqli_connect_error());
}
