#include <iostream>
#include <vector>
#include <chrono>
#include <cstdlib> // For std::rand()
#include <iomanip> // For std::setprecision

using namespace std;

// Standard matrix multiplication
void standardMatrixMultiplication(const vector<vector<int>>& A, const vector<vector<int>>& B, vector<vector<int>>& C) {
    int n = A.size();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            C[i][j] = 0;
            for (int k = 0; k < n; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

// Utility function to add two matrices
void add(const vector<vector<int>>& A, const vector<vector<int>>& B, vector<vector<int>>& C) {
    int n = A.size();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

// Utility function to subtract two matrices
void subtract(const vector<vector<int>>& A, const vector<vector<int>>& B, vector<vector<int>>& C) {
    int n = A.size();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
}

// Strassen's algorithm for matrix multiplication
void strassen(const vector<vector<int>>& A, const vector<vector<int>>& B, vector<vector<int>>& C) {
    int n = A.size();
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    // Split the matrices into quadrants
    int newSize = n / 2;
    vector<vector<int>> A11(newSize, vector<int>(newSize));
    vector<vector<int>> A12(newSize, vector<int>(newSize));
    vector<vector<int>> A21(newSize, vector<int>(newSize));
    vector<vector<int>> A22(newSize, vector<int>(newSize));
    vector<vector<int>> B11(newSize, vector<int>(newSize));
    vector<vector<int>> B12(newSize, vector<int>(newSize));
    vector<vector<int>> B21(newSize, vector<int>(newSize));
    vector<vector<int>> B22(newSize, vector<int>(newSize));

    for (int i = 0; i < newSize; ++i) {
        for (int j = 0; j < newSize; ++j) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + newSize];
            A21[i][j] = A[i + newSize][j];
            A22[i][j] = A[i + newSize][j + newSize];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + newSize];
            B21[i][j] = B[i + newSize][j];
            B22[i][j] = B[i + newSize][j + newSize];
        }
    }

    // Compute the 7 products using Strassen's formulas
    vector<vector<int>> M1(newSize, vector<int>(newSize));
    vector<vector<int>> M2(newSize, vector<int>(newSize));
    vector<vector<int>> M3(newSize, vector<int>(newSize));
    vector<vector<int>> M4(newSize, vector<int>(newSize));
    vector<vector<int>> M5(newSize, vector<int>(newSize));
    vector<vector<int>> M6(newSize, vector<int>(newSize));
    vector<vector<int>> M7(newSize, vector<int>(newSize));

    vector<vector<int>> AResult(newSize, vector<int>(newSize));
    vector<vector<int>> BResult(newSize, vector<int>(newSize));

    add(A11, A22, AResult); // A11 + A22
    add(B11, B22, BResult); // B11 + B22
    strassen(AResult, BResult, M1); // M1 = (A11 + A22) * (B11 + B22)

    add(A21, A22, AResult); // A21 + A22
    strassen(AResult, B11, M2); // M2 = (A21 + A22) * B11

    subtract(B12, B22, BResult); // B12 - B22
    strassen(A11, BResult, M3); // M3 = A11 * (B12 - B22)

    subtract(B21, B11, BResult); // B21 - B11
    strassen(A22, BResult, M4); // M4 = A22 * (B21 - B11)

    add(A11, A12, AResult); // A11 + A12
    strassen(AResult, B22, M5); // M5 = (A11 + A12) * B22

    subtract(A21, A11, AResult); // A21 - A11
    add(B11, B12, BResult); // B11 + B12
    strassen(AResult, BResult, M6); // M6 = (A21 - A11) * (B11 + B12)

    subtract(A12, A22, AResult); // A12 - A22
    add(B21, B22, BResult); // B21 + B22
    strassen(AResult, BResult, M7); // M7 = (A12 - A22) * (B21 + B22)

    // Compute the values for C
    vector<vector<int>> C11(newSize, vector<int>(newSize));
    vector<vector<int>> C12(newSize, vector<int>(newSize));
    vector<vector<int>> C21(newSize, vector<int>(newSize));
    vector<vector<int>> C22(newSize, vector<int>(newSize));

    add(M1, M4, C11); // C11 = M1 + M4
    subtract(C11, M5, C11); // C11 = C11 - M5
    add(M3, M2, C12); // C12 = M3 + M2

    add(M1, M3, C21); // C21 = M1 + M3
    add(M2, M4, C22); // C22 = M2 + M4

    // Combine the results into the final matrix C
    for (int i = 0; i < newSize; ++i) {
        for (int j = 0; j < newSize; ++j) {
            C[i][j] = C11[i][j];
            C[i][j + newSize] = C12[i][j];
            C[i + newSize][j] = C21[i][j];
            C[i + newSize][j + newSize] = C22[i][j];
        }
    }
}

// Function to generate a random matrix
vector<vector<int>> generateRandomMatrix(int n) {
    vector<vector<int>> matrix(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            matrix[i][j] = rand() % 10; // Random numbers between 0 and 9
        }
    }
    return matrix;
}

// Function to compare two matrices
bool compareMatrices(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (A[i][j] != B[i][j]) {
                return false;
            }
        }
    }
    return true;
}

// Function to measure execution time of matrix multiplication
void measureExecutionTime(int n) {
    // Generate random matrices
    auto A = generateRandomMatrix(n);
    auto B = generateRandomMatrix(n);
    vector<vector<int>> C(n, vector<int>(n));
    vector<vector<int>> D(n, vector<int>(n));

    // Measure time for standard multiplication
    auto startStandard = chrono::high_resolution_clock::now();
    standardMatrixMultiplication(A, B, C);
    auto endStandard = chrono::high_resolution_clock::now();
    chrono::duration<double, std::milli> durationStandard = endStandard - startStandard;

    // Measure time for Strassen's multiplication
    auto startStrassen = chrono::high_resolution_clock::now();
    strassen(A, B, D);
    auto endStrassen = chrono::high_resolution_clock::now();
    chrono::duration<double, std::milli> durationStrassen = endStrassen - startStrassen;

    // Output the results
    cout << "Matrix Size: " << n << " x " << n << endl;
    cout << "Standard Multiplication Time: " << durationStandard.count() << " ms" << endl;
    cout << "Strassen's Multiplication Time: " << durationStrassen.count() << " ms" << endl;

    // Verify results
    if (compareMatrices(C, D)) {
        cout << "Results are the same." << endl;
    } else {
        cout << "Results are different!" << endl;
    }
    cout << "-------------------------------------" << endl;
}

int main() {
    srand(time(nullptr)); // Seed for random number generation

    // Measure execution time for different sizes
    for (int size : {2, 4, 8, 16, 32, 64, 128, 256}) {
        measureExecutionTime(size);
    }

    return 0;
}
