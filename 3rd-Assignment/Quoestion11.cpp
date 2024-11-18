#include <iostream>
		#include <vector>
		#include <cmath>
		#include <cfloat>
		#include <iomanip>
		
		using namespace std;
		
		// Function to calculate the weight of the triangle formed by vertices i, j, k
		double weightFunction(const vector<pair<double, double>>& points, int i, int j, int k) {
			// Example weight function: Perimeter of the triangle
			double dx1 = points[i].first - points[j].first;
			double dy1 = points[i].second - points[j].second;
			double side1 = sqrt(dx1 * dx1 + dy1 * dy1);
			
			double dx2 = points[j].first - points[k].first;
			double dy2 = points[j].second - points[k].second;
			double side2 = sqrt(dx2 * dx2 + dy2 * dy2);
			
			double dx3 = points[k].first - points[i].first;
			double dy3 = points[k].second - points[i].second;
			double side3 = sqrt(dx3 * dx3 + dy3 * dy3);
			
			return side1 + side2 + side3; // Sum of the sides (Perimeter)
		}
		
		// Function to find the minimum total weight triangulation
		double minWeightTriangulation(const vector<pair<double, double>>& points) {
			int n = points.size();
			vector<vector<double>> dp(n, vector<double>(n, 0));
			
			// Fill dp table
			for (int gap = 2; gap < n; gap++) {
				for (int i = 0, j = i + gap; j < n; i++, j++) {
					dp[i][j] = DBL_MAX;
					for (int k = i + 1; k < j; k++) {
						double cost = dp[i][k] + dp[k][j] + weightFunction(points, i, k, j);
						if (cost < dp[i][j]) {
							dp[i][j] = cost;
						}
					}
				}
			}
			
			return dp[0][n - 1];
		}
		
		int main() {
			// Example convex polygon (vertices in order)
			vector<pair<double, double>> points = {
				{0, 0}, {1, 0}, {2, 1}, {1, 2}, {0, 2}
			};
			
			double minTotalWeight = minWeightTriangulation(points);
			cout << fixed << setprecision(2);
			cout << "Minimum Total Weight of Triangulation: " << minTotalWeight << endl;
			
			return 0;
		}