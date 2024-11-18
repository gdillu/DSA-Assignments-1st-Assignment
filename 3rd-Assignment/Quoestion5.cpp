#include <iostream>
		#include <vector>
		
		using namespace std;
		
		// Structure to hold the result
		struct Subsequence {
			int start;
			int end;
			int sum;
		};
		
		// Function to find the contiguous subsequence with maximum sum
		Subsequence maxSubsequence(const vector<int>& v) {
			Subsequence result;
			int max_so_far = 0;
			int max_ending_here = 0;
			int s = 0;
			result.start = 0;
			result.end = -1; // Indicates empty subsequence
			result.sum = 0;
			
			for(int i = 0; i < v.size(); i++) {
				max_ending_here += v[i];
				
				if(max_ending_here < 0) {
					max_ending_here = 0;
					s = i + 1;
				} else if(max_so_far < max_ending_here) {
					max_so_far = max_ending_here;
					result.start = s;
					result.end = i;
					result.sum = max_so_far;
				}
			}
			
			return result;
		}
		
		int main() {
			// Sample data
			vector<int> S = {5, 15, -30, 10, -5, 40, 10};
			
			// Find the maximum subsequence
			Subsequence max_seq = maxSubsequence(S);
			
			// Output the result
			cout << "Input Sequence: ";
			for (int num : S) {
				cout << num << " ";
			}
			cout << endl;
			
			if (max_seq.end == -1) {
				cout << "The maximum sum is 0 (empty subsequence)." << endl;
			} else {
				cout << "Maximum Sum: " << max_seq.sum << endl;
				cout << "Subsequence: ";
				for (int i = max_seq.start; i <= max_seq.end; ++i) {
					cout << S[i] << " ";
				}
				cout << endl;
			}
			
			return 0;
		}