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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{

    RGBTRIPLE copy[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    double red;
    double green;
    double blue;

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

            //Red Gx
            int zero_gx_red = (copy[first_row][first_column].rgbtRed) * (-1);
            int one_gx_red = (copy[first_row][second_column].rgbtRed) * (0);
            int two_gx_red = (copy[first_row][third_column].rgbtRed) * (1);
            int three_gx_red = (copy[second_row][first_column].rgbtRed) * (-2);
            int four_gx_red = (copy[second_row][second_column].rgbtRed) * (0);
            int five_gx_red = (copy[second_row][third_column].rgbtRed) * (2);
            int six_gx_red = (copy[third_row][first_column].rgbtRed) * (-1);
            int seven_gx_red = (copy[third_row][second_column].rgbtRed) * (0);
            int eight_gx_red = (copy[third_row][third_column].rgbtRed) * (1);

            //Red Gy
            int zero_gy_red = (copy[first_row][first_column].rgbtRed) * (-1);
            int one_gy_red = (copy[first_row][second_column].rgbtRed) * (-2);
            int two_gy_red = (copy[first_row][third_column].rgbtRed) * (-1);
            int three_gy_red = (copy[second_row][first_column].rgbtRed) * (0);
            int four_gy_red = (copy[second_row][second_column].rgbtRed) * (0);
            int five_gy_red = (copy[second_row][third_column].rgbtRed) * (0);
            int six_gy_red = (copy[third_row][first_column].rgbtRed) * (1);
            int seven_gy_red = (copy[third_row][second_column].rgbtRed) * (2);
            int eight_gy_red = (copy[third_row][third_column].rgbtRed) * (1);

            //Green Gx
            int zero_gx_green = (copy[first_row][first_column].rgbtGreen) * (-1);
            int one_gx_green = (copy[first_row][second_column].rgbtGreen) * (0);
            int two_gx_green = (copy[first_row][third_column].rgbtGreen) * (1);
            int three_gx_green = (copy[second_row][first_column].rgbtGreen) * (-2);
            int four_gx_green = (copy[second_row][second_column].rgbtGreen) * (0);
            int five_gx_green = (copy[second_row][third_column].rgbtGreen) * (2);
            int six_gx_green = (copy[third_row][first_column].rgbtGreen) * (-1);
            int seven_gx_green = (copy[third_row][second_column].rgbtGreen) * (0);
            int eight_gx_green = (copy[third_row][third_column].rgbtGreen) * (1);

            //Green Gy
            int zero_gy_green = (copy[first_row][first_column].rgbtGreen) * (-1);
            int one_gy_green = (copy[first_row][second_column].rgbtGreen) * (-2);
            int two_gy_green = (copy[first_row][third_column].rgbtGreen) * (-1);
            int three_gy_green = (copy[second_row][first_column].rgbtGreen) * (0);
            int four_gy_green = (copy[second_row][second_column].rgbtGreen) * (0);
            int five_gy_green = (copy[second_row][third_column].rgbtGreen) * (0);
            int six_gy_green = (copy[third_row][first_column].rgbtGreen) * (1);
            int seven_gy_green = (copy[third_row][second_column].rgbtGreen) * (2);
            int eight_gy_green = (copy[third_row][third_column].rgbtGreen) * (1);

            //Blue Gx
            int zero_gx_blue = (copy[first_row][first_column].rgbtBlue) * (-1);
            int one_gx_blue = (copy[first_row][second_column].rgbtBlue) * (0);
            int two_gx_blue = (copy[first_row][third_column].rgbtBlue) * (1);
            int three_gx_blue = (copy[second_row][first_column].rgbtBlue) * (-2);
            int four_gx_blue = (copy[second_row][second_column].rgbtBlue) * (0);
            int five_gx_blue = (copy[second_row][third_column].rgbtBlue) * (2);
            int six_gx_blue = (copy[third_row][first_column].rgbtBlue) * (-1);
            int seven_gx_blue = (copy[third_row][second_column].rgbtBlue) * (0);
            int eight_gx_blue = (copy[third_row][third_column].rgbtBlue) * (1);

            //Blue Gy
            int zero_gy_blue = (copy[first_row][first_column].rgbtBlue) * (-1);
            int one_gy_blue = (copy[first_row][second_column].rgbtBlue) * (-2);
            int two_gy_blue = (copy[first_row][third_column].rgbtBlue) * (-1);
            int three_gy_blue = (copy[second_row][first_column].rgbtBlue) * (0);
            int four_gy_blue = (copy[second_row][second_column].rgbtBlue) * (0);
            int five_gy_blue = (copy[second_row][third_column].rgbtBlue) * (0);
            int six_gy_blue = (copy[third_row][first_column].rgbtBlue) * (1);
            int seven_gy_blue = (copy[third_row][second_column].rgbtBlue) * (2);
            int eight_gy_blue = (copy[third_row][third_column].rgbtBlue) * (1);

            //Top left corner (4,5,7,8)
            if ((first_row < 0) && (first_column < 0))
            {
                int gx_red = (four_gx_red + five_gx_red + seven_gx_red + eight_gx_red);
                int gy_red = (four_gy_red + five_gy_red + seven_gy_red + eight_gy_red);
                int sub_red = pow(gx_red, 2) + pow(gy_red, 2);
                red = sqrt(sub_red);

                int gx_green = (four_gx_green + five_gx_green + seven_gx_green + eight_gx_green);
                int gy_green = (four_gy_green + five_gy_green + seven_gy_green + eight_gy_green);
                int sub_green = pow(gx_green, 2) + pow(gy_green, 2);
                green = sqrt(sub_green);

                int gx_blue = (four_gx_blue + five_gx_blue + seven_gx_blue + eight_gx_blue);
                int gy_blue = (four_gy_blue + five_gy_blue + seven_gy_blue + eight_gy_blue);
                int sub_blue = pow(gx_blue, 2) + pow(gy_blue, 2);
                blue = sqrt(sub_blue);
            }
            //Top right corner (3,4,6,7)
            else if ((first_row < 0) && (third_column == width))
            {
                int gx_red = (three_gx_red + four_gx_red + six_gx_red + seven_gx_red);
                int gy_red = (three_gy_red + four_gy_red + six_gy_red + seven_gy_red);
                int sub_red = pow(gx_red, 2) + pow(gy_red, 2);
                red = sqrt(sub_red);

                int gx_green = (three_gx_green + four_gx_green + six_gx_green + seven_gx_green);
                int gy_green = (three_gy_green + four_gy_green + six_gy_green + seven_gy_green);
                int sub_green = pow(gx_green, 2) + pow(gy_green, 2);
                green = sqrt(sub_green);

                int gx_blue = (three_gx_blue + four_gx_blue + six_gx_blue + seven_gx_blue);
                int gy_blue = (three_gy_blue + four_gy_blue + six_gy_blue + seven_gy_blue);
                int sub_blue = pow(gx_blue, 2) + pow(gy_blue, 2);
                blue = sqrt(sub_blue);
            }
            //Bottom left corner (1,2,4,5)
            else if ((third_row == height) && (first_column < 0))
            {
                int gx_red = (one_gx_red + two_gx_red + four_gx_red + five_gx_red);
                int gy_red = (one_gy_red + two_gy_red + four_gy_red + five_gy_red);
                int sub_red = pow(gx_red, 2) + pow(gy_red, 2);
                red = sqrt(sub_red);

                int gx_green = (one_gx_green + two_gx_green + four_gx_green + five_gx_green);
                int gy_green = (one_gy_green + two_gy_green + four_gy_green + five_gy_green);
                int sub_green = pow(gx_green, 2) + pow(gy_green, 2);
                green = sqrt(sub_green);

                int gx_blue = (one_gx_blue + two_gx_blue + four_gx_blue + five_gx_blue);
                int gy_blue = (one_gy_blue + two_gy_blue + four_gy_blue + five_gy_blue);
                int sub_blue = pow(gx_blue, 2) + pow(gy_blue, 2);
                blue = sqrt(sub_blue);
            }
            //Bottom right corner (0,1,3,4)
            else if ((third_row == height) && (third_column == width))
            {
                int gx_red = (zero_gx_red + one_gx_red + three_gx_red + four_gx_red);
                int gy_red = (zero_gy_red + one_gy_red + three_gy_red + four_gy_red);
                int sub_red = pow(gx_red, 2) + pow(gy_red, 2);
                red = sqrt(sub_red);

                int gx_green = (zero_gx_green + one_gx_green + three_gx_green + four_gx_green);
                int gy_green = (zero_gy_green + one_gy_green + three_gy_green + four_gy_green);
                int sub_green = pow(gx_green, 2) + pow(gy_green, 2);
                green = sqrt(sub_green);

                int gx_blue = (zero_gx_blue + one_gx_blue + three_gx_blue + four_gx_blue);
                int gy_blue = (zero_gy_blue + one_gy_blue + three_gy_blue + four_gy_blue);
                int sub_blue = pow(gx_blue, 2) + pow(gy_blue, 2);
                blue = sqrt(sub_blue);
            }
            //Top row (3,4,5,6,7,8)
            else if (first_row < 0)
            {
                int gx_red = (three_gx_red + four_gx_red + five_gx_red + six_gx_red + seven_gx_red + eight_gx_red);
                int gy_red = (three_gy_red + four_gy_red + five_gy_red + six_gy_red + seven_gy_red + eight_gy_red);
                int sub_red = pow(gx_red, 2) + pow(gy_red, 2);
                red = sqrt(sub_red);

                int gx_green = (three_gx_green + four_gx_green + five_gx_green + six_gx_green + seven_gx_green + eight_gx_green);
                int gy_green = (three_gy_green + four_gy_green + five_gy_green + six_gy_green + seven_gy_green + eight_gy_green);
                int sub_green = pow(gx_green, 2) + pow(gy_green, 2);
                green = sqrt(sub_green);

                int gx_blue = (three_gx_blue + four_gx_blue + five_gx_blue + six_gx_blue + seven_gx_blue + eight_gx_blue);
                int gy_blue = (three_gy_blue + four_gy_blue + five_gy_blue + six_gy_blue + seven_gy_blue + eight_gy_blue);
                int sub_blue = pow(gx_blue, 2) + pow(gy_blue, 2);
                blue = sqrt(sub_blue);
            }
            //Bottom row (0,1,2,3,4,5)
            else if (third_row == height)
            {
                int gx_red = (zero_gx_red + one_gx_red + two_gx_red + three_gx_red + four_gx_red + five_gx_red);
                int gy_red = (zero_gy_red + one_gy_red + two_gy_red + three_gy_red + four_gy_red + five_gy_red);
                int sub_red = pow(gx_red, 2) + pow(gy_red, 2);
                red = sqrt(sub_red);

                int gx_green = (zero_gx_green + one_gx_green + two_gx_green + three_gx_green + four_gx_green + five_gx_green);
                int gy_green = (zero_gy_green + one_gy_green + two_gy_green + three_gy_green + four_gy_green + five_gy_green);
                int sub_green = pow(gx_green, 2) + pow(gy_green, 2);
                green = sqrt(sub_green);

                int gx_blue = (zero_gx_blue + one_gx_blue + two_gx_blue + three_gx_blue + four_gx_blue + five_gx_blue);
                int gy_blue = (zero_gy_blue + one_gy_blue + two_gy_blue + three_gy_blue + four_gy_blue + five_gy_blue);
                int sub_blue = pow(gx_blue, 2) + pow(gy_blue, 2);
                blue = sqrt(sub_blue);
            }
            //Left side (1,2,4,5,7,8)
            else if (first_column < 0)
            {
                int gx_red = (one_gx_red + two_gx_red + four_gx_red + five_gx_red + seven_gx_red + eight_gx_red);
                int gy_red = (one_gy_red + two_gy_red + four_gy_red + five_gy_red + seven_gy_red + eight_gy_red);
                int sub_red = pow(gx_red, 2) + pow(gy_red, 2);
                red = sqrt(sub_red);

                int gx_green = (one_gx_green + two_gx_green + four_gx_green + five_gx_green + seven_gx_green + eight_gx_green);
                int gy_green = (one_gy_green + two_gy_green + four_gy_green + five_gy_green + seven_gy_green + eight_gy_green);
                int sub_green = pow(gx_green, 2) + pow(gy_green, 2);
                green = sqrt(sub_green);

                int gx_blue = (one_gx_blue + two_gx_blue + four_gx_blue + five_gx_blue + seven_gx_blue + eight_gx_blue);
                int gy_blue = (one_gy_blue + two_gy_blue + four_gy_blue + five_gy_blue + seven_gy_blue + eight_gy_blue);
                int sub_blue = pow(gx_blue, 2) + pow(gy_blue, 2);
                blue = sqrt(sub_blue);
            }
            //right side (0,1,3,4,6,7)
            else if (third_column == width)
            {
                int gx_red = (zero_gx_red + one_gx_red + three_gx_red + four_gx_red + six_gx_red + seven_gx_red);
                int gy_red = (zero_gy_red + one_gy_red + three_gy_red + four_gy_red + six_gy_red + seven_gy_red);
                int sub_red = pow(gx_red, 2) + pow(gy_red, 2);
                red = sqrt(sub_red);

                int gx_green = (zero_gx_green + one_gx_green + three_gx_green + four_gx_green + six_gx_green + seven_gx_green);
                int gy_green = (zero_gy_green + one_gy_green + three_gy_green + four_gy_green + six_gy_green + seven_gy_green);
                int sub_green = pow(gx_green, 2) + pow(gy_green, 2);
                green = sqrt(sub_green);

                int gx_blue = (zero_gx_blue + one_gx_blue + three_gx_blue + four_gx_blue + six_gx_blue + seven_gx_blue);
                int gy_blue = (zero_gy_blue + one_gy_blue + three_gy_blue + four_gy_blue + six_gy_blue + seven_gy_blue);
                int sub_blue = pow(gx_blue, 2) + pow(gy_blue, 2);
                blue = sqrt(sub_blue);
            }
            //(0,1,2,3,4,5,6,7,8)
            else
            {
                int gx_red = (zero_gx_red + one_gx_red + two_gx_red + three_gx_red + four_gx_red + five_gx_red + six_gx_red + seven_gx_red +
                              eight_gx_red);
                int gy_red = (zero_gy_red + one_gy_red + two_gy_red + three_gy_red + four_gy_red + five_gy_red + six_gy_red + seven_gy_red +
                              eight_gy_red);
                int sub_red = pow(gx_red, 2) + pow(gy_red, 2);
                red = sqrt(sub_red);

                int gx_green = (zero_gx_green + one_gx_green + two_gx_green + three_gx_green + four_gx_green + five_gx_green + six_gx_green +
                                seven_gx_green + eight_gx_green);
                int gy_green = (zero_gy_green + one_gy_green + two_gy_green + three_gy_green + four_gy_green + five_gy_green + six_gy_green +
                                seven_gy_green + eight_gy_green);
                int sub_green = pow(gx_green, 2) + pow(gy_green, 2);
                green = sqrt(sub_green);

                int gx_blue = (zero_gx_blue + one_gx_blue + two_gx_blue + three_gx_blue + four_gx_blue + five_gx_blue + six_gx_blue + seven_gx_blue
                               + eight_gx_blue);
                int gy_blue = (zero_gy_blue + one_gy_blue + two_gy_blue + three_gy_blue + four_gy_blue + five_gy_blue + six_gy_blue + seven_gy_blue
                               + eight_gy_blue);
                int sub_blue = pow(gx_blue, 2) + pow(gy_blue, 2);
                blue = sqrt(sub_blue);
            }

            int t_red = round(red);
            int t_green = round(green);
            int t_blue = round(blue);


            if (t_red > 255)
            {
                t_red = 255;
            }
            if (t_green > 255)
            {
                t_green = 255;
            }
            if (t_blue > 255)
            {
                t_blue = 255;
            }

            image[i][j].rgbtRed = t_red;
            image[i][j].rgbtGreen = t_green;
            image[i][j].rgbtBlue = t_blue;
        }
    }
    return;
}
