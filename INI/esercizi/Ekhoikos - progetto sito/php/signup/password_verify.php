<?php
$passwordInChiaro = $_POST['password'];
$nomeUtente       = $_POST['nomeUtente'];

// Recuperi l'hash salvato nel DB
$stmt = $pdo->prepare("SELECT psw FROM Utenti WHERE nomeUtente = ?");
$stmt->execute([$nomeUtente]);
$utente = $stmt->fetch();

if ($utente && password_verify($passwordInChiaro, $utente['psw'])) {
    // ✅ Password corretta → avvia la sessione
    session_start();
    $_SESSION['utenteLoggato'] = $nomeUtente;
    header("Location: dashboard.php");
} else {
    // ❌ Credenziali errate
    // Non specificare MAI se è sbagliato utente o password
    echo "Credenziali non valide.";
}