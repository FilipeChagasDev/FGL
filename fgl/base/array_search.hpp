// Author: Filipe Chagas

#ifndef ARRAY_SEARCH_HPP
#define ARRAY_SEARCH_HPP

#include <stdint.h>

float min_float(float *array, uint32_t len);
float max_float(float *array, uint32_t len);
void find_min_float(float *array, uint32_t len, float &min, uint32_t &min_index);
void find_min_float(float *array, uint32_t len, float &max, uint32_t &min_index);

#endif // ARRAY_SEARCH_H
