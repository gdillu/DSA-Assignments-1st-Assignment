	#include <iostream>
		#include <vector>
		
		using namespace std;
		
		// Function to determine if it is possible to make change for amount v
		bool canMakeChange(const vector<int>& coins, int v) {
			vector<bool> dp(v + 1, false);
			dp[0] = true; // Base case: we can make change for 0
			
			for(int coin : coins) {
				for(int i = coin; i <= v; i++) {
					if(dp[i - coin]) {
						dp[i] = true;
					}
				}
			}
			
			return dp[v];
		}
		
		int main() {
			// Sample test cases
			vector<pair<vector<int>, int>> test_cases = {
				{{5, 10}, 15},   // Expected: Possible
				{{5, 10}, 12},   // Expected: Not possible
				{{1, 2, 5}, 11}, // Expected: Possible
				{{2}, 3},        // Expected: Not possible
				{{2, 3, 7}, 14}, // Expected: Possible
				{{3, 6, 9}, 13}, // Expected: Not possible
				{{1, 5, 10, 25}, 30}, // Expected: Possible
				{{4, 5}, 7},     // Expected: Not possible
				{{1}, 0},        // Expected: Possible (amount 0)
				{{}, 5},         // Expected: Not possible (no coins)
			};
			
			for(size_t i = 0; i < test_cases.size(); ++i) {
				const vector<int>& coins = test_cases[i].first;
				int v = test_cases[i].second;
				bool result = canMakeChange(coins, v);
				
				cout << "Test Case " << i + 1 << ": " << endl;
				cout << "Coins: ";
				for(int coin : coins) {
					cout << coin << " ";
				}
				cout << "\nAmount v: " << v << endl;
				cout << "Can make change? " << (result ? "Yes" : "No") << endl;
				cout << "-----------------------------\n";
			}
			
			return 0;
		}