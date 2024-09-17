#include <iostream>
#include <fstream>
#include <cstring>

#pragma warning(disable:4996)

namespace GlobalConstants
{

    const int MAX_COLS = 15;
    const int MAX_ROWS = 100;
    const int MAX_CELL_SIZE = 50;

}

const char* subString(const char* inputString, const char* inputSubString)
{

    if (*inputSubString == '\0')
    {

        return inputString;

    }

    for (const char* currentPosition1 = inputString; *currentPosition1 != '\0'; currentPosition1++) // Iterate over each character in inputString
    {

        for (const char* n = inputSubString, *currentPosition2 = currentPosition1; ; n++, currentPosition2++) // Attempt to match inputSubString starting at current position currentPosition2
        {

            if (*n == '\0')  // If end of inputSubString reached, all characters matched, return start position
            {

                return currentPosition1;

            }
            if (*currentPosition2 != *n)  // If characters mismatch, break inner loop and move to the next position in inputString
            {

                break;

            }

        }

    }

    return nullptr;

}

void* customMemset(void* ptr, int inputValue, int inputCount) // The function converts the initial pointer ptr to type unsigned char*,
{                                                            // which allows the manipulation of the block of memory byte by byte and
                                                            // main purpose is to fill a block of memory with a specified byte value
    unsigned char* memoryPtr = (unsigned char*)(ptr);

    for (int i = 0; i < inputCount; i++)
    {

        memoryPtr[i] = (unsigned char)inputValue;

    }

    return ptr; // The function ends by returning the original ptr pointer

}

bool isDigit(char input)
{

    return input >= '0' && input <= '9';

}

int stringToInt(const char* inputString)
{

    int result = 0;

    while (isDigit(*inputString))
    {

        result = result * 10 + (*inputString - '0');
        inputString++;

    }

    return result;

}

void decodeHtmlEntities(char* inputString)
{

    char* readingIterator = inputString; // It is used to read and parse the input string, including searching for HTML entities to decode
    char* writtingIterator = inputString; // It used to record the decoding result

    while (*readingIterator) // Loop through each character of the input string
    {

        if (*readingIterator == '&' && *(readingIterator + 1) == '#' && isDigit(*(readingIterator + 2)))  // Check if current sequence is an HTML entity (e.g., "&#65;")
        {

            int code = 0;

            readingIterator = readingIterator + 2;

            while (isDigit(*readingIterator)) // Convert the numeric part of the entity to an integer
            {

                code = code * 10 + (*readingIterator - '0');
                readingIterator++;

            }

            if (*readingIterator == ';')  // Skip the closing ";" of the HTML entity
            {

                readingIterator++;

            }

            *writtingIterator++ = (char)code;

        }
        else
        {

            *writtingIterator++ = *readingIterator++; // Copy current character to output if not part of an HTML entity

        }
    }

    *writtingIterator = '\0';

}

class HtmlTable
{
private:

    char*** table;
    bool isHeader[GlobalConstants::MAX_ROWS][GlobalConstants::MAX_COLS];
    int rowCount;
    int colCount;
    int maxColWidths[GlobalConstants::MAX_COLS];

    void allocateTable()
    {

        table = new char** [GlobalConstants::MAX_ROWS]; // Allocate memory for all rows in the table

        for (int i = 0; i < GlobalConstants::MAX_ROWS; i++) // Iterate through each row
        {

            table[i] = new char* [GlobalConstants::MAX_COLS]; // Allocate memory for all columns in the current row

            for (int j = 0; j < GlobalConstants::MAX_COLS; j++) // Iterate through each column in the current row
            {

                table[i][j] = new char[GlobalConstants::MAX_CELL_SIZE]; // Allocate memory for the cell and initialize it with zeros
                customMemset(table[i][j], 0, GlobalConstants::MAX_CELL_SIZE); // Fill the newly allocated memory with zeros to clear it
                isHeader[i][j] = false; // Initialize the cell as not being a header cell

            }

        }

        customMemset(maxColWidths, 0, sizeof(maxColWidths)); // Initialize the array tracking maximum column widths with zeros

    }

    void calculateMaxColWidths()
    {

        customMemset(maxColWidths, 0, sizeof(maxColWidths)); // Initialize all column widths to 0. Ensures we start with a clean slate for this calculation.

        for (int i = 0; i < rowCount; i++) // Loop through each row of the table
        {

            for (int j = 0; j < colCount; j++) // Loop through each column in the current row
            {

                int cellLength = (int)(strlen(table[i][j])); // Calculate the length of the current cell's content

                if (isHeader[i][j])
                {

                    cellLength += 2;

                }
                if (cellLength > maxColWidths[j])
                {

                    maxColWidths[j] = cellLength;

                }

            }

        }

    }

    void printCellWithPadding(const char* cell, bool isHeaderCell, int colNumber)
    {

        if (isHeaderCell) // If the cell is a header cell, prepend it with an asterisk to denote its header status
        {

            std::cout << "*";

        }

        std::cout << cell; // Print the cell content

        int padding = maxColWidths[colNumber] - (int)(strlen(cell)); // Calculate the padding needed to align columns by 
        // finding the difference between the maximum column width and the cell's length
        if (isHeaderCell)
        {

            padding -= 2;

        }
        for (int i = 0; i < padding; i++) // Fill the remaining space with spaces to ensure uniform column widths
        {

            std::cout << ' ';

        }

        if (isHeaderCell) // If the cell is a header cell, append it with an asterisk to denote its header status
        {

            std::cout << "*";

        }

        std::cout << "|"; // End the cell with a vertical bar to separate it from the next cell

    }

public:

    HtmlTable() : rowCount(0), colCount(0)
    {

        allocateTable();

    }

    ~HtmlTable()
    {

        for (int i = 0; i < GlobalConstants::MAX_ROWS; i++)
        {

            for (int j = 0; j < GlobalConstants::MAX_COLS; j++)
            {

                delete[] table[i][j];

            }

            delete[] table[i];

        }

        delete[] table;

    }

    void readTableFromFile(const char* fileName)
    {

        std::ifstream file(fileName);

        if (!file.is_open())
        {

            std::cout << "Unable to open file" << std::endl;
            return;

        }

        this->~HtmlTable(); // Directly calls the destructor
        rowCount = 0;
        colCount = 0;
        allocateTable(); // Re-initialize the table structure

        char buffer[GlobalConstants::MAX_CELL_SIZE]; // Buffer to store each line read from the file
        char* rowData[GlobalConstants::MAX_COLS] = { nullptr }; // Temporary storage for row data before adding to the table
        int currentCol = 0; // Current column index
        bool inRow = false; // Flag to track if we're currently parsing a table row

        while (file.getline(buffer, GlobalConstants::MAX_CELL_SIZE))
        {

            decodeHtmlEntities(buffer);

            if (subString(buffer, "<tr>") != nullptr) // Check for the start of a table row
            {

                currentCol = 0;
                inRow = true;

            }
            else if (subString(buffer, "</tr>") != nullptr && inRow) // Check for the end of a table row
            {

                addRow(rowData, currentCol); // Add the collected row data to the table

                for (int i = 0; i < currentCol; i++) // Clear temporary row data after adding to the table
                {

                    if (rowData[i] != nullptr)
                    {

                        delete[] rowData[i];
                        rowData[i] = nullptr;

                    }

                }

                inRow = false;
                currentCol = 0;

            }
            else if ((subString(buffer, "<td>") != nullptr || subString(buffer, "<th>") != nullptr) && inRow) // Check for table data (td) or header (th) cells within a row
            {

                bool isHeaderCell = subString(buffer, "<th>") != nullptr; // Determine if the current cell is a header based on the presence of the <th> tag

                const char* start = subString(buffer, ">") + 1; // Extract the content between the cell tags
                const char* end = subString(start, "<");

                int length = end - start; // Calculate the length of the content

                char* cellContent = new char[length + 1]; // Allocate memory for the cell content

                strncpy(cellContent, start, length); // Copy the content into the new memory
                cellContent[length] = '\0';

                decodeHtmlEntities(cellContent);

                if (currentCol < GlobalConstants::MAX_COLS) // If there's room, add the cell content to the current row's data
                {

                    rowData[currentCol] = cellContent;
                    isHeader[rowCount][currentCol] = isHeaderCell;
                    currentCol++;

                }
                else
                {

                    delete[] cellContent;

                }

            }

        }

        calculateMaxColWidths(); // After reading all lines, calculate the maximum column widths for formatting
        file.close();

    }

    void addRow(char* inputRowData[], int inputDataSize)
    {

        if (rowCount < GlobalConstants::MAX_ROWS && inputDataSize <= GlobalConstants::MAX_COLS) // Check if there's room for another row and if the dataSize does not exceed the maximum number of columns
        {

            for (int i = 0; i < inputDataSize; i++) // Loop through each cell in the new row
            {

                strncpy(table[rowCount][i], inputRowData[i], GlobalConstants::MAX_CELL_SIZE - 1); // Copy data from rowData into the table, ensuring not to overflow the cell's memory
                table[rowCount][i][GlobalConstants::MAX_CELL_SIZE - 1] = '\0';

            }

            rowCount++;

            if (inputDataSize > colCount) // Update the colCount if the current row has more data than any previous rows
            {

                colCount = inputDataSize;

            }

            calculateMaxColWidths(); // Recalculate the maximum column widths, as the new row might contain wider cells

        }

    }

    void removeRow(int rowNumber)
    {

        rowNumber -= 1;  // Adjust for 1-based user input to 0-based indexing

        if (rowNumber >= 0 && rowNumber < rowCount) // Ensure the row to be removed is within the valid range
        {

            for (int j = 0; j < GlobalConstants::MAX_COLS; j++) // Delete all cells in the specified row
            {

                delete[] table[rowNumber][j];

            }


            for (int i = rowNumber; i < rowCount - 1; i++) // Shift all rows above the removed row one position down
            {

                table[i] = table[i + 1];

                for (int j = 0; j < GlobalConstants::MAX_COLS; j++) // Also adjust header flags for each column
                {

                    isHeader[i][j] = isHeader[i + 1][j];

                }

            }


            table[rowCount - 1] = nullptr; // Nullify the last row pointer after shifting

            for (int j = 0; j < GlobalConstants::MAX_COLS; j++)
            {

                isHeader[rowCount - 1][j] = false;

            }

            rowCount--;

        }
        else
        {

            std::cout << "Invalid row number" << std::endl;

        }

    }

    void editCell(int rowNumber, int colNumber, const char* inputValue)
    {

        // Adjust for 1-based indexing provided by the user
        rowNumber -= 1;
        colNumber -= 1;

        if (rowNumber >= 0 && rowNumber < rowCount && colNumber >= 0 && colNumber < colCount)
        {
            // Ensure the specified row and column numbers are within the bounds of the table

            strncpy(table[rowNumber][colNumber], inputValue, GlobalConstants::MAX_CELL_SIZE - 1); // Copy the inputValue into the specified cell, ensuring not to exceed its memory limit
            table[rowNumber][colNumber][GlobalConstants::MAX_CELL_SIZE - 1] = '\0';

        }

    }

    void saveToFile(const char* fileName)
    {

        std::ofstream file(fileName);

        if (!file.is_open())
        {

            std::cout << "Unable to open file for writing" << std::endl;
            return;

        }

        file << "<table>\n"; // Start the HTML table

        for (int i = 0; i < rowCount; i++)  // Iterate through each row of the table
        {

            file << "\t<tr>\n"; // Begin a table row

            for (int j = 0; j < colCount; j++) // Iterate through each column of the current row
            {

                const char* tag = isHeader[i][j] ? "th" : "td"; // Determine if the current cell is a header or data cell
                file << "\t\t<" << tag << ">" << table[i][j] << "</" << tag << ">\n"; // Output the cell with appropriate HTML tags
            }

            file << "\t</tr>\n"; // End the current table row

        }

        file << "</table>";
        file.close();

    }

    void print()
    {

        calculateMaxColWidths(); // Recalculates the maximum column widths to ensure proper alignment

        for (int i = 0; i < rowCount; i++) // Iterate over each row of the table
        {

            std::cout << "|"; // Start each row with a vertical bar

            for (int j = 0; j < colCount; j++) // Iterate over each column in the current row
            {

                printCellWithPadding(table[i][j], isHeader[i][j], j); // Print each cell with appropriate padding. 

            }

            std::cout << std::endl; // End each row with a newline.

        }

    }

};

int main()
{

    HtmlTable table;

    table.readTableFromFile("table.txt");
    //table.removeRow(1);
    //table.editCell(2, 1, "Updated Cell");
    table.print();
    std::cout << std::endl;

    char inputRow[3][10] = { "da", "Ivana", "123" };

    char* inputRowPointers[3] = { inputRow[0], inputRow[1], inputRow[2] };



    //table.addRow(inputRowPointers, 3);
    //table.print();

    return 0;

}

