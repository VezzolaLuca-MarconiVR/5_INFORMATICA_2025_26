<?php require 'addNewClient.php';?>
<!doctype html>
<html>
  <head>
    <title>Aggiungi nuovo cliente</title>
    <link rel="stylesheet" href="style.css" />
  </head>
  <body>
    <p><span class="error">* required field</span></p>

    <form
      method="POST"
      action="<?php echo htmlspecialchars($_SERVER['PHP_SELF']);?>"
    >
      <label for="name&surnameInput">Name and surname:</label>
      <input type="text" id="name&surnameInput" name="name&surname" />
      <span class="error">* <?php echo $unameAndSurnameErr;?></span>
      <br /><br />

      <label for="addressInput">Address:</label>
      <input type="text" id="addressInput" name="address" />
      <span class="error">* <?php echo $uaddressErr;?></span>
      <br /><br />

      <label for="cityInput">City:</label>
      <input type="text" id="cityInput" name="city" />
      <span class="error">* <?php echo $ucityErr;?></span>
      <br /><br />

      <label for="nationSelect">Nation:</label>
      <select id="nationSelect" class="nationSelect" name="nation"></select>
      <span class="error">* <?php echo $unationErr;?></span>
      <br /><br />

      <label for="sumbitButton">Submit</label>
      <input type="submit" id="sumbitButton" />
    </form>

    <script src="./addNationsToForm.js"></script>
  </body>
</html>
