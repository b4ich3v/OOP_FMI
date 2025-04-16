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

    Picture() = delete;

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

int main() 
{

    Picture picture(2, 3);
    picture.setPixel(0, 0, Pixel(255, 0, 0));
    picture.setPixel(0, 1, Pixel(0, 255, 0));
    picture.setPixel(0, 2, Pixel(0, 0, 255));
    picture.setPixel(1, 0, Pixel(128, 128, 128));
    picture.setPixel(1, 1, Pixel(64, 64, 64));
    picture.setPixel(1, 2, Pixel(192, 192, 192));

    picture.printPicture();
    std::cout << std::endl;

    picture.grayscale();
    picture.printPicture();

    return 0;

}

