<?php



$username = $_POST['username'];
$password = $_POST['password'];



$sql = "select * from member where username='$username'";


$conn = mysqli_connect("192.168.203.44", "pi", "27122001", "dataDoctor");
$username = stripcslashes($username);
$password = stripcslashes($password);
$username = mysqli_real_escape_string($conn, $username);
$password = mysqli_real_escape_string($conn, $password);

if (mysqli_connect_errno()) {
    echo "Failed to connect to MySQL: " . mysqli_connect_error();
    exit();
}



//query username

$result = mysqli_query($conn, $sql) or die("Failed to query database");
$row = mysqli_fetch_array($result);

if ($row['username'] == $username && $row['password'] == $password && $row != NULL) {
    //tiến hành lưu tên đăng nhập vào session để tiện xử lý sau này
    // Thực thi hành động sau khi lưu thông tin vào session
    // ở đây mình tiến hành chuyển hướng trang web tới một trang gọi là index.php
    header('Location: index.php');
} else {
    echo '<script language="javascript">alert("username and password are incorrect"); window.location="login.php";</script>';
}
