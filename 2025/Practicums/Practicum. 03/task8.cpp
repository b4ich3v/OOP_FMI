#include <iostream>
#include <fstream>
#include <cstring>

namespace HELPERS
{

	const int MAX_SIZE_NAME = 100;
	const int MAX_COUNT_PRODUCTS_WAREHOUESE = 150;

}

enum class Category
{

	ELECTRONICS = 0,
	CLOTHING = 1,
	BOOKS = 2,
	FOOD = 3

};

struct Product
{
public:

	char name[HELPERS::MAX_SIZE_NAME + 1];
	int countOfAvailable;
	double price;
	Category category;
	char deliveryName[HELPERS::MAX_SIZE_NAME + 1];

};

struct Warehouse
{
public:

	Product products[HELPERS::MAX_COUNT_PRODUCTS_WAREHOUESE];
	int countOfProducts;

};

int getFileSize(std::ifstream& file)
{

	int currentPos = file.tellg();
	file.seekg(0, std::ios::end);
	int result = file.tellg();
	file.seekg(currentPos);
	file.clear();

	return result;

}

bool alreadHasThisNameInBinaryFile(const char* name, std::ifstream& file)
{

	if (!name) return false;

	int currentPos = file.tellg();
	file.seekg(0, std::ios::beg);
	Product currentProduct;

	while (true)
	{

		file.read((char*)&currentProduct, sizeof(Product));

		if (!strcmp(currentProduct.name, name)) return true;
		if (file.eof()) break;

	}

	file.clear();
	file.seekg(currentPos);

	return false;

}

void writeProductToBinaryFile(std::ofstream& file, const Product& p)
{

	file.write((const char*)&p, sizeof(Product));

}

void writeWarehouseToBinaryFile(const char* fileName, const Warehouse& wh)
{

	if (!fileName) return;

	std::ofstream file(fileName, std::ios::binary);

	if (!file.is_open()) return;

	for (int i = 0; i < wh.countOfProducts; i++)
	{

		writeProductToBinaryFile(file, wh.products[i]);

	}

	file.close();

}

void writeWarehouseToBinaryFileByCategory(const char* fileName, Category c, const Warehouse& wh)
{

	if (!fileName) return;

	std::ofstream file(fileName, std::ios::binary);

	if (!file.is_open()) return;

	for (int i = 0; i < wh.countOfProducts; i++)
	{

		if((int)c == (int)wh.products[i].category) writeProductToBinaryFile(file, wh.products[i]);

	}

	file.close();

}

void changeCountOfAvailableForProduct(int newCountOfAvailable, const Product& target, Warehouse& wh, const char* fileName)
{

	for (int i = 0; i < wh.countOfProducts; i++)
	{

		if (!strcmp(wh.products[i].name, target.name))
		{

			wh.products[i].countOfAvailable = newCountOfAvailable;
			writeWarehouseToBinaryFile(fileName, wh);
			break;

		}

	}

}

Product readProductFromBinaryFile(std::ifstream& file)
{

	Product result;
	file.read((char*)&result, sizeof(Product));

	return result;

}

Warehouse readWarehouseFromBinaryFile(const char* fileName)
{

	if (!fileName) return {};

	std::ifstream file(fileName, std::ios::binary);

	if (!file.is_open()) return {};

	Warehouse result;
	result.countOfProducts = getFileSize(file) / sizeof(Product);

	for (int i = 0; i < result.countOfProducts; i++)
	{

		result.products[i] = readProductFromBinaryFile(file);

	}

	file.close();
	return result;

}

Product readProductFromConsole(std::ifstream& file)
{

	Product result;
	std::cin >> result.name;
	alreadHasThisNameInBinaryFile(result.name, file);
	std::cin >> result.countOfAvailable;
	std::cin >> result.price;
	int number = 0;
	std::cin >> number;
	result.category = (Category)number;
	std::cin >> result.deliveryName;

	return result;

}

Warehouse readWarehouseFromConsole(const char* fileName)
{

	if (!fileName) return {};

	std::ifstream file(fileName, std::ios::binary);

	if (!file.is_open()) return {};

	Warehouse result;
	std::cin >> result.countOfProducts;

	for (int i = 0; i < result.countOfProducts; i++)
	{

		result.products[i] = readProductFromConsole(file);

	}

	return result;

}

void printProduct(const Product& p)
{

	std::cout << p.name << " ";
	std::cout << p.countOfAvailable << " ";
	std::cout << p.price << " ";

	switch (p.category)
	{
	case Category::BOOKS: std::cout << "BOOKS "; break;
	case Category::CLOTHING: std::cout << "CLOTHING "; break;
	case Category::ELECTRONICS: std::cout << "ELECTRONICS "; break;
	case Category::FOOD: std::cout << "FOOD "; break;
	default: break;

	}

	std::cout << p.deliveryName << " ";
	std::cout << std::endl;

}

void printProductByName(const char* name, const Warehouse& wh)
{

	for (int i = 0; i < wh.countOfProducts; i++)
	{

		if (!strcmp(name, wh.products[i].name)) printProduct(wh.products[i]);

	}

}

void printWarehouse(const Warehouse& wh)
{

	for (int i = 0; i < wh.countOfProducts; i++)
	{

		printProduct(wh.products[i]);

	}

}

int main()
{

	Warehouse wh1 =
	{

		{{"Yoan", 31, 7.45, Category::BOOKS, "Baychev"},
		{"Ivo", 3, 4.5, Category::CLOTHING, "Kunchev"},
		{"Koki", 23, 3, Category::ELECTRONICS, "Markov"},
		{"Ilian", 1, 0.00, Category::FOOD, "Zaprqnov"}},
		4

	};

	writeWarehouseToBinaryFile("../file.dat", wh1);
	Warehouse wh1Read1 = readWarehouseFromBinaryFile("../file.dat");
	printWarehouse(wh1Read1);

	std::cout << std::endl;
	printProductByName("Koki", wh1);
	std::cout << std::endl;

	//Warehouse wh2 = readWarehouseFromConsole("../file.dat");
	writeWarehouseToBinaryFileByCategory("../file.dat", Category::BOOKS, wh1);
	Warehouse wh1Read2 = readWarehouseFromBinaryFile("../file.dat");
	printWarehouse(wh1Read2);
	std::cout << std::endl;

	Product target = { "Yoan", 31, 7.45, Category::BOOKS, "Baychev" };
	changeCountOfAvailableForProduct(0, target, wh1, "../file.dat");
	Warehouse wh1Read3 = readWarehouseFromBinaryFile("../file.dat");
	printWarehouse(wh1Read3);

	return 0;

}
