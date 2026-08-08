// This file contains the 'main' function. Program execution begins and ends there.
#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
//#define STBI_WRITE_NO_STDIO
#include "stb_image_write.h"

int width, height, channels;

int PosToIndex(int x, int y, int channel)
{
    return (x * channels + y * width * channels) + channel;
}

int main()
{
  
    // Load image
    unsigned char* img = stbi_load("media/test1.jpg", &width, &height, &channels, 0);

    if (img == nullptr)
    {
        printf("Error in loading image\n");
        return 1;
    }
    std::cout << "Loaded image with a width of " << width << "px, a height of " << height << "px, and " << channels << " channels.\n";
    

    // Copy image data to new vector
    const int arrayLength = width * height * channels;
    std::vector<unsigned char> pixels(arrayLength);

    for (int i = 0; i < arrayLength; i++)
    {
        pixels[i] = img[i];
    }
   
    std::cout << 
        "R:" << std::to_string(pixels[PosToIndex(700, 439, 0)]) <<
        " G:" << std::to_string(pixels[PosToIndex(700, 439, 1)]) <<
        " B:" << std::to_string(pixels[PosToIndex(700, 439, 2)]);
    
    stbi_write_png("media/test6.jpg", width, height, 2, img, width * channels);

    stbi_image_free(img);

    return 0;

}






