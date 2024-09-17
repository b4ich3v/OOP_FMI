#include "MainProgram.h"
#include "PartialFunctionFactory.h"
#include <iostream>
#include <stdexcept>
#include <fstream>
#include <cstring>

void processPartialFunction()
{

    PartialFunction* function = PartialFunctionFactory::createPartialFunction("func.dat");

    if (!function)
    {

        throw std::runtime_error("Failed to create partial function from file");

    }

    int mode;
    std::cout << "Enter mode (1 for interval, 2 for sequential): ";
    std::cin >> mode;

    if (std::cin.fail())
    {

        delete function;
        throw std::invalid_argument("Invalid input for mode");

    }

    std::ifstream file("func.dat", std::ios::binary);

    if (!file.is_open())
    {

        delete function;
        throw std::runtime_error("Failed to open the file to read max argument");

    }

    uint16_t N, T;
    file.read((char*)(&N), sizeof(N));
    file.read((char*)(&T), sizeof(T));

    uint32_t maxArg = 0;

    if (T == 0)
    {

        uint32_t* args = new uint32_t[N];
        file.read((char*)(args), sizeof(uint32_t) * N);

        for (int i = 0; i < N; ++i)
        {

            if (args[i] > maxArg)
            {

                maxArg = args[i];

            }

        }

        delete[] args;

    }
    else if (T == 1 || T == 2)
    {

        uint32_t* values = new uint32_t[N];
        file.read((char*)(values), sizeof(uint32_t) * N);

        for (int i = 0; i < N; i++)
        {

            if (values[i] > maxArg)
            {

                maxArg = values[i];

            }

        }

        delete[] values;

    }
    else if (T == 3 || T == 4)
    {

        char** filenames = new char* [N];

        for (int i = 0; i < N; i++)
        {

            filenames[i] = new char[MAX_FILENAME_FUNCTION_LENGTH];
            file.read(filenames[i], MAX_FILENAME_FUNCTION_LENGTH);

        }

        for (int i = 0; i < N; i++)
        {

            std::ifstream nestedFile(filenames[i], std::ios::binary);

            if (nestedFile.is_open())
            {

                nestedFile.read((char*)(&N), sizeof(N));
                nestedFile.read((char*)(&T), sizeof(T));

                uint32_t* args = new uint32_t[N];
                nestedFile.read((char*)(args), sizeof(uint32_t) * N);

                for (int j = 0; j < N; j++)
                {

                    if (args[j] > maxArg)
                    {

                        maxArg = args[j];

                    }

                }

                delete[] args;
                nestedFile.close();

            }

            delete[] filenames[i];

        }

        delete[] filenames;

    }

    file.close();

    if (mode == 1)
    {

        uint32_t a, b;

        std::cout << "Enter interval [a, b]: ";
        std::cin >> a >> b;

        if (a >= b)
        {

            delete function;
            throw std::invalid_argument("Invalid interval");

        }

        if (std::cin.fail())
        {

            delete function;
            throw std::invalid_argument("Invalid input for interval");

        }

        for (uint32_t i = a; i <= b; i++)
        {

            if (function->isDefined(i))
            {

                std::cout << "f(" << i << ") = " << function->calculate(i) << "   ";

            }

        }

        std::cout << std::endl;

    }
    else if (mode == 2)
    {

        int definedCount = 0;

        for (uint32_t i = 0; i <= maxArg && definedCount < maxArg; i++)
        {

            if (function->isDefined(i))
            {

                definedCount++;

            }

        }

        uint32_t start = 0;
        int count = 0;
        char input[10];

        while (true)
        {

            std::cout << "Enter 'next' to get the next defined value or 'exit' to quit: ";
            std::cin >> input;

            if (strcmp(input, "exit") == 0)
            {

                break;

            }
            else if (strcmp(input, "next") == 0)
            {

                if (count >= definedCount)
                {

                    std::cout << "No more defined values" << std::endl;
                    break;

                }

                while (!function->isDefined(start) && start <= maxArg)
                {

                    start++;

                }

                if (start <= maxArg)
                {

                    std::cout << "f(" << start << ") = " << function->calculate(start) << std::endl;
                    start++;
                    count++;

                }
                else
                {

                    std::cout << "No more defined values" << std::endl;
                    break;

                }

            }
            else
            {

                std::cout << "Invalid input." << std::endl;

            }

        }

    }
    else
    {

        delete function;
        throw std::invalid_argument("Invalid mode");

    }

    delete function;

}

int main()
{

    try
    {

        processPartialFunction();
        return 0;

    }
    catch (const std::exception& e)
    {

        std::cout << "An error occurred: " << e.what() << std::endl;
        return 1;

    }

}
