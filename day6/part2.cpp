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

ll calcRes(const std::vector<std::vector<int>>& nums, const std::vector<char>& operations) {
    ll result = 0;
	int cols{ (int)operations.size() };
    for (int j = 0; j < cols; ++j) {
        if (operations[j] == '*') {
            ll prod{ 1 };
            for (auto& num : nums[j])
                prod *= 1LL * num;
            result += prod;
        }
        else {
            ll sum{};
            for (auto& num : nums[j])
                sum += 1LL * num;
            result += sum;
        }
        //std::cout << "Current res: " << result << std::endl;
        
    }
    return result;
}

ll runOnce() {
    std::ifstream infile("day6.txt");
    if (!infile.is_open()) {
        std::cerr << "Failed to open file." << std::endl;
        return 1;
    }

    std::vector<std::vector<int>> nums;
    std::vector<char> operations;
    std::string line;
    std::vector<std::string> lines;
    int max_ind = INT_MIN;
    while (std::getline(infile, line)) {
        if (line[0] == '*' || line[0] == '+') break;
        lines.push_back(line);
        max_ind = std::max(max_ind, (int)line.size());
    }
    std::stringstream ss_ops(line);
    char op;
	while (ss_ops >> op) operations.push_back(op);
    std::vector<int> space_pos;
    infile.close();
    int i{};
    while (true) {
        int space_at = INT_MIN;
        bool last = false;
        for (auto& line : lines) {
            int pos = line.find(' ', i);
            if (pos == std::string::npos) {
                last = true;
                break;
            }
            space_at = std::max(space_at, pos);
        }
        if (last) break;
        space_pos.push_back(space_at);
        i = space_at + 1;
    }
    space_pos.push_back(max_ind);
    int start{};
    for (auto& space : space_pos) {
        std::vector<int> temp;
        for (int i = start; i < space; ++i) {
            int currnum{};
            for (auto& line : lines) {
                if (line[i] == ' ') continue;
                currnum = (currnum * 10) + (line[i] - '0');
            }
            temp.push_back(currnum);
        }
        nums.push_back(temp);
        start = space + 1;
    }

    return calcRes(nums, operations);
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

