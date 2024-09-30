#include <iostream>
#include <vector>
using namespace std;

// Function to merge two halves of the array and count inversions
int mergeAndCount(vector<int>& arr, vector<int>& temp, int left, int mid, int right) {
    int i = left;    // Starting index for left subarray
    int j = mid + 1; // Starting index for right subarray
    int k = left;    // Starting index to be merged
    int inv_count = 0;

    // Merge the two halves while counting inversions
    while ((i <= mid) && (j <= right)) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
            // Inversion found, since arr[i] > arr[j] and i < j
            inv_count += (mid - i + 1); // All elements from arr[i] to arr[mid] are greater than arr[j]
        }
    }

    // Copy remaining elements of left subarray (if any)
    while (i <= mid) {
        temp[k++] = arr[i++];
    }

    // Copy remaining elements of right subarray (if any)
    while (j <= right) {
        temp[k++] = arr[j++];
    }

    // Copy the merged subarray back into the original array
    for (i = left; i <= right; i++) {
        arr[i] = temp[i];
    }

    return inv_count;
}

// Recursive function to count inversions using divide and conquer
int mergeSortAndCount(vector<int>& arr, vector<int>& temp, int left, int right) {
    int mid, inv_count = 0;
    if (left < right) {
        mid = left + (right - left) / 2;

        // Recursively count inversions in the left and right halves
        inv_count += mergeSortAndCount(arr, temp, left, mid);
        inv_count += mergeSortAndCount(arr, temp, mid + 1, right);

        // Merge the two halves and count inversions across them
        inv_count += mergeAndCount(arr, temp, left, mid, right);
    }
    return inv_count;
}

// Main function to count inversions in the array
int countInversions(vector<int>& arr) {
    vector<int> temp(arr.size());
    return mergeSortAndCount(arr, temp, 0, arr.size() - 1);
}

int main() {
    vector<int> arr = {2, 3, 8, 6, 1};

    int inversion_count = countInversions(arr);
    cout << "Number of inversions: " << inversion_count << endl;

    return 0;
}
 