<?php
  // Inizializzazione delle variabili descrittive della connessione con il DB
  $servername = "localhost";
  $username = "root";
  $password = "";
  $dbname = "ekhoikos";

  // Create connection
  $conn = new mysqli($servername, $username, $password, $dbname);
  // Check connection
  if ($conn->connect_error) {
      die("Connection to DB failed: " . $conn->connect_error);
  }
?>