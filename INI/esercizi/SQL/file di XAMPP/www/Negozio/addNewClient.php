<?php
require 'functions';

// Inizializzazione delle variabili descrittive della connessione con il DB
$servername = "localhost";
$username = "root";
$password = "";
$dbname = "negozio";

// Variabili superglobali ottenute dal form in post html
$unameAndSurname = $_POST['name&surname'];
$uaddress = $_POST['address'];
$ucity = $_POST['city'];
$unation = $_POST['nation'];

// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);
// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

$sql = "INSERT INTO Clienti (nome, indirizzo, citta, nazione)
VALUES ('$unameAndSurname', '$uaddress', '$ucity', '$unation')";

if ($conn->query($sql) === TRUE) {
echo "New record created successfully";
} else {
echo "Error: " . $sql . "<br>" . $conn->eror;
}

$conn->close()

?>