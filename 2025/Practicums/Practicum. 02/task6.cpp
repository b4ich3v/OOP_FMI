#include <iostream>
#include <fstream>

struct Vector
{
public:

    int x;
    int y;
    int z;
    int mask;

};

struct VectorSpace
{
public:

    Vector vectors[50];
    int countOfVectors;

};

int gcd(int number1, int number2)
{

    int result = std::min(number1, number2);

    for (int i = 2; i <= result; i++)
    {

        if ((number1 % i == 0) && (number2 % i == 0)) return i;

    }

    return 1;

}

void serializeVector(const Vector& v, std::ofstream& file)
{

    file << std::abs(v.x) << " " << std::abs(v.y) << " " << std::abs(v.z) << " " << v.mask << "\n";

}

void serializeVectorSpace(const VectorSpace& space, const char* fileName)
{

    std::ofstream file(fileName);

    if (!file.is_open()) return;

    file << space.countOfVectors << "\n";

    for (int i = 0; i < space.countOfVectors; i++)
    {

        serializeVector(space.vectors[i], file);

    }

    file.close();

}

Vector deserializeVector(std::ifstream& file)
{

    Vector result;
    file >> result.x >> result.y >> result.z >> result.mask;

    return result;

}

VectorSpace deserializeVectorSpace(const char* fileName)
{

    std::ifstream file(fileName);

    if (!file.is_open())  return {};

    VectorSpace result;
    file >> result.countOfVectors;
    result.countOfVectors = std::min(result.countOfVectors, 50);

    for (int i = 0; i < result.countOfVectors; i++)
    {

        result.vectors[i] = deserializeVector(file);

    }

    file.close();
    return result;

}

void printVector(const Vector& v)
{

    Vector vC = v;

    if ((vC.mask & 0x001) == 0) vC.x *= -1;
    if ((vC.mask & 0x010) == 0) vC.y *= -1;
    if ((vC.mask & 0x100) == 0) vC.z *= -1;

    std::cout << "(" << vC.x << ", " << vC.y << ", " << vC.z << ") ";

}

void printVectorSpace(const VectorSpace& space)
{

    std::cout << "{ ";

    for (int i = 0; i < space.countOfVectors; i++)
    {

        printVector(space.vectors[i]);

    }

    std::cout << "}\n";

}

int getPowerOfLen(const Vector& v)
{

    return v.x * v.x + v.y * v.y + v.z * v.z;

}

void sort(VectorSpace& space)
{

    for (int i = 0; i < space.countOfVectors - 1; i++)
    {

        for (int j = 0; j < space.countOfVectors - i - 1; j++)
        {

            if (getPowerOfLen(space.vectors[j]) > getPowerOfLen(space.vectors[j + 1]))
            {

                std::swap(space.vectors[j], space.vectors[j + 1]);

            }

        }

    }

}

void evaluateVector(Vector& v)
{

    if ((v.mask & 0x001) == 0) v.x *= -1;
    if ((v.mask & 0x010) == 0) v.y *= -1;
    if ((v.mask & 0x100) == 0) v.z *= -1;

}

int scalarMult(const Vector& v1, const Vector& v2)
{

    Vector v1C = v1;
    Vector v2C = v2;

    evaluateVector(v1C);
    evaluateVector(v2C);

    return v1C.x * v2C.x + v1C.y * v2C.y + v1C.z * v2C.z;

}

Vector vectorMult(const Vector& v1, const Vector& v2)
{

    Vector v1C = v1, v2C = v2;
    evaluateVector(v1C);
    evaluateVector(v2C);

    Vector result;
    result.x = v1C.y * v2C.z - v1C.z * v2C.y;
    result.y = v1C.z * v2C.x - v1C.x * v2C.z;
    result.z = v1C.x * v2C.y - v1C.y * v2C.x;

    return result;

}

int mixedMult(const Vector& v1, const Vector& v2, const Vector& v3)
{

    Vector v1C = v1;
    Vector v2C = v2;
    Vector v3C = v3;

    evaluateVector(v1C);
    evaluateVector(v2C);
    evaluateVector(v3C);

    Vector left = vectorMult(v1C, v2C);
    Vector right = v3C;

    return scalarMult(left, right);

}

bool areLNZ(const VectorSpace& space, int i, int j)
{

    if (i >= space.countOfVectors || j >= space.countOfVectors || i < 0 || j < 0 || i == j) return false;
        
    Vector v1 = space.vectors[i];
    Vector v2 = space.vectors[j];

    evaluateVector(v1);
    evaluateVector(v2);

    return vectorMult(v1, v2).x != 0 || vectorMult(v1, v2).y != 0 || vectorMult(v1, v2).z != 0;

}

void simplify(Vector& v)
{

    int GCD = gcd(v.x, gcd(v.y, v.z));
    v.x /= GCD;
    v.y /= GCD;
    v.z /= GCD;

}

void printBaseVectors(const VectorSpace& space)
{

    bool* areBaseVectors = new bool[space.countOfVectors];

    for (int i = 0; i < space.countOfVectors; i++)
    {

        areBaseVectors[i] = true;

    }

    for (int i = 0; i < space.countOfVectors; i++)
    {

        for (int j = i + 1; j < space.countOfVectors; j++)
        {

            if (!areLNZ(space, i, j) && i != j)
            {

                areBaseVectors[i] = false;

            }

        }

    }

    for (int i = 0; i < space.countOfVectors; i++)
    {

        if (areBaseVectors[i])
        {

            Vector simpleForm = space.vectors[i];
            simplify(simpleForm);
            printVector(simpleForm);

        }

    }

    delete[] areBaseVectors;

}

int main()
{

    VectorSpace space;
    space.countOfVectors = 4;
    space.vectors[0] = { 1, 2, 3, 0x000 };
    space.vectors[1] = { 4, 15, 1, 0x011 };
    space.vectors[2] = { 7, 3, 1, 0x100 };
    space.vectors[3] = { 2, 4, 6, 0x000 };

    serializeVectorSpace(space, "../test1.txt");
    VectorSpace result = deserializeVectorSpace("../test1.txt");

    printVectorSpace(result);
    sort(result);
    printVectorSpace(result);
    std::cout << std::endl;
    printBaseVectors(space);
    std::cout << std::endl;

    Vector product1 = vectorMult(space.vectors[0], space.vectors[1]);
    printVector(product1);
    std::cout << std::endl;

    int product2 = scalarMult(space.vectors[0], space.vectors[1]);
    std::cout << product2;
    std::cout << std::endl;

    int product3 = mixedMult(space.vectors[0], space.vectors[1], space.vectors[2]);
    std::cout << product3;
    std::cout << std::endl;

    if (areLNZ(space, 0, 3)) std::cout << "Yes" << std::endl;
    else std::cout << "No" << std::endl;

    return 0;

}
