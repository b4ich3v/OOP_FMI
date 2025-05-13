#include <iostream>
#include "MyString.h"
#include "MyVector.hpp"

struct Size 
{
public:

    int height = 0;
    int width = 0;

    explicit Size(): height(0), width(0) {}

    explicit Size(int height, int width): height(height), width(width) {}

};

struct Point
{
public:
    
    int x = 0;
    int y = 0;

    explicit Point(): x(0), y(0) {}

    explicit Point(int x = 0, int y = 0): x(x), y(y) {}

};

class Control 
{
protected:

    Size size;
    Point location;

    void setNewSize(const Size& newSize) 
    {

        this->size = newSize;

    }

    void setNewLocation(const Point& location)
    {

        this->location = location;

    }

public:

    Control(int height, int width, const Point& location) : size(height, width), location(location) {}

    virtual void setDataDialog() = 0;

    virtual Control* clone() const = 0;

    virtual void resize(const Size& newSize) = 0;

    virtual void setLocation(const Point& newLocation) = 0;

    virtual ~Control() = default;

};

class TextBox: public Control 
{
private:

    MyString text;

public:

    TextBox(int height, int width, const MyString& text, const Point& location): Control(height, width, location)
    {

        this->text = text;

    }

    void setDataDialog() override 
    {

        std::cout << "Current text: " << text << std::endl;
        std::cout << "Enter new text: ";

        MyString input;
        std::cin >> input;

        this->text = input;

    }

    Control* clone() const override 
    {

        return new TextBox(*this);

    }

    void resize(const Size& newSize) override 
    {

        setNewSize(newSize);

    }

    void setLocation(const Point& newLocation) override 
    {

        setNewLocation(newLocation);

    }

};

class CheckBox: public Control 
{

    MyString text;
    bool checked = false;

public:

    CheckBox(int height, int width, const MyString& text, bool checked, const Point& location): Control(height, width, location) 
    {

        setText(text);
        this->checked = checked;

    }

    void setDataDialog() override 
    {

        std::cout << "Checkbox is currently " << (checked ? "checked" : "unchecked") << std::endl;
        std::cout << "Enter 1 to check, 0 to uncheck: ";

        int input;
        std::cin >> input;

        this->checked = (input != 0);

    }

    Control* clone() const override 
    {

        return new CheckBox(*this);

    }

    void resize(const Size& newSize) override 
    {

        setNewSize(newSize);

    }

    void setLocation(const Point& newLocation) override 
    {

        setNewLocation(newLocation);

    }

    void setText(const MyString& newText) 
    {

        this->text = text;

    }

};

class RadioButton: public Control 
{

    MyVector<MyString> options;
    size_t selectedIndex;

public:

    RadioButton(int height, int width, const MyVector<MyString>& options, size_t selectedIndex, Point location) :
        Control(height, width, location)
    {

        this->options = options;
        this->selectedIndex = selectedIndex;

    }

    void setDataDialog() override 
    {

        std::cout << "Choose one of the following options:" << std::endl;

        for (size_t i = 0; i < options.size(); i++)
        {

            std::cout << i << ": " << options[i] << (i == selectedIndex ? " [selected]" : "") << std::endl;

        }

        std::cout << "Enter index of selected option: ";
        size_t input;
        std::cin >> input;

        if (input < options.size()) 
        {

            this->selectedIndex = input;

        }
        else 
        {

            std::cout << "Invalid index!" << std::endl;

        }

    }

    Control* clone() const override 
    {

        return new RadioButton(*this);

    }

    void resize(const Size& newSize) override 
    {

        setNewSize(newSize);

    }

    void setLocation(const Point& newLocation) override 
    {

        setNewLocation(newLocation);

    }

};

class Form 
{
private:

    MyString name;
    Size size;
    MyVector<Control*> controls;

public:

    Form(const MyString& name, int height, int width) 
    {

        this->name = name;
        this->size = Size(height, width);

    }

    Form(const Form& other) = delete;

    Form& operator = (const Form& other) = delete;

    ~Form() 
    {

        for (int i = 0; i < controls.size(); i++)
        {

            delete controls[i];
            controls[i] = nullptr;

        }

    }

    void addControl(Control* control) 
    {

        if (!control) throw std::logic_error("Error");

        controls.push_back(control);

    }

    void resizeForm(const Size& newSize) 
    {

        this->size = newSize;

        for (int i = 0; i < controls.size(); i++) 
        {

            controls[i]->resize(newSize);

        }

    }

    void moveControl(size_t index, const Point& newLocation) 
    {

        if (index < 0 || index >= controls.size()) throw std::logic_error("Error");

        controls[index]->setLocation(newLocation);

    }

    void change(size_t index) 
    {

        if (index < 0 || index >= controls.size()) throw std::logic_error("Error");

        controls[index]->setDataDialog();

    }

};

int main()
{

    Form form("MyForm", 600, 800);

    TextBox* textBox = new TextBox(50, 200, "Enter name", Point(10, 10));
    form.addControl(textBox);


    CheckBox* checkBox = new CheckBox(30, 100, "Subscribe", true, Point(20, 80));
    form.addControl(checkBox);

    MyVector<MyString> options;
    options.push_back("Red");
    options.push_back("Green");
    options.push_back("Blue");

    RadioButton* radioButton = new RadioButton(60, 300, options, 0, Point(30, 150));
    form.addControl(radioButton);

    std::cout << "=== Initial Form ===" << std::endl;
    std::cout << "1 - Change TextBox" << std::endl;
    std::cout << "2 - Change CheckBox" << std::endl;
    std::cout << "3 - Change RadioButton" << std::endl;

    int choice = 0;
    std::cout << "Select control to modify (1-3): ";
    std::cin >> choice;

    try 
    {

        form.change(choice - 1); 

    }
    catch (const std::exception& e) 
    {

        std::cerr << "Error: " << e.what() << std::endl;

    }

    return 0;

}

