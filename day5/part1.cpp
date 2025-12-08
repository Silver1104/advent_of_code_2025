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

std::vector<std::vector<ll>> mergeIntervals(std::vector<std::vector<ll>>& fresh) {
    std::sort(fresh.begin(), fresh.end());
    std::vector < std::vector <ll>> res;
    std::vector<ll> temp = fresh[0];
    for (auto& el : fresh) {
        if (el[0] <= temp[1])
            temp[1] = std::max(temp[1], el[1]);
        else {
            res.push_back(temp);
            temp = el;
        }
    }
    res.push_back(temp);
    return res;
}

int countFresh(std::vector<ll> &ingredients, const std::vector<std::vector<ll>> &fresh) {
    int count{};
    int n{ (int)fresh.size() };
    for (ll& ing : ingredients) {
        int l{}, h{ n-1 }, mid;
        while (l <= h) {
            int mid = (l + h) >> 1;
            ll interval_beg = fresh[mid][0];
            ll interval_end = fresh[mid][1];
            if (ing > interval_end) {
                l = mid + 1;
                continue; 
            }
            else if (ing < interval_beg) {
                h = mid - 1;
                continue;
            }
            else {
                count++;
                break;
            }
        }
    }
    return count;
}

int runOnce() {
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

    while (std::getline(infile, line))
        ingredients.push_back(stoll(line));

    fresh_int = mergeIntervals(fresh_int);

    return countFresh(ingredients, fresh_int); // return something so compiler doesn’t remove logic
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

