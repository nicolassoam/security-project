#include "./security.h"
#include "config.h"

int main()
{   
    std::string fileName = INPUT_DIR;
    fileName += "/frase.txt";
    std::string phrase = util::ReadPhrase(fileName);
    std::vector<std::string> b = util::FullText((std::string)INPUT_DIR + "/biblia-em-txt.txt");
    util::LetterFrequencyPT(b);

    std::string cipheredPhrase = ApplyCaesarCipher(phrase);
    util::WritePhrase((std::string)OUTPUT_DIR + "/fraseCifrada.txt", cipheredPhrase);
    std::string decipheredPhrase = DeapplyCipher(cipheredPhrase);
    util::WritePhrase((std::string)OUTPUT_DIR + "/fraseDecifrada.txt", decipheredPhrase);
    std::string crpt ="GCUA VQ DTGCM";
    std::vector<std::string> text = util::FullText((std::string)INPUT_DIR + "/texto_cifrado.txt");
    // BruteForce(crpt);
    // MostFrequent("B wdugh, dshvdu gd haflwdhdr srsxodu mb vhu ehp ylvlyho, r uhl G. Fduorv haklelx-vh hp sdvvhlr qd Dyhqlgd gd Olehugdgh h vhx lupdr r lqidqwh G.");
    MostFrequentBig(text);
}