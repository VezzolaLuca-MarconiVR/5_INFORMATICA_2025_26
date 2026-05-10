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

$sql = "SELECT * from Clienti";
// Execute the SQL query
$result = $conn->query($sql);

// Output a title
echo "<h1>Query: SELECT * from Clienti</h1>";

// Process the result set
if ($result->num_rows > 0) {
  // Output data of each row
  while($row = $result->fetch_assoc()) {
    echo "<b>id:</b> " . $row["id_cliente"].
    "; <b>nome:</b> " . $row["nome"].
    "; <b>indirizzo:</b> " . $row["indirizzo"].
    "; <b>città:</b> " . $row["citta"].
    "; <b>nazione:</b> " . $row["nazione"].
    "<br>";
  }
} else {
  echo "0 results";
}

$conn->close();
?>