#include <iostream>
#include <algorithm> 
#include <cstring> 

namespace HELPERS
{

    const int MAX_BUFFER_SIZE = 1024;

    char toChar(int digit) 
    {

        return digit + '0';

    }

    int countOfDigits(int number) 
    {

        if (!number) return 1;

        int counter = 0;
        
        while (number)
        {

            counter += 1;
            number /= 10;

        }

        return counter;

    }

    void reverseStr(char* ptr, int count) 
    {

        for (int i = 0; i < count / 2; i++)
        {

            std::swap(ptr[i], ptr[count - i - 1]);

        }

    }

}

struct Term
{
public:

    int value = 0;
    bool used = false;
};

class Polynom
{
private:

    Term* terms = nullptr;
    int degree = 0;
    int capacity = 8;

    void copyFrom(const Polynom& other)
    {

        this->terms = new Term[other.capacity];
        this->capacity = other.capacity; 
        this->degree = other.degree;

        for (int i = 0; i < degree; i++)
        {

            this->terms[i] = other.terms[i];

        }

    }

    void free()
    {

        delete[] terms;
        terms = nullptr;
        degree = 0;
        capacity = 8;

    }

    void resize(int newCapacity)
    {

        if (newCapacity <= capacity) return;
        Term* newTerms = new Term[newCapacity];

        for (int i = 0; i < degree; i++)
        {

            newTerms[i] = terms[i];

        }

        delete[] terms;
        terms = newTerms;
        capacity = newCapacity;

    }

    void shiftLeft()
    {

        if (degree < 2)
        {
            
            degree = 0;
            return;

        }

        for (int i = 0; i < degree - 1; i++)  
        {

            int multNumber = i + 1;
            terms[i].value = terms[i + 1].value * multNumber;
            terms[i].used = terms[i + 1].used;

        }

        degree -= 1;

    }

    char* makeStr() const 
    {

        char* result = new char[HELPERS::MAX_BUFFER_SIZE];
        int currentIndex = 0;

        for (int i = 0; i < degree; i++)
        {

            result[currentIndex++] = '(';
            int currentCountOfDigitsForNumber = HELPERS::countOfDigits(terms[i].value);
            int copyOfCurrentNumber = terms[i].value;
            char* ptr = result;
            ptr += currentIndex;

            for (int j = 0; j < currentCountOfDigitsForNumber; j++)
            {

                int currentDigit = copyOfCurrentNumber % 10;
                result[currentIndex++] = HELPERS::toChar(currentDigit);
                copyOfCurrentNumber /= 10;

            }

            HELPERS::reverseStr(ptr, currentCountOfDigitsForNumber);
            result[currentIndex++] = ')';
            result[currentIndex++] = '^';
            result[currentIndex++] = HELPERS::toChar(i);
            result[currentIndex++] = '+';

        }

        if(result[currentIndex - 1] == '+') result[currentIndex - 1] = '\0';
        else result[currentIndex] = '\0';
        
        return result;

    }

public:

    Polynom()
    {

        capacity = 8;
        degree = 4;
        terms = new Term[capacity];

    }

    Polynom(const Polynom& other)
    {

        copyFrom(other);

    }

    Polynom(const Term* terms, int degree)
    {

        capacity = 8;
        while (capacity < degree)  capacity *= 2;
           

        this->terms = new Term[capacity];
        this->degree = degree;

        for (int i = 0; i < degree; i++)
        {

            this->terms[i] = terms[i];

        }

    }

    Polynom& operator = (const Polynom& other)
    {

        if (this != &other)
        {

            free();
            copyFrom(other);

        }

        return *this;

    }

    ~Polynom()
    {

        free();

    }

    const int& operator [] (int index) const
    {

        if (index < 0 || index >= degree) throw std::logic_error("Error");
        return terms[index].value;

    }

    int& operator [] (int index)
    {

        if (index < 0 || index >= degree) throw std::logic_error("Error");
        return terms[index].value;

    }

    int operator () (int param) const 
    {

        int result = 0;

        for (int i = 0; i < degree; i++)
        {

            if (terms[i].used) 
            {
                    
                result += terms[i].value * param;
            
            }

        }

        return result;

    }

    Polynom& operator += (const Polynom& other)
    {

        degree = std::max(degree, other.degree);
        capacity = std::max(capacity, other.capacity);
        resize(capacity);

        for (int i = 0; i < degree; i++)
        {

            terms[i].value += other.terms[i].value;

        }

        return *this;

    }

    Polynom& operator -= (const Polynom& other)
    {

        degree = std::max(degree, other.degree);
        capacity = std::max(capacity, other.capacity);
        resize(capacity);

        for (int i = 0; i < degree; i++)
        {

            terms[i].value -= other.terms[i].value;

        }

        return *this;

    }

    friend std::ostream& operator << (std::ostream& os, const Polynom& p)
    {

        for (int i = 0; i < p.degree; i++)
        {

            if (p.terms[i].used)
            {

                os << p.terms[i].value << " ";

            }

        }

        return os;

    }

    friend std::istream& operator >> (std::istream& is, Polynom& p)
    {

        for (int i = 0; i < p.degree; i++)
        {

            if (p.terms[i].used)
            {

                is >> p.terms[i].value;
            }

        }

        return is;

    }

    friend Polynom operator ~ (const Polynom& p)
    {

        Polynom result(p);
        result.shiftLeft();
        return result;

    }

    friend bool operator == (const Polynom& p1, const Polynom& p2)
    {

        char* ptr1 = p1.makeStr();
        char* ptr2 = p2.makeStr();

        bool pred = strcmp(ptr1, ptr2) == 0;

        delete[] ptr1;
        delete[] ptr2;

        return pred;

    }

    friend bool operator != (const Polynom& p1, const Polynom& p2)
    {

        return !(p1 == p2);

    }

    friend bool operator > (const Polynom& p1, const Polynom& p2)
    {

        char* ptr1 = p1.makeStr();
        char* ptr2 = p2.makeStr();

        bool pred = strcmp(ptr1, ptr2) > 0;

        delete[] ptr1;
        delete[] ptr2;

        return pred;

    }

    friend bool operator <= (const Polynom& p1, const Polynom& p2)
    {

        return !(p1 > p2);

    }

    friend bool operator < (const Polynom& p1, const Polynom& p2)
    {

        char* ptr1 = p1.makeStr();
        char* ptr2 = p2.makeStr();

        bool pred = strcmp(ptr1, ptr2) < 0;

        delete[] ptr1;
        delete[] ptr2;

        return pred;

    }

    friend bool operator >= (const Polynom& p1, const Polynom& p2)
    {

        return !(p1 < p2);

    }

    void printInStrVariant() const 
    {

        char* str = makeStr();
        std::cout << str << std::endl;
        delete[] str;

    }

};

int main()
{

    Term* terms1 = new Term[5];
    Term* terms2 = new Term[3];

    terms1[0] = { 1, true };
    terms1[1] = { 21, true };
    terms1[2] = { 2, true };
    terms1[3] = { 7, true };
    terms1[4] = { 10, true };

    terms2[0] = { -1, true };
    terms2[1] = { -11, true };
    terms2[2] = { 27, true };

    Polynom p1(terms1, 5);
    Polynom p2(terms2, 3);

    p1 += p2;

    std::cout << p1 << std::endl;
    std::cout << (~p1) << std::endl;
    std::cout << (p1 == p2) << std::endl;
    std::cout << (p1 > p2) << std::endl;

    p1.printInStrVariant();

    delete[] terms1;
    delete[] terms2;
    return 0;

}
