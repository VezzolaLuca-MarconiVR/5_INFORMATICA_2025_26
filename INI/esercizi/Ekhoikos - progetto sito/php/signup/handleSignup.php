<?php
require "../general/functions.php";

# Form field names
$formFieldsNames = array('name', 'surname', 'dateOfBirth', 'email', 'username', 'password', 'passwordConfirm');
# Form errors (associative array ('key'=>'value'))
$formErrors = array('name'=>'', 'surname'=>'', 'dateOfBirth'=>'', 'email'=>'', 'username'=>'', 'password'=>'', 'passwordConfirm'=>'');
# Form fields structure requirements in regexp
$formFieldsStructure = array('name'=>"/^[a-zA-Z-' ]*$/", 'surname'=>"/^[a-zA-Z-' ]*$/", 'dateOfBirth'=>'/^[0-9]{4}-(0[1-9]|1[0-2])-(0[1-9]|[1-2][0-9]|3[0-1])$/', 'email'=>"/^[\w\.-]+@[\w\.-]+\.\w{2,}$/", 'username'=>"/^[\w.-]{3,32}$/", 'password'=>"/^(?=.*?[A-Z])(?=.*?[a-z])(?=.*?[0-9])(?=.*?[#?!@$%^&*-]).{8,}$/", 'passwordConfirm'=>"/^(?=.*?[A-Z])(?=.*?[a-z])(?=.*?[0-9])(?=.*?[#?!@$%^&*-]).{8,}$/");

if ($_SERVER["REQUEST_METHOD"] == "POST") {
  // Check if all fields are not empty, otherwise warn user for the missing fields by adding the "* Required" error
  foreach ($formFieldsNames as $fieldName){
    if( empty($_POST[$fieldName]) ){
      // Field is not compiled
      $formErrors[$fieldName] = '* Required field';
    } else {
      // Field is compiled -> checkoing if it is structured correctly
      $_POST[$fieldName] = test_input($_POST[$fieldName]);
      if (!preg_match($formFieldsStructure[$fieldName], $_POST[$fieldName])) {
        // Field isn't structured correctly
        if($fieldName == 'password'){
          $formErrors[$fieldName] = "* The password must be at least 8 characters long and contain at least an upper case and lower case letter, a number and a special character.";
        } else {
          $formErrors[$fieldName] = "* Bad input inserted.";
        }
      } else {
        // Field is structured correctly
        $formErrors[$fieldName] = "";
      }
    }
  }

  // Controlla se la data è plausibile
  $date = DateTime::createFromFormat('Y-m-d', $_POST['dateOfBirth']);
  if (!$date || $date->format('Y-m-d') !== $_POST['dateOfBirth']) {
      $formErrors['dateOfBirth'] = "* Date is not correct";
  }

  // Controlla se la psw ripetuta è corretta
  if($_POST['passwordConfirm']!=$_POST['password']){
    $formErrors['passwordConfirm'] = "* Does not match the password written above";
  }

  // Controlla se non sono stati registrati errori
  $isFormOk = TRUE;
  foreach ($formErrors as $fieldError){
  if(!empty($fieldError)){
    $isFormOk = FALSE;
    }
  }
  
  // Se non è presente nessun errore, vai avanti e inserisci il nuovo utente iscrivendolo per poi creare una sessione e fare un redirect alla home
  if($isFormOk){
    // Connessione al DB
    require "./general/connect.php";

    // Preparazione della query
    $sql = "INSERT INTO Utenti (nome, cognome, dNascita, email, nomeUtente, psw) VALUES (?, ?, ?, ?, ?, ?)";

    // Codifica della password
    $passwordInChiaro = $_POST['password'];
    // PHP genera automaticamente un hash bcrypt sicuro
    // (salt casuale incluso, non devi gestirlo tu)
    $passwordHash = password_hash($passwordInChiaro, PASSWORD_BCRYPT);

    // Preparazione del template della query SQL
    if($stmt = $conn->prepare($sql)) {
      // Bind dei parametri con i formati corretti
      $stmt->bind_param("ssssss", $_POST[$formFieldsNames[0]], $_POST[$formFieldsNames[1]], $_POST[$formFieldsNames[2]], $_POST[$formFieldsNames[3]], $_POST[$formFieldsNames[4]], $passwordHash);

      $stmt->execute();

      echo("Iscrizione completata!");

      // // Ridireziona l'utente
      // header("Location: ../shop.php");
      // exit;
    } else {
      echo "Error: " . $sql . "<br>" . $conn->error;
    }
  }
  $conn->close();
}
?>