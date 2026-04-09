<?php
require "../general/functions.php";
require "../general/connect.php";

$sql = "SELECT idProd, nome, descrizione FROM Prodotti";
$result = $conn->query($sql);

$conn->close();

function displayProductsCards() {
  global $result;
  if($result->num_rows > 0) {
    while($row = $result->fetch_assoc()) {
      echo "<div class='product-card grainPaperTextureSmall'>
                  <img class='product-image' src='../../img/mountains-landscape.jpg' />
                  <div class='product-text'>
                    <h3 class='product-title'>" . $row["nome"] . "</h3>
                    <span class='product-description'>" . $row["descrizione"] . "</span>
                  </div>
                </div>";
    }
  } else {
    echo "Nessun prodotto ancora in vendita.";
  }
}
?>