#include <iostream>
#include <string>
#include <string_view>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <math.h>

using namespace std;

size_t circularModule(int n, int mod)
{
    int output = n % mod;
    if (output < 0)
        output += mod;
    
    return (size_t)output;
}

string polylphabeticCipherEncrypt(string_view input, string_view innerDisc, char innerDiscIndex)
{
    string output;
    output.reserve(input.size());

    string_view OUTER_DISC = "ABCDEFGILMNOPQRSTVXZ1234";
    if (OUTER_DISC.size() != innerDisc.size())
    {
        cout << "[Error]: The length of the inner disc must be equal to that of the outer disc (24 characters)" << endl;
        return output;
    }

    auto idxPos = innerDisc.find(innerDiscIndex);
    if (idxPos == string::npos) {
        cout << "[Error]: Invalid inner disc index character" << endl;
        return output;
    }

    int innerDiscIndexPosition = (int)idxPos;

    const int displacement = 4;
    size_t charsBeforeNewDisplacement;
    for (size_t encryptedChars = 0; encryptedChars < input.length(); encryptedChars += charsBeforeNewDisplacement)
    {
        output.push_back(OUTER_DISC[(size_t)circularModule(innerDiscIndexPosition + displacement, 24)]);

        for (char c : input)
        {
            output.push_back();
        }
    }

    return output;
}
string PolyalphabeticCipherDecrypt(string_view input, string_view innerDisc, char innerDiscIndex)
{
    string output;

    // Underestimated string capacity
    output.reserve(input.size());

    // 24 characters
    const string outerDisc = "ABCDEFGILMNOPQRSTVXZ1234";

    // The length of the inner disc must be equal to that of the outer disc (24 characters)
    if (outerDisc.size() != innerDisc.size())
    {
        cout << "[Error]: The length of the inner disc must be equal to that of the outer disc (24 characters)" << endl;
        return output;
    }

    // Looks for the position of the index in the inner disc and then uses it as an additional offset
    auto idxPos  = innerDisc.find(innerDiscIndex);
    if (idxPos == std::string::npos) {
        cout << "[Error]: Invalid inner disc index character" << endl;
        return output;
    }

    int innerDiscIndexPosition = (int)idxPos;

    // The displacement (rotation) of the inner disc relative to the outer disc
    int innerDiscDisplacement = -1;
    
    auto firstOuterPos = outerDisc.find(input[0]);
    if (firstOuterPos == string::npos)
    {
        cout << "[Error]: Invalid crypted message" << endl;
        return output;
    }
    
    bool lastWasInOuterDisc = false;

    for (char c : input)
    {   
        auto innerDiscPosition = innerDisc.find(c);
        auto outerDiscPosition = outerDisc.find(c);

        if (innerDiscPosition != string::npos)
        {   
            int idx = (int)innerDiscPosition;
            int outerPos = (int)(circularModule(idx - innerDiscIndexPosition + innerDiscDisplacement, 24));
            output.push_back(outerDisc[outerPos]);

            lastWasInOuterDisc = false;
        }
        else if (outerDiscPosition != string::npos)
        {   
            if (lastWasInOuterDisc)
            {
                cout << "[Error]: Invalid crypted message" << endl;
                output.clear();
                return output;
            }

            innerDiscDisplacement = (int)(outerDiscPosition) - innerDiscIndexPosition;

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

int main()
{
    const string OUTER_DISC = "ABCDEFGILMNOPQRSTVXZ1234";
    const string INNER_DISC = "ysomqihfdbacegklnprtvz&x";
    const char INDEX = 'm';
    const string INPUT = "CIAO";

    cout << "Message: " << INPUT << endl << endl;

    string_view output = polylphabeticCipherEncrypt(INPUT, INNER_DISC, INDEX);
    cout << "Encryption: " << output << endl;

    string_view output2 = PolyalphabeticCipherDecrypt(output, INNER_DISC, INDEX);
    cout << "Decryption: " << output2 << endl;
}