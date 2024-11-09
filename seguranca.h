#ifndef SECURITY_H_
#define SECURITY_H_

#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <sstream>
#include <string>
namespace util 
{
    using namespace std;
    auto shiftUp = [](char letter, int shift) { return letter + shift; };
    auto shiftDown = [](char letter, int shift) { return letter - shift; };

    string ReadPhrase(string fileName) 
    {
        string phrase;
        ifstream file;
        file.open(fileName);
        if (file.is_open()) 
        {
            getline(file, phrase);
            file.close();
        }
        return phrase;
    };

    void WritePhrase(string fileName, string phrase)
    {
        ofstream file;
        file.open(fileName, ios::out);
        if (file.is_open())
        {
            file << phrase;
            file.close();
        }
    }

    template <typename F>
    char LetterShiftLowercase(char letter, int shift, F shiftFunction)
    {
        if(shiftFunction(letter, shift) < 'a')
        {
            return shiftFunction(letter, shift) + 26;
        } 
        else if(shiftFunction(letter, shift) > 'z')
        {
            return shiftFunction(letter, shift) - 26;
        }
        else 
        {
            return shiftFunction(letter, shift);
        }
    }

    template <typename G>
    char LetterShift(char letter, int shift, G shiftFunction)
    {
        if(letter >= 'A' && letter <= 'Z')
        {
            return LetterShiftUppercase(letter, shift, shiftFunction);
        }
        else if(letter >= 'a' && letter <= 'z')
        {
            return LetterShiftLowercase(letter, shift, shiftFunction);
        }
        else if(letter >= '0' && letter <= '9')
        {
            return NumberShift(letter, shift, shiftFunction);
        }
        else
        {
            return letter;
        }
    }

    template <typename H>
    char NumberShift(char number, int shift, H shiftFunction)
    {
        if(shiftFunction(number, shift) < '0')
        {
            return shiftFunction(number, shift) + 10;
        }
        else if(shiftFunction(number, shift) > '9')
        {
            return shiftFunction(number, shift) - 10;
        }
        else
        {
            return shiftFunction(number, shift);
        }
    }

    template <typename I>
    char LetterShiftUppercase(char letter, int shift, I shiftFunction)
    {

        if(shiftFunction(letter, shift) < 'A')
        {
            return shiftFunction(letter, shift) + 26;
        } 
        else if(shiftFunction(letter, shift) > 'Z')
        {
            return shiftFunction(letter, shift) - 26;
        }
        else 
        {
            return shiftFunction(letter, shift);
        }
    }

}

std::string ApplyCaesarCyphre(std::string phrase)
{
    std::string cyphredPhrase = " ";
    for (int i = 0; i < phrase.size(); i++)
    {
        if(phrase[i] == ' ')
        {
            cyphredPhrase += ' ';
            continue;
        }
        cyphredPhrase+= util::LetterShift(phrase[i], 3, util::shiftUp);
    }
    return cyphredPhrase;
}

void BruteForce(std::string cyphredPhrase)
{
    for (int i = 0; i < 26; i++)
    {
        std::string decyphredPhrase = " ";
        for (int j = 0; j < cyphredPhrase.size(); j++)
        {
            if(cyphredPhrase[j] == ' ')
            {
                decyphredPhrase += ' ';
                continue;
            }
            decyphredPhrase += util::LetterShift(cyphredPhrase[j], i, util::shiftDown);
        }
        std::cout << "Try " << i << std::endl;
        std::cout << decyphredPhrase << std::endl;
    }
}

std::string DeapplyCyphre(std::string cyphredPhrase)
{
    std::string phrase = " ";
    for (int i = 0; i < cyphredPhrase.size(); i++)
    {
        if(cyphredPhrase[i] == ' ')
        {
            phrase += ' ';
            continue;
        }
        phrase += util::LetterShift(cyphredPhrase[i], 3, util::shiftDown);
    }
    return phrase;
}
#endif /* SECURITY_H_ */
