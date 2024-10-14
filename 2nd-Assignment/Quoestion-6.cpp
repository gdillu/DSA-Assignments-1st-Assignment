#include <bits/stdc++.h>
using namespace std;

void merge(vector<pair<int, int> >& v, vector<int>& ans,
           int l, int mid, int h)
{

    vector<pair<int, int> > t; // temporary array for merging both halves
    int i = l;
    int j = mid + 1;

    while (i < mid + 1 && j <= h) {

        // v[i].first is greater than all
        // the elements from j till h.
        if (v[i].first > v[j].first) {
            ans[v[i].second] += (h - j + 1);
            t.push_back(v[i]);
            i++;
        }
        else {
            t.push_back(v[j]);
            j++;
        }
    }

    // if any elements left in left array
    while (i <= mid)
        t.push_back(v[i++]);
    // if any elements left in right array
    while (j <= h)
        t.push_back(v[j++]);
    // putting elements back in main array in
    // descending order
    for (int k = 0, i = l; i <= h; i++, k++)
        v[i] = t[k];
}

void mergesort(vector<pair<int, int> >& v, vector<int>& ans,
               int i, int j)
{
    if (i < j) {
        int mid = (i + j) / 2;

        // calling mergesort for left half
        mergesort(v, ans, i, mid);

        // calling mergesort for right half
        mergesort(v, ans, mid + 1, j);

        // merging both halves and generating answer
        merge(v, ans, i, mid, j);
    }
}

vector<int> constructLowerArray(int* arr, int n)
{

    vector<pair<int, int> > v;
    // inserting elements and corresponding index
    // as pair
    for (int i = 0; i < n; i++)
        v.push_back({ arr[i], i });

    // answer array for keeping count
    // initialized by 0,
    vector<int> ans(n, 0);

    // calling mergesort
    mergesort(v, ans, 0, n - 1);

    return ans;
}

// Driver Code Starts.

int main()
{
    int arr[] = { 8,2,6,3,5};
    int n = sizeof(arr) / sizeof(arr[0]);

    auto ans = constructLowerArray(arr, n);
    for (auto x : ans) {
        cout << x << " ";
    }
    cout << "\n";
    return 0;
}