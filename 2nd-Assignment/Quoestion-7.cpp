#include <iostream>
#include <vector>
#include <algorithm>

// Function to count occurrences of a candidate in the array
int countOccurrences(const std::vector<int>& arr, int candidate) {
    int count = 0;
    for (int num : arr) {
        if (num == candidate) {
            count++;
        }
    }
    return count;
}

// Function to find the majority element in the array using divide and conquer
int findMajorityElement(const std::vector<int>& arr, int left, int right) {
    // Base case: if the array has only one element
    if (left == right) {
        return arr[left];
    }

    // Divide the array into two halves
    int mid = left + (right - left) / 2;
    int leftMajority = findMajorityElement(arr, left, mid);
    int rightMajority = findMajorityElement(arr, mid + 1, right);

    // Combine: determine the majority element
    if (leftMajority == rightMajority) {
        return leftMajority;
    }

    int leftCount = countOccurrences(arr, leftMajority);
    int rightCount = countOccurrences(arr, rightMajority);

    return leftCount > rightCount ? leftMajority : rightMajority;
}

// Function to check if there is a majority element and find it
int majorityElement(std::vector<int>& arr) {
    int candidate = findMajorityElement(arr, 0, arr.size() - 1);
    int count = countOccurrences(arr, candidate);
    if (count > arr.size() / 2) {
        return candidate;
    }
    return -1; // No majority element
}

int main() {
    std::vector<int> arr = {1, 2, 2, 2, 3, 4, 2, 2, 2};
    int result = majorityElement(arr);
    if (result != -1) {
        std::cout << "The majority element is " << result << std::endl;
    } else {
        std::cout << "No majority element found" << std::endl;
    }
    return 0;
}
