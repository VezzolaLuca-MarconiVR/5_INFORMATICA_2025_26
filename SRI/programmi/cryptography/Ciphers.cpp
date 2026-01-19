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
string cesarCipherEncrypt(string_view input);
string cesarCipherDecrypt(string_view input);
// Spartan Scital
string spartanScitalEncrypt(string_view input, size_t discreteCircumference);
string spartanScitalDecrypt(string_view input, size_t discreteCircumference);
// Leon B. A.'s polyalphabetic cipher
string polylphabeticCipherEncrypt(string &input, string &innerDisc, char innerDiscIndex);
string PolyalphabeticCipherDecrypt(string_view input, string_view innerDisc, char innerDiscIndex);
// Vigenerè's algorithm
string vigenereAlgorithmEncrypt(string_view input);
string vigenereAlgorithmDecrypt(string_view input);

// Returns the string without spaces
void removeSpaces(string &input);

// Applies a kind of "pacman effect"
size_t circularModule(int n, int mod);

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
      output = cesarCipherEncrypt(input);
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

      output = spartanScitalEncrypt(input, lastOptionSelected);

      break;
    case 3:
      char innerDiscIndex;

      cout << "Type the index character (one of the inner disc letters): ";
      getline(cin, userLastInput);
      innerDiscIndex = userLastInput.at(0);

      cout << "Type the inner disc (the start doesn't matter): ";
      getline(cin, userLastInput);

      // Leon B. A.'s polyalphabetic cipher
      output = polylphabeticCipherEncrypt(input, userLastInput, innerDiscIndex);

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
      output = cesarCipherDecrypt(input);
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

      output = spartanScitalDecrypt(input, lastOptionSelected);

      break;
    case 3:
      // Leon B. A.'s polyalphabetic cipher
      char innerDiscIndex;

      cout << "Type the index character (one of the inner disc letters): ";
      getline(cin, userLastInput);
      innerDiscIndex = userLastInput.at(0);

      cout << "Type the inner disc (the start doesn't matter): ";
      getline(cin, userLastInput);

      // Leon B. A.'s polyalphabetic cipher
      output = PolyalphabeticCipherDecrypt(input, userLastInput, innerDiscIndex);

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
string cesarCipherEncrypt(string_view input)
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
string cesarCipherDecrypt(string_view input)
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
string spartanScitalEncrypt(string_view input, size_t discreteCircumference)
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
string spartanScitalDecrypt(string_view input, size_t discreteCircumference)
{
  string output;
  output.reserve(input.size() / discreteCircumference);

  for (size_t i = 0; i < input.size(); i += discreteCircumference)
  {
    output.push_back(input.at(i));
  }

  return output;
}

// Leon B. A.'s polyalphabetic cipher (first method - explained in chapter XIV of "De Cifris")
string polylphabeticCipherEncrypt(string &input, string &innerDisc, char innerDiscIndex)
{
  string output;

  // Initializing a random seed
  srand(time(NULL));

  // Looks for the position of the index in the inner disc and then uses it as an additional offset
  int innerDiscIndexPosition = innerDisc.find(innerDiscIndex);

  // Underestimated string capacity
  output.reserve(input.size());

  // 24 characters
  const string outerDisc = "ABCDEFGILMNOPQRSTVXZ1234";

  // The displacement (rotation) of the inner disc relative to the outer disc
  int innerDiscDisplacement = 999;

  // Temporary random displacement variable
  int temp;

  size_t randomN;
  size_t charsBeforeNewDisplacement;

  // Encrypts all of the characters of the input into the output (adding special chars for rotating the disc)
  for (size_t encryptedChars = 0; encryptedChars < input.length(); encryptedChars += charsBeforeNewDisplacement)
  {

    // All of the rotation are made automatically by this function following random values
    // The displacement is between 0 and 23 and must be different from the last time
    do
    {
      temp = rand() % 24;
    } while (innerDiscDisplacement == temp);

    innerDiscDisplacement = temp;

    // Encrypts the alignment of the two discs in the message
    output.push_back(outerDisc.at((innerDiscIndexPosition + innerDiscDisplacement) % 24));

    // We will change displacement after a random number of characters between 12 and 24
    // (the rough average of letters in phrases of three or four words)
    // If ecceding the number of characters to be encrypted, it is the number of characters to be encrypted
    randomN = rand() % 12 + 12;
    charsBeforeNewDisplacement = randomN > input.length() - encryptedChars ? input.length() - encryptedChars : randomN;

    for (size_t i = 0; i < charsBeforeNewDisplacement; i++)
    {
      output.push_back(innerDisc.at(circularModule((outerDisc.find(input.at(i + encryptedChars)) - innerDiscDisplacement), 24)));
    }
  }

  return output;
}
string PolyalphabeticCipherDecrypt(string_view input, string_view innerDisc, char innerDiscIndex)
{
  string output;

  // The "standard" outer disc
  const string outerDisc = "ABCDEFGILMNOPQRSTVXZ1234";

  // The length of the inner disc must be equal to that of the outer disc (24 characters)
  if (outerDisc.size() != innerDisc.size())
  {
    cout << "[Error]: The length of the inner disc must be equal to that of the outer disc (24 characters)" << endl;
    return output;
  }

  // Reserving an underestimated string capacity for efficiency
  output.reserve(input.size());

  // Looks for the position of the index in the inner disc
  auto idxPos = innerDisc.find(innerDiscIndex);
  if (idxPos == std::string::npos)
  {
    cout << "[Error]: Invalid inner disc index character" << endl;
    return output;
  }

  int innerDiscIndexPosition = (int)idxPos;

  // The displacement (rotation) of the inner disc relative to the outer disc
  int innerDiscDisplacement = -1;

  bool lastWasInOuterDisc = false;

  for (char c : input)
  {
    auto innerDiscPosition = innerDisc.find(c);
    auto outerDiscPosition = outerDisc.find(c);

    if (innerDiscPosition != string::npos)
    {
      // The character is a lower case letter to decrypt

      int innerDiscCharPos = (int)innerDiscPosition;
      int outerPos = (int)(circularModule(innerDiscCharPos + innerDiscDisplacement, 24));
      output.push_back(outerDisc[outerPos]);

      lastWasInOuterDisc = false;
    }
    else if (outerDiscPosition != string::npos)
    {
      // The character is an upper case letter or a number - the displacement has changed

      if (lastWasInOuterDisc)
      {
        // Writing two outer-disc characters one after the other is forbidden,
        // so the crypted message is invalid

        cout << "[Error]: Invalid crypted message" << endl;
        output.clear();
        return output;
      }

      // Change the displacement according to the character just read
      innerDiscDisplacement = (int)(outerDiscPosition)-innerDiscIndexPosition;

      lastWasInOuterDisc = true;
    }
    else
    {
      cout << "[Error]: Invalid crypted message" << endl;
      output.clear();
      return output;
    }
  }

  return output;
}

// Vigenerè's algorithm
string vigenereAlgorithmEncrypt(string_view input)
{
  string output;

  return output;
}
string vigenereAlgorithmDecrypt(string_view input)
{
  string output;

  return output;
}

// Removing all spaces from a string
void removeSpaces(string &str)
{
  str.erase(remove(str.begin(), str.end(), ' '), str.end());
}

// Applies a kind of "pacman effect"
size_t circularModule(int n, int mod)
{
  size_t output;

  if (n >= 0)
  {
    output = n % mod;
  }
  else
  {
    output = mod + n;
  }

  return output;
}