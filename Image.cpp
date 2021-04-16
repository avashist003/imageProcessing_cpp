#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "stb_image.h"
#include "stb_image_write.h"

#include "Image.h"
#include <iostream>


Image::Image(const char* file_name)
{
    if(read(file_name))
    {
        std::cout << "SUCCESSFULLY Read the File! :-) : " << file_name << std::endl;
        _size = _width*_height*_channels;
    }
    else
    {
        std::cout << "FAILED to Read the Provided File! : " << file_name <<std::endl;
    }
}


Image::Image(int w, int h, int channels) : _width{w}, _height{h}, _channels{channels}, _size{w*h*channels}
{
    // dyn allocate the data
    data = new uint8_t[_size];
}


Image::Image(const Image& img) : Image(img._width, img._height, img._channels)
{
    // copy the data
    // void * memcpy ( void * destination, const void * source, size_t num );
    memcpy(data, img.data, _size);
}

Image::~Image()
{
    std::cout << "Destroying the image data here " << this << std::endl;
    stbi_image_free(data);
}

bool Image::read(const char* file_name)
{
    data = stbi_load(file_name, &_width, &_height, &_channels, 0);

    return data != NULL; // return true if data is not null else false
}

ImageExtn Image::getImageType(const char* file_name)
{
    const char* ext = strrchr(file_name, '.');
    if(ext != nullptr)
    {
		if(strcmp(ext, ".png") == 0) {
			return PNG;
		}
		else if(strcmp(ext, ".jpg") == 0) {
			return JPG;
		}
		else if(strcmp(ext, ".bmp") == 0) {
			return BMP;
		}
		else if(strcmp(ext, ".tga") == 0) {
			return TGA;
		}
	}

    return PNG;
}


bool Image::write(const char* file_name)
{
    ImageExtn type = getImageType(file_name);
    bool success;

    switch(type)
    {
        case PNG:
            success = stbi_write_png(file_name, _width, _height, _channels, data, _width*_channels);
            break;
        case JPG:
            success = stbi_write_jpg(file_name, _width, _height, _channels, data, 100);
            break;
        case BMP:
            success = stbi_write_bmp(file_name, _width, _height, _channels, data);
            break;
        case TGA:
            success = stbi_write_tga(file_name, _width, _height, _channels, data);
            break;
    }

    return success;
}

// void Image::to_grayscale()
// {
//     if(_channels < 3)
//         std::cout << "Image has less than 3 channels: " << std::endl;
    
//     else
//     {
//         for(int i = 0; i < _size; i+= _channels)
//         {
//             int gray_val = (data[i] + data[i+1] + data[i+2])/3;
//             memset(data+i, gray_val, 3);
//         }
//         std::cout << "SUCCESSFULLY converted img to GrayScale :-)" << std::endl;
//     }
    
// }


void Image::to_grayscaleAvg()
{
    assert(_channels == 3);

    // Logic //
    // (r+g+b)/3 and then set the gray value for all 3 channels per pixel // 
    int gray_value = 0;
    for(int i = 0; i < _size; i += _channels)
    {
        gray_value = (data[i] + data[i+1] + data[i+2])/3;
        memset(data+i, gray_value, 3);
    }
    std::cout << "SUCCESSFULLY converted img to GrayScale :-)" << std::endl;
}


void Image::colorMaskImage(float r, float g, float b)
{
    assert(_channels == 3);

    for(int i = 0; i < _size; i+=_channels)
    {
        data[i] = data[i]*r;
        data[i+1] = data[i+1]*g;
        data[i+2] = data[i+2]*b;
    }
}

void Image::to_grayscaleLum()
{
    assert(_channels == 3);

    int gray_value = 0;
    for(int i = 0; i < _size; i+=_channels)
    {
        // got this weight values from wiki :-p //
        gray_value = (0.2126*data[i] + 0.7152*data[i+1] + 0.0722*data[i+2])/3;
    }
}


void Image::flipVertical()
{
    assert(_channels == 3);

    uint8_t temp[3]; // temp for swap
    uint8_t* px1;
    uint8_t* px2;
    for(int y= 0; y < _height; ++y)
    {
        for(int x = 0; x < _width/2; ++x) // as we flip along vertical center
        {
            // we get the pixels and swap
            px1 = &data[(x+(y*_width))*_channels];
            px2 = &data[((_width -1 -x) + (y*_width))*_channels];
            memcpy(temp, px1, _channels);
            memcpy(px1, px2, _channels);
            memcpy(px2, temp, _channels);
        }
    }
}

// Steganography //
// void Image::encode(const std::string message)
// {
//     size_t len = message.length();
//     std::cout << "len in Bytes: " << len << std::endl;

//     // uint32_t len = strlen(message)*8;
//     // // check message size bound
//     //  // length in bits (so * by 8)
//     // if(len+ STEG_HEADDER_LEN > _size)
//     // {
//     //     std::cout << "[ERROR!!] Message too large to encode" << std::endl;
//     //     return;
//     // }
// }


// void Image::decode(char* buffer, size_t* messageLength)
// {
//     uint32_t len = 0;
//     for (uint8_t i = 0; i < STEG_HEADDER_LEN; i++)
//     {
//         len = (len << 1) | (data[i] & 1);
//     }

//     *messageLength = len/8; // in bytes

//     std::cout << "length: " << len << std::endl;
    
// }