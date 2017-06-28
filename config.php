<?php
ob_start(); //Turns on output buffering
session_start();

$timezone = date_default_timezone_set("Asia/Kolkata");
 $con = mysqli_connect("localhost","root","14051995","pagerank");  //connection variable

 if(mysqli_connect_errno())
 {
 	echo "Failed to connect ".mysqli_connect_errno();
 }

 
 ?>