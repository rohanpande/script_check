<?php

require_once("Mqtt.php");

$server = "broker.mqtt-dashboard.com";     // change if necessary
$port = 1883;                     // change if necessary
$username = "";                   // set your username
$password = "";                   // set your password
$client_id = "rohan-check"; // make sure this is unique for connecting to sever - you could use uniqid()

$mqtt = new Bluerhinos\Mqtt($server, $port, $client_id);

if ($mqtt->connect(true, null, $username, $password)) {
    $mqtt->publish("esp-test-check", 5, 0);
    $mqtt->close();
} else {
    echo "Time out!\n";
}
