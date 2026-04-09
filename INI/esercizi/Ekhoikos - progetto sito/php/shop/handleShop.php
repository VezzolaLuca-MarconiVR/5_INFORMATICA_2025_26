<?php
session_start();

require "../general/functions.php";
require "../general/connect.php";

$sql = "SELECT idProd, nome, descrizione, urlImmagine FROM Prodotti";
$result = $conn->query($sql);

$conn->close();

function displayProductsCards() {
  global $result;

  $prefix = "../../users_uploads/products/";
  $defaultImage = "../../img/default-product.png"; // percorso relativo dell'immagine di fallback

  if ($result->num_rows > 0) {
    while ($row = $result->fetch_assoc()) {

      // Se urlImmagine è vuoto o nullo, usa l'immagine di default
      if (!empty($row["urlImmagine"])) {
        $imagePath = $prefix . $row["urlImmagine"];
      } else {
        $imagePath = $defaultImage;
      }
      
      echo "<div class='product-card grainPaperTextureSmall'>
        <img class='product-image' 
             src='" . $imagePath . "' " .
             (empty($row["urlImmagine"]) ? "style='image-rendering: pixelated;'" : "") .
        " />
        <div class='product-text'>
          <h3 class='product-title'>" . $row["nome"] . "</h3>
          <span class='product-description'>" . $row["descrizione"] . "</span>
        </div>
      </div>";
    }
  } else {
    echo 'Nessun prodotto ancora in vendita.';
  }
}


?>