<?php require "handleSignup.php";?>

<!DOCTYPE html>
<html lang="it">
  <head>
    <meta charset="UTF-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <title>Ekhoikos - Signup</title>
    <link rel="stylesheet" href="../../css/general.css" />
    <link rel="stylesheet" href="../../css/login-signup.css" />
    <script src="../../js/index.js" defer></script>
  </head>

  <body>
    <!-- Navbar -->
    <nav>
      <ul>
        <li><a href="../index/index.php">Home</a></li>
        <li><a href="../shop/shop.php">Shop</a></li>
        <li><a href="../chat/chat.php">Chat</a></li>
        <li style="float: right">
          <?php
          if (isLoggedIn()) {
            echo "<a href='../user/user.php'>User: " . $_SESSION['username'] . "</a>";;
          } else {
            echo "<a href='../login/login.php'>Login</a>";
          }
          ?>
        </li>
      </ul>
    </nav>

    <!-- Form Container -->
    <main>
      <div class="center-both full-height">
        <!-- Form -->
        <form style="margin: 20px;" method="POST" action="<?php echo htmlspecialchars($_SERVER['PHP_SELF']);?>" class="padding rounded-corners">
          <h1>Registrati</h1>
          <div class="form-fields">
            <span class="error"><?php echo $formErrors['name'];?></span>
            <div class="data-form-field">
              <label for="name">Nome:</label>
              <input type="name" id="name" name="name" />
            </div>

            <span class="error"><?php echo $formErrors['surname'];?></span>
            <div class="data-form-field">
              <label for="surname">Cognome:</label>
              <input type="surname" id="surname" name="surname" />
            </div>

            <span class="error"><?php echo $formErrors['dateOfBirth'];?></span>
            <div class="data-form-field">
              <label for="dateOfBirth">Data di nascita:</label>
              <input type="date" id="dateOfBirth" name="dateOfBirth" />
            </div>
            
            <span class="error"><?php echo $formErrors['email'];?></span>
            <div class="data-form-field">
              <label for="email">Email:</label>
              <input type="email" id="email" name="email" />
            </div>

            <span class="error"><?php echo $formErrors['username'];?></span>
            <div class="data-form-field">
              <label for="username">Username:</label>
              <input type="text" id="username" name="username" />
            </div>

            <span class="error"><?php echo $formErrors['password'];?></span>
            <div class="data-form-field">
              <label for="password">Password:</label>
              <input type="password" id="password" name="password" />
            </div>

            <span class="error"><?php echo $formErrors['passwordConfirm'];?></span>
            <div class="data-form-field">
              <label for="passwordConfirm">Conferma la password:</label>
              <input type="password" id="passwordConfirm" name="passwordConfirm" />
            </div>
          </div>
          <input type="submit" id="form_submit" name="Login" />
        </form>
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
