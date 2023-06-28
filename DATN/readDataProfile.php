<?php
header('Content-Type: application/json');

// dang nhap vao database
include("configProfile.php");




// Doc gia tri tu database
$sql = "select * from IOT_project where  id>(select max(id) from IOT_project)-5";
$result = mysqli_query($conn, $sql);

$data = array();
foreach ($result as $row) {
    $data[] = $row;
}



mysqli_close($conn);
echo json_encode($data);
