#include <iostream>
#include <set>
#include <tuple>
using namespace std;

int grid[10][10];
bool hasBeans[10][10]; // Track if a cell has a bean

// Directions: 0=Up, 1=Right, 2=Down, 3=Left
int dr[] = {-1, 0, 1, 0};
int dc[] = {0, 1, 0, -1};

bool isValid(int r, int c) {
    return r >= 0 && r < 10 && c >= 0 && c < 10 && grid[r][c] != 0;
}

int main() {
    int startR = -1, startC = -1;

    // Read input
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            cin >> grid[i][j];
            hasBeans[i][j] = (grid[i][j] == 2);
            if (grid[i][j] == 4) {
                startR = i;
                startC = j;
            }
        }
    }

    int r = startR, c = startC;
    int dir = 0; // Starting direction is UP
    int score = 0;

    set<tuple<int, int, int>> visited; // (row, col, direction)
    visited.insert({r, c, dir});

    while (true) {
        // Try to move according to right-hand rule
        // Priority: right turn, straight, left turn, U-turn
        int nextDir = -1;
        int nextR = -1, nextC = -1;

        // Try directions in order: right, straight, left, back
        int priorities[] = {(dir + 1) % 4, dir, (dir + 3) % 4, (dir + 2) % 4};

        for (int i = 0; i < 4; i++) {
            int d = priorities[i];
            int nr = r + dr[d];
            int nc = c + dc[d];

            if (isValid(nr, nc)) {
                nextDir = d;
                nextR = nr;
                nextC = nc;
                break;
            }
        }

        // If no valid move, stuck (shouldn't happen based on problem)
        if (nextDir == -1) {
            break;
        }

        // Move to next position
        r = nextR;
        c = nextC;
        dir = nextDir;

        // Check if we collected a bean
        if (hasBeans[r][c]) {
            score += 2;
            hasBeans[r][c] = false; // Bean is consumed
        }

        // Check if we hit a ghost
        if (grid[r][c] == 3) {
            score -= 500;
            break;
        }

        // Check for loop (visited same state)
        if (visited.count({r, c, dir})) {
            cout << "Silly Pacman" << endl;
            return 0;
        }

        visited.insert({r, c, dir});
    }

    cout << score << endl;
    return 0;
}
