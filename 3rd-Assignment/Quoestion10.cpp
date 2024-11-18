#include <iostream>
		#include <vector>
		
		using namespace std;
		
		// Function to determine if it is possible to make change for amount v
		bool canMakeChangeOnce(const vector<int>& coins, int v) {
			int n = coins.size();
			vector<vector<bool>> dp(n + 1, vector<bool>(v + 1, false));
			dp[0][0] = true; // Base case: sum of 0 is possible with 0 coins
			
			for(int i = 1; i <= n; i++) {
				int coin = coins[i - 1];
				for(int j = 0; j <= v; j++) {
					// Exclude the current coin
					dp[i][j] = dp[i - 1][j];
					
					// Include the current coin if possible
					if(j >= coin && dp[i - 1][j - coin]) {
						dp[i][j] = true;
					}
				}
			}
			
			return dp[n][v];
		}
		
		int main() {
			// Sample test cases
			vector<pair<vector<int>, int>> test_cases = {
				{{1, 5, 10, 20}, 16}, // Expected: Yes (1 + 15)
				{{1, 5, 10, 20}, 31}, // Expected: Yes (1 + 10 + 20)
				{{1, 5, 10, 20}, 40}, // Expected: No
				{{2, 4, 6, 8}, 14},   // Expected: Yes (6 + 8)
				{{2, 4, 6, 8}, 15},   // Expected: No
				{{5, 10, 15}, 25},    // Expected: Yes (10 + 15)
				{{5, 10, 15}, 30},    // Expected: Yes (5 + 10 + 15)
				{{1, 2, 3, 4, 5}, 10},// Expected: Yes (1+2+3+4)
				{{}, 0},              // Expected: Yes (sum 0)
				{{}, 5},              // Expected: No (no coins)
			};
			
			for(size_t i = 0; i < test_cases.size(); ++i) {
				const vector<int>& coins = test_cases[i].first;
				int v = test_cases[i].second;
				bool result = canMakeChangeOnce(coins, v);
				
				cout << "Test Case " << i + 1 << ": " << endl;
				cout << "Coins: ";
				for(int coin : coins) {
					cout << coin << " ";
				}
				cout << "\nAmount v: " << v << endl;
				cout << "Can make change using each coin at most once? " << (result ? "Yes" : "No") << endl;
				cout << "-----------------------------\n";
			}
			
			return 0;
		}