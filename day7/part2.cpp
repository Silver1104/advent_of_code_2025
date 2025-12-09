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
    std::vector<ll> next_row(c, 1);
    int origin{};
    while (tachyons[0][origin] != 'S') ++origin;

    for (int i = r - 2; i >= 1; i--) {
        std::vector<ll> curr_row(c, 0);
        for (int j = 0; j < c; j++) {
            if (tachyons[i][j] != '^') {
                curr_row[j] = next_row[j];
                continue;
            }
            ll leftbeam = (j - 1 >= 0) ? next_row[j - 1] : 0;
            ll rightbeam = (j + 1 < c) ? next_row[j + 1] : 0;
            curr_row[j] = leftbeam + rightbeam;
        }
        next_row = curr_row;
        curr_row.clear();
    }

    return next_row[origin];
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

