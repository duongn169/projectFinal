<?php

if (isset($_GET['id'])) {
    $id = $_GET['id'];
    $servername = 'localhost';
    $username = "root";
    $password = "";
    $database = "doctorapp";

    $connection = new mysqli($servername, $username, $password, $database);
    $sql = "DELETE  FROM employees WHERE id= $id";
    $connection->query($sql);
}
header('location:patients.php');
exit;
