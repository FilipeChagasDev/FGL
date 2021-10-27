
/*
Author: Filipe Chagas
        filipe.ferraz0@gmail.com
*/

#include "ccw_sort.hpp"
#include <math.h>

#define ABS(v) (((v) >= 0) ? (v) : -(v))
#define PI 3.14159265359

float get_vec2d_ccw_rotation(float x, float y)
{
    float norm = sqrtf(x*x + y*y);
    float alpha = acos(x/norm);
    float beta = asin(y/norm);
    return (beta >= 0) ? alpha : 2*PI - alpha;
}

void calculate_centroid(float *x_array, float *y_array, uint32_t len, float &x_centroid, float &y_centroid)
{
    x_centroid = 0;
    y_centroid = 0;

    for(int i = 0; i < len; i++)
    {
        x_centroid += x_array[i];
        y_centroid += y_array[i];
    }

    x_centroid /= (float)len;
    y_centroid /= (float)len;
}

void ccw_selection_sort(float *x_array, float *y_array, uint32_t len)
{
    float cx, cy;
    calculate_centroid(x_array, y_array, len, cx, cy);

    for(int i = 0; i < len; i++)
    {
        int smaller_theta_index = i;
        float smaller_theta = get_vec2d_ccw_rotation(x_array[i]-cx, y_array[i]-cy);

        for(int j = i+1; j < len; j++)
        {
            float theta = get_vec2d_ccw_rotation(x_array[j]-cx, y_array[j]-cy);
            if(theta < smaller_theta)
            {
                smaller_theta_index = j;
                smaller_theta = theta;
            }
        }

        float tmpx = x_array[i];
        float tmpy = y_array[i];
        x_array[i] = x_array[smaller_theta_index];
        y_array[i] = y_array[smaller_theta_index];
        x_array[smaller_theta_index] = tmpx;
        y_array[smaller_theta_index] = tmpy;
    }
}
