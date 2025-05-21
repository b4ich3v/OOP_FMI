#include <iostream>
#include <string>
#include <cstring>

template <class T>

class MyVector
{
private:

public:

    T* data = nullptr;
    size_t sizeOfData = 0;
    size_t capacity = 8;

    void free();

    void copyFrom(const MyVector& other);

    void moveTo(MyVector&& other);

    void resize(size_t newCapacity);

public:

    MyVector();

    MyVector(const T* data, size_t sizeOfData);

    MyVector(const MyVector& other);

    MyVector(MyVector&& other) noexcept;

    MyVector& operator = (const MyVector& other);

    MyVector& operator = (MyVector&& other) noexcept;

    ~MyVector();

    const T& operator [] (size_t index) const;

    T& operator [] (size_t index);

    template<class U>

    friend std::ostream& operator << (std::ostream& os, const MyVector<U>& v);

    template<class U>

    friend std::istream& operator >> (std::istream& is, MyVector<U>& v);

    void pop_back();

    void push_back(const T& element);

    void clear();

    bool empty() const;

    size_t size() const;

};

template <class T>

void MyVector<T>::free()
{

    delete[] data;
    data = nullptr;
    sizeOfData = 0;
    capacity = 8;

}

template <class T>

void MyVector<T>::copyFrom(const MyVector& other)
{

    data = new T[other.capacity];
    sizeOfData = other.sizeOfData;
    capacity = other.capacity;

    for (size_t i = 0; i < sizeOfData; i++) data[i] = other.data[i];

}

template <class T>

void MyVector<T>::moveTo(MyVector&& other)
{

    data = other.data;
    sizeOfData = other.sizeOfData;
    capacity = other.capacity;

    other.data = nullptr;
    other.sizeOfData = 0;
    other.capacity = 8;

}

template <class T>

void MyVector<T>::resize(size_t newCapacity)
{

    if (newCapacity <= capacity) return;
    if (newCapacity < 1) newCapacity = 1;

    T* newData = new T[newCapacity]{};

    for (size_t i = 0; i < sizeOfData; i++) newData[i] = data[i];

    delete[] data;
    data = newData;
    capacity = newCapacity;

}

template <class T>

MyVector<T>::MyVector()
{

    capacity = 8;
    sizeOfData = 0;
    data = new T[capacity]{};

}

template <class T>

MyVector<T>::MyVector(const T* arr, size_t size)
    : data(nullptr), sizeOfData(size), capacity(size > 8 ? size : 8)
{

    data = new T[capacity];
    for (size_t i = 0; i < sizeOfData; i++) data[i] = arr[i];

}

template <class T>

MyVector<T>::MyVector(const MyVector& other)
{

    copyFrom(other);

}

template <class T>

MyVector<T>::MyVector(MyVector&& other) noexcept
{

    moveTo(std::move(other));

}

template <class T>

MyVector<T>& MyVector<T>::operator = (const MyVector& other)
{

    if (this != &other)
    {

        free();
        copyFrom(other);

    }

    return *this;

}

template <class T>

MyVector<T>& MyVector<T>::operator = (MyVector&& other) noexcept
{

    if (this != &other)
    {

        free();
        moveTo(std::move(other));

    }

    return *this;

}

template <class T>

MyVector<T>::~MyVector()
{

    delete[] data;

}

template <class T>

const T& MyVector<T>::operator[](size_t index) const
{

    if (index < 0 || index >= sizeOfData) throw std::out_of_range("Vector index out of range");
    return data[index];

}

template <class T>

T& MyVector<T>::operator[](size_t index)
{

    if (index < 0 || index >= sizeOfData) throw std::out_of_range("Vector index out of range");
    return data[index];

}

template <class T>

void MyVector<T>::pop_back()
{

    if (empty()) throw std::out_of_range("pop_back() on empty Vector");
    sizeOfData -= 1;

}

template <class T>

void MyVector<T>::push_back(const T& element)
{

    if (sizeOfData >= capacity) resize(capacity * 2);
    data[sizeOfData++] = element;

}

template <class T>

bool MyVector<T>::empty() const
{

    return sizeOfData == 0;

}

template <class T>

void MyVector<T>::clear()
{

    sizeOfData = 0;

}

template <class T>

size_t MyVector<T>::size() const
{

    return sizeOfData;

}

template <class T>

std::ostream& operator << (std::ostream& os, const MyVector<T>& v)
{

    os << '[';

    for (size_t i = 0; i < v.sizeOfData; i++)
    {

        os << v.data[i];
        if (i + 1 < v.sizeOfData) os << ", ";

    }

    os << ']';

    return os;

}

template <class T>

std::istream& operator >> (std::istream& is, MyVector<T>& v)
{

    size_t newSize;
    if (!(is >> newSize)) return is;

    v.free();
    v.capacity = 8;
    v.data = new T[v.capacity]{};

    while (newSize > v.capacity) v.resize(v.capacity * 2);
    v.sizeOfData = newSize;

    for (size_t i = 0; i < newSize; i++) is >> v.data[i];

    return is;

}

template <class K, class V>

struct Pair 
{
public:

	K key;
	V value;

    friend bool operator < (const Pair<K, V>& p1, const Pair<K, V>& p2) 
    {

        return p1.key < p2.key;

    }

    friend bool operator > (const Pair<K, V>& p1, const Pair<K, V>& p2)
    {

        return !(p1.key < p2.key) && p1 != p2; 

    }

    friend bool operator >= (const Pair<K, V>& p1, const Pair<K, V>& p2)
    {

        return !(p1.key < p2.key);

    }

    friend bool operator <= (const Pair<K, V>& p1, const Pair<K, V>& p2)
    {

        return (p1.key < p2.key) || p1 == p2;

    }

    friend bool operator == (const Pair<K, V>& p1, const Pair<K, V>& p2)
    {

        return p1 >= p2 && p1 <= p2;

    }

    friend bool operator != (const Pair<K, V>& p1, const Pair<K, V>& p2)
    {

        return !(p1 == p2);

    }

};

template <class K, class V>

class Dictionary
{
private:

	MyVector<Pair<K, V>> data;

public:

    Dictionary() = default;

    const V& operator [] (const K& key) const 
    {
        
        for (size_t i = 0; i < data.size(); i++) 
        {

            if (data[i].key == key)
            {

                return data[i].value;

            }

        }

        throw std::logic_error("Key not found");

    }

    V& operator [] (const K& key) 
    {
        
        for (size_t i = 0; i < data.size(); i++)
        {

            if (data[i].key == key) 
            {

                return data[i].value;

            }

        }

        data.push_back({key, V()});
        return data[data.size() - 1].value;

    }

    const K& getKeyByIndex(size_t index) const
    {

        return data[index].key;

    }

    size_t getCounOfPair() const 
    {

        return data.size();

    }

    friend std::ostream& operator << (std::ostream& os, const Dictionary& dict) 
    {

        for (int i = 0; i < dict.getCounOfPair(); i++)
        {

            os << "{";
            os << dict.getKeyByIndex(i) << " ";
            os << dict[dict.getKeyByIndex(i)] << "} ";

        }

        return os;

    }

};

class Contact
{
private:

    std::string name;
    char phoneNumber[11];
    std::string id;

public:

    Contact(const std::string& name, const std::string& id, const char* phoneNumber) :
        name(name), id(id)
    {

        strncpy(this->phoneNumber, phoneNumber, strlen(phoneNumber));
        this->phoneNumber[strlen(phoneNumber)] = '\0';

    }

    const std::string& getName() const
    {

        return name;

    }

    const std::string& getId() const
    {

        return id;

    }

    const char* getPhoneNumber() const
    {

        return phoneNumber;

    }

};

class ContactBook 
{
private:

    Dictionary<std::string, Contact*> dict1;
    Dictionary<const char*, Contact*> dict2;
    Dictionary<std::string, Contact*> dict3;

public:

    void addContact(Contact* contact) 
    {

        dict1[contact->getName()] = contact;
        dict2[contact->getPhoneNumber()] = contact;
        dict3[contact->getId()] = contact;

    }

    void removeContact(Contact* contact)
    {

        dict1[contact->getName()] = nullptr;
        dict2[contact->getPhoneNumber()] = nullptr;
        dict3[contact->getId()] = nullptr;

    }

    Contact* findContactName(const std::string& name) 
    {

        return dict1[name];

    }

    Contact* findContactNumber(const char* phoneNumber)
    {

        return dict2[phoneNumber];

    }

    Contact* findContactId(const std::string& id)
    {

        return dict3[id];

    }

    friend std::ostream& operator << (std::ostream& os, const ContactBook& book) 
    {

        int iter = book.dict1.getCounOfPair();

        for (int i = 0; i < iter; i++)
        {

            os << "{";

            if (book.dict1[book.dict1.getKeyByIndex(i)] != nullptr) 
            {

                os << book.dict1.getKeyByIndex(i);

            }

            os << ",";

            if (book.dict3[book.dict3.getKeyByIndex(i)] != nullptr)
            {

                os << book.dict3.getKeyByIndex(i);

            }

            os << ",";

            if (book.dict2[book.dict2.getKeyByIndex(i)] != nullptr)
            {

                os << book.dict2.getKeyByIndex(i);

            }

            os << "} " << std::endl;

        }

        return os;

    }

};

int main() 
{
    
    Contact c1("Yoan Baychev", "OMI0600328", "087...");
    Contact c2("Ivailo Kunchev", "OMI0600256", "081...");
    Contact c3("Ilian Zaprqnov", "OMI0600100", "086...");
    Contact c4("Kaloyan Markov", "OMI0600810", "089...");

    ContactBook book;
    book.addContact(&c1);
    book.addContact(&c2);
    book.addContact(&c3);
    book.addContact(&c4);

    std::cout << book << std::endl;
    book.removeContact(&c3);
    std::cout << book << std::endl;

    Contact* foundContact = book.findContactName("Yoan Baychev");
    std::cout << foundContact->getId();

	return 0;

}


