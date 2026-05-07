<?php require "./handleShop.php";?>

<!DOCTYPE html>
<html lang="it">
  <head>
    <meta charset="UTF-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <title>Ekhoikos - Shop</title>
    <link rel="stylesheet" href="../../css/general.css" />
    <link rel="stylesheet" href="../../css/shop.css" />
    <script src="../../js/index.js" defer></script>
  </head>

  <body>
    <!-- Navbar -->
    <nav>
      <ul>
        <li><a href="../index/index.php">Home</a></li>
        <li><a href="../shop/shop.php" class="active">Shop</a></li>
        <li><a href="../chat/chat.php">Chat</a></li>
        <?php
        if (isLoggedIn()) {
          echo "<li style='float: right'>
                  <a href='../general/logout.php'>Logout</a>
                </li>
                <li style='float: right'>
                  <a href='../user/user.php'>User: " . $_SESSION['username'] . "</a>
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
      <div id="main_container">
        <!-- Left Content → FILTERS -->
        <div id="left_content">
          <form action="link.xyz">
            <h3>Caratteristiche:</h3>
            <input type="checkbox" id="option1" name="option1" value="Bike" />
            <label for="option1"> option1</label><br />
            <input type="checkbox" id="option2" name="option2" value="Car" />
            <label for="option2"> option2</label><br />
            <input type="checkbox" id="option3" name="option3" value="Boat" />
            <label for="option3"> option3</label><br /><br />
            <input type="submit" name="Filtra" />
          </form>
        </div>

        <!-- Center Content → PRODUCTS LIST -->
        <div id="center_content">
          <?php displayProductsCards();?>
        </div>

        <!-- Right Content → MAP -->
        <div id="right_content">
          <div class="embed-map-responsive"><div class="embed-map-container"><iframe class="embed-map-frame" frameborder="0" scrolling="no" marginheight="0" marginwidth="0" src="https://maps.google.com/maps?width=600&height=400&hl=en&q=verona&t=k&z=13&ie=UTF8&iwloc=B&output=embed"></iframe></div>
          </div>
        </div>
      </div>
    </main>
  </body>
</html>
