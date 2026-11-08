#include <stddef.h>


ptrdiff_t linear_search(const int arr[], size_t n, int target){
    for(size_t i = 0; i <n; i++){
        if(arr[i] == target){
            return i;
        }
    }
    return -1;
}

ptrdiff_t binary_search(const int arr[], size_t n, int target){
    size_t left = 0;
    size_t right = n-1; 

    while(left <= right && target >= arr[left] && target <= arr[right]){   
        size_t mid = left + (right - left) / 2;

        if (arr[mid] == target) {
            return (ptrdiff_t)mid;
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            if (mid == 0) break;
            right = mid - 1;
        }
    }

    return -1;
}


ptrdiff_t interpolation_search(const int arr[], size_t n, int target){
    size_t left = 0;
    size_t right = n-1; 

    while(left <= right && target >= arr[left] && target <= arr[right]){   
        if (arr[left] == arr[right]) {
            if (arr[left] == target) return (ptrdiff_t)left;
            break;
        }

        size_t pos = left + (size_t)(((double)(target - arr[left]) / (arr[right] - arr[left])) * (right - left));

        if (arr[pos] == target) {
            return (ptrdiff_t)pos;
        } else if (arr[pos] < target) {
            left = pos + 1;
        } else {
            if (pos == 0) break;
            right = pos - 1;
        }
        
    }

    return -1;
}

