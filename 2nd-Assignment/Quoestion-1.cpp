#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Helper function to find the common prefix between two strings
string commonPrefix(const string& str1, const string& str2) {
    int minLength = min(str1.length(), str2.length());
    
    // Compare characters until they differ
    for (int i = 0; i < minLength; ++i) {
        if (str1[i] != str2[i]) {
            return str1.substr(0, i); // Return the substring up to the first mismatch
        }
    }
    
    return str1.substr(0, minLength); // If one string is a prefix of the other
}

// Recursive function that uses divide and conquer to find LCP in the range [low, high]
string longestCommonPrefixUtil(const vector<string>& arr, int low, int high) {
    // Base case: if there's only one string, return it
    if (low == high) {
        return arr[low];
    }

    // Divide the array into two halves
    int mid = low + (high - low) / 2;
    
    // LCP of the left half
    string leftLCP = longestCommonPrefixUtil(arr, low, mid);
    
    // LCP of the right half
    string rightLCP = longestCommonPrefixUtil(arr, mid + 1, high);
    
    // Return the common prefix of the two halves
    return commonPrefix(leftLCP, rightLCP);
}

// Main function to find the longest common prefix in an array of strings
string longestCommonPrefix(const vector<string>& arr) {
    if (arr.empty()) {
        return "";
    }
    return longestCommonPrefixUtil(arr, 0, arr.size() - 1);
}

int main() {
    vector<string> arr = {"apple", "ape", "april"};
    
    string result = longestCommonPrefix(arr);
    cout << "Longest Common Prefix: " << result << endl;
    
    return 0;
} 