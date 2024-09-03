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
    ifstream Bestfile("random_all_sizes.txt");
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


    vector<vector<double>> best_quick(3);
    vector<vector<double>> worst_quick(3);
    vector<vector<double>> random_quick(3);

    vector<vector<double>> best_quick_comparisons(3);
    vector<vector<double>> worst_quick_comparisons(3);
    vector<vector<double>> random_quick_comparisons(3);

    auto start = high_resolution_clock::now(), end = high_resolution_clock::now();
    duration<double> elapsed;
    string line;
    int count;
    double comparisons;
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

            test_copy = test_cases; // quick_normal
            start = high_resolution_clock::now();
            comparisons = quick(test_copy, 0, n - 1,0);
            end = high_resolution_clock::now();
            elapsed = end - start;
            best_quick_comparisons[count].push_back(elapsed.count()/comparisons);
            best_quick[count].push_back(elapsed.count());
            count++;

            test_copy = test_cases; // quick_median
            start = high_resolution_clock::now();
            comparisons = quick(test_copy, 0, n - 1,1);
            end = high_resolution_clock::now();
            elapsed = end - start;
            best_quick_comparisons[count].push_back(elapsed.count()/comparisons);
            best_quick[count].push_back(elapsed.count());
            count++;

            test_copy = test_cases; // quick_random
            start = high_resolution_clock::now();
            comparisons = quick(test_copy, 0, n - 1,2);
            end = high_resolution_clock::now();
            elapsed = end - start;
            best_quick_comparisons[count].push_back(elapsed.count()/comparisons);
            best_quick[count].push_back(elapsed.count());
            count++;

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

            test_copy = test_cases; // quick_random
            start = high_resolution_clock::now();
            comparisons = quick(test_copy, 0, n - 1,0);
            end = high_resolution_clock::now();
            elapsed = end - start;
            worst_quick_comparisons[count].push_back(elapsed.count()/comparisons);
            worst_quick[count].push_back(elapsed.count());
            count++;

            test_copy = test_cases; // quick_random
            start = high_resolution_clock::now();
            comparisons = quick(test_copy, 0, n - 1,1);
            end = high_resolution_clock::now();
            elapsed = end - start;
            worst_quick_comparisons[count].push_back(elapsed.count()/comparisons);
            worst_quick[count].push_back(elapsed.count());
            count++;

            test_copy = test_cases; // quick_random
            start = high_resolution_clock::now();
            comparisons = quick(test_copy, 0, n - 1,2);
            end = high_resolution_clock::now();
            elapsed = end - start;
            worst_quick_comparisons[count].push_back(elapsed.count()/comparisons);
            worst_quick[count].push_back(elapsed.count());
            count++;

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
            test_copy = test_cases; // quick_random
            start = high_resolution_clock::now();
            comparisons = quick(test_copy, 0, n - 1,0);
            end = high_resolution_clock::now();
            elapsed = end - start;
            cout << comparisons << endl;
            random_quick_comparisons[count].push_back(elapsed.count()/comparisons);
            random_quick[count].push_back(elapsed.count());
            count++;

            test_copy = test_cases; // quick_random
            start = high_resolution_clock::now();
            comparisons = quick(test_copy, 0, n - 1,1);
            end = high_resolution_clock::now();
            elapsed = end - start;
            random_quick_comparisons[count].push_back(elapsed.count()/comparisons);
            random_quick[count].push_back(elapsed.count());
            count++;

            test_copy = test_cases; // quick_random
           start =  high_resolution_clock::now();
            comparisons = quick(test_copy, 0, n - 1,2);
            end = high_resolution_clock::now();
            elapsed = end - start;
            random_quick_comparisons[count].push_back(elapsed.count()/comparisons);
            random_quick[count].push_back(elapsed.count());
            count++;

            Randomfile.ignore(); // Ignore the blank line after each section
        }
    }

    controlOver(best_quick, "Best Case");
    controlOver(worst_quick, "Worst Case");
    controlOver(random_quick, "Average Case");
    controlOver(best_quick_comparisons,"best Case Comparisons");
    controlOver(worst_quick_comparisons,"Worst Case Comparisons");
    controlOver(random_quick_comparisons,"Random Case Comparisons");

    return 0;
}
