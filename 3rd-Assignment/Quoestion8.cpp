#include <iostream>
		#include <vector>
		#include <string>
		#include <algorithm>
		
		using namespace std;
		
		// Function to find the length of the longest common substring
		int longestCommonSubstring(const string& X, const string& Y) {
			int n = X.size();
			int m = Y.size();
			int max_length = 0;
			
			// Create a 2D vector initialized with zeros
			vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
			
			// Build the dp table
			for(int i = 1; i <= n; i++) {
				for(int j = 1; j <= m; j++) {
					if(X[i - 1] == Y[j - 1]) {
						dp[i][j] = dp[i - 1][j - 1] + 1;
						max_length = max(max_length, dp[i][j]);
					} else {
						dp[i][j] = 0;
					}
				}
			}
			
			return max_length;
		}
		
		int main() {
			vector<pair<string, string>> test_cases = {
				{"ABAB", "BABA"},               // Expected: 3 ("ABA" or "BAB")
				{"abcdxyz", "xyzabcd"},         // Expected: 4 ("abcd")
				{"zxabcdezy", "yzabcdezx"},     // Expected: 6 ("abcdez")
				{"abc", "def"},                 // Expected: 0 (No common substring)
				{"abcdef", "abfdef"},           // Expected: 3 ("def")
				{"", "abcdef"},                 // Expected: 0 (Empty string)
				{"abcdef", ""},                 // Expected: 0 (Empty string)
				{"aaa", "aa"},                  // Expected: 2 ("aa")
				{"The quick brown fox", "quick brown"}, // Expected: 11 ("quick brown")
			};
			
			for(size_t i = 0; i < test_cases.size(); ++i) {
				const string& X = test_cases[i].first;
				const string& Y = test_cases[i].second;
				int length = longestCommonSubstring(X, Y);
				cout << "Test Case " << i + 1 << ": " << endl;
				cout << "String X: \"" << X << "\"" << endl;
				cout << "String Y: \"" << Y << "\"" << endl;
				cout << "Length of Longest Common Substring: " << length << endl;
				cout << "-----------------------------\n";
			}
			
			return 0;
		}