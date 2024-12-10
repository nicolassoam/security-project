#include "./security.h"
#include "config.h"

int main()
{   
    using namespace std;
    util::VigenereTable();
    string fileName = INPUT_DIR;
    fileName += "/frase.txt";
    string phrase = util::ReadPhrase(fileName);
    string vigenereKey = util::ReadPhrase((string)INPUT_DIR + "/vigenereKey.txt");
    string cipheredPhrase = ApplyVigenereCipher(phrase, vigenereKey);
    // string decipheredPhrase = DeapplyVigenereCipher(cipheredPhrase, vigenereKey);
    string railFence = ApplyRailFenceCipher(cipheredPhrase, 3);
    util::WritePhrase((std::string)OUTPUT_DIR + "/fraseVigenere.txt", cipheredPhrase);
    util::WritePhrase((std::string)OUTPUT_DIR + "/fraseRailFenceEVigenere.txt", railFence);
    // util::WritePhrase((std::string)OUTPUT_DIR + "/fraseDecifrada.txt", decipheredPhrase);
}