#include "sorting.h"
#include <stdlib.h> 
#include <stddef.h>

void bubble_sort(int arr[], size_t n){
    if(n < 2) return;

    for(size_t i = 0; i < (n-1); i++){
        for(size_t j=1; j < n; j++){
            if (arr[j - 1] > arr[j]) {
                    int temp = arr[j - 1];
                    arr[j - 1] = arr[j];
                    arr[j] = temp;
            }
        }
    }

}

void bubble_sort_optimized(int arr[], size_t n){
    if(n < 2) return;

    for(size_t i = 0; i < (n-1); i++){
        int switched = 0;

        for(size_t j=1; j < (n-i); j++){
            if (arr[j - 1] > arr[j]) {
                    int temp = arr[j - 1];
                    arr[j - 1] = arr[j];
                    arr[j] = temp;

                    switched = 1;
            }
        }

        if(!switched){
            break;
        }
    }
}



void insertion_sort(int arr[], size_t n){
    if(n < 2) return;

    for(size_t i = 1; i < n; i++){
        int key = arr[i];
        size_t j = i;

        while(j > 0 && arr[j - 1] > key){
            arr[j] = arr[j - 1];
            j--;
        }
        arr[j] = key;   
    }
}



void selection_sort(int arr[], size_t n){
    if(n < 2) return;

    for(size_t i = 0; i < (n-1); i++){
        size_t min = i;
        
        for(size_t j = i+1; j<n; j++){
            if(arr[j] < arr[min]){
                min = j;
            }
        }

        if(i != min){
            int temp = arr[i];
            arr[i] = arr[min];
            arr[min] = temp;
        }
    }
}




/////////////////////////////////////////////////////

// merge sort e auxiliares

static void merge(int arr[], int temp[], size_t left, size_t mid, size_t right) {
    size_t i = left;
    size_t j = mid;
    size_t k = left;

    while (i < mid && j < right) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
        }
    }

    while (i < mid) {
        temp[k++] = arr[i++];
    }

    while (j < right) {
        temp[k++] = arr[j++];
    }

    for (size_t p = left; p < right; p++) {
        arr[p] = temp[p];
    }
}

static void merge_sort_recursive(int arr[], int temp[], size_t left, size_t right) {
    if (right - left <= 1) {
        return;
    }

    size_t mid = left + (right - left) / 2;

    merge_sort_recursive(arr, temp, left, mid);
    merge_sort_recursive(arr, temp, mid, right);

    merge(arr, temp, left, mid, right);
}

void merge_sort(int arr[], size_t n) {
    if (n < 2) {
        return;
    }

    int *temp = malloc(n * sizeof(int));

    if (temp == NULL) {
        return;
    }

    merge_sort_recursive(arr, temp, 0, n);

    free(temp);
}



//////////////////////////////////////////////////////

// quick sort e auxiliares

static size_t partition(int arr[], size_t left, size_t right){
    int pivot = arr[right -1];
    size_t i = left;

    for(size_t j = left; j < (right - 1); j++){
        if(arr[j] <= pivot){
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            i++;
        }
    }

    int temp = arr[i];
    arr[i] = arr[right -1];
    arr[right -1] = temp;

    return i;
}

static void quick_sort_recursive(int arr[], size_t left, size_t right, int random_pivot){
    if (right - left <= 1) {
        return;
    }

    size_t pivot_index;

    if (random_pivot) {
        pivot_index = left + (size_t)rand() % (right - left);
    } else {
        pivot_index = left;
    }

    int temp = arr[pivot_index];
    arr[pivot_index] = arr[right -1];
    arr[right -1] = temp;

    size_t p = partition(arr, left, right);

    quick_sort_recursive(arr, left, p, random_pivot);
    quick_sort_recursive(arr, p + 1, right, random_pivot);
}

void quick_sort_first_pivot(int arr[], size_t n) {
    quick_sort_recursive(arr, 0, n, 0);
}

void quick_sort_random_pivot(int arr[], size_t n) {
    quick_sort_recursive(arr, 0, n, 1);
}
