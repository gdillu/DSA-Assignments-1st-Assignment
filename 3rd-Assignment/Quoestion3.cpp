#include <iostream>
		#include <vector>
		#include <algorithm>
		
		struct Activity {
			int id;
			int start;
			int finish;
		};
		
		// Comparator function to sort activities based on finish time
		bool activityCompare(Activity a, Activity b) {
			return a.finish < b.finish;
		}
		
		int main() {
			// Example input: list of activities with start and finish times
			std::vector<Activity> activities = {
				{1, 1, 4},
				{2, 3, 5},
				{3, 0, 6},
				{4, 5, 7},
				{5, 8, 9},
				{6, 5, 9}
			};
			
			// Sort activities based on their finish times
			std::sort(activities.begin(), activities.end(), activityCompare);
			
			std::cout << "Selected Activities:\n";
			
			// The first activity always gets selected
			int n = activities.size();
			int lastSelectedIndex = 0;
			std::cout << "Activity " << activities[lastSelectedIndex].id
			<< " (Time: " << activities[lastSelectedIndex].start
			<< " to " << activities[lastSelectedIndex].finish << ")\n";
			
			// Iterate through the rest of the activities
			for (int i = 1; i < n; i++) {
				// If the start time is greater or equal to the finish time
				// of the last selected activity, select it
				if (activities[i].start >= activities[lastSelectedIndex].finish) {
					std::cout << "Activity " << activities[i].id
					<< " (Time: " << activities[i].start
					<< " to " << activities[i].finish << ")\n";
					lastSelectedIndex = i;
				}
			}
			
			return 0;
		}