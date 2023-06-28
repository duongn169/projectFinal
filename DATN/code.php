<?php
session_start();
require 'dbconnectView.php';

if (isset($_POST['delete_user'])) {
    $user_id = mysqli_real_escape_string($con, $_POST['delete_user']);

    $query = "DELETE FROM patients WHERE id='$user_id' ";
    $query_run = mysqli_query($con, $query);

    if ($query_run) {
        $_SESSION['message'] = "Patient Deleted Successfully";
        header("Location: patients.php");
        exit(0);
    } else {
        $_SESSION['message'] = "Patient Not Deleted";
        header("Location: patients.php");
        exit(0);
    }
}

if (isset($_POST['update_user'])) {
    $user_id = mysqli_real_escape_string($con, $_POST['user_id']);

    $name = mysqli_real_escape_string($con, $_POST['name']);

    $age = mysqli_real_escape_string($con, $_POST['age']);
    $gender = mysqli_real_escape_string($con, $_POST['gender']);

    $email = mysqli_real_escape_string($con, $_POST['email']);
    $phone = mysqli_real_escape_string($con, $_POST['phone']);
    $address = mysqli_real_escape_string($con, $_POST['address']);

    $query = "UPDATE patients SET name='$name', age='$age',gender='$gender',email='$email', phone='$phone', address='$address' WHERE id='$user_id' ";
    $query_run = mysqli_query($con, $query);

    if ($query_run) {
        $_SESSION['message'] = "Patient Updated Successfully";
        header("Location: patients.php");
        exit(0);
    } else {
        $_SESSION['message'] = "Patient Not Updated";
        header("Location: patients.php");
        exit(0);
    }
}
