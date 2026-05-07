<?php
  // Inizializzazione delle variabili descrittive della connessione con il DB
  $dbServername = "localhost";
  $dbUsername = "root";
  $dbPassword = "";
  $dbname = "ekhoikos";

  // Create connection
  $conn = new mysqli($dbServername, $dbUsername, $dbPassword, $dbname);
  // Check connection
  if ($conn->connect_error) {
      die("Connection to DB failed: " . $conn->connect_error);
  }
?>