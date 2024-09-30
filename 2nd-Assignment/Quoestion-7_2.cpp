#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

// Function to count occurrences of a candidate in the original array
int countOccurrences(const vector<int>& arr, int candidate) {
    int count = 0;
    for (int num : arr) {
        if (num == candidate) {
            count++;
        }
    }
    return count;
}

// Recursive function to find the majority element
int findMajorityElementRec(const vector<int>& arr, int left, int right) {
    // Base case: if only one element
    if (left == right) {
        return arr[left];
    }

    // Pair up elements and discard accordingly
    vector<int> remaining;
    for (int i = left; i <= right; i += 2) {
        if (i + 1 <= right) { // Check for a valid pair
            if (arr[i] == arr[i + 1]) {
                remaining.push_back(arr[i]); // Keep one if they are the same
            }
            // If different, both are discarded
        } else {
            remaining.push_back(arr[i]); // Handle odd case
        }
    }

    // If there are no remaining elements, return -1
    if (remaining.empty()) {
        return -1;
    }

    // Recursively find the majority in the remaining elements
    return findMajorityElementRec(remaining, 0, remaining.size() - 1);
}

// Function to find the majority element
int findMajorityElement(const vector<int>& arr) {
    int candidate = findMajorityElementRec(arr, 0, arr.size() - 1);
    
    // Final check to see if candidate is actually a majority element
    if (countOccurrences(arr, candidate) > arr.size() / 2) {
        return candidate;
    }

    return -1; // No majority element
}

int main() {
    vector<int> nums = {2, 2, 1, 1, 1, 2, 2};
    int majorityElement = findMajorityElement(nums);
    
    if (majorityElement != -1) {
        cout << "The majority element is: " << majorityElement << endl;
    } else {
        cout << "There is no majority element." << endl;
    }

    return 0;
}
