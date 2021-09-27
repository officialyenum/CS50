#include "helpers.h"
#include "math.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Iterate over height
    for (int i = 0; i < height; i++)
    {
        // Iterare over width
        for (int j = 0; j < width; j++)
        {
            // Calculate the average of rgbt
            int k = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed)/3.0);

            // Update rgbt
            image[i][j].rgbtBlue = k;
            image[i][j].rgbtGreen = k;
            image[i][j].rgbtRed = k;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        //loop through width
        for (int j = 0; j < width; j++)
        {
            //USE SEPIA ALGORITHM and round to integer
            int sR = round((image[i][j].rgbtRed * .393) + (image[i][j].rgbtGreen * .769) + (image[i][j].rgbtBlue * .189));
            int sG = round((image[i][j].rgbtRed * .349) + (image[i][j].rgbtGreen * .686) + (image[i][j].rgbtBlue * .168));
            int sB = round((image[i][j].rgbtRed * .272) + (image[i][j].rgbtGreen * .534) + (image[i][j].rgbtBlue * .131));

            //CHECK IF SEPIA RED IS GREATER THAN 255 AND RE ASSIGN
            if (sR > 255)
            {
                sR = 255;
            }
            //CHECK IF SEPIA GREEN IS GREATER THAN 255 AND RE ASSIGN
            if (sG > 255)
            {
                sG = 255;
            }
            //CHECK IF SEPIA BLUE IS GREATER THAN 255 AND RE ASSIGN
            if (sB > 255)
            {
                sB = 255;
            }

            image[i][j].rgbtRed = sR;
            image[i][j].rgbtGreen = sG;
            image[i][j].rgbtBlue = sB;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    //LOOP HEIGHT
    for (int i = 0; i < height; i++)
    {
        //using IN-place implementation
        for (int low = 0, high = width - 1; low < high; low++, high--)
	    {
	        RGBTRIPLE copy = image[i][low];
            image[i][low] = image[i][high];
            image[i][high] = copy;
	    }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //duplicate image
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    //loop height
    for (int i = 0, red, green, blue, counter; i < height; i++)
    {
        //loop width
        for (int j = 0; j < width; j++)
        {
            //assign zero to rgb and counter
            red = green = blue = counter = 0;
            // add the center pixel
            if (i >= 0 && j >= 0)
            {
                red += copy[i][j].rgbtRed;
                green += copy[i][j].rgbtGreen;
                blue += copy[i][j].rgbtBlue;
                counter++;
            }
            // add below pixel
            if (i >= 0 && j - 1 >= 0)
            {
                red += copy[i][j - 1].rgbtRed;
                green += copy[i][j - 1].rgbtGreen;
                blue += copy[i][j - 1].rgbtBlue;
                counter++;
            }
            // add right pixel
            if ((i >= 0 && j + 1 >= 0) && (i >= 0 && j + 1 < width))
            {
                red += copy[i][j + 1].rgbtRed;
                green += copy[i][j + 1].rgbtGreen;
                blue += copy[i][j + 1].rgbtBlue;
                counter++;
            }
            // add left pixel
            if (i - 1 >= 0 && j >= 0)
            {
                red += copy[i - 1][j].rgbtRed;
                green += copy[i - 1][j].rgbtGreen;
                blue += copy[i - 1][j].rgbtBlue;
                counter++;
            }
            // add left below pixel
            if (i - 1 >= 0 && j - 1 >= 0)
            {
                red += copy[i - 1][j - 1].rgbtRed;
                green += copy[i - 1][j - 1].rgbtGreen;
                blue += copy[i - 1][j - 1].rgbtBlue;
                counter++;
            }
            // add left upper pixel
            if ((i - 1 >= 0 && j + 1 >= 0) && (i - 1 >= 0 && j + 1 < width))
            {
                red += copy[i - 1][j + 1].rgbtRed;
                green += copy[i - 1][j + 1].rgbtGreen;
                blue += copy[i - 1][j + 1].rgbtBlue;
                counter++;
            }
            // add upper pixel
            if ((i + 1 >= 0 && j >= 0) && (i + 1 < height && j >= 0))
            {
                red += copy[i + 1][j].rgbtRed;
                green += copy[i + 1][j].rgbtGreen;
                blue += copy[i + 1][j].rgbtBlue;
                counter++;
            }
            // add below right pixel
            if ((i + 1 >= 0 && j - 1 >= 0) && (i + 1 < height && j - 1 >= 0))
            {
                red += copy[i + 1][j - 1].rgbtRed;
                green += copy[i + 1][j - 1].rgbtGreen;
                blue += copy[i + 1][j - 1].rgbtBlue;
                counter++;
            }
            // add upper right pixel
            if ((i + 1 >= 0 && j + 1 >= 0) && (i + 1 < height && j + 1 < width))
            {
                red += copy[i + 1][j + 1].rgbtRed;
                green += copy[i + 1][j + 1].rgbtGreen;
                blue += copy[i + 1][j + 1].rgbtBlue;
                counter++;
            }

            //assign sum and pass it back to original pixel
            image[i][j].rgbtRed = round(red / (counter * 1.0));
            image[i][j].rgbtGreen = round(green / (counter * 1.0));
            image[i][j].rgbtBlue = round(blue / (counter * 1.0));
        }
    }

    return;
}
