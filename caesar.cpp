#include "./security.h"
#include "config.h"

int main()
{   
    using namespace std;
    string fileName = INPUT_DIR;
    fileName += "/frase.txt";
    string phrase = util::ReadPhrase(fileName);

    string cipheredPhrase = ApplyCaesarCipher(phrase);
    util::WritePhrase((std::string)OUTPUT_DIR + "/fraseCifrada.txt", cipheredPhrase);
    string decipheredPhrase = DeapplyCipher(cipheredPhrase);
    util::WritePhrase((std::string)OUTPUT_DIR + "/fraseDecifrada.txt", decipheredPhrase);
    string cipheredPhraseAnalysis ="GCUA VQ DTGCM";
    BruteForce(cipheredPhraseAnalysis);
}