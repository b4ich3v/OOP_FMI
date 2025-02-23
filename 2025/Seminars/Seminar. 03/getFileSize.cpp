#include <cstring>
#include <fstream>
#include <iostream>

int getFileSize(std::ifstream& file)
{

    file.seekg(0, std::ios::end);
    int result = file.tellg();
    file.seekg(0, std::ios::beg);

    return result;

}

int main()
{

    std::ifstream file("../file.dat", std::ios::binary);
    std::cout << getFileSize(file);
    file.close();

    return 0;

}
