#include "helpers.h"
#include <stdio.h>
#include <math.h>
void swap(BYTE *a, BYTE *b);
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height ; i++){
        for (int j = 0; j < width ; j ++){
            int newValue = ((image[i][j].rgbtBlue + image[i][j].rgbtRed + image[i][j].rgbtGreen)/3.0);
            image[i][j].rgbtBlue = newValue;
            image[i][j].rgbtRed = newValue;
            image[i][j].rgbtGreen = newValue;
        }
     }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height ; i++){
        for (int j = 0; j < width/2 ; j ++){
            swap(&image[i][j].rgbtBlue, &image[i][width - j - 1].rgbtBlue);
            swap(&image[i][j].rgbtRed, &image[i][width - j - 1].rgbtRed);
            swap(&image[i][j].rgbtGreen, &image[i][width - j - 1].rgbtGreen);
        }
    }
    return;
}
void swap(BYTE *a, BYTE *b){
    BYTE tmp = *a;
    *a = *b;
    *b = tmp;
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height ; i++){
        for (int j = 0; j < width ; j ++){
            int counter = 0;
            int red = 0, blue = 0, green = 0;

            for (int r = i - 1 ; r < i + 2; r++){
                for (int c = j - 1 ; c < j + 2; c++){
                    if (r>=0 && c >= 0 && r < height && c < width ){
                        blue += image[r][c].rgbtBlue;
                        red += image[r][c].rgbtRed;
                        green += image[r][c].rgbtGreen;
                        counter ++;
                    }
                }
            }
            temp[i][j].rgbtBlue = blue/counter;
            temp[i][j].rgbtRed = red/counter;
            temp[i][j].rgbtGreen = green/counter;
        }
    }
        for (int i = 0; i < height ; i++){
    for (int j = 0; j < width ; j ++){
        image[i][j] = temp[i][j];
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE renderImage[height][width];
    RGBTRIPLE tempMatrix[3][3];
    int Gx[3][3] = {{-1,0,1},{-2,0,2},{-1,0,1}};
    int Gy[3][3] = {{-1,-2,-1},{0,0,0},{1,2,1}};
    int value = 0;


    for (int i = 0; i < height ; i++){
        for (int j = 0; j < width ; j ++){
            int r_index = 0;
            int value_Red_y = 0, value_Green_y = 0, value_Blue_y = 0;
            int value_Red_x = 0, value_Green_x = 0, value_Blue_x = 0;
            for (int r = i - 1 ; r < i + 2; r++){
                int c_index = 0;
                for (int c = j - 1 ; c < j + 2; c++){
                        if (r>=0 && c >= 0 && r < height && c < width ){
                            tempMatrix[r_index][c_index] = image[r][c];
                        }
                        else {
                            tempMatrix[r_index][c_index].rgbtBlue = 0;
                            tempMatrix[r_index][c_index].rgbtRed = 0;
                            tempMatrix[r_index][c_index].rgbtGreen = 0;
                        }
                        value_Blue_x += (tempMatrix[r_index][c_index].rgbtBlue*Gx[r_index][c_index]);
                        value_Red_x += (tempMatrix[r_index][c_index].rgbtRed*Gx[r_index][c_index]);
                       value_Green_x += (tempMatrix[r_index][c_index].rgbtGreen*Gx[r_index][c_index]);

                        value_Blue_y += (tempMatrix[r_index][c_index].rgbtBlue*Gy[r_index][c_index]);
                        value_Red_y += (tempMatrix[r_index][c_index].rgbtRed*Gy[r_index][c_index]);
                        value_Green_y += (tempMatrix[r_index][c_index].rgbtGreen*Gy[r_index][c_index]);

                        c_index ++;
                }
                r_index ++;
            }

          renderImage[i][j].rgbtBlue = ((int)sqrt(pow(value_Blue_x,2)+pow(value_Blue_y,2))>255) ? 255 : (int)sqrt(pow(value_Blue_x,2)+pow(value_Blue_y,2));
           renderImage[i][j].rgbtRed = ((int)sqrt(pow(value_Red_x,2)+pow(value_Red_y,2))>255) ? 255 : (int)sqrt(pow(value_Red_x,2)+pow(value_Red_y,2));
           renderImage[i][j].rgbtGreen = ((int)sqrt(pow(value_Green_x,2)+pow(value_Green_y,2))>255) ? 255 : (int)sqrt(pow(value_Green_x,2)+pow(value_Green_y,2));
        }
    }

    for (int i = 0; i < height ; i++){
        for (int j = 0; j < width ; j ++){
            image[i][j] = renderImage[i][j];
        }
    }
    return;
}
