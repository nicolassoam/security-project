#ifndef SECURITY_H_
#define SECURITY_H_

#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <sstream>
#include <string>
#include "config.h"
namespace util 
{
    using namespace std;
    
    // auto shiftUp    = [](char letter, int shift) { return (char)(letter + shift); };
    // auto shiftDown  = [](char letter, int shift) { return (char)(letter - shift); };
    map<char, int> letterFrequency;
    priority_queue<pair<int, char>> sortedMostFrequent;
    const char mostFrequentLetters[] = "EARIOTNSLCUDPMHGBFYWKVXZJQ";
    map<char, map<char,char>> vigenereTable;

    void VigenereTable()
    {
        for(int i = 0; i < 26; i++)
        {
             //A = ABCDEFGHIJKLMNOPQRSTUVWXYZ
             //B = BCDEFGHIJKLMNOPQRSTUVWXYZA
            map<char, char> row;
            vigenereTable.insert(pair<char,map<char,char>>('A' + i, row));
            for(int j = 0; j < 26; j++)
            {
                vigenereTable['A' + i].insert(pair<char,char>('A' + j, 'A' + (j + i) % 26));
            }
        }

        for(int k = 0; k < 26; k++)
        {
            map<char, char> row;
            vigenereTable.insert(pair<char,map<char,char>>('a' + k, row));
            for(int l = 0; l < 26; l++)
            {
                vigenereTable['a' + k].insert(pair<char,char>('a' + l, 'a' + (l + k) % 26));
            }
        }
    }

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

    vector<string> FullText(string filename)
    {
        vector<string> text;
        ifstream file;
        file.open(filename);
        if (file.is_open())
        {
            string line;
            while (getline(file, line))
            {
                text.push_back(line);
            }
            file.close();
        }
        return text;
    }
    
    char GetKeyFromMap(map<char,char>m,char value)
    {
        for(auto it = m.begin(); it != m.end(); it++)
        {
            if(it->second == value)
            {
                return it->first;
            }
        }
        return ' ';

    }

    void WritePhrase(string fileName, string phrase)
    {
        ofstream file;
        file.open(fileName, ios::out);
        if (file.is_open())
        {
            file << phrase;
            file.close();
        }
        std::cout << "Frase escrita: " << phrase << std::endl;
        std::cout << "Output no arquivo " << fileName << std::endl;
    }

    void WriteText(string fileName, vector<string>text)
    {
        ofstream file;
        file.open(fileName, ios::out);
        if (file.is_open())
        {
            for (int i = 0; i < text.size(); i++)
            {
                file << text[i] << endl;
            }
            file.close();
        }
    }

    map<char,char> RankEquivalence(priority_queue<pair<int,char>> letterFrequency)
    {
        map<char, char> equivalence;
        int i = 0;
        std::cout << "equivalence: " << std::endl; 
        while (!letterFrequency.empty())
        {
            pair<int,char> topElement = letterFrequency.top();
            std::cout << topElement.second << " : " << sortedMostFrequent.top().second << std::endl;
            equivalence[topElement.second] = sortedMostFrequent.top().second;
            sortedMostFrequent.pop();
            letterFrequency.pop();
        }
        return equivalence;
    }

    void LetterFrequencyPT(vector<string> text)
    {
        for (int i = 0; i < text.size(); i++)
        {
            for (int j = 0; j < text[i].size(); j++)
            {
                if(text[i][j] == ',' || text[i][j] == '.' || text[i][j] == ';')
                {
                    continue;
                }
                if(letterFrequency.find(text[i][j]) == letterFrequency.end())
                {
                    letterFrequency[text[i][j]] = 1;
                }
                else
                {
                    letterFrequency[text[i][j]]++;
                }
            }
        }

        //sort 
    
        for (auto it = letterFrequency.begin(); it != letterFrequency.end(); it++)
        {
            cout << it->first << " : " << it->second << endl;
            sortedMostFrequent.push(make_pair(it->second, it->first));
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

#pragma region CaesarCipher
//Encriptação com cifra de Caesar
std::string ApplyCaesarCipher(std::string phrase)
{
    std::string cipheredPhrase = "";
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

//Decriptação da cifra de Caesar
std::string DeapplyCipher(std::string cipheredPhrase)
{
    std::string phrase = "";
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
#pragma endregion CaesarCipher

#pragma region Vignere

std::string ApplyVigenereCipher(std::string phrase, std::string key)
{
    std::string cipheredPhrase = "";
    
    for(int i = 0; i < phrase.size(); i++)
    {
        if(phrase[i] == ' ' || phrase[i] == ',' || phrase[i] == '.' || phrase[i] == ';')
        {
            cipheredPhrase += phrase[i];
            continue;
        }
        cipheredPhrase += util::vigenereTable[key[i]][phrase[i]];
    }

    return cipheredPhrase;
}

std::string DeapplyVigenereCipher(std::string phrase, std::string key)
{
    std::string decipheredPhrase = "";
    
    //inverse of encryption
    for(int i = 0; i < phrase.size(); i++)
    {
        if(phrase[i] == ' ' || phrase[i] == ',' || phrase[i] == '.' || phrase[i] == ';')
        {
            decipheredPhrase += phrase[i];
            continue;
        }
        //get column label
        decipheredPhrase += util::GetKeyFromMap(util::vigenereTable[key[i]], phrase[i]);
    }
    return decipheredPhrase;
}
#pragma endregion Vignere


#pragma region RailFencer
std::string ApplyRailFenceCipher(std::string text, int key)
{
    // create the matrix to cipher plain text
    // key = rows , length(text) = columns
    char ** rail = new char*[key];

    for(int i = 0; i < key; i++)
    {
        rail[i] = new char[text.length()];
    }
 
    // filling the rail matrix to distinguish filled
    // spaces from blank ones
    for (int i=0; i < key; i++)
        for (int j = 0; j < text.length(); j++)
            rail[i][j] = '\n';
 
    // to find the direction
    bool dir_down = false;
    int row = 0, col = 0;
 
    for (int i=0; i < text.length(); i++)
    {
        // check the direction of flow
        // reverse the direction if we've just
        // filled the top or bottom rail
        if (row == 0 || row == key-1)
            dir_down = !dir_down;
 
        // fill the corresponding alphabet
        rail[row][col++] = text[i];
 
        // find the next row using direction flag
        dir_down?row++ : row--;
    }
 
    //now we can construct the cipher using the rail matrix
    std::string result;
    for (int i=0; i < key; i++)
        for (int j=0; j < text.length(); j++)
            if (rail[i][j]!='\n')
                result.push_back(rail[i][j]);
 
    return result;
}
#pragma endregion RailFencer

// Decriptação de cifra de Caesar utilizando força bruta
void BruteForce(std::string cipheredPhrase)
{
    for (int i = 1; i <= 26; i++)
    {
        std::string decipheredPhrase = "";
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

void MostFrequent(std::string cipheredPhrase)
{
    std::map<char, int> letterFrequency;
    for (int i = 0; i < cipheredPhrase.size(); i++)
    {
        if(letterFrequency.find(cipheredPhrase[i]) == letterFrequency.end())
        {
            letterFrequency[cipheredPhrase[i]] = 1;
        }
        else
        {
            letterFrequency[cipheredPhrase[i]]++;
        }
    }
    //sort letterFrequency
    std::priority_queue<std::pair<int,char>> sortedLetterFrequency;
    
    for(auto it = letterFrequency.begin(); it != letterFrequency.end(); it++)
    {
        std::cout << it->second << " : " << it->first << std::endl;
        sortedLetterFrequency.push(std::make_pair(it->second, it->first));
    }
    //swap most frequent char from phrase with most frequent char from language
    std::map<char,char> equivalence = util::RankEquivalence(sortedLetterFrequency);
    std::string decipheredPhrase = "";

    for(int i = 0; i < cipheredPhrase.size(); i++)
    {
        
        decipheredPhrase += equivalence[cipheredPhrase[i]];

    }

    std::cout << decipheredPhrase << std::endl;
}


void MostFrequentBig(std::vector<std::string> cipheredPhrase)
{
    std::map<char, int> letterFrequency;
    for (int i = 0; i < cipheredPhrase.size(); i++)
    {
        std::string phrase = cipheredPhrase[i];
        for(int j = 0; j < phrase.size(); j++)
        {
            if(phrase[j] == ',' || phrase[j] == '.' || phrase[j] == ';')
            {
                continue;
            }

            if(letterFrequency.find(phrase[j]) == letterFrequency.end())
            {
                letterFrequency[phrase[j]] = 1;
            }
            else
            {
                letterFrequency[phrase[j]]++;
            }
        }
    }
    //sort letterFrequency
    std::priority_queue<std::pair<int,char>> sortedLetterFrequency;
    
    for(auto it = letterFrequency.begin(); it != letterFrequency.end(); it++)
    {
        std::cout << it->second << " : " << it->first << std::endl;
        sortedLetterFrequency.push(std::make_pair(it->second, it->first));
    }
    //swap most frequent char from phrase with most frequent char from language
    std::map<char,char> equivalence = util::RankEquivalence(sortedLetterFrequency);
    std::vector<std::string> decipheredPhrase;
    std::string dummy = "";
    for(int i = 0; i < cipheredPhrase.size(); i++)
    {
        dummy = "";
        for(int j = 0; j < cipheredPhrase[i].size(); j++)
        {
            dummy += equivalence[cipheredPhrase[i][j]];
        }
        decipheredPhrase.push_back(dummy);
    }

    // std::cout << decipheredPhrase[800] << std::endl;
    util::WriteText((std::string)OUTPUT_DIR + "/textoDecifrado.txt", decipheredPhrase);
}


#endif /* SECURITY_H_ */
