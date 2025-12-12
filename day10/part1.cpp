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

double minMoves(const std::string& start, const std::string& target,
    const std::vector<std::vector<int>>& ops) {
    if (start == target) return 0;

    std::unordered_map<std::string, double> dist;
    std::queue<std::string> q;

    q.push(start);
    dist[start] = 0;

    while (!q.empty()) {
        std::string curr = q.front();
        q.pop();

        if (curr == target) {
            return dist[curr];
        }

        for (const auto& op : ops) {
            std::string next = curr;
            // Apply operation
            for (int bit : op) {
                next[bit] = (next[bit] == '.') ? '#' : '.';
            }

            // If not visited yet
            if (dist.find(next) == dist.end()) {
                dist[next] = dist[curr] + 1;
                q.push(next);
            }
        }
    }

    return INT_MAX; // Target unreachable
}

double runCode(const std::vector<std::string>& indicators,
               const std::vector<std::vector<std::vector<int>>>& ops,
               const std::vector<std::vector<int>>& joltages) {
    int n{ (int)indicators.size() };
    double tot = 0;
    for (int i = 0; i < n; i++) {
        std::string target_ind = indicators[i];
        int x = target_ind.size();
        std::string start_ind(x, '.');
        double min_moves = minMoves(start_ind, target_ind, ops[i]);
        tot += min_moves;
    }
    return tot;
}

double getDataAndRun() {
    using namespace std::chrono;
    std::ifstream infile("day10.txt");
    if (!infile.is_open()) {
        std::cerr << "Failed to open file." << std::endl;
        return -1;
    }
    std::string line;
    std::vector<std::string> indicators;
    std::vector<std::vector<int>> joltages;
    std::vector<std::vector<std::vector<int>>> ops;
    while (std::getline(infile, line)) {
        std::vector<std::vector<int>> temp_ops = {};
        size_t indic_start = line.find('[');
        size_t indic_end = line.find(']');
        indicators.push_back(line.substr(indic_start + 1, indic_end - indic_start - 1));
        size_t jolt_start = line.find('{');
        size_t jolt_end = line.find('}');
        std::string jolts = line.substr(jolt_start + 1, jolt_end - jolt_start - 1);
        std::vector<int> temp_jolt = {};
        while (jolts != "") {
            //std::cout << jolts << std::endl;
            size_t comma = jolts.find(',');
            int jolt = (comma == std::string::npos) ? std::stoi(jolts) : std::stoi(jolts.substr(0, comma));
            temp_jolt.push_back(jolt);
            if (comma == std::string::npos) break;
            jolts = jolts.substr(comma + 1);
        }
        joltages.push_back(temp_jolt);
        std::string op = line.substr(indic_end + 2, jolt_start - 1 - indic_end - 2);
        while (op != "") {
            size_t beg = op.find("(");
            size_t end = op.find(")");
            std::vector<int> temp = {};
            std::string curr_ops = op.substr(beg+1, end - beg-1);
            //std::cout << curr_ops << " ";
            while (curr_ops != "") {
                size_t comma = curr_ops.find(',');
                int num = (comma == std::string::npos) ? std::stoi(curr_ops) : std::stoi(curr_ops.substr(0, comma));
                temp.push_back(num);
                if (comma == std::string::npos) break;
                curr_ops = curr_ops.substr(comma + 1);
            }
            temp_ops.push_back(temp);
            //std::cout << std::endl;
            op = op.substr(end + 1);
        }
        ops.push_back(temp_ops);
    }

    infile.close();
    const int RUNS = 5;
    double totalTime = 0;
    std::cout << std::fixed << std::setprecision(0);

    for (int i = 1; i <= RUNS; i++) {
        auto start = high_resolution_clock::now();
        double result = runCode(indicators, ops, joltages);
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
