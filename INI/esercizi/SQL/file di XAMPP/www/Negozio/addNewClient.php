<?php
require 'functions.php';

$unameAndSurnameErr = $uaddressErr = $ucityErr = $unationErr = "";
$unameAndSurname = $uaddress = $ucity = $unation = "";

if ($_SERVER["REQUEST_METHOD"] == "POST") {
  $nationsList = [
    "Afghanistan",
    "Albania",
    "Algeria",
    "Andorra",
    "Angola",
    "Antigua & Deps",
    "Argentina",
    "Armenia",
    "Australia",
    "Austria",
    "Azerbaigian",
    "Bahamas",
    "Bahrein",
    "Bangladesh",
    "Barbados",
    "Bielorussia",
    "Belgio",
    "Belize",
    "Benin",
    "Bhutan",
    "Bolivia",
    "Bosnia Erzegovina",
    "Botswana",
    "Brasile",
    "Brunei",
    "Bulgaria",
    "Burkina",
    "Burundi",
    "Cambogia",
    "Camerun",
    "Canada",
    "Capo Verde",
    "Rep. Centrafricana",
    "Ciad",
    "Cile",
    "Cina",
    "Colombia",
    "Comore",
    "Congo",
    "Congo (Rep. Democratica)",
    "Costa Rica",
    "Croazia",
    "Cuba",
    "Cipro",
    "Repubblica Ceca",
    "Danimarca",
    "Gibuti",
    "Dominica",
    "Repubblica Dominicana",
    "Timor Est",
    "Ecuador",
    "Egitto",
    "El Salvador",
    "Guinea Equatoriale",
    "Eritrea",
    "Estonia",
    "Etiopia",
    "Figi",
    "Finlandia",
    "Francia",
    "Gabon",
    "Gambia",
    "Georgia",
    "Germania",
    "Ghana",
    "Grecia",
    "Grenada",
    "Guatemala",
    "Guinea",
    "Guinea-Bissau",
    "Guyana",
    "Haiti",
    "Honduras",
    "Ungheria",
    "Islanda",
    "India",
    "Indonesia",
    "Iran",
    "Iraq",
    "Irlanda (Repubblica)",
    "Israele",
    "Italia",
    "Costa d'Avorio",
    "Giamaica",
    "Giappone",
    "Giordania",
    "Kazakistan",
    "Kenya",
    "Kiribati",
    "Corea Nord",
    "Corea Sud",
    "Kosovo",
    "Kuwait",
    "Kirghizistan",
    "Laos",
    "Lettonia",
    "Libano",
    "Lesotho",
    "Liberia",
    "Libia",
    "Liechtenstein",
    "Lituania",
    "Lussemburgo",
    "Macedonia",
    "Madagascar",
    "Malawi",
    "Malesia",
    "Maldive",
    "Mali",
    "Malta",
    "Isole Marshall",
    "Mauritania",
    "Mauritius",
    "Messico",
    "Micronesia",
    "Moldavia",
    "Monaco",
    "Mongolia",
    "Montenegro",
    "Marocco",
    "Mozambico",
    "Myanmar (Birmania)",
    "Namibia",
    "Nauru",
    "Nepal",
    "Paesi Bassi",
    "Nuova Zelanda",
    "Nicaragua",
    "Niger",
    "Nigeria",
    "Norvegia",
    "Oman",
    "Pakistan",
    "Palau",
    "Panama",
    "Papua Nuova Guinea",
    "Paraguay",
    "Perù",
    "Filippine",
    "Polonia",
    "Portogallo",
    "Qatar",
    "Romania",
    "Federazione Russa",
    "Ruanda",
    "Saint Kitts e Nevis",
    "St Lucia",
    "Saint Vincent e Grenadine",
    "Samoa",
    "San Marino",
    "Sao Tomé e Principe",
    "Arabia Saudita",
    "Senegal",
    "Serbia",
    "Seychelles",
    "Sierra Leone",
    "Singapore",
    "Slovacchia",
    "Slovenia",
    "Isole Salomone",
    "Somalia",
    "Sudafrica",
    "Sudan del Sud",
    "Spagna",
    "Sri Lanka",
    "Sudan",
    "Suriname",
    "Swaziland",
    "Svezia",
    "Svizzera",
    "Siria",
    "Taiwan",
    "Tagikistan",
    "Tanzania",
    "Thailandia",
    "Togo",
    "Tonga",
    "Trinidad e Tobago",
    "Tunisia",
    "Turchia",
    "Turkmenistan",
    "Tuvalu",
    "Uganda",
    "Ucraina",
    "Emirati Arabi Uniti",
    "Regno Unito",
    "Stati Uniti",
    "Uruguay",
    "Uzbekistan",
    "Vanuatu",
    "Città del Vaticano",
    "Venezuela",
    "Vietnam",
    "Yemen",
    "Zambia",
    "Zimbabwe",
  ];

  // Variabili superglobali ottenute dal form in post html + controllo degli errori di inserimento
  if( empty($_POST['name&surname']) ){
    $unameAndSurnameErr = "Name and Surname are required";
  } else {
    $unameAndSurname = test_input($_POST['name&surname']);
    if (!preg_match("/^[a-zA-Z-' ]*$/", $unameAndSurname)) {
      $unameAndSurnameErr = "Only letters and white space allowed";
    }
  }

  if( empty($_POST['address']) ){
    $uaddressErr = "Address is required";
  } else {
    $uaddress = test_input($_POST['address']);
    if (!preg_match("/^[A-Za-z0-9\s.,\-\/\\\\]+$/", $uaddress)) {
      $uaddressErr = "Only letters, numbers, spaces, commas, periods, hyphens, and forward/backward slashes allowed";
    }
  }

  if( empty($_POST['city']) ){
    $ucityErr = "City is required";
  } else {
      $ucity = test_input($_POST['city']);
    if (!preg_match("/^[a-zA-Z-' ]*$/", $ucity)) {
      $ucityErr = "Only letters and white space allowed";
    }
  }

  if( empty($_POST['nation']) ){
    $unationErr = "Nation is required";
  } else {
    $unation = test_input($_POST['nation']);
    if(!in_array($unation, $nationsList)){
      $unationErr = "The nation does not correspond to any of the options in the form";
    }
  }

  if(empty($unameAndSurnameErr) && empty($uaddressErr) && empty($ucityErr) && empty($unationErr)){
    // Data has been checked and is good
    require 'connect.php';
  }
}

?>