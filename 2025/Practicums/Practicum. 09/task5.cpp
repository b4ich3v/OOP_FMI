#include <iostream>
#include <stdexcept>
#include <cstring>

struct Pixel 
{
public:

    int red = 0;
    int green = 0;
    int blue = 0;
    double color = 0;

    void calculateColor() 
    {

        color = 0.333 * red + 0.333 * green + 0.333 * blue;

    }

    void printPixel() const 
    {

        std::cout << "(" << red << "," << green << "," << blue << ") ";

    }

    Pixel(int r, int g, int b)
    {

        if (r < 0 || g < 0 || b < 0 || r > 255 || g > 255 || b > 255)
            throw std::logic_error("Error: invalid color component");

        red = r;
        green = g;
        blue = b;
        calculateColor();

    }

};

class Picture
{
private:

    Pixel*** pixels = nullptr;
    int rows = 0;
    int cols = 0;

    void allocateMatrix(int newRows, int newCols) 
    {

        rows = newRows;
        cols = newCols;

        pixels = new Pixel** [rows];

        for (int i = 0; i < rows; i++) 
        {

            pixels[i] = new Pixel * [cols];

            for (int j = 0; j < cols; j++)
            {

                pixels[i][j] = nullptr;

            }

        }

    }

    void free() 
    {

        if (!pixels) return;

        for (int i = 0; i < rows; i++)
        {

            for (int j = 0; j < cols; j++) 
            {

                delete pixels[i][j];

            }

            delete[] pixels[i];

        }

        delete[] pixels;
        pixels = nullptr;
        rows = cols = 0;

    }

    void copyFrom(const Picture& other) 
    {

        allocateMatrix(other.rows, other.cols);

        for (int i = 0; i < rows; i++)
        {

            for (int j = 0; j < cols; j++) 
            {

                if (other.pixels[i][j])
                    pixels[i][j] = new Pixel(*other.pixels[i][j]);

            }

        }

    }

    void moveTo(Picture&& other)  
    {

        pixels = other.pixels;
        rows = other.rows;
        cols = other.cols;

        other.pixels = nullptr;
        other.rows = other.cols = 0;

    }

public:

    Picture()
    {

        rows = 4;
        cols = 4;

        pixels = new Pixel** [rows];

        for (int i = 0; i < rows; i++)
        {

            pixels[i] = new Pixel* [cols];

        }

        for (int i = 0; i < rows; i++)
        {

            for (int j = 0; j < cols; j++)
            {

                pixels[i][j] = new Pixel(0, 0, 0);

            }

        }

    }

    Picture(int newRows, int newCols) 
    {

        if (newRows <= 0 || newCols <= 0) throw std::logic_error("Error: invalid dimensions");
        allocateMatrix(newRows, newCols);

    }

    Picture(const Picture& other) 
    {

        copyFrom(other);

    }

    Picture(Picture&& other) noexcept 
    {

        moveTo(std::move(other));

    }

    Picture& operator = (const Picture& other) 
    {

        if (this != &other) 
        {

            free();
            copyFrom(other);

        }

        return *this;

    }

    Picture& operator = (Picture&& other) noexcept 
    {

        if (this != &other) 
        {

            free();
            moveTo(std::move(other));

        }

        return *this;

    }

    ~Picture() 
    {

        free();

    }

    void setPixel(int i, int j, const Pixel& p)
    {

        if (i < 0 || i >= rows || j < 0 || j >= cols)
            throw std::out_of_range("Error: pixel index out of range");

        delete pixels[i][j];
        pixels[i][j] = new Pixel(p);

    }

    Pixel* getPixel(int i, int j) const 
    {

        if (i < 0 || i >= rows || j < 0 || j >= cols)
            throw std::out_of_range("Error: pixel index out of range");

        return pixels[i][j];

    }

    void grayscale() 
    {

        for (int i = 0; i < rows; i++) 
        {

            for (int j = 0; j < cols; j++) 
            {

                Pixel* px = pixels[i][j];
                if (!px) continue;

                int gray = 0.299 * px->red + 0.587 * px->green + 0.114 * px->blue;
                px->red = px->green = px->blue = gray;
                px->calculateColor();

            }

        }

    }

    void monochrome() 
    {

        for (int i = 0; i < rows; i++) 
        {

            for (int j = 0; j < cols; j++) 
            {

                Pixel* px = pixels[i][j];
                if (!px) continue;

                if (px->color == 128)
                {

                    px->red = px->green = px->blue = 0;
                    px->calculateColor();

                }

            }

        }

    }

    void negative() 
    {

        for (int i = 0; i < rows; i++) 
        {

            for (int j = 0; j < cols; j++)
            {

                Pixel* px = pixels[i][j];
                if (!px) continue;

                px->red = 255 - px->red;
                px->green = 255 - px->green;
                px->blue = 255 - px->blue;
                px->calculateColor();

            }

        }

    }

    void printPicture() const
    {

        for (int i = 0; i < rows; i++)
        {

            for (int j = 0; j < cols; j++) 
            {

                Pixel* px = pixels[i][j];

                if (px) px->printPixel();
                else std::cout << "not valid";

            }

            std::cout << std::endl;

        }

    }

};

enum class FilterType
{

    GRAYSCALE = 0,
    MONOCHROME = 1,
    NEGATIVE = 2

};

class Gallery 
{
private:

    Picture* pics = nullptr;
    int size = 0;
    int capacity = 8;

    void free()
    {

        delete[] pics;
        pics = nullptr;
        size = 0;
        capacity = 8;

    }

    void resize(int newCapacity) 
    {

        if (newCapacity <= capacity) return;

        Picture* newPics = new Picture[newCapacity];

        for (int i = 0; i < size; i++)
        {

            newPics[i] = pics[i];

        }

        delete[] pics;
        pics = newPics;
        capacity = newCapacity;

    }

    void moveTo(Gallery&& other) 
    {

        pics = other.pics;
        size = other.size;
        capacity = other.capacity;

        other.pics = nullptr;
        other.size = 0;
        other.capacity = 8;
    
    }

    void copyFrom(const Gallery& other) 
    {

        pics = new Picture[other.capacity];
        capacity = other.capacity;
        size = other.size;

        for (int i = 0; i < size; i++)
        {

            pics[i] = other.pics[i];

        }

    }

    void doMonochrome() 
    {

        for (int i = 0; i < size; i++)
        {

            pics[i].monochrome();

        }

    }

    void doNegative()
    {

        for (int i = 0; i < size; i++)
        {

            pics[i].negative();

        }

    }

    void doGrayscale()
    {

        for (int i = 0; i < size; i++)
        {

            pics[i].grayscale();

        }

    }

public:

    Gallery() 
    {

        capacity = 8;
        size = 0;
        pics = new Picture[capacity];

    }

    Gallery(const Gallery& other) 
    {

        copyFrom(other);

    }

    Gallery(Gallery&& other) noexcept
    {

        moveTo(std::move(other));
            
    }

    Gallery& operator = (const Gallery& other) 
    {

        if(this != &other)
        {

            free();
            copyFrom(other);

        }

        return *this;

    }

    Gallery& operator = (Gallery&& other) noexcept
    {

        if (this != &other)
        {

            free();
            moveTo(std::move(other));

        }

        return *this;

    }

    ~Gallery() 
    {

        free();

    }

    void addPicture(const Picture& p)
    {

        if (size == capacity) resize(capacity * 2);

        pics[size] = p;
        size += 1;

    }

    void removePicture(int index)
    {

        if (index < 0 || index >= size) throw std::logic_error("Error");

        for (int i = index; i < size - 1; i++)
        {

            pics[i] = pics[i + 1];

        }

        size -= 1;

    }

    void doFilter(FilterType filter) 
    {

        switch (filter)
        {

        case FilterType::GRAYSCALE: doGrayscale(); break;
        case FilterType::MONOCHROME: doMonochrome(); break;
        case FilterType::NEGATIVE: doNegative(); break;
        default: break;
            
        }

    }

    const Picture& operator [] (int index) const 
    {

        if (index < 0 || index >= size) throw std::logic_error("Error");

        return pics[index];

    }

    Picture& operator [] (int index)
    {

        if (index < 0 || index >= size) throw std::logic_error("Error");

        return pics[index];

    }

    void printGallery() const 
    {

        for (int i = 0; i < size; i++)
        {

            pics[i].printPicture();
            std::cout << std::endl;

        }

        std::cout << std::endl;

    }
};

int main()
{

    Picture* pictures = new Picture[10];

    for (int i = 0; i < 10; i++)
    {

        int rows = i + 1;
        int cols = i + 2;
        pictures[i] = Picture(rows, cols);

        for (int r = 0; r < rows; r++) 
        {

            for (int c = 0; c < cols; c++)
            {

                int red = (i * 25) % 256;
                int green = (i * 50) % 256;
                int blue = (i * 75) % 256;
                pictures[i].setPixel(r, c, Pixel(red, green, blue));

            }

        }

        switch (i % 3) 
        {

        case 0: pictures[i].grayscale(); break;
        case 1: pictures[i].monochrome(); break;
        case 2: pictures[i].negative(); break;

        }

    }

    Gallery gallery;

    for (int i = 0; i < 10; i++)
    {

        gallery.addPicture(pictures[i]);

    }
    
    gallery.removePicture(3);
    gallery.removePicture(7);
    gallery.printGallery();

    gallery.doFilter(FilterType::NEGATIVE);
    gallery.printGallery();

    delete[] pictures;
    return 0;

}
