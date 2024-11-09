#include "./seguranca.h"
#include "config.h"

int main()
{   
    std::string fileName = PROJECT_DIR;
    fileName += "/frase.txt";
    std::string phrase = util::ReadPhrase(fileName);
    std::string cyphredPhrase = ApplyCaesarCyphre(phrase);
    WritePhrase((std::string)OUTPUT_DIR + "/fraseCifrada.txt", cyphredPhrase);
    std::string decyphredPhrase = DeapplyCyphre(cyphredPhrase);
    WritePhrase((std::string)OUTPUT_DIR + "/fraseDecifrada.txt", decyphredPhrase);
    std::string crpt ="GCUA VQ DTGCM"; 
    BruteForce(crpt);
}