#include <iostream> 
#include <stdio.h> 
#include <vector> 
#include <string> 
#include <unordered_map>

#define STB_IMAGE_IMPLEMENTATION 
#include "stb_image.h" 
#define STB_IMAGE_WRITE_IMPLEMENTATION 
#include "stb_image_write.h"

int width, height, channels;

int PosToIndex(int x, int y, int channels, int channel)
{
    return (x * channels + y * width * channels) + channel;
}

int PosToIndex(int x, int y)
{
    return x + (y * width);
}

int PosToIndex(int x, int y, int width)
{
    return x + (y * width);
}

int main()
{
  
    // Get image px array
    unsigned char* img = stbi_load("media/test1.jpg", &width, &height, &channels, 0);

    if (img == nullptr)
    {
        printf("Error in loading image\n");
        return 1;
    }
    std::cout << "Loaded image with a width of " << width << "px, a height of " << height << "px, and " << channels << " channels.\n";
    

    // Copy image data to new array
    const int arrayLength = width * height;
    unsigned char* greyscaleImg = new unsigned char[arrayLength];

    int count = 0;

    // Reduce to greyscale
    for (int i = 0; i < arrayLength * channels; i+=3)
    {
        int totalBrightness = 0;

        for (int j = 0; j < channels; j++)
        {
            totalBrightness += img[i + j];    
        }
        greyscaleImg[count] = static_cast<unsigned char>(totalBrightness / 3);
        count++;
    }

    // Downscale image
    int factor = 24; // Reduction = factor * factor
    int sqr = factor * factor;
    
    int downscaledLength = arrayLength / sqr;
    unsigned char* downscaledImg = new unsigned char[downscaledLength];

    int i = 0;

    int newHeight = 0;
    int newWidth = 0;

    for (int y = 0; y < height - factor; y += factor)
    {   
        newHeight++;
        newWidth = 0;
        for (int x = 0; x < width - factor; x += factor)
        {
            newWidth++;
            int sum = 0;
            for (int iy = 0; iy < factor; iy++)
            {
                for (int ix = 0; ix < factor; ix++)
                {
                    int index = PosToIndex(x + ix, y + iy);

                    sum += greyscaleImg[index];
                    sum *= 0.5; // Why tf does halving it give the correct brightness? thats not how averages work
                }
            }

            
            unsigned char result = static_cast<unsigned char>(sum);
            downscaledImg[i] = result;

            i++;
        } 
    }
    std::unordered_map<char, char> CharMap
    {
        { 0, ' ' },
        { 1, '.' },
        { 2, '-' },
        { 3, '+' },
        { 4, '*' },
        { 5, '#' },
        { 6, '&' },
        { 7, '@' },
    };

    std::string output;


    for (int i = 0; i < downscaledLength; i++)
    {
        char px = downscaledImg[i];
        output += CharMap[px / 16];
    }
    
    std::cout << output;
 
    //stbi_write_png("media/test40.jpg", newWidth, newHeight, 1, downscaledImg, newWidth);

    stbi_image_free(img);

    return 0;

}






