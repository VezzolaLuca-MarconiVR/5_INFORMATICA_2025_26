/* 1. Write a program that encrypts and decrypts a string using Caesar's algorithm;
 * 2. write a program that encrypts and decrypts a string using the Spartan Scital;
 * 3. write a program that encrypts and decrypts using Leon Battista Alberti's polyalphabetic cipher;
 * 4. write a program that encrypts and decrypts using the Vigenerè algorithm.
 */

#include <iostream>
#include <string>
#include <string_view>
#include <stdlib.h>
#include <time.h>
#include <algorithm>

using namespace std;

// Cesar's cipher
string CesarCipherEncrypt(string_view input);
string CesarCipherDecrypt(string_view input);
// Spartan Scital
string SpartanScitalEncrypt(string_view input, size_t discreteCircumference);
string SpartanScitalDecrypt(string_view input, size_t discreteCircumference);
// Leon B. A.'s polyalphabetic cipher
string PolylphabeticCipherEncrypt(string_view input);
string PolyalphabeticCipherDecrypt(string_view input);
// Vigenerè's algorithm
string VigenereAlgorithmEncrypt(string_view input);
string VigenereAlgorithmDecrypt(string_view input);

// Returns the string without spaces
void removeSpaces(string &input);

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
    cout << "\nSELECT AN OPTION:\n 1.Encrypt\n 2.Decrypt" << endl;
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
      cout << "\nSELECT AN ENCRYPTION METHOD:\n 1.Cesar's cipher\n 2.Spartan Scital\n 3.Leon B.A.'s polyalphabetic cipher\n 4.Vigenerè's algorithm" << endl;
      getline(cin, userLastInput);
      lastOptionSelected = stoi(userLastInput);
      if (lastOptionSelected < 1 || lastOptionSelected > 4)
        cout << "Incorrect input: please type one of the options' numbers" << endl;
    } while (lastOptionSelected < 1 || lastOptionSelected > 4);

    // User text to encrypt input
    cout << "Type the text to encrypt:" << endl;
    getline(cin, input);
    removeSpaces(input);

    switch (lastOptionSelected)
    {
    case 1:
      // Cesar's cipher
      output = CesarCipherEncrypt(input);
      break;
    case 2:
      // Spartan Scital

      // User scital's circumference (discrete) input
      do
      {
        cout << "Type the (discrete) circumference of the scital: ";
        getline(cin, userLastInput);
        lastOptionSelected = stoi(userLastInput);
        if (lastOptionSelected <= 0)
          cout << "Incorrect input: please type a natural number";
      } while (lastOptionSelected <= 0);

      output = SpartanScitalEncrypt(input, lastOptionSelected);

      break;
    case 3:
      // Leon B. A.'s polyalphabetic cipher
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
      cout << "\nSELECT A DECRYPTION METHOD:\n 1.Cesar's cipher\n 2.Spartan Scital\n 3.Leon B.A.'s polyalphabetic cipher\n 4.Vigenerè's algorithm" << endl;
      getline(cin, userLastInput);
      lastOptionSelected = stoi(userLastInput);
      if (lastOptionSelected < 1 || lastOptionSelected > 4)
        cout << "Incorrect input: please type one of the options' numbers" << endl;
    } while (lastOptionSelected < 1 || lastOptionSelected > 4);

    // User text to decrypt input
    cout << "Type the text to decrypt:" << endl;
    getline(cin, input);

    // Removing all spaces to make the encryption stronger
    removeSpaces(input);

    switch (lastOptionSelected)
    {
    case 1:
      // Cesar's cipher
      output = CesarCipherDecrypt(input);
      break;
    case 2:
      // Spartan Scital
      // User scital's circumference (discrete) input
      do
      {
        cout << "Type the (discrete) circumference of the scital: ";
        getline(cin, userLastInput);
        lastOptionSelected = stoi(userLastInput);
        if (lastOptionSelected <= 0)
          cout << "Incorrect input: please type a natural number" << endl;
      } while (lastOptionSelected <= 0);

      output = SpartanScitalDecrypt(input, lastOptionSelected);

      break;
    case 3:
      // Leon B. A.'s polyalphabetic cipher
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
  output.reserve(input.size());

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
string SpartanScitalEncrypt(string_view input, size_t discreteCircumference)
{
  string output;

  // To ease coding we will use a discrete circumference
  // (it can only be n characters wide)
  output.reserve(input.size() * discreteCircumference);

  // Initializing the random seed with the time function (non-secure method for random gen.)
  srand(time(NULL));

  // Checking if the message length is prime
  // If it is prime, then there will be added a random number to make it scomposable

  {
    for (char c : input)
    {
      output.push_back(c);
      for (size_t i = 0; i < discreteCircumference - 1; i++)
      {
        // Inserting random characters
        output.push_back(char(rand() % 26 + 'A'));
      }
    }
  }

  // Transforming all to upper to make the encryption stronger
  transform(output.begin(), output.end(), output.begin(), ::toupper);

  return output;
}
string SpartanScitalDecrypt(string_view input, size_t discreteCircumference)
{
  string output;
  output.reserve(input.size() / discreteCircumference);

  for (size_t i = 0; i < input.size(); i += discreteCircumference)
  {
    output.push_back(input.at(i));
  }

  return output;
}

// Leon B. A.'s polyalphabetic cipher
string PolylphabeticCipherEncrypt(string_view input)
{
  string output;

  return output;
}
string PolyalphabeticCipherDecrypt(string_view input)
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

// Removing all spaces from a string
void removeSpaces(string &str)
{
  str.erase(remove(str.begin(), str.end(), ' '), str.end());
}