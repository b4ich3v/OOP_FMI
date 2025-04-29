#include <iostream>
#include <cstring>

class Expression 
{
public:

    virtual double getValue() const = 0;

    virtual void print() const = 0;

    virtual ~Expression() = default;

};

class Constant: public Expression
{
private:

    double value = 0;

public:

    Constant(double value): value(value) {}

    void print() const override 
    {

        std::cout << value;

    }

    double getValue() const override
    {

        return value;

    }

};

class Variable: public Expression
{
private:

    char* name = nullptr;
    double value = 0;

    void free() 
    {

        delete[] name;
        name = nullptr;
        value = 0;

    }

    void copyFrom(const Variable& other) 
    {

        this->name = new char[strlen(other.name) + 1];
        strncpy(this->name, other.name, strlen(other.name));
        this->name[strlen(other.name)] = '\0';

        this->value = other.value;

    }

    void moveTo(Variable&& other) 
    {

        this->name = other.name;
        this->value = other.value;

        other.name = nullptr;
        other.value = 0;

    }

public:

    Variable(const char* name, double value): Expression()
    {

        if (this->name == name || !name) throw std::logic_error("Error");

        this->name = new char[strlen(name) + 1];
        strncpy(this->name, name, strlen(name));
        this->name[strlen(name)] = '\0';

        setValue(value);

    }

    Variable(const Variable& other): Expression(other)
    {

        copyFrom(other);

    }

    Variable(Variable&& other) noexcept: Expression(std::move(other))
    {

        moveTo(std::move(other));

    }

    Variable& operator = (const Variable& other)
    {

        if (this != &other) 
        {

            free();
            copyFrom(other);
            Expression::operator=(other);

        }

        return *this;

    }

    Variable& operator = (Variable&& other) noexcept
    {

        if (this != &other)
        {

            free();
            moveTo(std::move(other));
            Expression::operator=(std::move(other));

        }

        return *this;

    }

    ~Variable() 
    {

        free();

    }

    void print() const override
    {

        std::cout << name;

    }

    double getValue() const override
    {

        return value;

    }

    void setValue(double value) 
    {

        this->value = value;

    }

};

class Sum: public Expression
{
private:

    const Expression* left = nullptr;
    const Expression* right = nullptr;

public:

    Sum(const Expression* e1, const Expression* e2): left(e1), right(e2) {}

    void print() const override
    {

        std::cout << "(";
        left->print();
        std::cout << "+";
        right->print();
        std::cout << ")";

    }

    double getValue() const override
    {

        return left->getValue() + right->getValue();

    }

};

class Product: public Expression
{
private:

    const Expression* left = nullptr;
    const Expression* right = nullptr;

public:

    Product(const Expression* e1, const Expression* e2) : left(e1), right(e2) {}

    void print() const override
    {

        std::cout << "(";
        left->print();
        std::cout << "*";
        right->print();
        std::cout << ")";

    }

    double getValue() const override
    {

        return left->getValue() * right->getValue();

    }

};

int main() 
{

    Variable v0("number0", 100);
    Variable v1("number1", 1);
    Variable v2("number2", 14);
    Variable v3("number3", 7);

    Constant c0(0);
    Constant c1(1);
    Constant c2(2);

    Sum sum1(&v0, &v1);
    Sum sum2(&v0, &v3);
    Sum sum3(&v2, &v3);

    Product product1(&v0, &v1);
    Product product2(&v0, &v3);
    Product product3(&v2, &v3);

    Variable cVar("complicated", 47);
    Constant cCon(0);
    Sum cSum(&cVar, &cCon);
    Product cP(&cSum, &v1);

    Sum complicatedSum(&cP, & v2);
    complicatedSum.print();


    return 0;

}

