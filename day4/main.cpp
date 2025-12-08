#include <chrono>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_set>
#include <stack>

//typedef long long ll;
//std::unordered_set<ll> st;

int getAccesible(std::vector<std::string>& in) {
    const int r = static_cast<int>(in.size());
    const int c = static_cast<int>(in[0].size());

    constexpr int drow[] = { 1, 1, 1, 0, -1, -1, -1, 0 };
    constexpr int dcol[] = { -1, 0, 1, 1, 1, 0, -1, -1 };

    int res{};
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            if (in[i][j] != '@') continue;
            int tot{};
            for (int x = 0; x < 8; x++) {
                int ni = i + drow[x];
                int nj = j + dcol[x];
                if (ni >= 0 && ni < r && nj >= 0 && nj < c) {
                    if (in[ni][nj] == '@') {
                        ++tot;
                        if (tot > 3) break;
                    }
                }
            }
            if (tot <= 3) ++res;
        }
    }
    
    return res;
    
}

int runOnce() {
    std::ifstream infile("day4.txt");
    if (!infile.is_open()) {
        std::cerr << "Failed to open file." << std::endl;
        return 1;
    }

    std::string line;
    std::vector<std::string> inp;
    while (std::getline(infile, line)) {
        inp.push_back(line);
    }
    //9for (auto& el : inp) std::cout << el << std::endl;
    int res = getAccesible(inp);
    return res;  // return something so compiler doesn’t remove logic
}


int main() {
    using namespace std::chrono;

    const int RUNS = 5;
    double totalTime = 0;

    for (int i = 1; i <= RUNS; i++) {

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
