#include <iostream>
#include <cstring>

namespace HELPERS 
{
 
    int toDigit(char ch) 
    {

        return ch - '0';

    }

}

struct Encoding
{
public:

    char symbol = 'a';
    int code = 0;

    Encoding() = default;

    Encoding(char symbol, int code): symbol(symbol), code(code) {}

};

class Dossier 
{
private:

    char* text = nullptr;
    Encoding* codingTable = nullptr;
    int countOfPairs = 0;

    void free() 
    {

        delete[] text;
        text = nullptr;

        delete[] codingTable;
        codingTable = nullptr;

        countOfPairs = 0;

    }

    void moveTo(Dossier&& other)
    {

        text = other.text;
        codingTable = other.codingTable;
        countOfPairs = other.countOfPairs;

        other.text = nullptr;
        other.codingTable = nullptr;
        other.countOfPairs = 0;

    }

    void copyFrom(const Dossier& other)
    {

        text = new char[strlen(other.text) + 1];
        strncpy(text, other.text, strlen(other.text));
        text[strlen(other.text) + 1] = '\0';

        codingTable = new Encoding[other.countOfPairs];
        countOfPairs = other.countOfPairs;

        for (int i = 0; i < other.countOfPairs; i++)
        {

            codingTable[i] = other.codingTable[i];

        }

    }

public:

    Dossier() = default;

    Dossier(const Dossier& other) 
    {

        copyFrom(other);

    }

    Dossier(const Encoding* codingTable, int countOfPairs, const char* text) 
    {

        if (!text || !codingTable || countOfPairs < 0) throw std::logic_error("Error");

        this->text = new char[strlen(text) + 1];
        strncpy(this->text, text, strlen(text));
        this->text[strlen(text) + 1] = '\0';

        this->codingTable = new Encoding[countOfPairs];
        this->countOfPairs = countOfPairs;

        for (int i = 0; i < countOfPairs; i++)
        {

            this->codingTable[i] = codingTable[i];

        }

    }

    Dossier(Dossier&& other) noexcept
    {

        moveTo(std::move(other));

    }

    Dossier& operator = (const Dossier& other)
    {

        if (this != &other) 
        {

            free();
            copyFrom(other);

        }

        return *this;

    }

    Dossier& operator = (Dossier&& other) noexcept
    {

        if (this != &other)
        {

            free();
            moveTo(std::move(other));

        }

        return *this;

    }

    ~Dossier() 
    {

        free();

    }

    friend bool operator && (const Dossier& d1, const Dossier& d2) 
    {

        for (int i = 0; i < d1.countOfPairs; i++)
        {

            for (int j = 0; j < d2.countOfPairs; j++)
            {

                if (d1.codingTable[i].symbol == d2.codingTable[j].symbol) 
                {

                    if (d1.codingTable[i].code == d2.codingTable[j].code) return false;
                    break;

                }

            }

        }

        return true;

    }

    friend Dossier operator + (const Dossier& d1, const Dossier& d2)
    {

        if (!(d1 && d2)) return Dossier();

        Dossier result(d1);

        delete[] result.text;
        result.text = new char[strlen(d1.text) + strlen(d2.text) + 1];
        strncpy(result.text, d1.text, strlen(d1.text));
        strncat(result.text, d2.text, strlen(d2.text));
        result.text[strlen(d1.text) + strlen(d2.text)] = '\0';

        return result;

    }

    void printText() const 
    {

        char* newData = new char[strlen(text) + 1];
        strncpy(newData, text, strlen(text));
        newData[strlen(text)] = '\0';

        int iter = strlen(text);

        for (int i = 0; i < countOfPairs; i++)
        {

            int currentCode = codingTable[i].code;
            char currentSymbol = codingTable[i].symbol;

            for (int i = 0; i < iter; i++)
            {

                if (HELPERS::toDigit(newData[i]) == currentCode) 
                {

                    newData[i] = currentSymbol;

                }

            }

        }

        std::cout << newData << std::endl;
        delete[] newData;
        newData = nullptr;

    }

};

int main() 
{
    
    Encoding table1[] = 
    {

        {'A', 1},
        {'B', 2},
        {'C', 3},

    };

    int countOfPairs1 = sizeof(table1) / sizeof(table1[0]);
    const char* coded1 = "12321";
    Dossier d1(table1, countOfPairs1, coded1);
    d1.printText();   

    Encoding table2[] = 
    {

        {'X', 4},
        {'Y', 5},

    };

    int countOfPairs2 = sizeof(table2) / sizeof(table2[0]);
    const char* coded2 = "454";
    Dossier d2(table2, countOfPairs2, coded2);
    d2.printText();  

    bool compat = (d1 && d2);
    std::cout << std::boolalpha << compat << std::endl;

    if (compat)
    {

        Dossier d3 = d1 + d2;
        d3.printText();

    }
    else
    {

        std::cout << "Error" << std::endl;

    }

    return 0;
}

