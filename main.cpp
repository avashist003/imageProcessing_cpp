#include"Image.h"

int main()
{
    Image test_img("bee.jpg");
    // test_img.flipVertical();
    // test_img.write("write_img.png");

    // Image copy = test_img;
    // for(int i = 0; i < copy._width*copy._channels; ++i)
    //     copy.data[i] = 255; // set top row pixels in copy image to white(255)
    
    // copy.write("copy.png");

    // Image blank(100,100,3);
    // blank.write("blank.png");

    Image gray_avg = test_img;
    gray_avg.to_grayscaleAvg();
    gray_avg.write("gray_img.png");

    Image mask_color = test_img;
    mask_color.colorMaskImage(1,0.5,1);
    mask_color.write("mask_img1.png");

    // std::string msg_in = "A";
    // test_img.encode(msg_in);
    // size_t len = 0;
    // char buffer[256];
    // test_img.decode(buffer, &len);

    return 0;
}