<?php
  session_start();
  
  // Connect to DB to fetch data
  require "../general/connect.php";

  // Fetch products data
  $sql = "SELECT idProd, nome, descrizione FROM Prodotti";
  $result = $conn->query($sql);
  // The output is inside the html
?>