<?php
// Esegui questo script UNA volta per ottenere gli hash reali da inserire nel DB
$utenti = ['anna_terra', 'chiara_vento', 'fabio_pietra', 'luca_fiume', 'riccardo_mare'];
$password = 'Test1234!'; // password di test uguale per tutti

foreach ($utenti as $u) {
    $hash = password_hash($password, PASSWORD_BCRYPT, ['cost' => 12]);
    echo "'$u' → $hash<br>";
}