<?php
require "./general/connect.php";
require "./general/functions.php";

# Form field names
$formFieldsNames = array('name', 'surname', 'username', 'password', 'passwordConfirm');
# Form errors (associative array ('key'=>'value'))
$formErrors = array('name'=>'', 'surname'=>'', 'user'=>'', 'password'=>'', 'passwordConfirm'=>'');
# Form fields structure requirements in regexp
$formFieldsStructure = array('name'=>"/^[a-zA-Z-' ]*$/", 'surname'=>"/^[a-zA-Z-' ]*$/", 'user'=>"/^[\w.-]{3,32}$/", 'password'=>"/^(?=.*?[A-Z])(?=.*?[a-z])(?=.*?[0-9])(?=.*?[#?!@$%^&*-]).{8,}$/", 'passwordConfirm'=>"/^(?=.*?[A-Z])(?=.*?[a-z])(?=.*?[0-9])(?=.*?[#?!@$%^&*-]).{8,}$/");

if ($_SERVER["REQUEST_METHOD"] == "POST") {
  // Check if all fields are not empty, otherwise warn user for the missing fields by adding the "* Required" error
  foreach ($formFieldsNames as $fieldName){
    if( empty($_POST[$fieldName]) ){
      # Field is not compiled
      $formErrors[$fieldName] = '* Required field';
    } else {
      # Field is compiled -> checkoing if it is structured correctly
      $unameAndSurname = test_input($_POST['name&surname']);
      if (!preg_match($formFieldsStructure[$fieldName], $unameAndSurname)) {
        # Field isn't structured correctly
        $formErrors[$fieldName] = "Only letters and white space allowed";
      } else {
        # Field is structured correctly
        $formErrors[$fieldName] = "";
      }
    }
  }

  # Controlla se la psw ripetuta è corretta

  # Se nessun errore non è vuoto, vai avanti e inserisci il nuovo utente iscrivendolo per poi mandare alla home
}
?>