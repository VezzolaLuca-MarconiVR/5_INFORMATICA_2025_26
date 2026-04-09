<?php
require "../general/functions.php";

session_start();

$loginError = "";

# =============== AUTHENTICATION HANDLER ===============
if($_SERVER['REQUEST_METHOD'] === 'POST') {
  $loginUsername = test_input($_POST['username']);
  $plainTextPassword = $_POST['password'];

  
  // Connect to DB
  require "../general/connect.php";
  
  // Use direct query with proper escaping
  $escapedUsername = $conn->real_escape_string($loginUsername);
  $sql = "SELECT psw FROM Utenti WHERE nomeUtente = '" . $escapedUsername . "'";
  
  $result = $conn->query($sql);
  
  if (!$result) {
    $loginError = "Credenziali non valide!";
  } else {
    $userQuery = $result->fetch_assoc();
    
    if ($userQuery === null) {
      $loginError = "Credenziali non valide!";
    } else {
      // Check password
      if (password_verify($plainTextPassword, $userQuery['psw'])) {
        // Correct password -> start session
        $_SESSION['username'] = $loginUsername;
        $_SESSION['logged_in'] = true;
        header("Location: ../index/index.php");
        exit;
      } else {
        $loginError = "Credenziali non valide!";
      }
    }
  }
  
  $conn->close();
}
?>