<?php

$con = mysqli_connect("localhost","root","","doctorapp");

if(!$con){
    die('Connection Failed'. mysqli_connect_error());
}
