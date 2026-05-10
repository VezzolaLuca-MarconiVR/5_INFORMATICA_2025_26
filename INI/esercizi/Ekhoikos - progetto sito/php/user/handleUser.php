<?php
session_start();
require "../general/functions.php";

if (isLoggedIn()){
  require "../general/connect.php";

  $sql = "SELECT nomeUtente, nome, cognome, dNascita, email FROM Utenti WHERE nomeUtente = '" . $_SESSION['username'] . "'";
  $result = $conn->query($sql);

  if ($result->num_rows == 1 && $row = $result->fetch_assoc()) {
    $u_username = $row["nomeUtente"];
    $u_name = $row["nome"];
    $u_surname = $row["cognome"];
    $u_dateofbirth = $row["dNascita"];
    $u_email = $row["email"];
  }
}
?>