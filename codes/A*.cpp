#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
using namespace std;

// A structure to represent a cell in the grid
struct Cell {
    int parent_i, parent_j;
    double f, g, h;
};

struct Point {
    int x, y;
    bool operator==(const Point& p) const {
        return x == p.x && y == p.y;
    }
};

// A utility function to check if a given cell (row, col) is a valid cell
bool isValid(int row, int col, int ROW, int COL) {
    return (row >= 0) && (row < ROW) && (col >= 0) && (col < COL);
}

// A utility function to check if a given cell is blocked
bool isUnBlocked(const vector<vector<int>>& grid, int row, int col) {
    return grid[row][col] == 1;
}

// A utility function to check if the destination cell has been reached
bool isDestination(int row, int col, const Point& dest) {
    return row == dest.x && col == dest.y;
}

// A utility function to calculate the 'h' heuristics
double calculateHValue(int row, int col, const Point& dest) {
    // Using Euclidean distance as the heuristic
    return sqrt((row - dest.x) * (row - dest.x) + (col - dest.y) * (col - dest.y));
}

// A utility function to trace the path from the source to destination
void tracePath(vector<vector<Cell>>& cellDetails, const Point& dest) {
    cout << "The path is: ";
    int row = dest.x;
    int col = dest.y;

    vector<Point> path;

    while (!(cellDetails[row][col].parent_i == row && cellDetails[row][col].parent_j == col)) {
        path.push_back({row, col});
        int temp_row = cellDetails[row][col].parent_i;
        int temp_col = cellDetails[row][col].parent_j;
        row = temp_row;
        col = temp_col;
    }

    path.push_back({row, col});
    while (!path.empty()) {
        Point p = path.back();
        path.pop_back();
        cout << "-> (" << p.x << "," << p.y << ") ";
    }
    cout << endl;
}

void aStarSearch(vector<vector<int>>& grid, const Point& src, const Point& dest) {
    int ROW = grid.size();
    int COL = grid[0].size();

    if (!isValid(src.x, src.y, ROW, COL) || !isValid(dest.x, dest.y, ROW, COL)) {
        cout << "Source or the destination is invalid\n";
        return;
    }

    if (!isUnBlocked(grid, src.x, src.y) || !isUnBlocked(grid, dest.x, dest.y)) {
        cout << "Source or the destination is blocked\n";
        return;
    }

    if (isDestination(src.x, src.y, dest)) {
        cout << "We are already at the destination\n";
        return;
    }

    vector<vector<bool>> closedList(ROW, vector<bool>(COL, false));
    vector<vector<Cell>> cellDetails(ROW, vector<Cell>(COL));

    int i, j;

    for (i = 0; i < ROW; i++) {
        for (j = 0; j < COL; j++) {
            cellDetails[i][j].f = FLT_MAX;
            cellDetails[i][j].g = FLT_MAX;
            cellDetails[i][j].h = FLT_MAX;
            cellDetails[i][j].parent_i = -1;
            cellDetails[i][j].parent_j = -1;
        }
    }

    i = src.x, j = src.y;
    cellDetails[i][j].f = 0.0;
    cellDetails[i][j].g = 0.0;
    cellDetails[i][j].h = 0.0;
    cellDetails[i][j].parent_i = i;
    cellDetails[i][j].parent_j = j;

    priority_queue<pair<double, Point>, vector<pair<double, Point>>, greater<pair<double, Point>>> openList;
    openList.emplace(0.0, Point{i, j});

    bool foundDest = false;

    while (!openList.empty()) {
        const pair<double, Point>& p = openList.top();
        i = p.second.x;
        j = p.second.y;
        openList.pop();
        closedList[i][j] = true;

        double gNew, hNew, fNew;

        const int rowNum[] = {-1, 0, 0, 1};
        const int colNum[] = {0, -1, 1, 0};

        for (int k = 0; k < 4; k++) {
            int adjX = i + rowNum[k];
            int adjY = j + colNum[k];

            if (isValid(adjX, adjY, ROW, COL)) {
                if (isDestination(adjX, adjY, dest)) {
                    cellDetails[adjX][adjY].parent_i = i;
                    cellDetails[adjX][adjY].parent_j = j;
                    cout << "The destination cell is found\n";
                    tracePath(cellDetails, dest);
                    foundDest = true;
                    return;
                } else if (!closedList[adjX][adjY] && isUnBlocked(grid, adjX, adjY)) {
                    gNew = cellDetails[i][j].g + 1.0;
                    hNew = calculateHValue(adjX, adjY, dest);
                    fNew = gNew + hNew;

                    if (cellDetails[adjX][adjY].f == FLT_MAX || cellDetails[adjX][adjY].f > fNew) {
                        openList.emplace(fNew, Point{adjX, adjY});

                        cellDetails[adjX][adjY].f = fNew;
                        cellDetails[adjX][adjY].g = gNew;
                        cellDetails[adjX][adjY].h = hNew;
                        cellDetails[adjX][adjY].parent_i = i;
                        cellDetails[adjX][adjY].parent_j = j;
                    }
                }
            }
        }
    }

    if (!foundDest)
        cout << "Failed to find the Destination Cell\n";
    return;
}

// Driver code
int main() {
    int ROW, COL;
    cout << "Enter the number of rows: ";
    cin >> ROW;
    cout << "Enter the number of columns: ";
    cin >> COL;

    vector<vector<int>> grid(ROW, vector<int>(COL));

    cout << "Enter the grid (1 for open cell, 0 for blocked cell):\n";
    for (int i = 0; i < ROW; ++i) {
        for (int j = 0; j < COL; ++j) {
            cin >> grid[i][j];
        }
    }

    Point src, dest;
    cout << "Enter the source point (x y): ";
    cin >> src.x >> src.y;
    cout << "Enter the destination point (x y): ";
    cin >> dest.x >> dest.y;

    aStarSearch(grid, src, dest);

    return 0;
}
