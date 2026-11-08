#ifndef SEARCH_H
#define SEARCH_H

#include <stddef.h>

ptrdiff_t linear_search(const int arr[], size_t n, int target);
ptrdiff_t binary_search(const int arr[], size_t n, int target);
ptrdiff_t interpolation_search(const int arr[], size_t n, int target);

#endif