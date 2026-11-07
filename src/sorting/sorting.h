#ifndef SORT_H
#define SORT_H

#include <stddef.h>

void bubble_sort(int arr[], size_t n);
void bubble_sort_optimized(int arr[], size_t n);
void insertion_sort(int arr[], size_t n);
void selection_sort(int arr[], size_t n);

void merge_sort(int arr[], size_t n);
void quick_sort_first_pivot(int arr[], size_t n);
void quick_sort_random_pivot(int arr[], size_t n);
void heap_sort(int arr[], size_t n);

#endif