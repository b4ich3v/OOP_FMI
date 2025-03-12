#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>

namespace CONSTANTS
{

    const int MAX_ROWS = 100;
    const int MAX_COLS = 100;
    const int MAX_BUFFER_SIZE = 1024;

}

struct Row
{
public:

    double currentRow[CONSTANTS::MAX_COLS]{ 0 };

};

class MatrixFile
{
private:

    Row rows[CONSTANTS::MAX_ROWS];
    int countOfRows = 0;
    int countOfCols = 0;
    char* fileName = nullptr;

    void readFromFile(const char* fileName)
    {

        if (!fileName) return;

        std::ifstream file(fileName);

        if (!file.is_open()) return;

        file >> countOfRows;
        file >> countOfCols;
        file.ignore();

        char buffer[CONSTANTS::MAX_BUFFER_SIZE];


        for (int i = 0; i < countOfRows; i++)
        {

            file.getline(buffer, CONSTANTS::MAX_BUFFER_SIZE);
            std::stringstream ss(buffer);

            for (int j = 0; j < countOfCols; j++)
            {

                ss >> rows[i].currentRow[j];

            }

        }

        file.close();
        this->fileName = new char[strlen(fileName) + 1];
        strncpy(this->fileName, fileName, strlen(fileName));
        this->fileName[strlen(fileName)] = '\0';

    }

    void writeToFile(const char* fileName)
    {

        if (!fileName) return;

        std::ofstream file(fileName);

        if (!file.is_open()) return;

        file << countOfRows;
        file << " ";
        file << countOfCols;
        file << std::endl;

        for (int i = 0; i < countOfRows; i++)
        {

            for (int j = 0; j < countOfCols; j++)
            {

                file << rows[i].currentRow[j] << " ";

            }

            if (i != countOfRows - 1) file << std::endl;

        }

        file.close();

    }

    void copyFrom(const MatrixFile& other)
    {

        setRowsCount(other.countOfRows);
        setColsCount(other.countOfCols);

        for (int i = 0; i < countOfRows; i++)
        {

            for (int j = 0; j < countOfCols; j++)
            {

                rows[i].currentRow[j] = other.rows[i].currentRow[j];

            }

        }

        char* newFileName = new char[strlen(other.fileName) + 1];
        strncpy(newFileName, other.fileName, strlen(other.fileName));
        newFileName[strlen(other.fileName)] = '\0';

        delete[] fileName;
        fileName = newFileName;

    }

public:

    MatrixFile() : countOfRows(0), countOfCols(0), fileName(nullptr) {}

    MatrixFile(const char* fileName)
    {

        readFromFile(fileName);

    }

    ~MatrixFile()
    {

        writeToFile(fileName);
        delete[] fileName;

    }

    void setRowsCount(int newRowsCount)
    {

        this->countOfRows = newRowsCount;

    }

    void setColsCount(int newColsCount)
    {

        this->countOfCols = newColsCount;

    }

    void printMatrix() const
    {

        for (int i = 0; i < countOfRows; i++)
        {

            for (int j = 0; j < countOfCols; j++)
            {

                std::cout << rows[i].currentRow[j] << " ";

            }

            std::cout << std::endl;

        }

        std::cout << std::endl;

    }

    int getRowsCount() const
    {

        return countOfRows;

    }

    int getColsCount() const
    {

        return countOfCols;

    }

    void transposeMatrix()
    {

        MatrixFile newMatrix;
        newMatrix.setRowsCount(this->countOfCols);
        newMatrix.setColsCount(this->countOfRows);

        newMatrix.fileName = new char[strlen(fileName) + 1];
        strncpy(newMatrix.fileName, fileName, strlen(fileName));
        newMatrix.fileName[strlen(fileName)] = '\0';

        for (int i = 0; i < newMatrix.countOfRows; i++)
        {

            for (int j = 0; j < newMatrix.countOfCols; j++)
            {

                newMatrix.rows[i].currentRow[j] = rows[j].currentRow[i];

            }

        }

        copyFrom(newMatrix);

    }

    void multiplicationWithScalar(double scalar)
    {

        MatrixFile newMatrix;
        newMatrix.setRowsCount(countOfRows);
        newMatrix.setColsCount(countOfCols);

        newMatrix.fileName = new char[strlen(fileName) + 1];
        strncpy(newMatrix.fileName, fileName, strlen(fileName));
        newMatrix.fileName[strlen(fileName)] = '\0';

        for (int i = 0; i < countOfRows; i++)
        {

            for (int j = 0; j < countOfCols; j++)
            {

                newMatrix.rows[i].currentRow[j] = rows[i].currentRow[j] * scalar;

            }

        }

        copyFrom(newMatrix);

    }

    void changeValueAt(int i, int j, int newValue)
    {

        if (i < 0 || j < 0 || i >= countOfRows || j >= countOfCols) return;

        rows[i].currentRow[j] = newValue;

    }

};

int main()
{

    MatrixFile matrix("../test.txt");
    matrix.printMatrix();

    matrix.multiplicationWithScalar(2);
    matrix.printMatrix();

    matrix.transposeMatrix();
    matrix.printMatrix();
    matrix.transposeMatrix();

    matrix.multiplicationWithScalar(0.5);
    matrix.printMatrix();

    return 0;

}
