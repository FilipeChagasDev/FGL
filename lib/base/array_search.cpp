#include "array_search.hpp"
#include <assert.h>

float min_float(float *array, uint32_t len)
{
    assert(len > 0);
    assert(array != nullptr);

    float min = array[0];

    for(int i = 1; i < len; i++)
        if(array[i] < min) min = array[i];

    return min;
}

float max_float(float *array, uint32_t len)
{
    assert(len > 0);
    assert(array != nullptr);

    float max = array[0];

    for(int i = 1; i < len; i++)
        if(array[i] > max) max = array[i];

    return max;
}

void find_min_float(float *array, uint32_t len, float &min, uint32_t &min_index)
{
    assert(len > 0);
    assert(array != nullptr);

    min = array[0];
    min_index = 0;

    for(int i = 1; i < len; i++)
    {
        if(array[i] < min)
        {
            min = array[i];
            min_index = i;
        }
    }
}

void find_max_float(float *array, uint32_t len, float &max, uint32_t &max_index)
{
    assert(len > 0);

    max = array[0];
    max_index = 0;

    for(int i = 1; i < len; i++)
    {
        if(array[i] > max)
        {
            max = array[i];
            max_index = i;
        }
    }
}
