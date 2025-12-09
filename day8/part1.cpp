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

typedef long long ll;

class disJointSet {
private:
    std::vector<int> par;
    std::vector<int> size;
    std::map<int,int> mpp;
public:
    disJointSet(const int n) {
        par.resize(n);
        size.resize(n, 1);
        for (int i = 0; i < n; i++) {
            par[i] = i;
            mpp[1]++;
        }
    }
    int findPar(int x) {
        if (par[x] == x) return x;
        return findPar(par[x]);
    }
    void unionize(const int &u, const int &v) {
        int pu = findPar(u);
        int pv = findPar(v);
        if (pu == pv) return;
        if (size[pu] > size[pv]) {
            par[pv] = pu;
            if (--mpp[size[pu]] == 0) mpp.erase(size[pu]);
            if (--mpp[size[pv]] == 0) mpp.erase(size[pv]);
            size[pu] += size[pv];
            mpp[size[pu]]++;
        }
        else {
            par[pu] = pv;
            if (--mpp[size[pu]] == 0) mpp.erase(size[pu]);
            if (--mpp[size[pv]] == 0) mpp.erase(size[pv]);
            size[pv] += size[pu];
            mpp[size[pv]]++;
        }
    }
    std::map<int,int> getAllSizes() {
        return mpp;
    }
    void printSet() {
        for (auto& el : mpp) {
            std::cout << "For size " << el.first << ", count: " << el.second << std::endl;

        }
    }
};

std::map<int,int> makeAllGroups(const std::map<double, std::vector<std::pair<int, int>>> dist, const int &n) {
    disJointSet ds(n);
    ds.printSet();
    int amt{};
    bool end = false;
    for (auto& curr_dist : dist) {
        for (auto& coord : curr_dist.second) {
            //std::cout << "Uniting: " << coord.first << "," << coord.second << std::endl;
            ds.unionize(coord.first, coord.second);
            ++amt;
            //ds.printSet();
            if (amt == 1000) {
                end = true;
                break;
            }

        }
        if (end) break;
    }
    return ds.getAllSizes();
}

double findDist(const std::vector<int> &coord1, const std::vector<int> &coord2) {
    double sqx = static_cast<double>(pow(coord1[0] - coord2[0], 2));
    double sqy = static_cast<double>(pow(coord1[1] - coord2[1], 2));
    double sqz = static_cast<double>(pow(coord1[2] - coord2[2], 2));
    double tot = sqx + sqy + sqz;
    double dist = static_cast<double>(pow(tot, 0.5));
    return dist;
}

std::map<double,std::vector<std::pair<int,int>>> makeDistMap(const std::vector<std::vector<int>> coords, const int &n) {
    std::map<double, std::vector<std::pair<int, int>>> mpp;
    for (int i = 0; i < n-1; ++i) {
        for (int j = i + 1; j < n; ++j) {
            double currdist = findDist(coords[i], coords[j]);
            mpp[currdist].push_back({ i,j });
        }
    }
    return mpp;
}

ll runOnce() {
    std::ifstream infile("day8.txt");
    if (!infile.is_open()) {
        std::cerr << "Failed to open file." << std::endl;
        return 1;
    }

    std::vector<std::vector<int>> coords;
    std::string line;
    int n{};
    while (std::getline(infile, line)) {
        size_t first = line.find(',');
        size_t second = line.find(',', first + 1);
        int x = stoi(line.substr(0, first));
        int y = stoi(line.substr(first + 1, second - first - 1));
        int z = stoi(line.substr(second + 1));
        coords.push_back({ x,y,z });
        n++;
    }
    infile.close();
    std::map<double, std::vector<std::pair<int, int>>> distances = makeDistMap(coords, n);
    std::map<int,int> si = makeAllGroups(distances, n);
    /*for (auto& el : si) {
        std::cout << "For size " << el.first << ", count: " << el.second << std::endl;
    }*/
    /*std::cout << std::endl;*/
    ll res = 1;
    int amt{3};

    /*for (auto& el : si) {
        std::cout << "For size " << el.first << ", count: " << el.second << std::endl;

    }*/

    for (auto it = si.rbegin(); it != si.rend(); ++it) {
        int size = it->second;
        while (size && amt) {
            res *= it->first;
            --size;
            --amt;
        }
        if (amt == 0) break;
    }
    return res;
    
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

