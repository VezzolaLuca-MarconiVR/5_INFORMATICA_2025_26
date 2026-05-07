<?php require "./handleUser.php";?>

<!DOCTYPE html>
<html lang="it">
  <head>
    <meta charset="UTF-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <title>Ekhoikos - TEMPLATE</title>
    <link rel="stylesheet" href="../../css/general.css" />
    <link rel="stylesheet" href="../../css/THIS_PAGE_CSS" />
    <script src="../../js/index.js" defer></script>
  </head>

  <body>
    <!-- Navbar -->
    <nav>
      <ul>
        <li><a href="../index/index.php">Home</a></li>
        <li><a href="../shop/shop.php">Shop</a></li>
        <li><a href="../chat/chat.php">Chat</a></li>
        <?php
        if (isLoggedIn()) {
          echo "<li style='float: right'>
                  <a href='../general/logout.php'>Logout</a>
                </li>
                <li style='float: right'>
                  <a href='../user/user.php' class='active'>User: " . $_SESSION['username'] . "</a>
                </li>";
        } else {
          echo "<li style='float: right'>
                  <a href='../login/login.php'>Login</a>
                </li>";
        }
        ?>
      </ul>
    </nav>

    <main>
      <!-- MAIN CONTENT-->
      <div id="userDataContainer">
        <p>Nome utente:</p>
        <p><?php $u_username?></p>

        <p>Nome:</p>
        <p><?php $u_name?></p>

        <p>Cognome:</p>
        <p><?php $u_surname?></p>

        <p>Data di nascita:</p>
        <p><?php $u_dateofbirth?></p>

        <p>Email:</p>
        <p><?php $u_email?></p>
      </div>
    </main>

    <footer>
      <p>Grazie per aver scelto Ekhoikos!</p>

      <p>
        Tel: <phone class="selectable-content">+39 3370071503</phone> email:
        <email class="selectable-content">help@ekhoikos.com</email>
      </p>
    </footer>
  </body>
</html>