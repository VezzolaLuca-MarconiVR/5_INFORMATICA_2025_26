<?php
// Reference: https://www.w3schools.com/php/php_mysql_select.asp

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

$sql = "SELECT P.id_prodotto, P.nome  from Prodotti AS P JOIN Categorie AS C on P.id_categorie = C.id_categoria WHERE C.nome = 'Libri e Riviste'";
// Execute the SQL query
$result = $conn->query($sql);

// Output a title
echo "<h1>Query: SELECT P.id_prodotto, P.nome  from Prodotti AS P JOIN Categorie AS C on P.id_categorie = C.id_categoria WHERE C.nome = 'Libri e Riviste'</h1>";

// Process the result set
if ($result->num_rows > 0) {
  // Output data of each row
  while($row = $result->fetch_assoc()) {
    echo "<b>id:</b> " . $row["id_prodotto"].
    "; <b>nome:</b> " . $row["nome"].
    "<br>";
  }
} else {
  echo "0 results";
}

$conn->close();
?>