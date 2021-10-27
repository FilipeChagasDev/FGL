/*
Author: Filipe Chagas
        filipe.ferraz0@gmail.com
*/

#ifndef CCW_SORT_H
#define CCW_SORT_H

#include <stdint.h>

float get_vec2d_ccw_rotation(float x, float y);
void calculate_centroid(float *x_array, float *y_array, uint32_t len, float &x_centroid, float &y_centroid);
void ccw_selection_sort(float *x_array, float *y_array, uint32_t len);

#endif
