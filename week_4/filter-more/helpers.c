#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float Grey_value;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            Grey_value = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);

            image[i][j].rgbtRed = Grey_value;
            image[i][j].rgbtGreen = Grey_value;
            image[i][j].rgbtBlue = Grey_value;
        }
    }
    return;
}


// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int temp[3];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            temp[0] = image[i][j].rgbtRed;
            temp[1] = image[i][j].rgbtGreen;
            temp[2] = image[i][j].rgbtBlue;

            image[i][j].rgbtRed = image[i][width - j - 1].rgbtRed;
            image[i][j].rgbtGreen = image[i][width - j - 1].rgbtGreen;
            image[i][j].rgbtBlue = image[i][width - j - 1].rgbtBlue;

            image[i][width - j - 1].rgbtRed = temp[0];
            image[i][width - j - 1].rgbtGreen = temp[1];
            image[i][width - j - 1].rgbtBlue = temp[2];
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //create a copy of image
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int totalrgb[] = {0, 0, 0};
            float counter = 0.00;

            //Get neighbouring pixels
            for (int x = -1; x < 2; x++)
            {
                for (int y = -1; y < 2; y++)
                {
                    int aX = i + x;
                    int aY = j + y;

                    //check for valid neighbouring pexels
                    if (aX < 0 || aX > (height - 1) || aY < 0 || aY > (width - 1))
                    {
                        continue;
                    }

                    //Get the image value
                    totalrgb[0] += image[aX][aY].rgbtRed;
                    totalrgb[1] += image[aX][aY].rgbtGreen;
                    totalrgb[2] += image[aX][aY].rgbtBlue;

                    counter++;
                }

                //do the average of neigbhouring pexels
                temp[i][j].rgbtRed = round(totalrgb[0] / counter);
                temp[i][j].rgbtGreen = round(totalrgb[1] / counter);
                temp[i][j].rgbtBlue = round(totalrgb[2] / counter);
            }
        }

    }

    //copy the blurr image to the original image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = temp[i][j].rgbtRed;
            image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
            image[i][j].rgbtBlue = temp[i][j].rgbtBlue;
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    //Create copy of image
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];
        }
    }

    //Create array for sobel algorithm values
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int Gxrgb[] = {0, 0, 0};
            int Gyrgb[] = {0, 0, 0};

            //Going through the 3x3 grid
            for (int x = -1; x < 2; x++)
            {
                for (int y = -1; y < 2; y++)
                {
                    int aX = i + x;
                    int aY = j + y;

                    //check for valid neighbouring pixels
                    if (aX < 0 || aX > (height - 1) || aY < 0 || aY > (width - 1))
                    {
                        continue;
                    }
                    //add total up
                    Gxrgb[0] += temp[aX][aY].rgbtRed * Gx[x + 1][y + 1];
                    Gxrgb[1] += temp[aX][aY].rgbtGreen * Gx[x + 1][y + 1];
                    Gxrgb[2] += temp[aX][aY].rgbtBlue * Gx[x + 1][y + 1];
                    Gyrgb[0] += temp[aX][aY].rgbtRed * Gy[x + 1][y + 1];
                    Gyrgb[1] += temp[aX][aY].rgbtGreen * Gy[x + 1][y + 1];
                    Gyrgb[2] += temp[aX][aY].rgbtBlue * Gy[x + 1][y + 1];

                }
            }

            int rgb[3];

            for (int k = 0; k < 3; k++)
            {
                rgb[k] = round(sqrt((Gxrgb[k] * Gxrgb[k]) + (Gyrgb[k] * Gyrgb[k])));

                if (rgb[k] > 255)
                {
                    rgb[k] = 255;
                }
            }
            image[i][j].rgbtRed = rgb[0];
            image[i][j].rgbtGreen = rgb[1];
            image[i][j].rgbtBlue = rgb[2];
        }
    }

    return;
}
