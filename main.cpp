#include "./security.h"
#include "config.h"

int main()
{   
    std::string fileName = PROJECT_DIR;
    fileName += "/frase.txt";
    std::string phrase = util::ReadPhrase(fileName);
    std::string cipheredPhrase = ApplyCaesarCipher(phrase);
    util::WritePhrase((std::string)OUTPUT_DIR + "/fraseCifrada.txt", cipheredPhrase);
    std::string decipheredPhrase = DeapplyCipher(cipheredPhrase);
    util::WritePhrase((std::string)OUTPUT_DIR + "/fraseDecifrada.txt", decipheredPhrase);
    std::string crpt ="GCUA VQ DTGCM"; 
    BruteForce(crpt);
}