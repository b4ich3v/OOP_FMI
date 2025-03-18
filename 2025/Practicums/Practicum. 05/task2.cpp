#include <iostream>
#include <cstring>

struct Item
{
public:

    char name[30] = "Default Item";
    int code = 0;

    Item() = default;

    Item(const char* name, int code)
    {

        if (name != nullptr)
        {

            strncpy(this->name, name, strlen(name));
            this->name[strlen(name)] = '\0';
            this->code = code;

        }

    }

    bool operator == (const Item& other) const
    {

        return !(strcmp(this->name, other.name)) && (this->code == other.code);

    }

    bool operator != (const Item& other) const
    {

        return !(*this == other);

    }

    void printItem() const
    {

        std::cout << name << " ";
        std::cout << code << std::endl;

    }

};

class Order
{
private:

    Item* items = nullptr;
    int countOfItems = 0;
    int capacity = 8;

    void free()
    {

        delete[] items;
        items = nullptr;
        countOfItems = 0;
        capacity = 8;

    }

    void copyFrom(const Order& other)
    {

        items = new Item[other.capacity];

        for (int i = 0; i < other.countOfItems; i++)
        {

            items[i] = other.items[i];

        }

        capacity = other.capacity;
        countOfItems = other.countOfItems;

    }

    void resize(int newCapaicty)
    {

        if (newCapaicty <= capacity) return;

        Item* newItems = new Item[newCapaicty];

        for (int i = 0; i < countOfItems; i++)
        {

            newItems[i] = items[i];

        }

        delete[] items;
        items = newItems;
        capacity = newCapaicty;

    }

public:

    Order()
    {

        countOfItems = 0;
        capacity = 8;
        items = new Item[capacity];

    }

    ~Order()
    {

        free();

    }

    Order(const Item* items, int countOfItems)
    {

        while (capacity <= countOfItems) capacity *= 2;

        this->items = new Item[capacity];
        this->countOfItems = countOfItems;

        for (int i = 0; i < countOfItems; i++)
        {

            this->items[i] = items[i];

        }

    }

    Order(const Order& other)
    {

        copyFrom(other);

    }

    Order& operator = (const Order& other)
    {

        if (this != &other)
        {

            free();
            copyFrom(other);

        }

        return *this;

    }

    void printOrder() const
    {

        if (countOfItems == 0)
        {

            std::cout << "Empty order" << std::endl;
            return;

        }

        for (int i = 0; i < countOfItems; i++)
        {

            items[i].printItem();

        }

        std::cout << std::endl;

    }

    void addItem(const Item& item)
    {

        if (countOfItems == capacity) resize(capacity * 2);

        items[countOfItems] = item;
        countOfItems += 1;

    }

    void removeItem(const Item& item)
    {

        for (int i = 0; i < countOfItems; i++)
        {

            if (items[i] == item)
            {

                std::swap(items[i], items[countOfItems - 1]);
                countOfItems -= 1;
                break;

            }

        }

    }

    void cancel()
    {

        while (countOfItems)
        {

            removeItem(items[0]);

        }

    }

};

int main()
{

    Item item1 = { "Yoan", 10 };
    Item item2 = { "Ivo", 11 };
    Item item3 = { "Koki", 12 };
    Item item4 = { "Ilian", 13 };

    Item item5 = { "DA", -1 };

    Item* items = new Item[4];
    items[0] = item1;
    items[1] = item2;
    items[2] = item3;
    items[3] = item4;

    Order order(items, 4);
    order.printOrder();

    order.addItem(item5);
    order.printOrder();

    order.cancel();
    order.printOrder();

    delete[] items;
    return 0;

}
