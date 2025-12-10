#include <chrono>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <stack>
#include <algorithm>
#include <unordered_map>

typedef long double ld;

ld getMaxArea(const std::map<int, std::pair<int, int>>& coords, const ld& max_h) {
    std::vector<std::pair<int, std::pair<int, int>>> vec(coords.begin(), coords.end());
    ld max_area = 0;
    int n = vec.size();
    for (int i = 0; i < n; ++i) {
        int xl = vec[i].first;
        int y_min_left = vec[i].second.first;
        int y_max_left = vec[i].second.second;

        for (int j = n - 1; j >= i; --j) {
            int xr = vec[j].first;
            ld curr_length = static_cast<ld>(xr - xl + 1);
            if (curr_length * max_h <= max_area) {
                break;
            }

            int y_min_right = vec[j].second.first;
            int y_max_right = vec[j].second.second;

            ld width_1 = static_cast<ld>(y_max_left - y_min_right + 1);
            ld width_2 = static_cast<ld>(y_max_right - y_min_left + 1);

            ld ar1 = curr_length * width_1;
            ld ar2 = curr_length * width_2;

            max_area = std::max(max_area, std::max(ar1, ar2));
        }
    }

    return max_area;
}

ld runOnce() {
    std::ifstream infile("day9.txt");
    if (!infile.is_open()) {
        std::cerr << "Failed to open file." << std::endl;
        return 1;
    }

    std::map<int, std::pair<int, int>> coords;
	int g_max_y = INT_MIN;
	int g_min_y = INT_MAX;
    std::string line;
    int n{};
    while (std::getline(infile, line)) {
        size_t comma = line.find(',');
        int x = std::stoi(line.substr(0, comma));
        int y = std::stoi(line.substr(comma + 1));
        g_max_y = std::max(g_max_y, y);
        g_min_y = std::min(g_min_y, y);
        if (!coords.count(x)) {
            coords[x] = { y, y };
        }
        else {
            coords[x].first = std::min(coords[x].first, y);
            coords[x].second = std::max(coords[x].second, y);
        }
    }

    ld max_height = static_cast<ld>(g_max_y - g_min_y + 1);

    ld res = getMaxArea(coords, max_height);
    //std::cout << "Yipee";
    infile.close();
    return res;
}

int main() {
    using namespace std::chrono;

    const int RUNS = 5;
    double totalTime = 0;
    std::cout << std::fixed << std::setprecision(0);
    for (int i = 1; i <= 5; i++) {

        auto start = high_resolution_clock::now();
        ld result = runOnce();

        auto end = high_resolution_clock::now();
        double ms = duration_cast<milliseconds>(end - start).count();

        std::cout << "Run " << i << " time: " << ms << " ms, result=" << result << std::endl;

        totalTime += ms;
    }

    std::cout << "\nAverage time = " << (totalTime / RUNS) << " ms\n";
    return 0;
}

