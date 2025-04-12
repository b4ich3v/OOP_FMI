#include <iostream>
#include <algorithm> 

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

    delete[] terms1;
    delete[] terms2;
    return 0;

}

