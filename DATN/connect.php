<?php
include 'xuly.php';

if ($row['username'] == $username && $row['password'] == $password && $row != NULL) {

    include 'index.php';
} else {
    echo "Failed to login";
}
