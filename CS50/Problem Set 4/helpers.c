#include "helpers.h"
#include <math.h>
#include <stdlib.h>

int cap(double color);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            int avg = round(((float)image[i][j].rgbtBlue + (float)image[i][j].rgbtGreen + (float)image[i][j].rgbtRed)/3.0);
            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtRed = avg;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int width_len = width / 2; // if width is even, then we will do the whole row. Else, we do not modify the middle column.

    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width_len; j++)
        {
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width-j-1];
            image[i][width-j-1] = temp;
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int total_pixels = height * width;

    RGBTRIPLE tempimage[height][width];

    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            tempimage[i][j] = image[i][j];
        }
    }

    for(int i = 0; i < height; i++)
    {
        int startr = i-1;
        int endr = i+2;

        if(i == 0)
        {
            startr=i;
        }
        if(i == height-1)
        {
            endr = i+1;
        }

        for(int j = 0; j < width; j++)
        {
            int startc = j-1;
            int endc = j+2;
            int totalB = 0;
            int totalR = 0;
            int totalG = 0;
            int count = 0;

            if(j == 0)
            {
                startc = j;
            }
            if(j == width-1)
            {
                endc = j+1;
            }

            for(int k = startr; k < endr; k++)
            {
                for(int f = startc; f < endc; f++)
                {
                    totalB = totalB + tempimage[k][f].rgbtBlue;
                    totalR = totalR + tempimage[k][f].rgbtRed;
                    totalG = totalG + tempimage[k][f].rgbtGreen;
                    count++;
                }
            }

            image[i][j].rgbtBlue = round((float)totalB/(float)count);
            image[i][j].rgbtRed = round((float)totalR/(float)count);
            image[i][j].rgbtGreen = round((float)totalG/(float)count);
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{

    int padh = height + 2;
    int padw = width + 2;

    int gx[3][3] = {{-1, 0, 1},
                    {-2, 0, 2},
                    {-1, 0, 1}};

    int gy[3][3] = {{-1, -2, -1},
                    {0, 0, 0},
                    {1, 2, 1}};

    RGBTRIPLE(*tempimage)[width + 2] = calloc(height + 2, sizeof(RGBTRIPLE) * (width + 2));; // creating image copy with padding

    for(int i = 0; i < padh; i++)
    {
        for(int j = 0; j < padw; j++)
        {
            if(i == 0 || j == 0 || j == padw-1 || i == padh-1)
            {
                tempimage[i][j].rgbtBlue = 0;
                tempimage[i][j].rgbtGreen = 0;
                tempimage[i][j].rgbtRed = 0;
            }
            else
            {
                tempimage[i][j] = image[i-1][j-1];
            }
        }
    }

    for(int i = 1; i < padh-1; i++)
    {
        for(int j = 1; j < padw-1; j++)
        {
            int totalB_gx = 0;
            int totalR_gx = 0;
            int totalG_gx = 0;
            int totalB_gy = 0;
            int totalR_gy = 0;
            int totalG_gy = 0;

            int final_B = 0;
            int final_R = 0;
            int final_G = 0;

            for(int k = i-1, r = 0; k <= i + 1; k++, r++)
            {
                for(int f = j-1, c = 0; f <= j + 1; f++, c++)
                {

                    totalB_gx += (tempimage[k][f].rgbtBlue * gx[r][c]);
                    totalB_gy += (tempimage[k][f].rgbtBlue * gy[r][c]);
                    totalR_gx += (tempimage[k][f].rgbtRed * gx[r][c]);
                    totalR_gy += (tempimage[k][f].rgbtRed * gy[r][c]);
                    totalG_gx += (tempimage[k][f].rgbtGreen * gx[r][c]);
                    totalG_gy += (tempimage[k][f].rgbtGreen * gy[r][c]);
                }
            }

            final_B = cap(sqrt((pow(totalB_gx, 2.0)) + (pow(totalB_gy, 2.0))));
            final_R = cap(sqrt((pow(totalR_gx, 2.0)) + (pow(totalR_gy, 2.0))));
            final_G = cap(sqrt((pow(totalG_gx, 2.0)) + (pow(totalG_gy, 2.0))));

            image[i-1][j-1].rgbtBlue = final_B;
            image[i-1][j-1].rgbtRed = final_R;
            image[i-1][j-1].rgbtGreen = final_G;
        }
    }

    free(tempimage);

    return;
}

int cap(double color)
{
    int res;

    if(color > 255)
    {
        res = 255;
    }
    else
    {
        res = (int)round(color);
    }

    return res;
}


