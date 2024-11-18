#include <iostream>
#include <vector>
#include <algorithm>
		
		using namespace std;
		
		// Function to compute the Longest Common Subsequence (LCS)
		int lcs(const vector<char>& v1, const vector<char>& v2) {
			int n = v1.size();
			vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
			
			// Build the dp table
			for(int i = 1; i <= n; i++) {
				for(int j = 1; j <= n; j++) {
					if(v1[i - 1] == v2[j - 1]) {
						dp[i][j] = dp[i - 1][j - 1] + 1;
					} else {
						dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
					}
				}
			}
			// Return the length of the LCS
			return dp[n][n];
		}
		
		// Function to find the length of the longest palindromic subsequence
		int longestPalindromicSubsequence(const vector<char>& v) {
			vector<char> reversed_v = v;
			reverse(reversed_v.begin(), reversed_v.end());
			return lcs(v, reversed_v);
		}
		
		int main() {
			vector<vector<char>> test_cases = {
				{'A', 'G', 'T', 'A', 'T', 'G', 'D'},    // Expected LPS length: 5
				{'A', 'B', 'C', 'B', 'A'},              // Expected LPS length: 5
				{'A', 'A', 'A', 'A'},                   // Expected LPS length: 4
				{'B', 'A', 'B', 'B', 'A'},              // Expected LPS length: 5
				{'C', 'A', 'C', 'A', 'C'},              // Expected LPS length: 5
				{'D', 'E', 'F', 'E', 'D'},              // Expected LPS length: 5
				{'M', 'A', 'D', 'A', 'M'},              // Expected LPS length: 5
				{'R', 'A', 'C', 'E', 'C', 'A', 'R'},    // Expected LPS length: 7
				{'N', 'O', 'O', 'N'},                   // Expected LPS length: 4
				{'S', 'E', 'R', 'I', 'A', 'L'},         // Expected LPS length: 1
			};
			
			for (size_t i = 0; i < test_cases.size(); ++i) {
				cout << "Test Case " << i + 1 << ": ";
				for (char c : test_cases[i]) {
					cout << c << ' ';
				}
				cout << "\nLongest Palindromic Subsequence Length: ";
				int length = longestPalindromicSubsequence(test_cases[i]);
				cout << length << endl;
				cout << "-----------------------------\n";
			}
			return 0;
		}