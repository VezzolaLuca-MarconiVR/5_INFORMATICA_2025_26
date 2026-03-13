<?php
  // Inizializzazione delle variabili descrittive della connessione con il DB
  $servername = "localhost";
  $username = "root";
  $password = "";
  $dbname = "negozio";

  // Create connection
  $conn = new mysqli($servername, $username, $password, $dbname);
  // Check connection
  if ($conn->connect_error) {
      die("Connection failed: " . $conn->connect_error);
  }

  $sql = "INSERT INTO Clienti (nome, indirizzo, citta, nazione)
  VALUES ('$unameAndSurname', '$uaddress', '$ucity', '$unation')";

  if ($conn->query($sql) === TRUE) {
    echo "<span class='success'>New client added successfully!</span>";
  } else {
  echo "Error: " . $sql . "<br>" . $conn->eror;
  }

  $conn->close();
?>