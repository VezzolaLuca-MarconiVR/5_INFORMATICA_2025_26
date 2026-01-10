/* 1. Write a program that encrypts and decrypts a string using Caesar's algorithm;
 * 2. write a program that encrypts and decrypts a string using the Spartan Scital;
 * 3. write a program that encrypts and decrypts using Leon Battista Alberti's monoalphabetic cipher;
 * 4. write a program that encrypts and decrypts using the Vigenerè algorithm.
 */

#include <iostream>
#include <string>
#include <string_view>

using namespace std;

void CesarCipher(string_view input, string_view output);

int main()
{
  // The input for the cipher function selected and its output
  string encryptorInput;
  string encryptorOutput;

  // Re-usable user option handling variables
  string userLastInput;
  int lastOptionSelected;

  // User action selection
  do
  {
    cout << "SELECT AN OPTION:\n\n 1.  Encrypt\n 2. Decrypt" << endl;
    getline(cin, userLastInput);
    lastOptionSelected = stoi(userLastInput);
    if (lastOptionSelected < 1 || lastOptionSelected > 2)
      cout << "Incorrect input: please type one of the options' numbers" << endl;
  } while (lastOptionSelected < 1 || lastOptionSelected > 2);

  switch (lastOptionSelected)
  {
  case 1:
    // Option selected: Encrypt

    // User encryption method selection
    do
    {
      cout << "SELECT AN ENCRYPTION METHOD:\n\n 1.  Cesar's cipher\n 2. Spartan Scital\n 3. Leon B.A.'s monoalphabetic cipher\n 4. Vigenerè's algorithm" << endl;
      getline(cin, userLastInput);
      lastOptionSelected = stoi(userLastInput);
      if (lastOptionSelected < 1 || lastOptionSelected > 4)
        cout << "Incorrect input: please type one of the options' numbers" << endl;
    } while (lastOptionSelected < 1 || lastOptionSelected > 4);

    // User text to encrypt input
    cout << "Type the text to encrypt:" << endl;
    getline(cin, encryptorInput);

    switch (lastOptionSelected)
    {
    case 1:
      // Cesar's cipher
      break;
    case 2:
      // Spartan Scital
      break;
    case 3:
      // Leon B. A.'s monoalphabetic cipher
      break;
    case 4:
      // Vigenerè's algorithm
      break;
    }
    break;
  case 2:
    // Option selected: Decrypt

    // User decryption method selection
    do
    {
      cout << "SELECT A DECRYPTION METHOD:\n\n 1.  Cesar's cipher\n 2. Spartan Scital\n 3. Leon B.A.'s monoalphabetic cipher\n 4. Vigenerè's algorithm" << endl;
      getline(cin, userLastInput);
      lastOptionSelected = stoi(userLastInput);
      if (lastOptionSelected < 1 || lastOptionSelected >= 4)
        cout << "Incorrect input: please type one of the options' numbers" << endl;
    } while (lastOptionSelected < 1 || lastOptionSelected >= 4);

    // User text to decrypt input
    cout << "Type the text to decrypt:" << endl;
    getline(cin, encryptorInput);

    switch (lastOptionSelected)
    {
    case 1:
      // Cesar's cipher
      break;
    case 2:
      // Spartan Scital
      break;
    case 3:
      // Leon B. A.'s monoalphabetic cipher
      break;
    case 4:
      // Vigenerè's algorithm
      break;
    }

  default:
  }
}

void CesarCipher(string_view input, string_view output)
{
}