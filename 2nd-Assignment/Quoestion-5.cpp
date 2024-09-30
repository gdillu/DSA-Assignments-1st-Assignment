#include <iostream>
#include <vector>
using namespace std;

// Function to count the number of elements in the matrix less than or equal to mid
int countLessEqual(const vector<vector<int>>& matrix, int mid, int m, int n) {
    int count = 0;
    int row = 0;         // Start from the first row
    int col = n - 1;     // Start from the last column
    
    // Traverse the matrix from the top-right corner
    while (row < m && col >= 0) {
        if (matrix[row][col] <= mid) {
            count += (col + 1);  // All elements in this row up to col are <= mid
            row++;               // Move to the next row
        } else {
            col--;               // Move to the left in the same row
        }
    }
    return count;
}

// Function to find the k-th smallest element in the matrix
int kthSmallest(const vector<vector<int>>& matrix, int k) {
    int m = matrix.size();
    int n = matrix[0].size();
    
    // Set binary search bounds
    int low = matrix[0][0];
    int high = matrix[m-1][n-1];
    
    // Binary search on the value range between matrix[0][0] and matrix[m-1][n-1]
    while (low < high) {
        int mid = low + (high - low) / 2;
        
        // Count the number of elements less than or equal to mid
        int count = countLessEqual(matrix, mid, m, n);
        
        // If count is less than k, the k-th smallest element is larger than mid
        if (count < k) {
            low = mid + 1;
        } else {
            high = mid;
        }
    }
    
    // After the loop, low == high and it points to the k-th smallest element
    return low;
}

int main() {
    vector<vector<int>> matrix = {
        {1, 2, 2},
        {3, 4, 5},
        {4, 5, 7}
    };
    
    int k = 3;
    int result = kthSmallest(matrix, k);
    cout << "The " << k << "-th smallest element is: " << result << endl;

    return 0;
} 