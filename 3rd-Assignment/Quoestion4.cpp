#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include<algorithm>
using namespace std;

class Graph {
public:
    Graph(int n) : n(n), adjList(n) {}

    void addEdge(int u, int v) {
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    void removeEdge(int u, int v) {
        adjList[u].erase(remove(adjList[u].begin(), adjList[u].end(), v), adjList[u].end());
        adjList[v].erase(remove(adjList[v].begin(), adjList[v].end(), u), adjList[v].end());
    }

    int getDegree(int u) const {
        return adjList[u].size();
    }

    const vector<int>& getNeighbors(int u) const {
        return adjList[u];
    }

private:
    int n;
    vector<vector<int>> adjList;
};

int partyAlgo(int numPeople) {
    Graph G(numPeople);
    vector<bool> invite(numPeople, true);
    queue<int> rejects;
    
    // Simulate the acquaintance relationships
    cout << "Enter the relationships:\n";
    for (int i = 0; i < numPeople; ++i) {
        cout << "Who does person " << i + 1 << " know? Type -1 to end.\n";
        int input;
        while (true) {
            cout << "Person " << i + 1 << " knows: ";
            cin >> input;
            if (input == -1) break;
            if (input != i + 1 && input > 0 && input <= numPeople) {
                G.addEdge(i, input - 1);
            } else {
                cout << "Invalid input, try again.\n";
            }
        }
    }

    // First screening of invitees
    for (int i = 0; i < numPeople; ++i) {
        if (G.getDegree(i) < 5) {
            rejects.push(i);
            invite[i] = false;
        }
    }

    // Ensure everyone knows at least 5 people
    while (!rejects.empty()) {
        int j = rejects.front();
        rejects.pop();
        for (int i = 0; i < numPeople; ++i) {
            if (invite[i] && G.getDegree(i) < 5) {
                rejects.push(i);
                invite[i] = false;
            }
        }
    }

    // Print the results
    int accepted = 0;
    cout << "Final invitees:\n";
    for (int i = 0; i < numPeople; ++i) {
        if (invite[i]) {
            cout << "Person " << i + 1 << " is invited.\n";
            ++accepted;
        }
    }

    return accepted;
}

int main() {
    int numPeople;
    cout << "Enter number of people: ";
    cin >> numPeople;

    int output = partyAlgo(numPeople);

    if (output == 0) {
        cout << "No one knew enough people, so there cannot be a party.\n";
    } else {
        cout << "Out of " << numPeople << " people, " << output << " can come to the party.\n";
    }

    return 0;
}
