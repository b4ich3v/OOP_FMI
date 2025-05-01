#include <iostream>
#include <cstring>

namespace CONSTANTS 
{

	const double CPU_PRICE_MULT = 29.99;
	const int LOWER_BOUND_FREQ = 1;
	const int UPPER_BOUND_FREQ = 1000;
	const int LOWER_BOUND_CORES = 1;
	const int UPPER_BOUND_CORES = 8;

	const double MEMORY_PRICE_MULT = 99.99;
	const int LOWER_BOUND_CAP = 1;
	const int UPPER_BOUND_CAP = 1000;

	const int BUFFER_MAX_SIZE = 1024;

}

enum class Type
{

	CPU = 0,
	MEMORY = 1

};

class Component 
{
private:

	char* name = nullptr;

	void free() 
	{

		delete[] name;
		name = nullptr;

	}

	void copyFrom(const Component& other) 
	{

		this->name = new char[strlen(other.name) + 1];
		strncpy(this->name, other.name, strlen(other.name));
		this->name[strlen(other.name)] = '\0';

	}

	void moveTo(Component&& other) 
	{

		this->name = other.name;
		other.name = nullptr;

	}

public:

	Component(): name(nullptr) {}

	Component(const char* name)
	{

		if (!name) throw std::logic_error("Error");

		this->name = new char[strlen(name) + 1];
		strncpy(this->name, name, strlen(name));
		this->name[strlen(name)] = '\0';

	}

	Component(const Component& other) 
	{

		copyFrom(other);

	}

	Component(Component&& other) noexcept 
	{
		
		moveTo(std::move(other));

	}

	Component& operator = (const Component& other) 
	{

		if (this != &other) 
		{

			free();
			copyFrom(other);

		}

		return *this;

	}

	Component& operator = (Component&& other) noexcept
	{

		if (this != &other)
		{

			free();
			moveTo(std::move(other));

		}

		return *this;

	}

	const char* getName() const 
	{

		return name;

	}

	virtual ~Component()
	{

		free();

	}

	virtual double price() const = 0;

	virtual void output(std::ostream& os) const = 0;

};

class CPU: public Component
{
private:

	unsigned short coresCount = 0;
	unsigned short frequency = 0;

public:

	CPU(const char* name, unsigned short coresCount, unsigned short frequency): Component(name)
	{

		if (coresCount < CONSTANTS::LOWER_BOUND_CORES ||
			coresCount > CONSTANTS::UPPER_BOUND_CORES) throw std::logic_error("Error");

		if (frequency < CONSTANTS::LOWER_BOUND_FREQ ||
			frequency > CONSTANTS::UPPER_BOUND_FREQ) throw std::logic_error("Error");

		this->coresCount = coresCount;
		this->frequency = frequency;

	}

	double price() const override 
	{

		return coresCount * CONSTANTS::CPU_PRICE_MULT;

	}

	void output(std::ostream& os) const override
	{

		os << getName() << " ";
		os << coresCount << " " << frequency << " ";

	}

	friend std::ostream& operator << (std::ostream& os, const CPU& cpu)
	{

		cpu.output(os);
		os << cpu.price() << " ";

		return os;

	}

};

class Memory: public Component
{
private:

	unsigned short capacity = 0;

public:

	Memory(const char* name, unsigned short capacity): Component(name)
	{

		if (capacity < CONSTANTS::LOWER_BOUND_CAP ||
			capacity > CONSTANTS::UPPER_BOUND_CAP) throw std::logic_error("Error");

		this->capacity = capacity;

	}

	double price() const override
	{

		return capacity * CONSTANTS::MEMORY_PRICE_MULT;

	}

	void output(std::ostream& os) const override
	{

		os << getName() << " ";
		os << capacity << " ";
		
	}

	friend std::ostream& operator << (std::ostream& os, const Memory& memory)
	{

		memory.output(os);
		os << memory.price() << " ";

		return os;

	}

};

class Configuration 
{
private:

	Component** components = nullptr;
	int size = 0;
	int capacity = 8;
	
	void resize(int newCapacity) 
	{

		if (newCapacity <= capacity) return;

		Component** newCompnents  = new Component* [newCapacity] {nullptr};

		for (int i = 0; i < size; i++)
		{

			newCompnents[i] = components[i];

		}

		delete[] components;
		components = newCompnents;
		capacity = newCapacity;

	}

	void free() 
	{

		delete[] components;
		components = nullptr;
		size = 0;
		capacity = 8;

	}

	void copyFrom(const Configuration& other)
	{

		this->components = new Component * [other.capacity];

		for (int i = 0; i < other.size; i++)
		{

			this->components[i] = other.components[i]; 

		}

		this->size = other.size;
		this->capacity = other.capacity;

	}

	void moveTo(Configuration&& other)
	{

		this->components = other.components;
		this->size = other.size;
		this->capacity = other.capacity;

		other.components = nullptr;
		other.size = 0;
		other.capacity = 8;

	}

	int findFirstFreeIndex() const 
	{

		for (int i = 0; i < size; i++)
		{

			if (!components[i]) return i;

		}

		return -1;

	}

public:

	Configuration() 
	{

		this->components = new Component* [8] {nullptr};
		this->capacity = 8;
		this->size = 0;

	}

	Configuration(const Configuration& other) 
	{

		copyFrom(other);

	}

	Configuration(Configuration&& other) noexcept 
	{
			
		moveTo(std::move(other));
	
	}

	Configuration& operator = (const Configuration& other) 
	{

		if (this != &other) 
		{

			free();
			copyFrom(other);
			
		}

		return *this;

	}

	Configuration& operator = (Configuration&& other) noexcept
	{

		if (this != &other)
		{

			free();
			moveTo(std::move(other));

		}

		return *this;

	}

	~Configuration() 
	{

		free();

	}

	void insert(Component* component) 
	{

		if (!component) return;

		int index = findFirstFreeIndex();
		if (index == -1) resize(capacity * 2);

		components[size] = component;
		size += 1;

	}

	double price() const 
	{

		double result = 0;

		for (int i = 0; i < size; i++)
		{

			result += components[i]->price();

		}

		return result;

	}

	int getSize() const 
	{

		return size;

	}

	const Component& operator [] (int index) const 
	{

		if (index < 0 || index >= size) throw std::logic_error("Error");

		return *components[index];

	}

	friend std::ostream& operator << (std::ostream& os, const Configuration& config) 
	{

		for (int i = 0; i < config.size; i++)
		{

			config[i].output(os);         
			os << config[i].price() << " ";

		}

		return os;

	}

};

class ComponentFactory
{
public:

	static Component* Create_Component() 
	{

		std::cout << "Enter number: " << std::endl;

		int number = 0;
		std::cin >> number;
		std::cin.ignore(1);

		if (number < 0 || number > 1) return nullptr;

		Type type = (Type)number;

		switch (type)
		{

		case Type::CPU: 
		{

			std::cout << "Write name, cores, Count and frequency: " << std::endl;
			char name[CONSTANTS::BUFFER_MAX_SIZE];
			unsigned short coresCount = 0;
			unsigned short frequency = 0;

			std::cin.getline(name, CONSTANTS::BUFFER_MAX_SIZE);
			std::cin >> coresCount;
			std::cin >> frequency;

			return new CPU(name, coresCount, frequency);

		}
		case Type::MEMORY: 
		{

			std::cout << "Write name and capacity: " << std::endl;
			char name[CONSTANTS::BUFFER_MAX_SIZE];
			unsigned short capacity = 0;

			std::cin.getline(name, CONSTANTS::BUFFER_MAX_SIZE);
			std::cin >> capacity;

			return new Memory(name, capacity);

		}
		default: return nullptr;
			
		}

		return nullptr;

	}

};

int main()
{

	Configuration config;
	Component* cpu = ComponentFactory::Create_Component();

	if (cpu) config.insert(cpu);

	std::cin.ignore();
	std::cout << std::endl;

	Component* memory = ComponentFactory::Create_Component();

	if (memory) config.insert(memory);

	std::cout << config;
	std::cout << config.price() << std::endl;

	delete cpu;
	delete memory;
	
	return 0;

}
