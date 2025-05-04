#include "ArrFileSorting.h"
#include "CsvFileSorting.h"
#include "BinaryFileSorting.h"
#include "FileSorting.h"

static FileSorting* makeSorter(const MyString& name)
{

    const char* strData = name.getData();
    int size = name.getSize();

    if (size > 4)
    {

        const char* target = strData + size - 4;  
        
        if (std::strcmp(target, ".csv") == 0) return new CsvFileSorting(name);
        if (std::strcmp(target, ".arr") == 0) return new ArrFileSorting(name);
        if (std::strcmp(target, ".dat") == 0) return new BinaryFileSorting(name);

    }

    return nullptr;

}

int main() 
{
    
    MyString in("input.csv");
    MyString out("output.csv");

    FileSorting* reader = makeSorter(in);
    FileSorting* writer = makeSorter(out);

    if (!reader || !writer) 
    {
        
        delete reader;
        delete writer;
        return 1;

    }

    reader->read();
    writer->setData(reader->getData(), reader->getSize());
    writer->write();

    delete reader;
    delete writer;
    return 0;

}
