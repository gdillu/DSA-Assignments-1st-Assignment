#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include "all_algorithms.h"
#include <cstdlib>
#include <sstream>

using namespace std;
using namespace std::chrono;

void controlOver(const vector<vector<double>> &allTimes, string title)
{
    // Convert vector<vector<double>> to JSON-like string
    ostringstream list;
    list << "[";
    for (size_t i = 0; i < allTimes.size(); ++i)
    {
        const auto &executionTimes = allTimes[i];
        list << "[";
        for (size_t j = 0; j < executionTimes.size(); ++j)
        {
            list << executionTimes[j];
            if (j < executionTimes.size() - 1)
            {
                list << ", ";
            }
        }
        list << "]";
        if (i < allTimes.size() - 1)
        {
            list << ", ";
        }
    }
    list << "]";
    string execList = list.str();

    // Construct the command to call the Python script
    string command = "python graph_sketch.py \"" + execList + "\" '" + title + "'";

    cout << "Executing: " << command << endl;

    // Execute the command
    int success = system(command.c_str());
    if (success == 0)
    {
        cout << "Execution successful!" << endl;
    }
    else
    {
        cerr << "Error executing command!" << endl;
    }
}

int main()
{
    ifstream Bestfile("Best_all_sizes.txt");
    ifstream Worstfile("Worst_all_sizes.txt");
    ifstream Randomfile("random_all_sizes.txt");
    if (!Bestfile)
    {
        cerr << "Best File could not be opened!" << endl;
        return 1;
    }
    if (!Worstfile)
    {
        cerr << "Worst File could not be opened!" << endl;
        return 1;
    }
    if (!Randomfile)
    {
        cerr << "Random File could not be opened!" << endl;
        return 1;
    }

    vector<vector<double>> best_time(6);
    vector<vector<double>> worst_time(6);
    vector<vector<double>> random_time(6);

    vector<vector<double>> best_quick(3);
    vector<vector<double>> worst_quick(3);
    vector<vector<double>> random_quick(3);

    auto start = high_resolution_clock::now(), end = high_resolution_clock::now();
    duration<double> elapsed;
    string line;
    int count;
    while (getline(Bestfile, line))
    {
        if (line.find("Test cases for n=") != string::npos)
        {
            int n;
            sscanf(line.c_str(), "Test cases for n=%d:", &n);
            vector<int> test_cases(n);
            vector<int> test_copy;
            for (int i = 0; i < n; ++i)
            {
                Bestfile >> test_cases[i];
            }
            count = 0;

            test_copy = test_cases; // Buuble sort best
            start = high_resolution_clock::now();
            bubble(test_copy);
            end = high_resolution_clock::now();
            elapsed = end - start;
            best_time[count].push_back(elapsed.count());
            count += 1;

            test_copy = test_cases; // Insertion sort best
            start = high_resolution_clock::now();
            insertion(test_copy);
            end = high_resolution_clock::now();
            elapsed = end - start;
            best_time[count].push_back(elapsed.count());
            count += 1;

            test_copy = test_cases; // Merge
            start = high_resolution_clock::now();
            merge_sort(test_copy, 0, n - 1);
            end = high_resolution_clock::now();
            elapsed = end - start;
            best_time[count].push_back(elapsed.count());
            count += 1;

            test_copy = test_cases; // quick_random
            start = high_resolution_clock::now();
            quick(test_copy, 0, n - 1,1);
            end = high_resolution_clock::now();
            elapsed = end - start;
            best_time[count].push_back(elapsed.count());
            count++;

            test_copy = test_cases; // Copy the original test cases
            start = high_resolution_clock::now();
            heap(test_copy);
            end = high_resolution_clock::now();
            elapsed = end - start;
            best_time[count].push_back(elapsed.count());
            count += 1;

            test_copy = test_cases; // Copy the original test cases
            start = high_resolution_clock::now();
            radix(test_copy);
            end = high_resolution_clock::now();
            elapsed = end - start;
            best_time[count].push_back(elapsed.count());
            count += 1;

            Bestfile.ignore(); // Ignore the blank line after each section
        }
    }

    while (getline(Worstfile, line))
    {
        if (line.find("Test cases for n=") != string::npos)
        {
            int n;
            sscanf(line.c_str(), "Test cases for n=%d:", &n);
            vector<int> test_cases(n);
            vector<int> test_copy;
            for (int i = 0; i < n; ++i)
            {
                Worstfile >> test_cases[i];
            }
            count = 0;

            test_copy = test_cases; // Buuble sort best
            start = high_resolution_clock::now();
            bubble(test_copy);
            end = high_resolution_clock::now();
            elapsed = end - start;
            worst_time[count].push_back(elapsed.count());
            count += 1;

            test_copy = test_cases; // Insertion sort best
            start = high_resolution_clock::now();
            insertion(test_copy);
            end = high_resolution_clock::now();
            elapsed = end - start;
            worst_time[count].push_back(elapsed.count());
            count += 1;

            test_copy = test_cases; // Merge
            start = high_resolution_clock::now();
            merge_sort(test_copy, 0, n - 1);
            end = high_resolution_clock::now();
            elapsed = end - start;
            worst_time[count].push_back(elapsed.count());
            count += 1;

            test_copy = test_cases; // quick_random
            start = high_resolution_clock::now();
            quick(test_copy, 0, n - 1,1);
            end = high_resolution_clock::now();
            elapsed = end - start;
            worst_time[count].push_back(elapsed.count());
            count++;

            test_copy = test_cases; // Copy the original test cases
            start = high_resolution_clock::now();
            heap(test_copy);
            end = high_resolution_clock::now();
            elapsed = end - start;
            worst_time[count].push_back(elapsed.count());
            count += 1;

            test_copy = test_cases; // Copy the original test cases
            start = high_resolution_clock::now();
            radix(test_copy);
            end = high_resolution_clock::now();
            elapsed = end - start;
            worst_time[count].push_back(elapsed.count());
            count += 1;

            Worstfile.ignore(); // Ignore the blank line after each section
        }
    }

    while (getline(Randomfile, line))
    {
        if (line.find("Test cases for n=") != string::npos)
        {
            int n;
            sscanf(line.c_str(), "Test cases for n=%d:", &n);
            vector<int> test_cases(n);
            vector<int> test_copy;
            for (int i = 0; i < n; ++i)
            {
                Randomfile >> test_cases[i];
            }
            count = 0;

            test_copy = test_cases; // Buuble sort best
            start = high_resolution_clock::now();
            bubble(test_copy);
            end = high_resolution_clock::now();
            elapsed = end - start;
            random_time[count].push_back(elapsed.count());
            count += 1;

            test_copy = test_cases; // Insertion sort best
            start = high_resolution_clock::now();
            insertion(test_copy);
            end = high_resolution_clock::now();
            elapsed = end - start;
            random_time[count].push_back(elapsed.count());
            count += 1;

            test_copy = test_cases; // Merge
            start = high_resolution_clock::now();
            merge_sort(test_copy, 0, n - 1);
            end = high_resolution_clock::now();
            elapsed = end - start;
            random_time[count].push_back(elapsed.count());
            count += 1;

            test_copy = test_cases; // quick_random
            start = high_resolution_clock::now();
            quick(test_copy, 0, n - 1,1);
            end = high_resolution_clock::now();
            elapsed = end - start;
            random_time[count].push_back(elapsed.count());
            count++;

            test_copy = test_cases; // Copy the original test cases
            start = high_resolution_clock::now();
            heap(test_copy);
            end = high_resolution_clock::now();
            elapsed = end - start;
            random_time[count].push_back(elapsed.count());
            count += 1;

            test_copy = test_cases; // Copy the original test cases
            start = high_resolution_clock::now();
            radix(test_copy);
            end = high_resolution_clock::now();
            elapsed = end - start;
            random_time[count].push_back(elapsed.count());
            count += 1;

            Randomfile.ignore(); // Ignore the blank line after each section
        }
    }


    controlOver(best_time, "Best Case");
    controlOver(worst_time, "Worst Case");
    controlOver(random_time, "Average Case");
    

    return 0;
}
