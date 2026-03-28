<?php
function test_input($data) {
  $data = trim($data);
  $data = stripslashes($data);
  $data = htmlspecialchars($data);
  return $data;
}

# Returns true if $_SESSION contains 'logged_in' set to true
function isLoggedIn() {
  return isset($_SESSION['logged_in']) && $_SESSION['logged_in'] === true;
}
?>