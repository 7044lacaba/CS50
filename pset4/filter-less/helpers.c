#include "helpers.h"
#include <math.h>
#include <cs50.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>



// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            double average = ((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
            average = round(average);
            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            double sepia_red = (image[i][j].rgbtRed * 0.393) + (image[i][j].rgbtGreen * 0.769) + (image[i][j].rgbtBlue * 0.189);
            double sepia_green = (image[i][j].rgbtRed * 0.349) + (image[i][j].rgbtGreen * 0.686) + (image[i][j].rgbtBlue * 0.168);
            double sepia_blue = (image[i][j].rgbtRed * 0.272) + (image[i][j].rgbtGreen * 0.534) + (image[i][j].rgbtBlue * 0.131);

            if (sepia_red > 255)
            {
                sepia_red = 255;
            }
            if (sepia_green > 255)
            {
                sepia_green = 255;
            }
            if (sepia_blue > 255)
            {
                sepia_blue = 255;
            }

            image[i][j].rgbtRed = round(sepia_red);
            image[i][j].rgbtGreen = round(sepia_green);
            image[i][j].rgbtBlue = round(sepia_blue);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < (width / 2); j++)
        {
            int left = ((width - 1) - (width - j - 1));
            int right = (width - j - 1);

            //

            BYTE temp_a = image[i][left].rgbtRed;
            image[i][left].rgbtRed = image[i][right].rgbtRed;
            image[i][right].rgbtRed = temp_a;

            BYTE temp_b = image[i][left].rgbtGreen;
            image[i][left].rgbtGreen = image[i][right].rgbtGreen;
            image[i][right].rgbtGreen = temp_b;

            BYTE temp_c = image[i][left].rgbtBlue;
            image[i][left].rgbtBlue = image[i][right].rgbtBlue;
            image[i][right].rgbtBlue = temp_c;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //Copy all information from image to copy

    RGBTRIPLE copy[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int first_row = (i - 1);
            int second_row = i;
            int third_row = (i + 1);
            int first_column = (j - 1);
            int second_column = j;
            int third_column = (j + 1);

            BYTE red;
            BYTE green;
            BYTE blue;

            //Top left corner (4,5,7,8)
            if ((first_row < 0) && (first_column < 0))
            {
                red = round((copy[second_row][second_column].rgbtRed + copy[second_row][third_column].rgbtRed +
                             copy[third_row][second_column].rgbtRed + copy[third_row][third_column].rgbtRed) / 4.0);
                green = round((copy[second_row][second_column].rgbtGreen + copy[second_row][third_column].rgbtGreen +
                               copy[third_row][second_column].rgbtGreen + copy[third_row][third_column].rgbtGreen) / 4.0);
                blue = round((copy[second_row][second_column].rgbtBlue + copy[second_row][third_column].rgbtBlue +
                              copy[third_row][second_column].rgbtBlue + copy[third_row][third_column].rgbtBlue) / 4.0);
            }
            //Top right corner (3,4,6,7)
            else if ((first_row < 0) && (third_column == width))
            {
                red = round((copy[second_row][first_column].rgbtRed + copy[second_row][second_column].rgbtRed +
                             copy[third_row][first_column].rgbtRed + copy[third_row][second_column].rgbtRed) / 4.0);
                green = round((copy[second_row][first_column].rgbtGreen + copy[second_row][second_column].rgbtGreen +
                               copy[third_row][first_column].rgbtGreen + copy[third_row][second_column].rgbtGreen) / 4.0);
                blue = round((copy[second_row][first_column].rgbtBlue + copy[second_row][second_column].rgbtBlue +
                              copy[third_row][first_column].rgbtBlue + copy[third_row][second_column].rgbtBlue) / 4.0);
            }
            //Bottom left corner (1,2,4,5)
            else if ((third_row == height) && (first_column < 0))
            {
                red = round((copy[first_row][second_column].rgbtRed + copy[first_row][third_column].rgbtRed +
                             copy[second_row][second_column].rgbtRed + copy[second_row][third_column].rgbtRed) / 4.0);
                green = round((copy[first_row][second_column].rgbtGreen + copy[first_row][third_column].rgbtGreen +
                               copy[second_row][second_column].rgbtGreen + copy[second_row][third_column].rgbtGreen) / 4.0);
                blue = round((copy[first_row][second_column].rgbtBlue + copy[first_row][third_column].rgbtBlue +
                              copy[second_row][second_column].rgbtBlue + copy[second_row][third_column].rgbtBlue) / 4.0);
            }
            //Bottom right corner (0,1,3,4)
            else if ((third_row == height) && (third_column == width))
            {
                red = round((copy[first_row][first_column].rgbtRed + copy[first_row][second_column].rgbtRed + copy[second_row][first_column].rgbtRed
                             + copy[second_row][second_column].rgbtRed) / 4.0);
                green = round((copy[first_row][first_column].rgbtGreen + copy[first_row][second_column].rgbtGreen +
                               copy[second_row][first_column].rgbtGreen + copy[second_row][second_column].rgbtGreen) / 4.0);
                blue = round((copy[first_row][first_column].rgbtBlue + copy[first_row][second_column].rgbtBlue +
                              copy[second_row][first_column].rgbtBlue + copy[second_row][second_column].rgbtBlue) / 4.0);
            }
            //Top row (3,4,5,6,7,8)
            else if (first_row < 0)
            {
                red = round((copy[second_row][first_column].rgbtRed + copy[second_row][second_column].rgbtRed +
                             copy[second_row][third_column].rgbtRed + copy[third_row][first_column].rgbtRed + copy[third_row][second_column].rgbtRed +
                             copy[third_row][third_column].rgbtRed) / 6.0);
                green = round((copy[second_row][first_column].rgbtGreen + copy[second_row][second_column].rgbtGreen +
                               copy[second_row][third_column].rgbtGreen + copy[third_row][first_column].rgbtGreen + copy[third_row][second_column].rgbtGreen +
                               copy[third_row][third_column].rgbtGreen) / 6.0);
                blue = round((copy[second_row][first_column].rgbtBlue + copy[second_row][second_column].rgbtBlue +
                              copy[second_row][third_column].rgbtBlue + copy[third_row][first_column].rgbtBlue + copy[third_row][second_column].rgbtBlue +
                              copy[third_row][third_column].rgbtBlue) / 6.0);
            }
            //Bottom row (0,1,2,3,4,5)
            else if (third_row == height)
            {
                red = round((copy[first_row][first_column].rgbtRed + copy[first_row][second_column].rgbtRed + copy[first_row][third_column].rgbtRed
                             + copy[second_row][first_column].rgbtRed + copy[second_row][second_column].rgbtRed + copy[second_row][third_column].rgbtRed) / 6.0);
                green = round((copy[first_row][first_column].rgbtGreen + copy[first_row][second_column].rgbtGreen +
                               copy[first_row][third_column].rgbtGreen + copy[second_row][first_column].rgbtGreen + copy[second_row][second_column].rgbtGreen +
                               copy[second_row][third_column].rgbtGreen) / 6.0);
                blue = round((copy[first_row][first_column].rgbtBlue + copy[first_row][second_column].rgbtBlue +
                              copy[first_row][third_column].rgbtBlue + copy[second_row][first_column].rgbtBlue + copy[second_row][second_column].rgbtBlue +
                              copy[second_row][third_column].rgbtBlue) / 6.0);
            }
            //Left side (1,2,4,5,7,8)
            else if (first_column < 0)
            {
                red = round((copy[first_row][second_column].rgbtRed + copy[first_row][third_column].rgbtRed +
                             copy[second_row][second_column].rgbtRed + copy[second_row][third_column].rgbtRed + copy[third_row][second_column].rgbtRed +
                             copy[third_row][third_column].rgbtRed) / 6.0);
                green = round((copy[first_row][second_column].rgbtGreen + copy[first_row][third_column].rgbtGreen +
                               copy[second_row][second_column].rgbtGreen + copy[second_row][third_column].rgbtGreen + copy[third_row][second_column].rgbtGreen +
                               copy[third_row][third_column].rgbtGreen) / 6.0);
                blue = round((copy[first_row][second_column].rgbtBlue + copy[first_row][third_column].rgbtBlue +
                              copy[second_row][second_column].rgbtBlue + copy[second_row][third_column].rgbtBlue + copy[third_row][second_column].rgbtBlue +
                              copy[third_row][third_column].rgbtBlue) / 6.0);
            }
            //right side (0,1,3,4,6,7)
            else if (third_column == width)
            {
                red = round((copy[first_row][first_column].rgbtRed + copy[first_row][second_column].rgbtRed + copy[second_row][first_column].rgbtRed
                             + copy[second_row][second_column].rgbtRed + copy[third_row][first_column].rgbtRed + copy[third_row][second_column].rgbtRed) / 6.0);
                green = round((copy[first_row][first_column].rgbtGreen + copy[first_row][second_column].rgbtGreen +
                               copy[second_row][first_column].rgbtGreen + copy[second_row][second_column].rgbtGreen + copy[third_row][first_column].rgbtGreen +
                               copy[third_row][second_column].rgbtGreen) / 6.0);
                blue = round((copy[first_row][first_column].rgbtBlue + copy[first_row][second_column].rgbtBlue +
                              copy[second_row][first_column].rgbtBlue + copy[second_row][second_column].rgbtBlue + copy[third_row][first_column].rgbtBlue +
                              copy[third_row][second_column].rgbtBlue) / 6.0);
            }
            //(0,1,2,3,4,5,6,7,8)
            else
            {
                red = round((copy[first_row][first_column].rgbtRed + copy[first_row][second_column].rgbtRed + copy[first_row][third_column].rgbtRed
                             + copy[second_row][first_column].rgbtRed + copy[second_row][second_column].rgbtRed + copy[second_row][third_column].rgbtRed +
                             copy[third_row][first_column].rgbtRed + copy[third_row][second_column].rgbtRed + copy[third_row][third_column].rgbtRed) / 9.0);
                green = round((copy[first_row][first_column].rgbtGreen + copy[first_row][second_column].rgbtGreen +
                               copy[first_row][third_column].rgbtGreen + copy[second_row][first_column].rgbtGreen + copy[second_row][second_column].rgbtGreen +
                               copy[second_row][third_column].rgbtGreen + copy[third_row][first_column].rgbtGreen + copy[third_row][second_column].rgbtGreen +
                               copy[third_row][third_column].rgbtGreen) / 9.0);
                blue = round((copy[first_row][first_column].rgbtBlue + copy[first_row][second_column].rgbtBlue +
                              copy[first_row][third_column].rgbtBlue + copy[second_row][first_column].rgbtBlue + copy[second_row][second_column].rgbtBlue +
                              copy[second_row][third_column].rgbtBlue + copy[third_row][first_column].rgbtBlue + copy[third_row][second_column].rgbtBlue +
                              copy[third_row][third_column].rgbtBlue) / 9.0);
            }

            image[i][j].rgbtRed = red;
            image[i][j].rgbtGreen = green;
            image[i][j].rgbtBlue = blue;
        }
    }
    return;
}
