<?php
@ob_start();
session_start();


require 'dbconnectView.php';






?>
<!DOCTYPE html>
<html lang="en">


<head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0, user-scalable=0">
    <link rel="shortcut icon" type="image/x-icon" href="assets/img/favicon.ico">
    <title>Profile Patient </title>
    <link rel="stylesheet" type="text/css" href="assets/css/bootstrap.min.css">
    <link rel="stylesheet" type="text/css" href="assets/css/font-awesome.min.css">
    <link rel="stylesheet" type="text/css" href="assets/css/style.css">
    <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/6.0.0/css/all.min.css"
        integrity="sha512-9usAa10IRO0HhonpyAIVpjrylPvoDwiPUiKdWk5t3PyolY1cOd4DSE0Ga+ri4AuTroPR5aQvXU9xC6qOPnzFeg=="
        crossorigin="anonymous" referrerpolicy="no-referrer" />
    <style>
    i.fa.fa-thermometer-half.temp {
        font-size: 40px;
        color: green;

    }

    i.fa.fa-solid.fa-weight-scale.bmi {
        font-size: 40px;
        color: blue;

    }

    i.fa.fa-heartbeat.heart {
        font-size: 40px;
        color: red;
    }

    i.fas.fa-walking.walk {
        font-size: 40px;

    }
    </style>

</head>

<body>
    <div class="main-wrapper">
        <div class="header">
            <div class="header-left">
                <a href="index.php" class="logo">
                    <img src="assets/img/logo.png" width="35" height="35" alt=""> <span>Preclinic</span>
                </a>
            </div>
            <a id="toggle_btn" href="javascript:void(0);"><i class="fa fa-bars"></i></a>
            <a id="mobile_btn" class="mobile_btn float-left" href="#sidebar"><i class="fa fa-bars"></i></a>
            <ul class="nav user-menu float-right">
                <li class="nav-item dropdown d-none d-sm-block">
                    <a href="#" class="dropdown-toggle nav-link" data-toggle="dropdown"><i class="fa fa-bell-o"></i>
                        <span class="badge badge-pill bg-danger float-right">3</span></a>
                    <div class="dropdown-menu notifications">
                        <div class="topnav-dropdown-header">
                            <span>Notifications</span>
                        </div>
                        <div class="drop-scroll">
                            <ul class="notification-list">
                                <li class="notification-message">
                                    <a href="activities.php">
                                        <div class="media">
                                            <span class="avatar">
                                                <img alt="John Doe" src="assets/img/user.jpg" class="img-fluid">
                                            </span>
                                            <div class="media-body">
                                                <p class="noti-details"><span class="noti-title">John Doe</span> added
                                                    new task <span class="noti-title">Patient appointment booking</span>
                                                </p>
                                                <p class="noti-time"><span class="notification-time">4 mins ago</span>
                                                </p>
                                            </div>
                                        </div>
                                    </a>
                                </li>
                                <li class="notification-message">
                                    <a href="activities.php">
                                        <div class="media">
                                            <span class="avatar">V</span>
                                            <div class="media-body">
                                                <p class="noti-details"><span class="noti-title">Tarah Shropshire</span>
                                                    changed the task name <span class="noti-title">Appointment booking
                                                        with payment gateway</span></p>
                                                <p class="noti-time"><span class="notification-time">6 mins ago</span>
                                                </p>
                                            </div>
                                        </div>
                                    </a>
                                </li>
                                <li class="notification-message">
                                    <a href="activities.html">
                                        <div class="media">
                                            <span class="avatar">L</span>
                                            <div class="media-body">
                                                <p class="noti-details"><span class="noti-title">Misty Tison</span>
                                                    added <span class="noti-title">Domenic Houston</span> and <span
                                                        class="noti-title">Claire Mapes</span> to project <span
                                                        class="noti-title">Doctor available module</span></p>
                                                <p class="noti-time"><span class="notification-time">8 mins ago</span>
                                                </p>
                                            </div>
                                        </div>
                                    </a>
                                </li>
                                <li class="notification-message">
                                    <a href="activities.html">
                                        <div class="media">
                                            <span class="avatar">G</span>
                                            <div class="media-body">
                                                <p class="noti-details"><span class="noti-title">Rolland Webber</span>
                                                    completed task <span class="noti-title">Patient and Doctor video
                                                        conferencing</span></p>
                                                <p class="noti-time"><span class="notification-time">12 mins ago</span>
                                                </p>
                                            </div>
                                        </div>
                                    </a>
                                </li>
                                <li class="notification-message">
                                    <a href="activities.html">
                                        <div class="media">
                                            <span class="avatar">V</span>
                                            <div class="media-body">
                                                <p class="noti-details"><span class="noti-title">Bernardo Galaviz</span>
                                                    added new task <span class="noti-title">Private chat module</span>
                                                </p>
                                                <p class="noti-time"><span class="notification-time">2 days ago</span>
                                                </p>
                                            </div>
                                        </div>
                                    </a>
                                </li>
                            </ul>
                        </div>
                        <div class="topnav-dropdown-footer">
                            <a href="activities.html">View all Notifications</a>
                        </div>
                    </div>
                </li>
                <li class="nav-item dropdown d-none d-sm-block">
                    <a href="javascript:void(0);" id="open_msg_box" class="hasnotifications nav-link"><i
                            class="fa fa-comment-o"></i> <span
                            class="badge badge-pill bg-danger float-right">8</span></a>
                </li>
                <li class="nav-item dropdown has-arrow">
                    <a href="#" class="dropdown-toggle nav-link user-link" data-toggle="dropdown">
                        <span class="user-img"><img class="rounded-circle" src="assets/img/user.jpg" width="40"
                                alt="Admin">
                            <span class="status online"></span></span>
                        <span>Admin</span>
                    </a>
                    <div class="dropdown-menu">

                        <a class="dropdown-item" href="login.php">Logout</a>
                    </div>
                </li>
            </ul>
            <div class="dropdown mobile-user-menu float-right">
                <a href="#" class="nav-link dropdown-toggle" data-toggle="dropdown" aria-expanded="false"><i
                        class="fa fa-ellipsis-v"></i></a>
                <div class="dropdown-menu dropdown-menu-right">

                    <a class="dropdown-item" href="login.php">Logout</a>
                </div>
            </div>
        </div>
        <div class="sidebar" id="sidebar">
            <div class="sidebar-inner slimscroll">
                <div id="sidebar-menu" class="sidebar-menu">
                    <ul>
                        <li class="menu-title">Main</li>
                        <li>
                            <a href="index.php"><i class="fa fa-dashboard"></i> <span>Dashboard</span></a>
                        </li>

                        <li>
                            <a href="patients.php"><i class="fa fa-wheelchair"></i> <span>Patients</span></a>
                        </li>

                        <li class="submenu">
                            <a href="#"><i class="fa fa-columns"></i> <span>Account</span> <span
                                    class="menu-arrow"></span></a>
                            <ul style="display: none;">
                                <li><a href="login.php"> Login </a></li>
                                <li><a href="register.php"> Register </a></li>
                                <li><a href="forgot-password.php"> Forgot Password </a></li>
                                <li><a href="change-password2.php"> Change Password </a></li>

                            </ul>
                        </li>

                    </ul>
                </div>
            </div>
        </div>
        <div class="page-wrapper">
            <div class="content">
                <div class="row">
                    <div class="col-sm-7 col-6">
                        <h4 class="page-title">My Profile</h4>
                    </div>


                </div>
                <div class="card-box profile-header">
                    <div class="row">
                        <div class="col-md-12">
                            <div class="profile-view">
                                <div class="profile-img-wrap">
                                    <div class="profile-img">
                                        <a href="#"><img class="avatar" src="assets/img/male.jpg" alt=""></a>
                                    </div>
                                </div>
                                <div class="profile-basic">
                                    <div class="row">
                                        <?php
                                        if (isset($_GET['id'])) {

                                            $user_id = mysqli_real_escape_string($con, $_GET['id']);
                                            $query = "SELECT * FROM patients WHERE id='$user_id' ";
                                            $query_run = mysqli_query($con, $query);

                                            if (mysqli_num_rows($query_run) > 0) {
                                                $user = mysqli_fetch_array($query_run);

                                        ?>
                                        <div class="col-md-5">
                                            <div class="profile-info-left">
                                                <h3 class="user-name m-t-0 mb-0">
                                                    <b>
                                                        <p class="form-control">
                                                            <?= $user['name']; ?>
                                                        </p>
                                                    </b>
                                                </h3>

                                                <h3 class="user-name m-t-0 mb-0">
                                                    <b>
                                                        <p class="form-control">
                                                            <?= $user['age']; ?>
                                                        </p>
                                                    </b>
                                                </h3>
                                                <h3 class="user-name m-t-0 mb-0">
                                                    <b>
                                                        <p class="form-control">
                                                            <?= $user['gender']; ?>
                                                        </p>
                                                    </b>
                                                </h3>


                                            </div>
                                        </div>
                                        <div class="col-md-7">
                                            <ul class="personal-info">
                                                <li>
                                                    <span class="title">Phone:</span>
                                                    <p class="form-control">
                                                        <?= $user['phone'];
                                                                $GLOBALS['phoneNum'] = $user['phone']; ?>
                                                    </p>
                                                </li>
                                                <li>
                                                    <span class="title">Email:</span>
                                                    <p class="form-control">
                                                        <?= $user['email']; ?>
                                                    </p>
                                                </li>

                                                <li>
                                                    <span class="title">Address:</span>
                                                    <p class="form-control">
                                                        <?= $user['address']; ?>
                                                    </p>
                                                </li>

                                            </ul>
                                        </div>
                                        <?php
                                            } else {
                                                echo "<h4>No Such Id Found</h4>";
                                            }
                                        }
                                        ?>

                                    </div>
                                </div>
                            </div>
                        </div>
                    </div>
                </div>
                <table class="table table-hover">
                    <thead>
                        <tr>
                            <th scope="col"><i class='fa fa-heartbeat heart'></i> Heartbeat</th>
                            <th scope="col"><i class='fa fa-solid fa-weight-scale bmi'></i>BMI</th>
                            <th scope="col"><i class="fa fa-thermometer-half temp" aria-hidden="true"></i>Temperature
                            </th>
                            <th scope="col"><i class='fas fa-walking walk'></i>Activities Status</th>

                        </tr>
                    </thead>
                    <tbody>
                        <tr>

                            <td>60</td>
                            +                            <!-- data for bmi -->
                            <td>
                            <?php
                                $server1 = "192.168.1.214";
                                $user1 = "pi";
                                $pass1 = "27122001";
                                $dbname1 = "doctorapp";

                                $conn1 = mysqli_connect($server1, $user1, $pass1, $dbname1);

                                // Check connection
                                if ($conn1 === false) {
                                    die("ERROR: Could not connect. " . mysqli_connect_error());
                                }

                                $user_id = 46; // Replace with the actual user ID you want to retrieve height and weight for

                                $query1 = "SELECT height, weight FROM patients WHERE id='$user_id'";
                                $query_run1 = mysqli_query($conn1, $query1);

                                if ($query_run1) {
                                    // Check if any rows were returned
                                    if (mysqli_num_rows($query_run1) > 0) {
                                        // Fetch the height and weight from the first row
                                        $row = mysqli_fetch_assoc($query_run1);
                                        $height = $row['height'];
                                        $weight = $row['weight'];

                                        // Calculate BMI
                                        $height_in_meters = $height / 100; // Convert height to meters
                                        $bmi = $weight / ($height_in_meters * $height_in_meters);
                                        $bmi = number_format($bmi, 2);

                                        // Output the retrieved height and weight
                                        echo "Height: " . $height . "<br>";
                                        echo "Weight: " . $weight . "<br>";
                                        echo "BMI: " . $bmi;
                                    } else {
                                        echo "No data found for user ID: " . $user_id;
                                    }
                                } else {
                                    echo "Error in the query: " . mysqli_error($conn1);
                                }

                                // Close the database connection
                                mysqli_close($conn1);
                                ?>

                                
                            </td>
                            <td>
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
                                        
                            </td>                


                        </tr>
                </table>
                <div class="profile-tabs">
                    <ul class="nav nav-tabs nav-tabs-bottom">
                        <li class="nav-item"><a class="nav-link active">Chart</a> </li>
                    </ul>
                </div>


                <div>
                    <div class="row">
                        <div class="col-12 col-md-6 col-lg-6 col-xl-6">
                            <div class="card">
                                <div class="card-body">
                                    <div class="chart-title">
                                        <h4>Humidity and Temperature</h4>
                                    </div>
                                    <canvas id="myChart1"></canvas>
                                </div>
                            </div>
                        </div>
                        <div class="col-12 col-md-6 col-lg-6 col-xl-6">
                            <div class="card">
                                <div class="card-body">
                                    <div class="chart-title">
                                        <h4>Patients In</h4>
                                        <div class="float-right">
                                            <ul class="chat-user-total">
                                                <li><i class="fa fa-circle current-users" aria-hidden="true"></i>ICU
                                                </li>
                                                <li><i class="fa fa-circle old-users" aria-hidden="true"></i> OPD</li>
                                            </ul>
                                        </div>
                                    </div>
                                    <canvas id="mybar1"></canvas>
                                </div>
                            </div>
                        </div>
                    </div>
                </div>


            </div>
            <div class="sidebar-overlay" data-reff=""></div>
            <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.5.1/jquery.min.js"></script>
            <script src="https://cdnjs.cloudflare.com/ajax/libs/Chart.js/3.2.0/chart.min.js"> </script>
            <script src="assets/js/jquery-3.2.1.min.js"></script>
            <script src="assets/js/popper.min.js"></script>
            <script src="assets/js/bootstrap.min.js"></script>
            <script src="assets/js/jquery.slimscroll.js"></script>
            <script src="assets/js/app.js"></script>
            <script src="assets/js/chartProfile.js"></script>



</body>


<!-- profile23:03-->

<?php

$user_id;
$user_id = $_GET['id'];
echo $user_id;

$_SESSION['userId'] = $user_id;

?>



</html>