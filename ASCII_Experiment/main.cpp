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
    int factor = 2; // Reduction = factor * factor
    int sqr = factor * factor;
    
    int downscaledLength = arrayLength / sqr;
    unsigned char* downscaledImg = new unsigned char[downscaledLength];

    int i = 0;
    int avg = 0;

    for (int y = 0; y < height; y += factor)
    {   
        for (int x = 0; x < width; x += factor)
        {
            for (int iy = 0; iy < factor; iy++)
            {
                for (int ix = 0; ix < factor; ix++)
                {
                    avg = 0;
                    avg += greyscaleImg[PosToIndex(x + ix, y + iy, width)];
                    avg /= sqr;
                }
            }
            
            unsigned char result = static_cast<unsigned char>(avg);
            downscaledImg[i] = result;

            i++;
        } 
        
        

    }
  
    
    //stbi_write_png("media/test26.jpg", width, height, 1, greyscaleImg, width-100);
    stbi_write_png("media/test29.jpg", width / factor, height / factor, 1, downscaledImg, width / factor);

    stbi_image_free(img);

    return 0;

}






