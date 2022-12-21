#include "helpers.h"
#include <math.h>
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // for each pixel, calculate the mean of the 3 color values, then match the 3 color values to the mean
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int gray = roundf((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            image[i][j].rgbtBlue = gray;
            image[i][j].rgbtGreen = gray;
            image[i][j].rgbtRed = gray;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // define 3 sebia colors for calculations
    float sebiared;
    float sebiagreen;
    float sebiablue;

    // for each pixel, calculate sebia values
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            sebiared = 0.393 * image[i][j].rgbtRed + 0.769 * image[i][j].rgbtGreen + 0.189 * image[i][j].rgbtBlue;
            sebiagreen = 0.349 * image[i][j].rgbtRed + 0.686 * image[i][j].rgbtGreen + 0.168 * image[i][j].rgbtBlue;
            sebiablue = 0.272 * image[i][j].rgbtRed + 0.534 * image[i][j].rgbtGreen + 0.131 * image[i][j].rgbtBlue;

            // capping sebia colors to 255
            if (sebiared > 255.0)
            {
                sebiared = 255.0;
            }
            if (sebiagreen > 255.0)
            {
                sebiagreen = 255.0;
            }
            if (sebiablue > 255.0)
            {
                sebiablue = 255.0;
            }

            //rounding up
            image[i][j].rgbtRed = roundf(sebiared);
            image[i][j].rgbtGreen = roundf(sebiagreen);
            image[i][j].rgbtBlue = roundf(sebiablue);

        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // define buffer as RGBTRIBLE containing 3 BYTES
    RGBTRIPLE buffer;

    // for each pixel, on the first horizontal half of the image, swap the values with its mirror pixel from other side
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            buffer = image[i][j];
            image[i][j] = image[i][(width - 1) - j];
            image[i][(width - 1) - j] = buffer;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // define 3 matrices the size of image, one for each color
    double bufferR1[height][width];
    double bufferG1[height][width];
    double bufferB1[height][width];

    // sum the middle digits with the 2 digits on its side, and output te value to the buffer
    for (int i = 0; i < height; i++)
    {
        for (int j = 1; j < width - 1; j++)
        {
            bufferR1[i][j] = ((image[i][j - 1].rgbtRed + image[i][j].rgbtRed + image[i][j + 1].rgbtRed) / 3.00);
            bufferG1[i][j] = ((image[i][j - 1].rgbtGreen + image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen) / 3.00);
            bufferB1[i][j] = ((image[i][j - 1].rgbtBlue + image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue) / 3.00);
        }
    }
    // sum the sides each with the column next to it, and output the value to buffer
    for (int i = 0; i < height; i++)
    {
        bufferR1[i][0] = ((image[i][0].rgbtRed + image[i][1].rgbtRed) / 2.00);
        bufferG1[i][0] = ((image[i][0].rgbtGreen + image[i][1].rgbtGreen) / 2.00);
        bufferB1[i][0] = ((image[i][0].rgbtBlue + image[i][1].rgbtBlue) / 2.00);
        //====================================================================//
        bufferR1[i][width - 1] = ((image[i][width - 1].rgbtRed + image[i][width - 2].rgbtRed) / 2.00);
        bufferG1[i][width - 1] = ((image[i][width - 1].rgbtGreen + image[i][width - 2].rgbtGreen) / 2.00);
        bufferB1[i][width - 1] = ((image[i][width - 1].rgbtBlue + image[i][width - 2].rgbtBlue) / 2.00);
    }

    //=============================================================================================//

    // sum each digit with the one on top of it, and the one below it, and then round and save it in image array
    for (int i = 1; i < height - 1; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = round((bufferR1[i - 1][j] + bufferR1[i][j] + bufferR1[i + 1][j]) / 3.00);
            image[i][j].rgbtGreen = round((bufferG1[i - 1][j] + bufferG1[i][j] + bufferG1[i + 1][j]) / 3.00);
            image[i][j].rgbtBlue = round((bufferB1[i - 1][j] + bufferB1[i][j] + bufferB1[i + 1][j]) / 3.00);
        }
    }
    // sum each digit with the one on top of it, or the one below it, and then round and save it in image array
    for (int j = 0; j < width; j++)
    {
        image[0][j].rgbtRed = round((bufferR1[0][j] + bufferR1[1][j]) / 2.00);
        image[0][j].rgbtGreen = round((bufferG1[0][j] + bufferG1[1][j]) / 2.00);
        image[0][j].rgbtBlue = round((bufferB1[0][j] + bufferB1[1][j]) / 2.00);
        //====================================================================//
        image[height - 1][j].rgbtRed = round((bufferR1[height - 1][j] + bufferR1[height - 2][j]) / 2.00);
        image[height - 1][j].rgbtGreen = round((bufferG1[height - 1][j] + bufferG1[height - 2][j]) / 2.00);
        image[height - 1][j].rgbtBlue = round((bufferB1[height - 1][j] + bufferB1[height - 2][j]) / 2.00);
    }
    return;
}