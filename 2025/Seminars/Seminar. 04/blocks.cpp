#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <cstdint>

namespace HELPERS
{

    const int DATA_SIZE = 32;
    const int MAX_DATA_SIZE = 28;
    const int SIZE_FOR_NEXT_SIZE = 2;
    const char DEFAULT_DATA_NAME[8] = "DEFAULT";

    int getFileSize(std::ifstream& file)
    {

        int currentPos = file.tellg();
        file.seekg(0, std::ios::end);
        int result = file.tellg();
        file.seekg(currentPos);
        file.clear();
        return result;
    }

}

struct Block
{
public:

    int16_t next;
    int16_t size;
    char data[HELPERS::MAX_DATA_SIZE + 1];

    void parser(std::ifstream& file)
    {

        file.read((char*)&next, HELPERS::SIZE_FOR_NEXT_SIZE);
        file.read((char*)&size, HELPERS::SIZE_FOR_NEXT_SIZE);
        file.read((char*)data, HELPERS::MAX_DATA_SIZE);
        data[size] = '\0';

    }

    Block()
    {

        next = 0;
        size = 0;
        strncpy(data, HELPERS::DEFAULT_DATA_NAME, sizeof(data) - 1);
        data[strlen(data)] = '\0';

    }

    Block(int16_t next, int16_t size, const char* data)
    {

        this->next = next;
        this->size = size;
        strncpy(this->data, data, size);
        this->data[size] = '\0';

    }

    Block(std::ifstream& file)
    {

        parser(file);

    }

    void printData() const
    {

        std::cout << data << " ";

    }

};

class ContainerOfBloks
{
private:

    Block* blocks;
    int countOfBlocks;

    int getCountOfBlocks(std::ifstream& file) const
    {

        return HELPERS::getFileSize(file) / HELPERS::DATA_SIZE;

    }

    void readFromFile(const char* fileName)
    {

        if (!fileName) return;

        std::ifstream file(fileName, std::ios::binary);

        if (!file.is_open()) return;

        countOfBlocks = getCountOfBlocks(file);
        blocks = new Block[countOfBlocks];

        for (int i = 0; i < countOfBlocks; i++)
        {

            blocks[i].parser(file);

        }

        file.close();

    }

    void free()
    {

        delete[] blocks;
        blocks = nullptr;
        countOfBlocks = 0;

    }

public:

    ContainerOfBloks(const char* fileName)
    {

        blocks = nullptr;
        countOfBlocks = 0;
        readFromFile(fileName);

    }

    ~ContainerOfBloks()
    {

        free();

    }

    void sortByOrder()
    {

        for (int i = 0; i < countOfBlocks - 1; i++)
        {

            for (int j = 0; j < countOfBlocks - i - 1; j++)
            {

                if (blocks[j].next > blocks[j + 1].next)
                {

                    std::swap(blocks[j], blocks[j + 1]);

                }

            }

        }

    }

    void printByOrder()
    {

        sortByOrder();

        if (blocks[0].next == -1)
        {

            for (int i = 1; i < countOfBlocks; i++)
            {

                blocks[i].printData();

            }

            blocks[0].printData();

        }

        std::cout << std::endl;

    }

};

int main()
{

    Block b1(4, 3, "C++");
    Block b2(0, 6, "si-oop");
    Block b3(5, 3, "The");
    Block b4(3, 4, "Test");
    Block b5(2, 2, "Is");
    Block b6(-1, 9, "Greatest");
    Block b7(2, 5, "dummy");

    b1.printData();
    b2.printData();
    b3.printData();
    b4.printData();
    b5.printData();
    b6.printData();
    b7.printData();

    // Writing blocks to file (uncomment if needed)
    /*
    std::ofstream file("../file.dat", std::ios::binary);
    file.write((const char*)&b1, HELPERS::DATA_SIZE);
    file.write((const char*)&b2, HELPERS::DATA_SIZE);
    file.write((const char*)&b3, HELPERS::DATA_SIZE);
    file.write((const char*)&b4, HELPERS::DATA_SIZE);
    file.write((const char*)&b5, HELPERS::DATA_SIZE);
    file.write((const char*)&b6, HELPERS::DATA_SIZE);
    file.write((const char*)&b7, HELPERS::DATA_SIZE);
    file.close();
    */

    std::cout << std::endl;
    ContainerOfBloks collection("../file.dat");
    collection.printByOrder();

    return 0;

}
