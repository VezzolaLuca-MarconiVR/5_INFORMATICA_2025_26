<?php
session_start();

// Clear and destroy session
$_SESSION = array();
session_destroy();
header("Location: ../login/login.php");
exit;
?>