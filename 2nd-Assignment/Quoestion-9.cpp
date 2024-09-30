#include <iostream>
#include <vector>

using namespace std;

void coverBoard(vector<vector<int>>& board, int x, int y, int size, int tileNum) {
    if (size == 2) {
        // Base case: fill the 2x2 area with one L-shaped triomino
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 2; ++j) {
                if (i != 1 || j != 1) { // Leave one square empty
                    board[x + i][y + j] = tileNum;
                }
            }
        }
        return;
    }

    // Divide the board into four quadrants
    int halfSize = size / 2;

    // Coordinates of the center (where we will place the triomino)
    int centerX = x + halfSize - 1;
    int centerY = y + halfSize - 1;

    // Identify which quadrant has the missing square
    int missingX, missingY;
    // Find the missing square
    for (int i = x; i < x + size; ++i) {
        for (int j = y; j < y + size; ++j) {
            if (board[i][j] == -1) { // Assuming -1 represents the missing square
                missingX = i;
                missingY = j;
            }
        }
    }

    // Place the triomino in the center
    if (missingX < centerX && missingY < centerY) {
        // Missing in top-left
        board[centerX][centerY] = tileNum; // Cover center
        coverBoard(board, x, y, halfSize, tileNum + 1); // Top-left
        coverBoard(board, x, y + halfSize, halfSize, tileNum + 1); // Top-right
        coverBoard(board, x + halfSize, y, halfSize, tileNum + 1); // Bottom-left
        coverBoard(board, x + halfSize, y + halfSize, halfSize, tileNum + 1); // Bottom-right
    } else if (missingX < centerX && missingY >= centerY) {
        // Missing in top-right
        board[centerX][centerY - 1] = tileNum; // Cover center
        coverBoard(board, x, y, halfSize, tileNum + 1); // Top-left
        coverBoard(board, x, y + halfSize, halfSize, tileNum + 1); // Top-right
        coverBoard(board, x + halfSize, y, halfSize, tileNum + 1); // Bottom-left
        coverBoard(board, x + halfSize, y + halfSize, halfSize, tileNum + 1); // Bottom-right
    } else if (missingX >= centerX && missingY < centerY) {
        // Missing in bottom-left
        board[centerX - 1][centerY] = tileNum; // Cover center
        coverBoard(board, x, y, halfSize, tileNum + 1); // Top-left
        coverBoard(board, x, y + halfSize, halfSize, tileNum + 1); // Top-right
        coverBoard(board, x + halfSize, y, halfSize, tileNum + 1); // Bottom-left
        coverBoard(board, x + halfSize, y + halfSize, halfSize, tileNum + 1); // Bottom-right
    } else {
        // Missing in bottom-right
        board[centerX - 1][centerY - 1] = tileNum; // Cover center
        coverBoard(board, x, y, halfSize, tileNum + 1); // Top-left
        coverBoard(board, x, y + halfSize, halfSize, tileNum + 1); // Top-right
        coverBoard(board, x + halfSize, y, halfSize, tileNum + 1); // Bottom-left
        coverBoard(board, x + halfSize, y + halfSize, halfSize, tileNum + 1); // Bottom-right
    }
}

int main() {
    int n;
    cout << "Enter the size of the chessboard (n = 2^k, k > 0): ";
    cin >> n;

    // Create an n x n chessboard initialized to -1 (indicating empty)
    vector<vector<int>> board(n, vector<int>(n, -1));

    // Input the position of the missing square
    int missingRow, missingCol;
    cout << "Enter the position of the missing square (row column): ";
    cin >> missingRow >> missingCol;

    // Set the missing square
    board[missingRow][missingCol] = -1;

    // Start covering the board
    coverBoard(board, 0, 0, n, 1);

    // Output the filled board
    cout << "Covered chessboard with triominoes:\n";
    for (const auto& row : board) {
        for (const auto& tile : row) {
            cout << (tile == -1 ? '.' : tile) << " ";
        }
        cout << endl;
    }

    return 0;
}
