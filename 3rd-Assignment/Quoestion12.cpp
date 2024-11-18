#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Function to find the minimum number of guards and their positions
vector<double> findGuardPositions(const vector<double>& paintings) {
	int n = paintings.size();
	vector<double> guards;
	
	// Sort the positions of the paintings
	vector<double> sorted_paintings = paintings;
	sort(sorted_paintings.begin(), sorted_paintings.end());
	
	int i = 0;
	while (i < n) {
		// Position of the leftmost uncovered painting
		double x = sorted_paintings[i];
		
		// Place a guard at position p = x + 1
		double guard_position = x + 1;
		guards.push_back(guard_position);
		
		// Advance i to skip all paintings covered by this guard
		i++;
		while (i < n && sorted_paintings[i] <= guard_position + 1) {
			i++;
		}
	}
	
	return guards;
}

int main() {
	// Example positions of paintings
	vector<double> paintings = {0.5, 1.2, 2.8, 3.0, 4.1, 5.5, 6.0, 7.2, 8.5, 9.1};
	
	vector<double> guard_positions = findGuardPositions(paintings);
	
	// Output the results
	cout << "Minimum number of guards required: " << guard_positions.size() << endl;
	cout << "Guard positions:" << endl;
	for (double pos : guard_positions) {
		cout << pos << " ";
	}
	cout << endl;
	
	return 0;
}