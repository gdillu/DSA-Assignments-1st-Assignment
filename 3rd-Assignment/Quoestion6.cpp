#include <iostream>
#include <vector>
#include <algorithm>
		
using namespace std;

void solve(int n, vector<int>& v) {
	// Include the starting point at mile post 0
	v.insert(v.begin(), 0);
	n = v.size();
	
	vector<int> dp(n, INT_MAX);
	vector<int> parent(n, -1); // To reconstruct the path
	dp[0] = 0; // No penalty at the starting point
	
	for(int i = 1; i < n; i++) {
		for(int j = 0; j < i; j++) {
			int distance = v[i] - v[j];
			int penalty = (200 - distance) * (200 - distance);
			int totalPenalty = dp[j] + penalty;
			if(totalPenalty < dp[i]) {
				dp[i] = totalPenalty;
				parent[i] = j; // Store the previous hotel index
			}
		}
	}
	
	// Output the minimum total penalty
	cout << "Minimum Total Penalty: " << dp[n - 1] << endl;
	
	// Reconstruct the optimal sequence of hotels
	vector<int> path;
	int idx = n - 1;
	while(idx != -1) {
		path.push_back(idx);
		idx = parent[idx];
	}
	reverse(path.begin(), path.end());
	
	// Output the optimal sequence of hotels
	cout << "Optimal Sequence of Hotels (mile posts):" << endl;
	for(int i = 1; i < path.size(); i++) { // Skip the starting point at index 0
		cout << v[path[i]] << " ";
	}
	cout << endl;
}

int main() {
	int n = 5;
	vector<int> v = {150,300,500,650,800}; // Hotel mile posts
	
	solve(n, v);
	
	return 0;
}