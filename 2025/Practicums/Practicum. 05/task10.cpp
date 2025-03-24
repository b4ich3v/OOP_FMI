#include <iostream>
#include <cstring>
#include <fstream>

namespace HELPERS 
{

	const char SEPARATOR = ',';

}

enum class Type
{

	mammal = 0,
	reptile = 1,
	fish = 2,
	bird = 3,
	amphibian = 4,
	ivertebrates = 5

};

class Animal 
{
private:

	char* name = nullptr;
	Type type = Type::amphibian;
	int age = 0;

	void setName(const char* name) 
	{

		if (!name || name == this->name) throw std::logic_error("Error");

		delete[] this->name;
		this->name = new char[strlen(name) + 1];
		strncpy(this->name, name, strlen(name));
		this->name[strlen(name)] = '\0';

	}

	void setType(Type type) 
	{

		this->type = type;

	}

	void setAge(int age) 
	{

		if (age <= 0) throw std::logic_error("Error");

		this->age = age;

	}

	void copyFrom(const Animal& other)
	{

		this->name = new char[strlen(other.name) + 1];
		strncpy(this->name, other.name, strlen(other.name));
		this->name[strlen(other.name)] = '\0';

		this->age = other.age;
		this->type = other.type;

	}

	void free()
	{

		delete[] name;
		name = nullptr;

	}

public:

	Animal() = default;

	Animal(const char* name, Type type, int age) 
	{

		setName(name);
		setType(type);
		setAge(age);

	}

	Animal(const Animal& other) 
	{

		copyFrom(other);

	}

	Animal& operator = (const Animal& other) 
	{

		if (this != &other) 
		{

			free();
			copyFrom(other);

		}

		return *this;

	}

	~Animal()
	{

		free();

	}

	const char* getName() const
	{

		return name;

	}

	int getAge() const
	{

		return age;

	}

	Type getType() const
	{

		return type;

	}

	void printAnimal() const 
	{

		std::cout << name << " ";

		switch (type)
		{

		case Type::mammal: std::cout << "mammal "; break;
		case Type::reptile: std::cout << "reptile "; break;
		case Type::fish: std::cout << "fish "; break;
		case Type::bird: std::cout << "bird "; break;
		case Type::amphibian: std::cout << "amphibian "; break;
		case Type::ivertebrates: std::cout << "ivertebrates "; break;
		default: break;
			
		}

		std::cout << age << " ";
		std::cout << std::endl;

	}

	void writeAnimalToFile(std::ofstream& file) const 
	{

		file << name;
		file << HELPERS::SEPARATOR;

		file << (int)type;
		file << HELPERS::SEPARATOR;

		file << age;
		file << std::endl;

	}

};

class Zoo 
{
private:

	Animal* animals = nullptr;
	int size = 0;
	int capacity = 8;

	void copyFrom(const Zoo& other) 
	{
		
		animals = new Animal[other.capacity];

		for (int i = 0; i < other.size; i++)
		{

			animals[i] = other.animals[i];

		}

		size = other.size;
		capacity = other.capacity;

	}

	void free() 
	{

		delete[] animals;
		animals = nullptr;

	}

	void resize(int newCapacity) 
	{

		if (newCapacity <= capacity) return;

		Animal* newAnimals = new Animal[newCapacity];

		for (int i = 0; i < size; i++)
		{

			newAnimals[i] = animals[i];

		}

		delete[] animals;
		animals = newAnimals;
		capacity = newCapacity;

	}

public:

	Zoo()
	{

		size = 0;
		capacity = 8;
		animals = new Animal[capacity];

	}

	Zoo(const Zoo& other)
	{

		copyFrom(other);

	}

	Zoo& operator = (const Zoo& other)
	{

		if (this != &other)
		{

			free();
			copyFrom(other);

		}

		return *this;

	}

	~Zoo()
	{

		free();

	}

	void addAnimal(const Animal& animal) 
	{

		if (size == capacity) resize(capacity * 2);

		animals[size] = animal;
		size += 1;

	}

	void removeAnimalByName(const char* name) 
	{

		for (int i = 0; i < size; i++)
		{

			if (!strcmp(animals[i].getName(), name)) 
			{

				std::swap(animals[i], animals[size - 1]);
				size -= 1;
				break;

			}

		}

	}

	int getCountOfAnimalsByType(Type type) const 
	{

		int counter = 0;

		for (int i = 0; i < size; i++)
		{

			if ((int)animals[i].getType() == (int)type) counter += 1;

		}

		return counter;

	}

	void printAnimals() const
	{

		for (int i = 0; i < size; i++)
		{

			animals[i].printAnimal();

		}

		std::cout << std::endl;

	}

	void writeToFile(std::ofstream& file) const
	{

		if (!file.is_open()) return;

		for (int i = 0; i < size; i++)
		{

			animals[i].writeAnimalToFile(file);

		}

	}

};

int main()
{

	Animal a1("Yoan Baychev", Type::mammal, 17);
	Animal a2("Ivailo Kunchev", Type::bird, 89);
	Animal a3("Ilian Zaprqnov", Type::reptile, 7);
	Animal a4("Kaloyan Markov", Type::ivertebrates, 21);
	Animal a5("Tugay Kafa", Type::fish, 47);

	Zoo zoo;
	zoo.addAnimal(a1);
	zoo.addAnimal(a2);
	zoo.addAnimal(a3);
	zoo.addAnimal(a4);
	zoo.addAnimal(a5);

	zoo.printAnimals();
	zoo.removeAnimalByName("Kaloyan Markov");
	zoo.printAnimals();
	
	std::ofstream file("../test1.txt");
	zoo.writeToFile(file);
	file.close();

	return 0;

}
