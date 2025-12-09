#include <chrono>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_set>
#include <stack>
#include <algorithm>

typedef long long ll;

int dfs(int r, int c, const std::vector<std::string> &tach, const int &rows, const int &cols, std::vector<std::vector<int>> &visited) {
    if (visited[r][c]) return 0;
    visited[r][c] = 1;
    for (int i = r; i < rows; i++) {
        if (tach[i][c] == '^') {
            if (visited[i][c]) return 0;
            visited[i][c] = 1;
            //std::cout << "Tachyon found at (" << i << "," << c << ")" << std::endl;
            int left_beam = ((c - 1) >= 0) ? dfs(i+1, c - 1, tach, rows, cols, visited) : 0;
            int right_beam = ((c + 1) < cols) ? dfs(i+1, c + 1, tach, rows, cols, visited) : 0;
            //std::cout << "After splitting at row : "<< i << " and col " << c << ": " << left_beam << " " << right_beam << std::endl;
            return (1 + left_beam + right_beam);
        }
    }
    return 0;
}

int runOnce() {
    std::ifstream infile("day7.txt");
    if (!infile.is_open()) {
        std::cerr << "Failed to open file." << std::endl;
        return 1;
    }

    std::vector<std::string> tachyons;
    std::string line;
    while (std::getline(infile, line)) {
        tachyons.push_back(line);
    }
    infile.close();
    int r{ (int)tachyons.size() };
    int c{ (int)tachyons[0].size() };
    std::vector<std::vector<int>> visited(r, std::vector<int>(c, 0));
    int origin{};
    while (tachyons[0][origin] != 'S') ++origin;
    return dfs(1, origin, tachyons, r, c, visited);
}


int main() {
    using namespace std::chrono;

    const int RUNS = 5;
    double totalTime = 0;

    for (int i = 1; i <= 5; i++) {

        auto start = high_resolution_clock::now();

        int result = runOnce();   // <-- CALL YOUR COMPUTATION

        auto end = high_resolution_clock::now();
        double ms = duration_cast<milliseconds>(end - start).count();

        std::cout << "Run " << i << " time: " << ms << " ms, result=" << result << std::endl;

        totalTime += ms;
    }

    std::cout << "\nAverage time = " << (totalTime / RUNS) << " ms\n";
    return 0;
}

