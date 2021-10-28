/*
Author: Filipe Chagas
        filipe.ferraz0@gmail.com
*/

#ifndef CCW_SORT_H
#define CCW_SORT_H

#include <stdint.h>

/**
 * @brief Get the counterclockwise rotation of a 2D vector.
 * 
 * @param x 
 * @param y 
 * @return float 
 */
float get_vec2d_ccw_rotation(float x, float y);

/**
 * @brief Calculate the centroid of a set of 2D vectors.
 * 
 * @param x_array Array of x-axis coordinates.
 * @param y_array Array of y-axis coordinates.
 * @param len Array length.
 * @param x_centroid Reference to the variable where centroid x coordinate will be stored.
 * @param y_centroid Reference to the variable where centroid y coordinate will be stored.
 */
void calculate_centroid(float *x_array, float *y_array, uint32_t len, float &x_centroid, float &y_centroid);

/**
 * @brief Sort points counterclosckwise.
 * 
 * @param x_array Array of x-axis coordinates.
 * @param y_array Array of y-axis coordinates.
 * @param len Array length.
 */
void ccw_selection_sort(float *x_array, float *y_array, uint32_t len);

#endif
