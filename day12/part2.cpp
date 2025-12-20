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



int findValid(const std::vector<int>& gift_dim, const std::vector<std::vector<int>>& regions) {
    int ways{};
    for (auto& region : regions) {
		//std::cout << "Checking region of size " << region[0] << "x" << region[1] << std::endl;
        int length = region[0];
		int breadth = region[1];
        int total_tiles_available = length * breadth;
        int total_presents{};
		int min_fitting_presents = (length / 3) * (breadth / 3);
		//std::cout << "Can easily fit: " << min_fitting_presents << std::endl;
		for (int i = 2; i < 8; i++) total_presents += region[i];
		//std::cout << "Total presents: " << total_presents << std::endl;
        if (total_presents <= min_fitting_presents) {
            ways++;
            continue;
        }
		//std::cout << "Total area " << total_tiles_available << std::endl;
        int total_presents_area{};
        for (int i = 2; i < 8; ++i)
			total_presents_area += region[i] * gift_dim[i - 2];
		//std::cout << "Total presents area " << total_presents_area << std::endl;
        if(total_presents_area > total_tiles_available) {
            continue;
		}
        ways++;
    }
    return ways;
}

int getDataAndRun() {
    using namespace std::chrono;
    std::ifstream infile("day12.txt");
    if (!infile.is_open()) {
        std::cerr << "Failed to open file." << std::endl;
        return -1;
    }
    std::string line;
    std::vector<int> gift_dim(6);
    std::vector<std::vector<int>> regions;
    int curr_count{};
    for (int i = 0; i < 6; i++) {
        std::getline(infile, line);
        int curr_hash{};
        for (int row = 0; row < 3; ++row) {
            std::getline(infile, line);
            for (char& ch : line) if (ch == '#') curr_hash++;
        }
        gift_dim[i] = curr_hash;
        std::getline(infile, line);
    }
    while (std::getline(infile, line)) {
		size_t colon_pos = line.find(':');
		size_t x_pos = line.find('x');
        int length = std::stoi(line.substr(0, x_pos));
		int breadth = std::stoi(line.substr(x_pos + 1, colon_pos - x_pos - 1));
		line = line.substr(colon_pos + 2);
		std::vector<int> curr_region = { length, breadth };
        std::stringstream ss(line);
        std::string curr;
		while (std::getline(ss, curr, ' ')) {
            curr_region.push_back(std::stoi(curr));
        }
		regions.push_back(curr_region);
    }
    infile.close();

    for (auto& el : regions) {
		for (auto& e : el) std::cout << e << " ";
		std::cout << std::endl;
    }

    /*for (auto& el : adj_map) {
        for (auto& n : el.second) std::cout << n << " ";
        std::cout << std::endl;
    }*/

    const int RUNS = 5;
    double totalTime = 0;
    std::cout << std::fixed << std::setprecision(0);

    for (int i = 1; i <= RUNS; i++) {
        auto start = high_resolution_clock::now();
		int res = findValid(gift_dim, regions);
        auto end = high_resolution_clock::now();
        double ms = duration_cast<milliseconds>(end - start).count();
        std::cout << "Run " << i << " time: " << ms << " ms, result=" << res << std::endl;
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
