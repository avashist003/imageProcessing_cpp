#include <stdint.h>
#include <stdlib.h>
#include <string>
#include <cassert>

class Image
{
public:
    // constructor
    Image(){}
    Image(const char* file_name);
    Image(int w, int h, int channels);

    // copy constructor
    Image(const Image& img);

    ~Image();

    bool read(const char* file_name);
    bool write(const char* file_name);

    ImageExtn getImageType(const char* file_name);

    // image manipulation //
    void to_grayscaleAvg();
    void to_grayscaleLum();

    void colorMaskImage(float r, float g, float b);

    void flipVertical();

private:
    // 1-byte (8-bits) of pixel data
    uint8_t* data = nullptr;
    int _size;
    int _width;
    int _height;
    int _channels;
};


enum ImageExtn
{
    PNG, JPG, BMP, TGA
};