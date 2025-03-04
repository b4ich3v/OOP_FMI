#include <iostream>
#include <fstream>

namespace HELPERS
{

    const char SEPARATOR1 = '|';
    const char SEPARATOR2 = ',';
    const int ROW_MAX_SIZE = 50;
    const int COUNT_OF_COLS = 3;

    int countOfSeparators(std::ifstream& file)
    {

        int counter = 0;
        char currentChar = 'a';

        while (true)
        {

            currentChar = file.get();

            if (currentChar == SEPARATOR1) counter += 1;
            if (file.eof()) break;


        }

        file.clear();
        file.seekg(0, std::ios::beg);

        return counter;

    }

}

struct Row
{
public:

    int numbers[HELPERS::COUNT_OF_COLS];

};

struct Matrix
{
public:

    Row rows[HELPERS::ROW_MAX_SIZE];
    int countOfRows;
    int countOfCols = HELPERS::COUNT_OF_COLS;

};

void writeRowToFile(const Row& row, std::ofstream& file)
{

    file << row.numbers[0];
    file << HELPERS::SEPARATOR2;
    file << row.numbers[1];
    file << HELPERS::SEPARATOR2;
    file << row.numbers[2];
    file << HELPERS::SEPARATOR1;

}

void writeMatrixToFile(const Matrix& matrix, const char* fileName)
{

    std::ofstream file(fileName);

    if (!file.is_open()) return;

    file << HELPERS::SEPARATOR1;

    for (int i = 0; i < matrix.countOfRows; i++)
    {

        writeRowToFile(matrix.rows[i], file);

    }

    file.close();

}

Matrix readMatrixFromFile(const char* fileName)
{

    std::ifstream file(fileName);

    if (!file.is_open()) return {};

    Matrix result;
    result.countOfRows = HELPERS::countOfSeparators(file) - 1;

    for (int i = 0; i < result.countOfRows; i++)
    {

        file.ignore();
        file >> result.rows[i].numbers[0];
        file.ignore();
        file >> result.rows[i].numbers[1];
        file.ignore();
        file >> result.rows[i].numbers[2];

    }

    file.close();
    return result;

}

Matrix multiplication(const Matrix& matrix1, const Matrix& matrix2)
{

    if (matrix1.countOfCols != matrix2.countOfRows) return {};

    Matrix result;
    result.countOfRows = matrix1.countOfRows;
    result.countOfCols = matrix2.countOfCols;

    for (int i = 0; i < result.countOfRows; i++)
    {

        for (int j = 0; j < result.countOfCols; j++)
        {

            result.rows[i].numbers[j] = 0;

            for (int k = 0; k < matrix1.countOfCols; k++)
            {

                result.rows[i].numbers[j] += matrix1.rows[i].numbers[k] * matrix2.rows[k].numbers[j];

            }

        }

    }

    return result;

}

int main()
{

    Row matrix1Rw1 = { 1 ,2 ,3 };
    Row matrix1Rw2 = { 3, 2, 1 };
    Row matrix1Rw3 = { 1, 2, 3 };
    Matrix matrix1 = { {matrix1Rw1, matrix1Rw2, matrix1Rw3}, 3 };
    writeMatrixToFile(matrix1, "../test1.txt");

    Row matrix2Rw1 = { 4, 5, 6 };
    Row matrix2Rw2 = { 6, 5, 4 };
    Row matrix2Rw3 = { 4, 6, 5 };
    Matrix matrix2 = { {matrix2Rw1, matrix2Rw2, matrix1Rw3}, 3 };
    writeMatrixToFile(matrix2, "../test2.txt");

    Matrix m1 = readMatrixFromFile("../test1.txt");
    Matrix m2 = readMatrixFromFile("../test2.txt");

    Matrix product = multiplication(m1, m2);
    writeMatrixToFile(product, "../result.txt");

    return 0;

}
