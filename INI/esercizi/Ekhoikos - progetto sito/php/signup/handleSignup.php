<?php
require "./general/functions.php";

# Form field names
$formFieldsNames = array('name', 'surname', 'username', 'password', 'passwordConfirm');
# Form errors (associative array ('key'=>'value'))
$formErrors = array('name'=>'', 'surname'=>'', 'username'=>'', 'password'=>'', 'passwordConfirm'=>'');
# Form fields structure requirements in regexp
$formFieldsStructure = array('name'=>"/^[a-zA-Z-' ]*$/", 'surname'=>"/^[a-zA-Z-' ]*$/", 'username'=>"/^[\w.-]{3,32}$/", 'password'=>"/^(?=.*?[A-Z])(?=.*?[a-z])(?=.*?[0-9])(?=.*?[#?!@$%^&*-]).{8,}$/", 'passwordConfirm'=>"/^(?=.*?[A-Z])(?=.*?[a-z])(?=.*?[0-9])(?=.*?[#?!@$%^&*-]).{8,}$/");

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
        $formErrors[$fieldName] = "* The password must be at least 8 characters long and contain at least an upper case and lower case letter, a number and a special character.";
      } else {
        // Field is structured correctly
        $formErrors[$fieldName] = "";
      }
    }
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
    $sql = "INSERT INTO Utenti (nomeUtente, psw, nome, cognome, dNascita, email) VALUES (?, ?, ?, ?, ?, ?)";

    // // Prepare the SQL query template
    // if($stmt = $conn->prepare($sql)) {
    //   // Bind parameters
    //   $stmt->bind_param("sss", $firstname, $lastname, $email);

    //   // Set parameters and execute
    //   $firstname = "John";
    //   $lastname = "Doe";
    //   $email = "john@example.com";
    //   $stmt->execute();

    //   $firstname = "Mary";
    //   $lastname = "Moe";
    //   $email = "mary@example.com";
    //   $stmt->execute();

    //   $firstname = "Julie";
    //   $lastname = "Dooley";
    //   $email = "julie@example.com";
    //   $stmt->execute();
    //   echo "New records created successfully";
    // } else {
    //   echo "Error: " . $sql . "<br>" . $conn->error;
    // }
  }
  $conn->close();
}
?>