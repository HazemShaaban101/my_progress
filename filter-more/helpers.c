#include "helpers.h"
#include <math.h>
#include <string.h>

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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int negative = -1;
    // identifying buffer Gx and Gy
    int bufferRx[height][width];
    int bufferGx[height][width];
    int bufferBx[height][width];
    int bufferRy[height][width];
    int bufferGy[height][width];
    int bufferBy[height][width];


    // buffer for corner 1
    {
        bufferRx[0][0] = (2 * image[0][1].rgbtRed) + image[1][1].rgbtRed;
        bufferGx[0][0] = (2 * image[0][1].rgbtGreen) + image[1][1].rgbtGreen;
        bufferBx[0][0] = (2 * image[0][1].rgbtBlue) + image[1][1].rgbtBlue;

        bufferRy[0][0] = (2 * image[1][0].rgbtRed) + image[1][1].rgbtRed;
        bufferGy[0][0] = (2 * image[1][0].rgbtGreen) + image[1][1].rgbtGreen;
        bufferBy[0][0] = (2 * image[1][0].rgbtBlue) + image[1][1].rgbtBlue;
    }
    // buffer for corner 2
    {
        bufferRx[0][width - 1] = (-2 * image[0][width - 2].rgbtRed) - image[1][width - 2].rgbtRed;
        bufferGx[0][width - 1] = (-2 * image[0][width - 2].rgbtGreen) - image[1][width - 2].rgbtGreen;
        bufferBx[0][width - 1] = (-2 * image[0][width - 2].rgbtBlue) - image[1][width - 2].rgbtBlue;

        bufferRy[0][width - 1] = (2 * image[1][width - 1].rgbtRed) + image[1][width - 2].rgbtRed;
        bufferGy[0][width - 1] = (2 * image[1][width - 1].rgbtGreen) + image[1][width - 2].rgbtGreen;
        bufferBy[0][width - 1] = (2 * image[1][width - 1].rgbtBlue) + image[1][width - 2].rgbtBlue;
    }
    // buffer for corner 3
    {
        bufferRx[height - 1][0] = (2 * image[height - 1][1].rgbtRed) + image[height - 2][1].rgbtRed;
        bufferGx[height - 1][0] = (2 * image[height - 1][1].rgbtGreen) + image[height - 2][1].rgbtGreen;
        bufferBx[height - 1][0] = (2 * image[height - 1][1].rgbtBlue) + image[height - 2][1].rgbtBlue;

        bufferRy[height - 1][0] = (-2 * image[height - 2][0].rgbtRed) - image[height - 2][1].rgbtRed;
        bufferGy[height - 1][0] = (-2 * image[height - 2][0].rgbtGreen) - image[height - 2][1].rgbtGreen;
        bufferBy[height - 1][0] = (-2 * image[height - 2][0].rgbtBlue) - image[height - 2][1].rgbtBlue;
    }
    // buffer for corner 4
    {
        bufferRx[height - 1][width - 1] = (-2 * image[height - 1][width - 2].rgbtRed) - image[height - 2][width - 2].rgbtRed;
        bufferGx[height - 1][width - 1] = (-2 * image[height - 1][width - 2].rgbtGreen) - image[height - 2][width - 2].rgbtGreen;
        bufferBx[height - 1][width - 1] = (-2 * image[height - 1][width - 2].rgbtBlue) - image[height - 2][width - 2].rgbtBlue;

        bufferRy[height - 1][width - 1] = (-2 * image[height - 2][width - 1].rgbtRed) - image[height - 2][width - 2].rgbtRed;
        bufferGy[height - 1][width - 1] = (-2 * image[height - 2][width - 1].rgbtGreen) - image[height - 2][width - 2].rgbtGreen;
        bufferBy[height - 1][width - 1] = (-2 * image[height - 2][width - 1].rgbtBlue) - image[height - 2][width - 2].rgbtBlue;
    }

    // loop for horizontal sides
    for (int j = 1; j < width - 1; j++)
    {
        // upper row
        bufferRx[0][j] = (2 * image[0][j + 1].rgbtRed) - (2 * image[0][j - 1].rgbtRed) + image[1][j + 1].rgbtRed -
                         image[1][j - 1].rgbtRed;
        bufferGx[0][j] = (2 * image[0][j + 1].rgbtGreen) - (2 * image[0][j - 1].rgbtGreen) + image[1][j + 1].rgbtGreen -
                         image[1][j - 1].rgbtGreen;
        bufferBx[0][j] = (2 * image[0][j + 1].rgbtBlue) - (2 * image[0][j - 1].rgbtBlue) + image[1][j + 1].rgbtBlue -
                         image[1][j - 1].rgbtBlue;

        bufferRy[0][j] = (2 * image[1][j].rgbtRed) + image[1][j + 1].rgbtRed + image[1][j - 1].rgbtRed;
        bufferGy[0][j] = (2 * image[1][j].rgbtGreen) + image[1][j + 1].rgbtGreen + image[1][j - 1].rgbtGreen;
        bufferBy[0][j] = (2 * image[1][j].rgbtBlue) + image[1][j + 1].rgbtBlue + image[1][j - 1].rgbtBlue;

        // lower row
        bufferRx[height - 1][j] = (2 * image[height - 1][j + 1].rgbtRed) - (2 * image[height - 1][j - 1].rgbtRed) +
                                  image[height - 2][j + 1].rgbtRed - image[height - 2][j - 1].rgbtRed;
        bufferGx[height - 1][j] = (2 * image[height - 1][j + 1].rgbtGreen) - (2 * image[height - 1][j - 1].rgbtGreen) +
                                  image[height - 2][j + 1].rgbtGreen - image[height - 2][j - 1].rgbtGreen;
        bufferBx[height - 1][j] = (2 * image[height - 1][j + 1].rgbtBlue) - (2 * image[height - 1][j - 1].rgbtBlue) +
                                  image[height - 2][j + 1].rgbtBlue - image[height - 2][j - 1].rgbtBlue;

        bufferRy[height - 1][j] = (-2 * image[height - 2][j].rgbtRed) - image[height - 2][j + 1].rgbtRed -
                                  image[height - 2][j - 1].rgbtRed;
        bufferGy[height - 1][j] = (-2 * image[height - 2][j].rgbtGreen) - image[height - 2][j + 1].rgbtGreen -
                                  image[height - 2][j - 1].rgbtGreen;
        bufferBy[height - 1][j] = (-2 * image[height - 2][j].rgbtBlue) - image[height - 2][j + 1].rgbtBlue -
                                  image[height - 2][j - 1].rgbtBlue;
    }

    // loop for vertical sides
    for (int i = 1; i < height - 1; i++)
    {
        // right column
        bufferRy[i][0] = (2 * image[i + 1][0].rgbtRed) - (2 * image[i - 1][0].rgbtRed) + image[i + 1][1].rgbtRed -
                         image[i - 1][1].rgbtRed;
        bufferGy[i][0] = (2 * image[i + 1][0].rgbtGreen) - (2 * image[i - 1][0].rgbtGreen) + image[i + 1][1].rgbtGreen -
                         image[i - 1][1].rgbtGreen;
        bufferBy[i][0] = (2 * image[i + 1][0].rgbtBlue) - (2 * image[i - 1][0].rgbtBlue) + image[i + 1][1].rgbtBlue -
                         image[i - 1][1].rgbtBlue;

        bufferRx[i][0] = (2 * image[i][1].rgbtRed) + image[i + 1][1].rgbtRed + image[i - 1][1].rgbtRed;
        bufferGx[i][0] = (2 * image[i][1].rgbtGreen) + image[i + 1][1].rgbtGreen + image[i - 1][1].rgbtGreen;
        bufferBx[i][0] = (2 * image[i][1].rgbtBlue) + image[i + 1][1].rgbtBlue + image[i - 1][1].rgbtBlue;

        // left column
        bufferRy[i][width - 1] = (2 * image[i + 1][width - 1].rgbtRed) - (2 * image[i - 1][width - 1].rgbtRed) +
                                 image[i + 1][width - 2].rgbtRed - image[i - 1][width - 2].rgbtRed;
        bufferGy[i][width - 1] = (2 * image[i + 1][width - 1].rgbtGreen) - (2 * image[i - 1][width - 1].rgbtGreen) +
                                 image[i + 1][width - 2].rgbtGreen - image[i - 1][width - 2].rgbtGreen;
        bufferBy[i][width - 1] = (2 * image[i + 1][width - 1].rgbtBlue) - (2 * image[i - 1][width - 1].rgbtBlue) +
                                 image[i + 1][width - 2].rgbtBlue - image[i - 1][width - 2].rgbtBlue;

        bufferRx[i][width - 1] = (-2 * image[i][width - 2].rgbtRed) - image[i + 1][width - 2].rgbtRed -
                                 image[i - 1][width - 2].rgbtRed;
        bufferGx[i][width - 1] = (-2 * image[i][width - 2].rgbtGreen) - image[i + 1][width - 2].rgbtGreen -
                                 image[i - 1][width - 2].rgbtGreen;
        bufferBx[i][width - 1] = (-2 * image[i][width - 2].rgbtBlue) - image[i + 1][width - 2].rgbtBlue -
                                 image[i - 1][width - 2].rgbtBlue;
    }

    // loop for Gx values
    for (int i = 1; i < height - 1; i++)
    {
        for (int j = 1; j < width - 1; j++)
        {
            // RED x buffer
            bufferRx[i][j] = (negative * image[i - 1][j - 1].rgbtRed) + 1 * (image[i - 1][j + 1].rgbtRed) +
                             (negative * 2 * image[i][j - 1].rgbtRed) + (2 * image[i][j + 1].rgbtRed) +
                             (negative * image[i + 1][j - 1].rgbtRed) + (1 * image[i + 1][j + 1].rgbtRed);

            // GREEN x buffer
            bufferGx[i][j] = (negative * image[i - 1][j - 1].rgbtGreen) + 1 * (image[i - 1][j + 1].rgbtGreen) +
                             (negative * 2 * image[i][j - 1].rgbtGreen) + (2 * image[i][j + 1].rgbtGreen) +
                             (negative * image[i + 1][j - 1].rgbtGreen) + (1 * image[i + 1][j + 1].rgbtGreen);

            // BLUE x buffer
            bufferBx[i][j] = (negative * image[i - 1][j - 1].rgbtBlue) + 1 * (image[i - 1][j + 1].rgbtBlue) +
                             (negative * 2 * image[i][j - 1].rgbtBlue) + (2 * image[i][j + 1].rgbtBlue) +
                             (negative * image[i + 1][j - 1].rgbtBlue) + (1 * image[i + 1][j + 1].rgbtBlue);
        }
    }

    // loop for Gy values
    for (int i = 1; i < height - 1; i++)
    {
        for (int j = 1; j < width - 1; j++)
        {
            // RED y buffer
            bufferRy[i][j] = (negative * image[i - 1][j - 1].rgbtRed) + (negative * 2 * image[i - 1][j].rgbtRed) +
                             (negative * image[i - 1][j + 1].rgbtRed) + (1 * image[i + 1][j - 1].rgbtRed) +
                             (2 * image[i + 1][j].rgbtRed) + (1 * image[i + 1][j + 1].rgbtRed);

            // GREEN y buffer
            bufferGy[i][j] = (negative * image[i - 1][j - 1].rgbtGreen) + (negative * 2 * image[i - 1][j].rgbtGreen) +
                             (negative * image[i - 1][j + 1].rgbtGreen) + (1 * image[i + 1][j - 1].rgbtGreen) +
                             (2 * image[i + 1][j].rgbtGreen) + (1 * image[i + 1][j + 1].rgbtGreen);

            // BLUE y buffer
            bufferBy[i][j] = (negative * image[i - 1][j - 1].rgbtBlue) + (negative * 2 * image[i - 1][j].rgbtBlue) +
                             (negative * image[i - 1][j + 1].rgbtBlue) + (1 * image[i + 1][j - 1].rgbtBlue) +
                             (2 * image[i + 1][j].rgbtBlue) + (1 * image[i + 1][j + 1].rgbtBlue);
        }
    }

    // capping all values to 255
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (bufferRx[i][j] > 255)
            {
                bufferRx[i][j] = 255;
            }
            if (bufferGx[i][j] > 255)
            {
                bufferGx[i][j] = 255;
            }
            if (bufferBx[i][j] > 255)
            {
                bufferBx[i][j] = 255;
            }
            if (bufferRy[i][j] > 255)
            {
                bufferRy[i][j] = 255;
            }
            if (bufferGy[i][j] > 255)
            {
                bufferGy[i][j] = 255;
            }
            if (bufferBy[i][j] > 255)
            {
                bufferBy[i][j] = 255;
            }
        }
    }
    // loop for output values
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            bufferRx[i][j] = round(sqrt(pow(bufferRx[i][j], 2) + pow(bufferRy[i][j], 2)));
            bufferGx[i][j] = round(sqrt(pow(bufferGx[i][j], 2) + pow(bufferGy[i][j], 2)));
            bufferBx[i][j] = round(sqrt(pow(bufferBx[i][j], 2) + pow(bufferBy[i][j], 2)));

            if (bufferRx[i][j] > 255)
            {
                bufferRx[i][j] = 255;
            }
            if (bufferGx[i][j] > 255)
            {
                bufferGx[i][j] = 255;
            }
            if (bufferBx[i][j] > 255)
            {
                bufferBx[i][j] = 255;
            }

            image[i][j].rgbtRed = bufferRx[i][j];
            image[i][j].rgbtGreen = bufferGx[i][j];
            image[i][j].rgbtBlue = bufferBx[i][j];

        }
    }
    return;
}
