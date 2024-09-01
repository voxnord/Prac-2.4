#include <iostream>
#include <string>
#include <Windows.h>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

string snull{ "   " };

void textfilewords()
{
    ifstream file1("C:\\Users\\knox\\source\\repos\\Prac 2.4\\src\\file1.txt");

    string word1, word2;

    getline(file1, word1);
    getline(file1, word2);

    int countWord1 = 0;
    int countWord2 = 0;
    int countAdjacent = 0;

    string prevWord, cWord;

    while (file1 >> cWord) {
       
        transform(cWord.begin(), cWord.end(), cWord.begin(), ::tolower);

        if (cWord == word1) {
            countWord1++;
            if (prevWord == word2) {
                countAdjacent++;
            }
        }

        if (cWord == word2) {
            countWord2++;
            if (prevWord == word1) {
                countAdjacent++;
            }
        }

        prevWord = cWord;
    }

    file1.close();

    cout << "Слово \"" << word1 << "\" встречается " << countWord1 << " раз." << endl;
    cout << snull << "Слово \"" << word2 << "\" встречается " << countWord2<< " раз." << endl;
    cout << snull << "Слова \"" << word1 << "\" и \"" << word2 << "\" встречаются друг за другом " << countAdjacent << " раз." << endl;
}

void textfilestrings()
{
    ifstream file1("C:\\Users\\knox\\source\\repos\\Prac 2.4\\src\\file1.txt");

    int count = 0;
    string str;

    while (getline(file1, str))
    {
        if (str.length() > 0)
        {
            string lcStr = str;

            transform(str.begin(), str.end(), str.begin(), ::tolower);

            char fCh = lcStr.front();
            char lCh = lcStr.back();

            if (lCh == fCh)
            {
                count++;
            }
        }
    }
    file1.close();

    cout << "Число строк, которые начинаются и заканчиваются одним и тем же символом: " << count << endl;
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    SetConsoleTitle(L"Семестр 2. Практическая работа 4");

    cout << "Вариант 10\n" << endl;

    cout << "1) ";
    textfilewords();
    cout << "2) ";
    textfilestrings();

    return 0;
}
