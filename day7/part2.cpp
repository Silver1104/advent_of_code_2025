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

ll dfs(int r, int c, const std::vector<std::string> &tach, const int &rows, const int &cols, std::vector<std::vector<ll>> &visited) {
    for (int i = r; i < rows; i++) {
        if (tach[i][c] == '^') {
            if (visited[i][c] != -1) return visited[i][c];
            ll left_beam = ((c - 1) >= 0) ? dfs(i+1, c - 1, tach, rows, cols, visited) : 0;
            ll right_beam = ((c + 1) < cols) ? dfs(i+1, c + 1, tach, rows, cols, visited) : 0;
            return visited[i][c] = (left_beam + right_beam);
        }
    }
    return 1;
}

ll runOnce() {
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
    std::vector<std::vector<ll>> visited(r, std::vector<ll>(c, -1));
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

        ll result = runOnce();   // <-- CALL YOUR COMPUTATION

        auto end = high_resolution_clock::now();
        double ms = duration_cast<milliseconds>(end - start).count();

        std::cout << "Run " << i << " time: " << ms << " ms, result=" << result << std::endl;

        totalTime += ms;
    }

    std::cout << "\nAverage time = " << (totalTime / RUNS) << " ms\n";
    return 0;
}

