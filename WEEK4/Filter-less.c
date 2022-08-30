#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int avg;
    // looping through each pixel
    for (int r = 0; r < height; r++)
    {
        for (int c = 0; c < width; c++)
        {
            // taking each color of the pixel and calculating its average
            avg = round((image[r][c].rgbtRed + image[r][c].rgbtBlue + image[r][c].rgbtGreen) / 3.0);
            // and then assigning the same value to each color
            image[r][c].rgbtRed = avg;
            image[r][c].rgbtBlue = avg;
            image[r][c].rgbtGreen = avg;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // declaring local variables to store the sepia colors
    int sepiaRed, sepiaGreen, sepiaBlue;
    // looping through each pixel
    for (int r = 0; r < height; r++)
    {
        for (int c = 0; c < width; c++)
        {
            // calculating sepia colors
            sepiaRed = round(.393 * image[r][c].rgbtRed + .769 * image[r][c].rgbtGreen + .189 * image[r][c].rgbtBlue);
            sepiaGreen = round(.349 * image[r][c].rgbtRed + .686 * image[r][c].rgbtGreen + .168 * image[r][c].rgbtBlue);
            sepiaBlue = round(.272 * image[r][c].rgbtRed + .534 * image[r][c].rgbtGreen + .131 * image[r][c].rgbtBlue);

            // checking the overflow condition with the ternary operator and assigning the correct value
            image[r][c].rgbtRed = sepiaRed > 255 ? 255 : sepiaRed;
            image[r][c].rgbtBlue = sepiaBlue > 255 ? 255 : sepiaBlue;
            image[r][c].rgbtGreen = sepiaGreen > 255 ? 255 : sepiaGreen;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // temporary variable to store the pixel value
    RGBTRIPLE temp;
    for (int r = 0; r < height; r++)
    {
        // looping through half of the columns because if we loop through all of the columns than in the first half of the columns it will reflect the image but then in the next half it will again reflect the image which would lead you to the end where the image would not be reflected
        for (int c = 0; c < (width / 2); c++)
        {
            temp = image[r][c];
            image[r][c] = image[r][width - (c + 1)];
            image[r][width - (c + 1)] = temp;
        }
    }
    return;
}

int getBlur(int i, int j, int height, int width, RGBTRIPLE image[height][width], int colorPos)
{
    // declaring a average variable for calculating the color of the current pixel
    float sum = 0;
    // declaring a counter variable to check how many pixel's color we have mapped
    int counter = 0;

    // starting the row loop from an index before the original pixel's index and maping three indexes values (that is one after the original pixel's index {counting one row up and one down from the original row in which the our pixel is present})
    for (int r = (i - 1); r < (i + 2); r++)
    {
        // starting the column loop from an index before the original pixel's index and maping three indexes values (that is one after the original pixel's index {counting one column left and one right from the original column in which the our pixel is present} )
        for (int c = (j - 1); c < (j + 2); c++)
        {
            // checking if our rows and columns get out of the range, if they do then we will skip the current iteration of for loop and move to the next one
            if (r < 0 || c < 0 || r >= height || c >= width)
            {
                continue;
            }
            // if the color position passed in the parameter is 0, which means it is a red color then we will calculating the sum of red color for all surrounding pixels
            if(colorPos == 0)
            {
                sum += image[r][c].rgbtRed;
            }
            // if the color position passed in the parameter is 1, which means it is a green color then we will calculating the sum of green color for all surrounding pixels
            else if(colorPos == 1)
            {
                sum += image[r][c].rgbtGreen;
            }
            // if the color position passed in the parameter is 2, which means it is a blue color then we will calculating the sum of blue color for all surrounding pixels
            else
            {
                sum += image[r][c].rgbtBlue;
            }
            counter++;

        }
    }
    // calculating the average for a specific color of all pixels and returning it
    return round(sum/counter);
}
// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // creating a copy of the original image
    RGBTRIPLE copy[height][width];

    // copying pixel by pixel value of the image[][] into copy[][]
    for (int r = 0; r < height; r++)
    {
        for (int c = 0; c < width; c++)
        {
            copy[r][c] = image[r][c];
        }
    }

    // iterating through each pixel to calculate its color
    for (int r = 0; r < height; r++)
    {
        for (int c = 0; c < width; c++)
        {
            // calling function on specific color with its color position( 0, 1 or 2)
            // also you may notice that we are passing the copy of the image as a parameter because it is not getting effected by the calculations of the colors, we are only retrieving the colors from it
            image[r][c].rgbtRed = getBlur(r, c, height, width, copy, 0);
            image[r][c].rgbtGreen = getBlur(r, c, height, width, copy, 1);
            image[r][c].rgbtBlue = getBlur(r, c, height, width, copy, 2);
        }
    }
    return;
}
