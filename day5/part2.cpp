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

ll mergeAndCountIntervals(std::vector<std::vector<ll>>& fresh) {
    std::sort(fresh.begin(), fresh.end());
    ll res{};
    std::vector<ll> temp = fresh[0];
    for (auto& el : fresh) {
        if (el[0] <= temp[1])
            temp[1] = std::max(temp[1], el[1]);
        else {
            res += (temp[1] - temp[0] + 1);
            temp = el;
        }
    }
    res += (temp[1] - temp[0] + 1);
    return res;
}

ll runOnce() {
    std::ifstream infile("day5.txt");
    if (!infile.is_open()) {
        std::cerr << "Failed to open file." << std::endl;
        return 1;
    }

    std::vector<std::vector<ll>> fresh_int;
    std::vector<ll> ingredients;
    std::string line;

    while (std::getline(infile, line)) {
        if (line.empty()) break;
        size_t dash = line.find('-');
        ll L = stoll(line.substr(0, dash));
        ll R = stoll(line.substr(dash + 1));
        fresh_int.push_back({ L, R });
    }
    infile.close();
    return mergeAndCountIntervals(fresh_int);
}


int main() {
    using namespace std::chrono;

    const int RUNS = 5;
    double totalTime = 0;

    for (int i = 1; i <= 1; i++) {

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

