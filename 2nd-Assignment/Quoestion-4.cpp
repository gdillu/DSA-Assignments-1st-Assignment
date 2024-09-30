#include <iostream>

int partition(int arr[], int left, int right, int pivotIndex) {
    int pivot = arr[pivotIndex];
    std::swap(arr[pivotIndex], arr[left]); // Move pivot to the start
    int i = left + 1;
    int j = right;
    while(i<j){
        while (arr[i] <= pivot && i <= right-1){
            i++;
        }
        while (arr[j] >= pivot && j >= left -1){
            j--;
        }
        if (i<j){
            std::swap(arr[i],arr[j]);
        }
    }
    std::swap(arr[left],arr[j]);
    return j;
}

int quickselect(int arr[], int left, int right, int k) {
    if (left == right) {
        return arr[left]; // Only one element
    }

    // Randomly select a pivot index (for simplicity, we choose the rightmost element)
    int pivotIndex = left + (right - left) / 2; // or any other method to select pivot
    pivotIndex = partition(arr, left, right, pivotIndex);

    // The pivot is in its final sorted position
    if (k == pivotIndex) {
        return arr[k];
    } else if (k < pivotIndex) {
        return quickselect(arr, left, pivotIndex - 1, k);
    } else {
        return quickselect(arr, pivotIndex + 1, right, k);
    }
}

int findKthSmallest(int arr[], int n, int k) {
    // k is 1-based index
    return quickselect(arr, 0, n - 1, k - 1); // Convert k to 0-based index
}

int main() {
    int arr[] = {7, 10, 4, 3, 20, 15};
    int n = sizeof(arr) / sizeof(arr[0]);
    int k = 4; // Find the 3rd smallest element
    int result = findKthSmallest(arr, n, k);
    std::cout << "The " << k << "-th smallest element is " << result << std::endl;
    return 0;
}