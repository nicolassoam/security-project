#ifndef FILEREADING_H_
#define FILEREADING_H_

#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <sstream>
#include <string>
namespace util 
{
    std::set<char> alfabeto;
    const char alfa[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::string LerFrase(std:: string nomeArquivo) 
    {
        std::string frase;
        std::ifstream arquivo;
        arquivo.open(nomeArquivo);
        if (arquivo.is_open()) 
        {
            getline(arquivo, frase);
            arquivo.close();
        }
        return frase;
    };

    void CarregaAlfabeto()
    {
        for (char c = 'A'; c <= 'Z'; c++)
        {
            alfabeto.insert(c);
            std::cout << c << std::endl;
        }
        
    }
}

std::string AplicarCifra(std::string frase)
{
    std::string fraseCifrada = " ";
    for (int i = 0; i < frase.size(); i++)
    {
        if(frase[i] == ' ')
        {
            fraseCifrada += ' ';
            continue;
        }
        fraseCifrada += (frase[i] + 3);
    }
    return fraseCifrada;
}

void EscreverFrase(std::string nomeArquivo, std::string frase)
{
    std::ofstream arquivo;
    arquivo.open(nomeArquivo);
    if (arquivo.is_open())
    {
        arquivo << frase;
        arquivo.close();
    }
}

void ForcaBruta(std::string fraseCriptografada)
{
    for (int i = 0; i < 26; i++)
    {
        std::string fraseDecifrada = " ";
        for (int j = 0; j < fraseCriptografada.size(); j++)
        {
            if(fraseCriptografada[j] == ' ')
            {
                fraseDecifrada += ' ';
                continue;
            }
            fraseDecifrada += util::alfa[((char)fraseCriptografada[j] - i)%26];
        }
        std::cout << "Tentativa " << i << std::endl;
        std::cout << fraseDecifrada << std::endl;
    }
}

std::string DesaplicaCifra(std::string fraseCifrada)
{
    std::string frase = " ";
    for (int i = 0; i < fraseCifrada.size(); i++)
    {
        if(fraseCifrada[i] == ' ')
        {
            frase += ' ';
            continue;
        }
        frase += (fraseCifrada[i] - 3);
    }
    return frase;
}
#endif /* FILEREADING_H_ */
