/* 1. Write a program that encrypts and decrypts a string using Caesar's algorithm;
 * 2. write a program that encrypts and decrypts a string using the Spartan Scital;
 * 3. write a program that encrypts and decrypts using Leon Battista Alberti's monoalphabetic cipher;
 * 4. write a program that encrypts and decrypts using the Vigenerè algorithm.
 */

#include <iostream>
#include <string>
#include <string_view>

using namespace std;

// Cesar's cipher
string CesarCipherEncrypt(string_view input);
string CesarCipherDecrypt(string_view input);
// Spartan Scital
string SpartanScitalEncrypt(string_view input);
string SpartanScitalDecrypt(string_view input);
// Leon B. A.'s monoalphabetic cipher
string MonoalphabeticCipherEncrypt(string_view input);
string MonoalphabeticCipherDecrypt(string_view input);
// Vigenerè's algorithm
string VigenereAlgorithmEncrypt(string_view input);
string VigenereAlgorithmDecrypt(string_view input);

int main()
{
  // The input for the cipher function selected and its output
  string input;
  string output;

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
  {
    // Option selected: Encrypt

    // User encryption method selection
    do
    {
      cout << "SELECT AN ENCRYPTION METHOD:\n\n 1. Cesar's cipher\n 2. Spartan Scital\n 3. Leon B.A.'s monoalphabetic cipher\n 4. Vigenerè's algorithm" << endl;
      getline(cin, userLastInput);
      lastOptionSelected = stoi(userLastInput);
      if (lastOptionSelected < 1 || lastOptionSelected > 4)
        cout << "Incorrect input: please type one of the options' numbers" << endl;
    } while (lastOptionSelected < 1 || lastOptionSelected > 4);

    // User text to encrypt input
    cout << "Type the text to encrypt:" << endl;
    getline(cin, input);

    switch (lastOptionSelected)
    {
    case 1:
      // Cesar's cipher
      output = CesarCipherEncrypt(input);
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
  }
  case 2:
  {
    // Option selected: Decrypt

    // User decryption method selection
    do
    {
      cout << "SELECT A DECRYPTION METHOD:\n\n 1. Cesar's cipher\n 2. Spartan Scital\n 3. Leon B.A.'s monoalphabetic cipher\n 4. Vigenerè's algorithm" << endl;
      getline(cin, userLastInput);
      lastOptionSelected = stoi(userLastInput);
      if (lastOptionSelected < 1 || lastOptionSelected > 4)
        cout << "Incorrect input: please type one of the options' numbers" << endl;
    } while (lastOptionSelected < 1 || lastOptionSelected > 4);

    // User text to decrypt input
    cout << "Type the text to decrypt:" << endl;
    getline(cin, input);

    switch (lastOptionSelected)
    {
    case 1:
      // Cesar's cipher
      output = CesarCipherDecrypt(input);
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
  }
  }

  cout << "Output: " << output << endl;
}

// Cesar's cipher
string CesarCipherEncrypt(string_view input)
{
  string output;
  output.reserve(input.size());

  // Shifting every letter forward by 3 positions
  // (Cesar used a shift of 3 positions, so we will do the same)
  for (char c : input)
  {
    if (c >= 'A' && c <= 'Z')
    {
      // Upper case letter
      output.push_back((c - 'A' + 3) % 26 + 'A');
    }
    else if (c >= 'a' && c <= 'z')
    {
      // Lower case letter
      output.push_back((c - 'a' + 3) % 26 + 'a');
    }
    else
    {
      output.push_back(c);
    }
  }

  return output;
}
string CesarCipherDecrypt(string_view input)
{
  string output;

  // Shifting every letter backwards by 3 positions
  // (Cesar used a shift of 3 positions, so we will do the same)
  for (char c : input)
  {
    if (c >= 'A' && c <= 'Z')
    {
      // Upper case letter
      output.push_back((c - 'A' + 23) % 26 + 'A');
    }
    else if (c >= 'a' && c <= 'z')
    {
      // Lower case letter
      output.push_back((c - 'a' + 23) % 26 + 'a');
    }
    else
    {
      output.push_back(c);
    }
  }

  return output;
}

// Spartan Scital
string SpartanScitalEncrypt(string_view input)
{
  string output;

  return output;
}
string SpartanScitalDecrypt(string_view input)
{
  string output;

  return output;
}

// Leon B. A.'s monoalphabetic cipher
string MonoalphabeticCipherEncrypt(string_view input)
{
  string output;

  return output;
}
string MonoalphabeticCipherDecrypt(string_view input)
{
  string output;

  return output;
}

// Vigenerè's algorithm
string VigenereAlgorithmEncrypt(string_view input)
{
  string output;

  return output;
}
string VigenereAlgorithmDecrypt(string_view input)
{
  string output;

  return output;
}
