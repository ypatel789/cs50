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

int max (int RGB)
{
    if (RGB > 255)
    {
        RGB = 255;
    }
    return RGB;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    float sepiared;
    float sepiagreen;
    float sepiablue;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            sepiared = max(round((image[i][j].rgbtRed * 0.393) + (image[i][j].rgbtGreen * 0.769) + (image[i][j].rgbtBlue * 0.189)));
            sepiagreen = max(round((image[i][j].rgbtRed * 0.349) + (image[i][j].rgbtGreen * 0.686) + (image[i][j].rgbtBlue * 0.168)));
            sepiablue = max(round((image[i][j].rgbtRed * 0.272) + (image[i][j].rgbtGreen * 0.534) + (image[i][j].rgbtBlue * 0.131)));

            image[i][j].rgbtRed = sepiared;
            image[i][j].rgbtGreen = sepiagreen;
            image[i][j].rgbtBlue = sepiablue;
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
    //create a temporary image to implement blurred algorithm on it.
    RGBTRIPLE temp[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int totalrgb[] = {0, 0, 0};
            float counter = 0.00;

            //Get the neighbouring pexels
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
