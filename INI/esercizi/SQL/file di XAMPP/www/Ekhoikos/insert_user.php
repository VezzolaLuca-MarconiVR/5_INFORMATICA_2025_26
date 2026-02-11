<?php
// Dati fondamentali per la connessione al server DB
$servername = "localhost"; // localhost per usare un server DB locale
$username = "root"; // root because this is the "master user"
$password = ""; // for now, no password is needed
$dbname = "ekhoikos";

// Variabili superglobali ottenute dal form in post html
$uname=$_POST['uname']; // deve essere uguale all'attributo 'name' dell'elemento HTML input
$usurname=$_POST['usurname'];
$uemail=$_POST['uemail'];

// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);
//Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

$sql = "INSERT INTO Users (name, surname, email)
VALUES ('$uname', '$usurname', '$uemail')";

if ($conn->query($sql) === TRUE) {
echo "New record created successfully";
} else {
echo "Error: " . $sql . "<br>" . $conn->eror;
}

$conn->close();

?> 