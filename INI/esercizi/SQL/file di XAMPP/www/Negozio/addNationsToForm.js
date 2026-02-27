const nationSelect = document.getElementById("nationSelect");

const nationsList = ["Nessuno", "Afghanistan", "Albania", "Algeria", "Andorra", "Angola", "Antigua & Deps", "Argentina", "Armenia", "Australia", "Austria", "Azerbaigian", "Bahamas", "Bahrein", "Bangladesh", "Barbados", "Bielorussia", "Belgio", "Belize", "Benin", "Bhutan", "Bolivia", "Bosnia Erzegovina", "Botswana", "Brasile", "Brunei", "Bulgaria", "Burkina", "Burundi", "Cambogia", "Camerun", "Canada", "Capo Verde", "Rep. Centrafricana", "Ciad", "Cile", "Cina", "Colombia", "Comore", "Congo", "Congo (Rep. Democratica)", "Costa Rica", "Croazia", "Cuba", "Cipro", "Repubblica Ceca", "Danimarca", "Gibuti", "Dominica", "Repubblica Dominicana", "Timor Est", "Ecuador", "Egitto", "El Salvador", "Guinea Equatoriale", "Eritrea", "Estonia", "Etiopia", "Figi", "Finlandia", "Francia", "Gabon", "Gambia", "Georgia", "Germania", "Ghana", "Grecia", "Grenada", "Guatemala", "Guinea", "Guinea-Bissau", "Guyana", "Haiti", "Honduras", "Ungheria", "Islanda", "India", "Indonesia", "Iran", "Iraq", "Irlanda (Repubblica)", "Israele", "Italia", "Costa d'Avorio", "Giamaica", "Giappone", "Giordania", "Kazakistan", "Kenya", "Kiribati", "Corea Nord", "Corea Sud", "Kosovo", "Kuwait", "Kirghizistan", "Laos", "Lettonia", "Libano", "Lesotho", "Liberia", "Libia", "Liechtenstein", "Lituania", "Lussemburgo", "Macedonia", "Madagascar", "Malawi", "Malesia", "Maldive", "Mali", "Malta", "Isole Marshall", "Mauritania", "Mauritius", "Messico", "Micronesia", "Moldavia", "Monaco", "Mongolia", "Montenegro", "Marocco", "Mozambico", "Myanmar (Birmania)", "Namibia", "Nauru", "Nepal", "Paesi Bassi", "Nuova Zelanda", "Nicaragua", "Niger", "Nigeria", "Norvegia", "Oman", "Pakistan", "Palau", "Panama", "Papua Nuova Guinea", "Paraguay", "Perù", "Filippine", "Polonia", "Portogallo", "Qatar", "Romania", "Federazione Russa", "Ruanda", "Saint Kitts e Nevis", "St Lucia", "Saint Vincent e Grenadine", "Samoa", "San Marino", "Sao Tomé e Principe", "Arabia Saudita", "Senegal", "Serbia", "Seychelles", "Sierra Leone", "Singapore", "Slovacchia", "Slovenia", "Isole Salomone", "Somalia", "Sudafrica", "Sudan del Sud", "Spagna", "Sri Lanka", "Sudan", "Suriname", "Swaziland", "Svezia", "Svizzera", "Siria", "Taiwan", "Tagikistan", "Tanzania", "Thailandia", "Togo", "Tonga", "Trinidad e Tobago", "Tunisia", "Turchia", "Turkmenistan", "Tuvalu", "Uganda", "Ucraina", "Emirati Arabi Uniti", "Regno Unito", "Stati Uniti", "Uruguay", "Uzbekistan", "Vanuatu", "Città del Vaticano", "Venezuela", "Vietnam", "Yemen", "Zambia", "Zimbabwe"];

let node;
let textnode;

nationsList.forEach((el) => {
    node = document.createElement("option");
    
    textnode = document.createTextNode(el);
    node.appendChild(textnode);
    
    node.setAttribute("value", el);

    nationSelect.appendChild(node);
});