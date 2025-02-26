#include <iostream>
#include <fstream>

typedef bool (*predicate1)(int, int);

enum class Type
{

	TV = 0,
	SMARTPHONE = 1,
	LAPTOP = 2,
	PC = 3,
	CAMERA = 4,
	NONE = 5

};

struct Device
{
public:

	char name[33];
	int quantity;
	double price;
	Type type;
	char supplier[33];

};

struct Warehouse
{
public:

	Device devices[50];
	int countOfDevices;
	char owner[33];

};

typedef bool (*predicate2)(const Device&, const Device&);

Device createDevice()
{

	Device result;

	std::cin.getline(result.name, 33);
	std::cin >> result.quantity;
	std::cin >> result.price;

	int option = 0;
	std::cin >> option;

	switch (option)
	{

	case 0: result.type = Type::TV; break;
	case 1: result.type = Type::SMARTPHONE; break;
	case 2: result.type = Type::LAPTOP; break;
	case 3: result.type = Type::PC; break;
	case 4: result.type = Type::CAMERA; break;
	default: result.type = Type::NONE; break;

	}

	std::cin.getline(result.supplier, 33);

	return result;

}

Warehouse  createWarehouse()
{

	int size = 0;
	std::cin >> size;

	Warehouse result;
	result.countOfDevices = size;

	for (int i = 0; i < size; i++)
	{

		result.devices[i] = createDevice();

	}

	return result;

}

void addDevice(const Device& d, Warehouse& wh)
{

	if (wh.countOfDevices == 50) return;

	wh.devices[wh.countOfDevices] = d;
	wh.countOfDevices += 1;

}

void serializeDevice(std::ofstream& file, const Device& d)
{

	file << d.name << " ";
	file << d.quantity << " ";
	file << d.price << " ";
	file << (int)d.type << " ";
	file << d.supplier << " ";

}

Device deserializeDevice(std::ifstream& file)
{

	Device result;
	file >> result.name;
	file >> result.quantity;
	file >> result.price;

	int option = 0;
	file >> option;

	switch (option)
	{

	case 0: result.type = Type::TV; break;
	case 1: result.type = Type::SMARTPHONE; break;
	case 2: result.type = Type::LAPTOP; break;
	case 3: result.type = Type::PC; break;
	case 4: result.type = Type::CAMERA; break;
	default: result.type = Type::NONE; break;

	}

	file >> result.supplier;

	return result;

}

void serializeWarehouse(const char* fileName, const Warehouse& wh)
{

	std::ofstream file(fileName);

	if (!file.is_open()) return;

	file << wh.owner << " ";

	for (int i = 0; i < wh.countOfDevices; i++)
	{

		serializeDevice(file, wh.devices[i]);

	}

	file.close();

}

Warehouse deserializeWarehouse(const char* fileName)
{

	std::ifstream file(fileName);
	int index = 0;

	if (!file.is_open()) return {};

	Warehouse result;
	file >> result.owner;

	while (!file.eof())
	{

		result.devices[index] = deserializeDevice(file);
		index += 1;

		if (index == 50) break;

	}

	file.close();
	result.countOfDevices = index;
	return result;

}

void printDevice(const Device& d)
{

	std::cout << d.name << " ";
	std::cout << d.quantity << " ";
	std::cout << d.price << " ";

	switch (d.type)
	{

	case Type::TV: std::cout << "TV ";  break;
	case Type::SMARTPHONE: std::cout << "SMARTPHONE "; break;
	case Type::LAPTOP: std::cout << "LAPTOP "; break;
	case Type::PC: std::cout << "PC "; break;
	case Type::CAMERA: std::cout << "CAMERA "; break;
	default: std::cout << "NONE "; break;

	}

	std::cout << d.supplier << " ";

}

void printWarehouse(const Warehouse& wh)
{

	for (int i = 0; i < wh.countOfDevices; i++)
	{

		printDevice(wh.devices[i]);
		std::cout << std::endl;

	}

}

void sortWarehouse(Warehouse& wh, predicate1 func)
{

	for (int i = 0; i < wh.countOfDevices - 1; i++)
	{

		for (int j = 0; j < wh.countOfDevices - i - 1; j++)
		{

			if (func(wh.devices[j].price, wh.devices[j + 1].price))
			{

				std::swap(wh.devices[j], wh.devices[j + 1]);

			}

		}

	}

}

void findDevice(const Warehouse& wh, predicate2 func)
{

	Device temp;

	for (int i = 0; i < wh.countOfDevices - 1; i++)
	{

		if (func(wh.devices[i], wh.devices[i + 1]))
		{

			temp = wh.devices[i];

		}

	}

	printDevice(temp);

}

bool min1(int number1, int number2)
{

	return number1 < number2;

}

bool min2(const Device& d1, const Device& d2)
{

	return d1.price < d2.price;

}

int main()
{

	Device d1 = { "1", 3, 0.5, Type::TV, "1" };
	Device d2 = { "2", 3, 0.5, Type::SMARTPHONE, "2" };
	Device d3 = { "3", 3, 0.5, Type::CAMERA, "3" };

	Warehouse wh = { {d1, d2, d3}, 3 , "da" };

	serializeWarehouse("../test1.txt", wh);
	Warehouse newWh = deserializeWarehouse("../test1.txt");
	printWarehouse(newWh);
	sortWarehouse(newWh, min1);
	printWarehouse(newWh);

	findDevice(wh, min2);

	return 0;

}
