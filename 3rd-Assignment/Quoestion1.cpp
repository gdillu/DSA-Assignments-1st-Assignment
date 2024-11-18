// Dance partners: You are pairing couples for a very conservative formal ball. There are
// n men and m women, and you know the height and gender of each person there. Each
// dancing couple must be a man and a woman, and the man must be at least as tall as,
// but no more than 3 inches taller than, his partner. You wish to maximize the number of
// dancing couples given this constraint.

#include <iostream>
#include <vector>
#include <algorithm>
		
		// Function to calculate the maximum number of dancing couples
int calculate_max_pairs(std::vector<int>& men_heights, std::vector<int>& women_heights) {
    // Sort the heights
    std::sort(men_heights.begin(), men_heights.end());
    std::sort(women_heights.begin(), women_heights.end());
    
    std::vector<std::pair<int, int>> partners;
    int i = 0; // Index for men
    int j = 0; // Index for women
    int matches = 0;
    int n = men_heights.size();
    int m = women_heights.size();

    // Match couples based on the height constraints
    while (i < n && j < m) {
        if (men_heights[i] < women_heights[j]) {
            // Man is shorter than the woman; move to the next man
            ++i;
        } else if (men_heights[i] > women_heights[j] + 3) {
            // Man is more than 3 inches taller; move to the next woman
            ++j;
        } else {
            // Valid couple found
            ++matches;
            partners.emplace_back(men_heights[i], women_heights[j]);  // Store the matched pair
            ++i;
            ++j;
        }
    }

    // Optional: print matched pairs
    std::cout << "Matched pairs:\n";
    for (const auto& p : partners) {
        std::cout << "(" << p.first << ", " << p.second << ")\n";
    }

    return matches;
}
		
int main() {
			// Test case
	int n;  // Number of heights
    std::vector<int> men_heights;
    std::vector<int> women_heights;

    // Input for men's heights
    std::cout << "Enter the number of men's heights: ";
    std::cin >> n;
    std::cout << "Enter the heights for men:\n";
    for (int i = 0; i < n; ++i) {
        int height;
        std::cin >> height;
        men_heights.push_back(height);
    }

    // Input for women's heights
    std::cout << "Enter the number of women's heights: ";
    std::cin >> n;
    std::cout << "Enter the heights for women:\n";
    for (int i = 0; i < n; ++i) {
        int height;
        std::cin >> height;
        women_heights.push_back(height);
    }

    // Displaying the vectors
    std::cout << "\nMen's heights: ";
    for (int height : men_heights) {
        std::cout << height << " ";
    }

    std::cout << "\nWomen's heights: ";
    for (int height : women_heights) {
        std::cout << height << " ";
    }
			
	int max_pairs = calculate_max_pairs(men_heights, women_heights);
			
	std::cout << "Maximum number of dancing couples: " << max_pairs << std::endl;
			
	return 0;
}