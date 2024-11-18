// Homework Grade Maximization: In a class, there are n assignments. You have H
// hours to spend on all assignments, and you cannot divide an hour between assignments,
// but must spend each hour entirely on a single assignment. The i-th hour you spend
// on assignment j will improve your grade on assignment j by B[i, j], where for each j,
// B[1, j] ≥ B[2, j] ≥ · · · ≥ B[H, j] ≥ 0. In other words, if you spend h hours on assignment
// j, your grade will be Ph
// i=1 B[i, j], and time spent on each project has diminishing returns,
// with the next hour being worth less than the previous one. You want to divide your H
// hours between the assignments to maximize your total grade on all the assignments. Give
// an efficient algorithm for this problem
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

// Function to maximize the total grade and track hour allocations
// Parameters:
// - n: number of assignments
// - H: total hours available
// - B: 2D vector where each subvector represents the grades for each hour spent on an assignment
pair<int, vector<int>> maximizeGrades(int n, int H, vector<vector<int>>& B) {
    // Priority queue to store grades with corresponding assignment index
    // Higher grades have higher priority
    priority_queue<pair<int, int>> pq;

    // Initialize the priority queue with the first grade of each assignment
    for(int i = 0; i < n; i++) {
        if(!B[i].empty()) { // Ensure there is at least one grade
            pq.push({B[i][0], i});
        }
    }

    int totalGrade = 0; // Variable to store the maximum total grade
    vector<int> hoursSpent(n, 0); // Vector to track hours spent on each assignment
    vector<int> allocation; // Vector to track which assignment each hour is allocated to

    // Loop while there are hours available and grades in the priority queue
    while(!pq.empty() && H > 0) {
        auto [currentGrade, assignmentIdx] = pq.top(); // Get the highest grade available
        pq.pop(); // Remove it from the queue

        // Accumulate grade and reduce available hours
        totalGrade += currentGrade;
        H--;

        hoursSpent[assignmentIdx]++; // Increment the hours spent on the current assignment
        allocation.push_back(assignmentIdx); // Record the assignment allocated for this hour

        // If there are more grades available for the current assignment, push the next grade
        if(hoursSpent[assignmentIdx] < B[assignmentIdx].size()) {
            pq.push({B[assignmentIdx][hoursSpent[assignmentIdx]], assignmentIdx});
        }
    }

    return {totalGrade, allocation}; // Return the total grade and allocation details
}

int main() {
    int n = 3; // Number of assignments
    int H = 5; // Total hours available for study

    // Grades available per hour of effort on each assignment (decreasing order)
    vector<vector<int>> B = {
        {9, 6, 4, 2, 1},  // Assignment 1
        {7, 5, 3, 2, 1},  // Assignment 2
        {8, 6, 4, 2}      // Assignment 3
    };

    // Calculate the maximum total grade and get allocation details
    pair<int, vector<int>> result = maximizeGrades(n, H, B);
    int maxTotalGrade = result.first;
    vector<int> allocation = result.second;

    // Output the maximum total grade
    cout << "Maximum total grade: " << maxTotalGrade << endl;

    // Output the allocation of each hour
    cout << "Hour allocations:" << endl;
    for(int hour = 1; hour <= allocation.size(); hour++) {
        // Adding 1 to assignment index for 1-based numbering
        cout << "Hour " << hour << ": Assignment " << (allocation[hour - 1] + 1) << endl;
    }

    return 0;
}
