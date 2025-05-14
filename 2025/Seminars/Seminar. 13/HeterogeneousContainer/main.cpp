#include <iostream>

struct Animal
{
public:

    virtual ~Animal() = default;                  

    virtual Animal* clone() const = 0;            

    virtual void speak() const 
    {

        std::cout << "Some generic animal sound" << std::endl;

    }

};

struct Dog: public Animal 
{
public:

    Dog* clone() const override 
    {

        return new Dog(*this);

    }

    void speak() const override 
    {

        std::cout << "Woof!" << std::endl;

    }

};

struct Cat: public Animal 
{
public:

    Cat* clone() const override 
    {

        return new Cat(*this);

    }

    void speak() const override 
    {

        std::cout << "Meow!" << std::endl;

    }

};

int main() 
{
    
    Animal* original = new Dog();
    Animal* copy = original->clone();

    original->speak();  
    copy->speak();      

    delete original;
    delete copy;

    original = new Cat();
    copy = original->clone();
    original->speak();  
    copy->speak();      
    delete original;
    delete copy;

    return 0;

}
