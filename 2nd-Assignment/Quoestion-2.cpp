#include <iostream>
#include <vector>
#include <algorithm> // For std::max
using namespace std;
vector<int> longestIncreasingSubsequence(const std::vector<int>& arr) {
    int n = arr.size();
    if (n == 0) return {};

    // Initialize the LIS array
    std::vector<int> LIS(n, 1);
    vector<int> prev(n,-1);
    // Compute optimized LIS values in a bottom-up manner
    for (int i = 1; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            if (arr[i] > arr[j] && LIS[i] < LIS[j] + 1) {
                LIS[i] = LIS[j] + 1;
                prev[i] = j;
            }
        }
    }

    // Find the maximum value in the LIS array
    int max = -1;
    int ind = -1;
    for(int i=0;i<n;i++){
        if (max < LIS[i]){
            max = LIS[i];
            ind = i;
        }
    }

    vector<int> sequence;
    for(int i=ind;i>=0;i=prev[i]){
        sequence.push_back(arr[i]);
        if(prev[i]==-1) break;
    }
    return sequence;
}

int main() {
    std::vector<int> arr = {4, 8, 5, 7, 2, 9, 10, 1};
    vector<int> res = longestIncreasingSubsequence(arr);
    std::cout << "The LIS is: ";
    for (int i=res.size()-1;i>=0;i--) {
        std::cout << res[i] << " ";
    }
    std::cout << std::endl;
    return 0;
}
