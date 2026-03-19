<?php
// La password arriva dal form in chiaro
$passwordInChiaro = $_POST['password'];

// PHP genera automaticamente un hash bcrypt sicuro
// (salt casuale incluso, non devi gestirlo tu)
$passwordHash = password_hash($passwordInChiaro, PASSWORD_BCRYPT);

// Salvi $passwordHash nel database (colonna psw varchar(255))
$stmt = $pdo->prepare("INSERT INTO Utenti (nomeUtente, psw, ...) VALUES (?, ?, ...)");
$stmt->execute([$nomeUtente, $passwordHash, ...]);