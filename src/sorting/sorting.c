#include "sorting.h"

void bubble_sort(int arr[], size_t n){
    if(n < 2) return;

    for(size_t i = 0; i < (n-1); i++){
        for(size_t j=1; j < n; j++){
            if (arr[j - 1] < arr[j]) {
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
            if (arr[j - 1] < arr[j]) {
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
    
    for(int i = 1; i < n; i++){
        int key = arr[i];
        int j = (int)i-1;

        while(j>=0 && arr[j] > key){
            arr[j+1] = arr[j];
            j = j-1;
        }

        arr[j+1] = key;   
    }
}


void selection_sort(int arr[], size_t n){
    if(n < 2) return;

    for(int i = 0; i < (n-1); i++){
        int min = i;
        
        for(int j = i+1; j<n; j++){
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


void merge(int arr[], int left, int right, int mid){
    int size_temp1 = mid - left +1;
    int size_temp2 = right - mid;

    int temp1[size_temp1], temp2[size_temp2];


    for(int i = 0; i < size_temp1; i++){
        temp1[i] = arr[left + i];
    }

    for(int j = 0; j < size_temp2; j++){
        temp2[j] = arr[mid + 1 + j];
    }

    int i = 0, j = 0, k = left;

    while(i < size_temp1 && j < size_temp2){
        if(temp1[i] <= temp2[j]){
            arr[k] = temp1[i];
            i++;
        } else{
            arr[k] = temp2[j];
            j++;
        }
        k++;
    }

    while(i < temp1){
        arr[k] = temp1[i];
        i++;
        k++;
    }
    
    while(j < temp2){
        arr[k] = temp2[j];
        j++;
        k++;
    }
}

void merge_sort(int arr[], size_t n);
void quick_sort_first_pivot(int arr[], size_t n);
void quick_sort_random_pivot(int arr[], size_t n);
void heap_sort(int arr[], size_t n);