<?php
  // Get data from GET request
  $prodId = htmlspecialchars($_GET["idProd"]);

  // Connect to DB to fetch data
  require "../general/connect.php";

  // Fetch product data
  $sql = "SELECT * FROM Prodotti WHERE idProd=?";

  if($stmt = $conn->prepare($sql)) {
    // Bind parameters
    $stmt->bind_param("s", $prodId);
    $stmt->fetch();
  }

  $conn->close();
?>