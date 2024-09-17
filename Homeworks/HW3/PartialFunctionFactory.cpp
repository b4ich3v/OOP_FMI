#include "PartialFunctionFactory.h"
#include "T0PartialFunction.h"
#include "T1PartialFunction.h"
#include "T2PartialFunction.h"
#include "MaxPartialFunction.h"
#include "MinPartialFunction.h"
#include <iostream>
#include <fstream>
#include <stdexcept>

PartialFunction* PartialFunctionFactory::createPartialFunction(const char* fileName)
{

    std::ifstream file(fileName, std::ios::binary);

    if (!file.is_open())
    {

        std::cout << "Error opening file " << fileName << std::endl;
        return nullptr;

    }

    uint16_t N;
    uint16_t T;

    file.read((char*)(&N), sizeof(N));

    if (N > 32 || N < 0 || file.fail())
    {

        std::cout << "Error: N exceeds maximum allowed value of 32 in file " << fileName << std::endl;
        return nullptr;

    }

    file.read((char*)(&T), sizeof(T));

    if (T < 0 || T > 4)
    {

        std::cout << "Error: Invalid function type T in file " << fileName << std::endl;
        return nullptr;

    }

    if (T == 0)
    {

        uint32_t* args = new uint32_t[N];
        uint32_t* results = new uint32_t[N];

        for (int i = 0; i < N; i++)
        {

            file.read((char*)(&args[i]), sizeof(args[i]));

            if (file.fail())
            {

                std::cout << "Error reading args from file " << fileName << std::endl;
                delete[] args;
                delete[] results;
                return nullptr;

            }

        }

        for (int i = 0; i < N; i++)
        {

            file.read((char*)(&results[i]), sizeof(results[i]));

            if (file.fail())
            {

                std::cout << "Error reading results from file " << fileName << std::endl;
                delete[] args;
                delete[] results;
                return nullptr;

            }

        }

        file.close();
        return new T0PartialFunction(args, results, N);

    }
    else if (T == 1)
    {

        uint32_t* excluded = new uint32_t[N];

        for (int i = 0; i < N; i++)
        {

            file.read((char*)(&excluded[i]), sizeof(excluded[i]));

            if (file.fail())
            {

                std::cout << "Error reading excluded from file " << fileName << std::endl;
                delete[] excluded;
                return nullptr;

            }

        }

        file.close();
        return new T1PartialFunction(excluded, N);

    }
    else if (T == 2)
    {

        uint32_t* defined = new uint32_t[N];

        for (int i = 0; i < N; i++)
        {

            file.read((char*)(&defined[i]), sizeof(defined[i]));

            if (file.fail())
            {

                std::cout << "Error reading defined from file " << fileName << std::endl;
                delete[] defined;
                return nullptr;

            }

        }

        file.close();
        return new T2PartialFunction(defined, N);

    }
    else if (T == 3 || T == 4)
    {

        char** filenames = new char* [N];

        for (int i = 0; i < N; i++)
        {

            filenames[i] = new char[MAX_FILENAME_FUNCTION_LENGTH];
            file.read(filenames[i], MAX_FILENAME_FUNCTION_LENGTH);

            if (file.fail())
            {

                std::cout << "Error reading filenames from file " << fileName << std::endl;

                for (int j = 0; j <= i; j++)
                {

                    delete[] filenames[j];

                }

                delete[] filenames;
                return nullptr;

            }

        }

        file.close();

        PartialFunction** functions = new PartialFunction * [N];

        for (int i = 0; i < N; i++)
        {

            functions[i] = createPartialFunction(filenames[i]);
            delete[] filenames[i];

            if (functions[i] == nullptr)
            {

                std::cout << "Error reading nested function from file " << filenames[i] << std::endl;

                for (int j = 0; j <= i; j++)
                {

                    delete functions[j];

                }

                delete[] functions;
                return nullptr;

            }

        }

        delete[] filenames;

        if (T == 3)
        {

            return new MaxPartialFunction(functions, N);

        }
        else
        {

            return new MinPartialFunction(functions, N);

        }

    }

    file.close();
    return nullptr;

}
