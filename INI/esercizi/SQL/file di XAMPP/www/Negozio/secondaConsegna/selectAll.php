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

// Process the result set
if ($result->num-rows > 0) {
  // Output data of each row
  while($row = $result->fetch_assoc()) {
    echo "id_cliente:" . $row["id"].  "nome:" . $row["name"]. "indirizzo:" . $row["address"]. "città:" . $row["city"]. "nazione:" . $row["nation"]. "<br>";
  }
} else {
  echo "0 results";
}

$conn->close();
?>