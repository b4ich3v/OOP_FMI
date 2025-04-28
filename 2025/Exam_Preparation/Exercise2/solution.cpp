#include <iostream>
#include <cstring>

class Relation;
std::ostream& operator<<(std::ostream& os, const Relation& r);

struct historyComposition 
{
public:

    const Relation* r1;
    const char* separator = ", which";
    const Relation* r2;

    historyComposition(const Relation* r1, const Relation* r2, 
        const char* separator = ", which"): r1(r1), r2(r2), separator(separator) {}

    void print() const 
    {

        std::cout << *r1;
        std::cout << separator << " ";
        std::cout << *r2;

    }

};

class Relation 
{
private:

    historyComposition* history = nullptr;

    int subject = 0;
    int object = 0;
    char* relation = nullptr;
    
    void free() 
    {

        delete[] relation;
        relation = nullptr;

        delete  history;
        history = nullptr;

        subject = 0;
        object = 0;

    }

    void copyFrom(const Relation& other) 
    {

        this->relation = new char[strlen(other.relation) + 1];
        strncpy(this->relation, other.relation, strlen(other.relation));
        this->relation[strlen(other.relation)] = '\0';

        this->subject = other.subject;
        this->object = other.object;
        this->history = other.history;

    }

    void moveTo(Relation&& other) 
    {

        this->relation = other.relation;
        this->subject = other.subject;
        this->object = other.object;
        this->history = other.history;

        other.relation = nullptr;
        other.subject = 0;
        other.object = 0;
        other.history = nullptr;

    }

public:

    Relation() = default;

    Relation(const char* relation, int subject, int object) 
    {

        if (!relation) throw std::logic_error("Error");

        this->relation = new char[strlen(relation) + 1];
        strncpy(this->relation, relation, strlen(relation));
        this->relation[strlen(relation)] = '\0';

        this->subject = subject;
        this->object = object;
        this->history = nullptr;

    }

    Relation(const Relation& other) 
    {

        copyFrom(other);

    }

    Relation(Relation&& other) noexcept 
    {

        moveTo(std::move(other));

    }

    Relation& operator = (const Relation& other) 
    {

        if (this != &other) 
        {

            free();
            copyFrom(other);

        }

        return *this;

    }

    Relation& operator = (Relation&& other) noexcept
    {

        if (this != &other)
        {

            free();
            moveTo(std::move(other));

        }

        return *this;

    }

    ~Relation() 
    {

        free();

    }

    friend std::ostream& operator<<(std::ostream& os, const Relation& r) 
    {

        os << r.subject << " " << r.relation << " " << r.object;

        if (r.history)
        {

            os << " ";
            r.history->print();

        }

        return os;

    }

    friend Relation operator*(const Relation& r1, const Relation& r2)
    {
        
        if (r1.object != r2.subject)  return Relation(r1);
        
        Relation result(r1.relation, r1.subject, r2.object);
        result.history = new historyComposition(&r1, &r2);
        return result;

    }

};

int main() 
{

    Relation r1("loves", 1, 2);
    Relation r2("hates", 2, 3);

    Relation r3 = r1 * r2;
    std::cout << "r1 * r2 = " << r3 << std::endl;

    Relation r4("knows", 4, 5);
    Relation r5 = r1 * r4;
    std::cout << "r1 * r4 = " << r5 << std::endl;
 

    return 0;

}

