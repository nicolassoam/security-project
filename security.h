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
    
    // auto shiftUp    = [](char letter, int shift) { return (char)(letter + shift); };
    // auto shiftDown  = [](char letter, int shift) { return (char)(letter - shift); };

    const char mostFrequentLetters[] = "EARIOTNSLCUDPMHGBFYWKVXZJQ";

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
    
#pragma region LetterShifting

    char Shift(char letter, int shift)
    {
        return (char)(letter + shift);
    }

    char LetterShiftLowercase(char letter, int shift)
    {
        char shiftedLetter = Shift(letter, shift);
        if(shiftedLetter < 'a')
        {
            return shiftedLetter + 26;
        } 
        else if(shiftedLetter > 'z')
        {
            return shiftedLetter - 26;
        }
        else 
        {
            return shiftedLetter;
        }
    }

    char NumberShift(char number, int shift)
    {
        char shiftedNumber = Shift(number, shift);

        if(shiftedNumber < '0')
        {
            return shiftedNumber + 10;
        }
        else if(shiftedNumber > '9')
        {
            return shiftedNumber - 10;
        }
        else
        {
            return shiftedNumber;
        }
    }


    char LetterShiftUppercase(char letter, int shift)
    {
        char shiftedLetter = Shift(letter, shift);
        if(shiftedLetter < 'A')
        {
            return shiftedLetter + 26;
        } 
        else if(shiftedLetter > 'Z')
        {
            return shiftedLetter - 26;
        }
        else 
        {
            return shiftedLetter;
        }
    }

    char LetterShift(char letter, int shift)
    {
        if(letter >= 'A' && letter <= 'Z')
        {
            return LetterShiftUppercase(letter, shift);
        }
        else if(letter >= 'a' && letter <= 'z')
        {
            return LetterShiftLowercase(letter, shift);
        }
        else if(letter >= '0' && letter <= '9')
        {
            return NumberShift(letter, shift);
        }
        else
        {
            return letter;
        }
    }
#pragma endregion LetterShifting

}

std::string ApplyCaesarCipher(std::string phrase)
{
    std::string cipheredPhrase = " ";
    for (int i = 0; i < phrase.size(); i++)
    {
        if(phrase[i] == ' ')
        {
            cipheredPhrase += ' ';
            continue;
        }
        cipheredPhrase+= util::LetterShift(phrase[i], 3);
    }
    return cipheredPhrase;
}

void BruteForce(std::string cipheredPhrase)
{
    for (int i = 1; i <= 26; i++)
    {
        std::string decipheredPhrase = " ";
        for (int j = 0; j < cipheredPhrase.size(); j++)
        {
            if(cipheredPhrase[j] == ' ')
            {
                decipheredPhrase += ' ';
                continue;
            }
            decipheredPhrase += util::LetterShift(cipheredPhrase[j], -i);
        }
        std::cout << "Try " << i << std::endl;
        std::cout << decipheredPhrase << std::endl;
    }
}

std::string DeapplyCipher(std::string cipheredPhrase)
{
    std::string phrase = " ";
    for (int i = 0; i < cipheredPhrase.size(); i++)
    {
        if(cipheredPhrase[i] == ' ')
        {
            phrase += ' ';
            continue;
        }
        phrase += util::LetterShift(cipheredPhrase[i], -3);
    }
    return phrase;
}
#endif /* SECURITY_H_ */
