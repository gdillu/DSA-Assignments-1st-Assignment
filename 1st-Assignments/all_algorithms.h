#ifndef ALL_SORTS_H
#define ALL_SORTS_H

#include <vector>
#include <algorithm> // For std::swap
#include <iostream>
#include <cstdlib> 
#include <fstream> // For file operations

using namespace std;


// Bubble Sort
double bubble(std::vector<int>& vec) {
    double comparisons = 0; // Reset comparison counter
    int n = vec.size();
    for (int i = 0; i < n-1; ++i) {
        for (int j = 0; j < n-i-1; ++j) {
            comparisons++; // Count comparison
            if (vec[j] > vec[j+1]) {
                std::swap(vec[j], vec[j+1]);
            }
        }
    }
    return comparisons;
}

// Merge Sort
void merge(std::vector<int>& vec, int left, int mid, int right, double& comparisons) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    std::vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; ++i)
        L[i] = vec[left + i];
    for (int j = 0; j < n2; ++j)
        R[j] = vec[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        comparisons++; // Count comparison
        if (L[i] <= R[j]) {
            vec[k] = L[i];
            i++;
        } else {
            vec[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        vec[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        vec[k] = R[j];
        j++;
        k++;
    }
}

double merge_sort(std::vector<int>& vec, int left, int right) {
    double comparisons = 0;
    if (left < right) {
        int mid = left + (right - left) / 2;

        comparisons += merge_sort(vec, left, mid);
        comparisons += merge_sort(vec, mid + 1, right);

        merge(vec, left, mid, right, comparisons);
    }
    return comparisons;
}

// Quick Sort
int partition(std::vector<int> &arr, int low, int high, double& comparisons) {
    int pivot = arr[low];
    int left = low + 1;
    int right = high;

    while (true) {
        while (left <= right && arr[left] <= pivot) {
            comparisons++; // Count comparison
            left++;
        }
        while (left <= right && arr[right] >= pivot) {
            comparisons++; // Count comparison
            right--;
        }
        if (left > right) break;
        std::swap(arr[left], arr[right]);
    }
    std::swap(arr[low], arr[right]);
    return right;
}

int partitionMedian(std::vector<int> &arr, int low, int high, double& comparisons) {
    int mid = low + (high - low) / 2;
    if (arr[mid] < arr[low]) std::swap(arr[mid], arr[low]);
    if (arr[high] < arr[low]) std::swap(arr[high], arr[low]);
    if (arr[mid] > arr[high]) std::swap(arr[mid], arr[high]);
    std::swap(arr[mid], arr[low]);
    return partition(arr, low, high, comparisons);
}

int partitionRandom(std::vector<int> &arr, int low, int high, double& comparisons) {
    int pivotIndex = low + rand() % (high - low + 1);
    std::swap(arr[low], arr[pivotIndex]);
    return partition(arr, low, high, comparisons);
}

double quick(std::vector<int> &arr, int low, int high, int pivotType) {
    double comparisons = 0; // Reset comparison counter
    while (low < high) {
        int pi;
        if (pivotType == 0) {
            pi = partition(arr, low, high, comparisons);
        } else if (pivotType == 1) {
            pi = partitionMedian(arr, low, high, comparisons);
        } else {
            pi = partitionRandom(arr, low, high, comparisons);
        }

        if (pi - low < high - pi) {
            comparisons += quick(arr, low, pi - 1, pivotType);
            low = pi + 1;
        } else {
            comparisons += quick(arr, pi + 1, high, pivotType);
            high = pi - 1;
        }
    }
    return comparisons;
}

// Heap Sort
void heapify(std::vector<int>& vec, int n, int i, double& comparisons) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n) {
        comparisons++; // Count comparison
        if (vec[left] > vec[largest])
            largest = left;
    }

    if (right < n) {
        comparisons++; // Count comparison
        if (vec[right] > vec[largest])
            largest = right;
    }

    if (largest != i) {
        std::swap(vec[i], vec[largest]);
        heapify(vec, n, largest, comparisons);
    }
}

double heap(std::vector<int>& vec) {
    double comparisons = 0; // Reset comparison counter
    int n = vec.size();

    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(vec, n, i, comparisons);

    for (int i = n - 1; i >= 0; i--) {
        std::swap(vec[0], vec[i]);
        heapify(vec, i, 0, comparisons);
    }
    return comparisons;
}

// Insertion Sort
double insertion(std::vector<int>& vec) {
    double comparisons = 0; // Reset comparison counter
    int n = vec.size();
    for (int i = 1; i < n; ++i) {
        int key = vec[i];
        int j = i - 1;

        while (j >= 0) {
            comparisons++; // Count comparison
            if (vec[j] > key) {
                vec[j + 1] = vec[j];
                j = j - 1;
            } else {
                break;
            }
        }
        vec[j + 1] = key;
    }
    return comparisons;
}

// Radix Sort
int getMax(const vector<int>& arr) {
    return *max_element(arr.begin(), arr.end());
}

void countingSort(vector<int>& arr, int exp) {
    int n = arr.size();
    vector<int> output(n); // output array to store sorted values
    int count[10] = {0};

    for (int i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;

    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];

    for (int i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }

    for (int i = 0; i < n; i++)
        arr[i] = output[i];
}

double radix(vector<int>& arr) {
    double comparisons = 0; // Reset comparison counter
    int maxNum = getMax(arr);

    for (int exp = 1; maxNum / exp > 0; exp *= 10)
        countingSort(arr, exp);
    return comparisons;
}
#endif
