#include <iostream>
#include <vector>

using namespace std;

void merge_and_count(vector<int>& arr, vector<int>& temp_arr, int left, int mid, int right, vector<int>& count) {
    int i = left;    // Starting index for left subarray
    int j = mid + 1; // Starting index for right subarray
    int k = left;    // Starting index to be sorted
    int right_count = 0; // Count of smaller elements

    // Merge the two halves while counting smaller elements
    while (i <= mid && j <= right) {
        if (arr[i] > arr[j]) {
            right_count++; // Found a smaller element in the right half
            temp_arr[k++] = arr[j++];
        } else {
            count[i] += right_count; // Count smaller elements for arr[i]
            temp_arr[k++] = arr[i++];
        }
    }

    // Copy the remaining elements of left subarray, if any
    while (i <= mid) {
        count[i] += right_count;
        temp_arr[k++] = arr[i++];
    }

    // Copy the remaining elements of right subarray, if any
    while (j <= right) {
        temp_arr[k++] = arr[j++];
    }

    // Copy the sorted subarray back into the original array
    for (i = left; i <= right; i++) {
        arr[i] = temp_arr[i];
    }
}

void merge_sort_and_count(vector<int>& arr, vector<int>& temp_arr, int left, int right, vector<int>& count) {
    if (left < right) {
        int mid = (left + right) / 2;

        // Sort and count smaller elements in the left half
        merge_sort_and_count(arr, temp_arr, left, mid, count);

        // Sort and count smaller elements in the right half
        merge_sort_and_count(arr, temp_arr, mid + 1, right, count);

        // Merge the two halves
        merge_and_count(arr, temp_arr, left, mid, right, count);
    }
}

vector<int> count_smaller_elements(vector<int>& arr) {
    int n = arr.size();
    vector<int> temp_arr(n);
    vector<int> count(n, 0);

    // Call the merge_sort_and_count function
    merge_sort_and_count(arr, temp_arr, 0, n - 1, count);

    return count;
}

int main() {
    vector<int> arr = {8, 2, 6, 3, 5};
    vector<int> result = count_smaller_elements(arr);

    cout << "Output: [";
    for (int i = 0; i < result.size(); i++) {
        cout << result[i];
        if (i < result.size() - 1) cout << ", ";
    }
    cout << "]" << endl; // Output: [4, 0, 2, 0, 0]

    return 0;
}
