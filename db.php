<?php
$servername = "localhost";
$username = "root";
$password = "";
$dbname = "motion_db";
$conn = new mysqli($servername, $username, $password, $dbname);
if($conn){
    //echo "Connected successfully";
}
else{
    echo "Connection failed: " . $conn->connect_error;
}
?>