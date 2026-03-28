<?php
# =============== AUTHENTICATION HANDLER ===============
if($_REQUEST == 'POST') {
  $passwordInChiaro = $_POST['password'];
  $nomeUtente       = $_POST['nomeUtente'];
  
  // Recuperi l'hash salvato nel DB
  $stmt = $pdo->prepare("SELECT psw FROM Utenti WHERE nomeUtente = ?");
  $stmt->execute([$nomeUtente]);
  $utente = $stmt->fetch();
  
  if ($utente && password_verify($passwordInChiaro, $utente['psw'])) {
    // Password corretta -> avvia la sessione
    session_start();
    $_SESSION['username'] = $_POST['username'];
    $_SESSION['logged_in'] = true;
    header("Location: ../index/index.php");
    exit;
  } else {
    // Credenziali errate
    // Non specificare MAI se è sbagliato utente o password
    echo "<p class='error'>Credenziali non valide!</p>";
  }
}
?>