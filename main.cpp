#include "./seguranca.h"
#include "config.h"
int main()
{   
    std::string nomeArqu = PROJECT_DIR;
    nomeArqu += "/frase.txt";
    std::string frase = util::LerFrase(nomeArqu);
    std::string fraseCifrada = AplicarCifra(frase);
    EscreverFrase("fraseCifrada.txt", fraseCifrada);
    std::string fraseDecifrada = DesaplicaCifra(fraseCifrada);
    EscreverFrase("fraseDecifrada.txt", fraseDecifrada);
    std::string crpt ="GCUA VQ DTGCM"; 
    ForcaBruta(crpt);
}