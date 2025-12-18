#include <chrono>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <iomanip>
#include <unordered_map>
#include <unordered_set>
#include <queue>

int allPaths(int curr, const int& end, const std::unordered_map<int, std::vector<int>>& adj_map, std::unordered_set<int>& vis) {
    if (curr == end) return 1;
    if (vis.find(curr) != vis.end()) return 0;
    vis.insert(curr);
    if (adj_map.find(curr) == adj_map.end()) return 0;

    int total{};
    for (auto& output : adj_map.at(curr)) {
        total += allPaths(output, end, adj_map, vis);
    }
    vis.erase(curr);
    return total;
}

double getDataAndRun() {
    using namespace std::chrono;
    std::ifstream infile("day11.txt");
    if (!infile.is_open()) {
        std::cerr << "Failed to open file." << std::endl;
        return -1;
    }
    std::string line;
    std::unordered_map<int, std::vector<int>> adj_map;
    std::unordered_map<std::string, int> string_map;
    int i{};
    while (std::getline(infile, line)) {
        size_t pos = line.find(':');
        std::string curr_device = line.substr(0, pos);
        int curr_device_ind;
        if (string_map.find(curr_device) == string_map.end())
            string_map[curr_device] = curr_device_ind = i++;
        else curr_device_ind = string_map[curr_device];

        line = line.substr(pos + 2);
        std::stringstream ss(line);
        std::string output;
        while (std::getline(ss, output, ' ')) {
            int output_ind;
            if (string_map.find(output) == string_map.end())
                string_map[output] = output_ind = i++;
            else output_ind = string_map[output];
            adj_map[curr_device_ind].push_back(output_ind);
        }
    }
    infile.close();
    int start_search = string_map["you"];
    int end_search = string_map["out"];
    /*for (auto& el : adj_map) {
        for (auto& n : el.second) std::cout << n << " ";
        std::cout << std::endl;
    }*/
    std::cout << start_search << " " << end_search << std::endl;
    const int RUNS = 5;
    double totalTime = 0;
    std::cout << std::fixed << std::setprecision(0);

    for (int i = 1; i <= RUNS; i++) {
        auto start = high_resolution_clock::now();
        std::unordered_set<int> visited;
        int result = allPaths(start_search, end_search, adj_map, visited);
        auto end = high_resolution_clock::now();
        double ms = duration_cast<milliseconds>(end - start).count();
        std::cout << "Run " << i << " time: " << ms << " ms, result=" << result << std::endl;
        totalTime += ms;
    }

    std::cout << "\nAverage time = " << (totalTime / RUNS) << " ms\n";
    return 1;
}

int main() {
    using namespace std::chrono;

    getDataAndRun();
    return 0;
}
