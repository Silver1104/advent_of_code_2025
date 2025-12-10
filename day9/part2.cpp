#include <chrono>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <iomanip>
#include <unordered_map>
#include <queue>

std::unordered_map<int, int> compressSizes(const std::vector<int>& vec) {
    std::unordered_map<int, int> mpp;
    int i{};
    int n{ (int)vec.size() };
    for (int i = 0; i < n - 1; i++) {
        mpp[i * 2 + 1] = vec[i + 1] - vec[i] - 1;
    }
    return mpp;
}

int findPos(const std::unordered_map<int, int>& x, const int& elem) {
    auto it = x.find(elem);
    return it->second;
}

void makeCompressedGrid(
    std::vector<std::vector<int>>& grid,
    const std::unordered_map<int, int>& xmap,
    const std::unordered_map<int, int>& ymap,
    const std::vector<std::pair<int, int>>& points)
{
    int n = points.size();

    for (int i = 0; i < n; i++) {
        auto [x1, y1] = points[i];
        auto [x2, y2] = points[(i + 1) % n]; // wraparound

        int cx1 = xmap.at(x1) * 2;
        int cx2 = xmap.at(x2) * 2;
        int cy1 = ymap.at(y1) * 2;
        int cy2 = ymap.at(y2) * 2;

        if (cx1 > cx2) std::swap(cx1, cx2);
        if (cy1 > cy2) std::swap(cy1, cy2);

        for (int cx = cx1; cx <= cx2; cx++) {
            for (int cy = cy1; cy <= cy2; cy++) {
                grid[cx][cy] = 1;
            }
        }
    }
}

void fillGrid(std::vector<std::vector<int>>& grid) {
    int xmax = grid.size();
    int ymax = grid[0].size();
    const std::vector<std::pair<int, int>> dir = { {1,0}, {0,1}, {-1,0}, {0,-1} };
    std::queue<std::pair<int, int>> q;
    q.push({ -1,-1 });
    std::set<std::pair<int, int>> outside;
    while (!q.empty()) {
        auto [x1, y1] = q.front();
        q.pop();
        for (int i = 0; i < 4; i++) {
            int nx = x1 + dir[i].first;
            int ny = y1 + dir[i].second;
            if (ny < -1 || nx < -1 || nx > xmax || ny > ymax) continue;
            if (nx >= 0 && nx < xmax && ny >= 0 && ny < ymax && grid[nx][ny] == 1) continue;
            if (outside.find({ nx,ny }) != outside.end()) continue;
            outside.insert({ nx,ny });
            q.push({ nx,ny });
        }
    }
    for (int i = 0; i < xmax; i++)
        for (int j = 0; j < ymax; j++)
            if (outside.find({ i,j }) == outside.end()) grid[i][j] = 1;
}

void findPrefix(std::vector<std::vector<int>>& grid) {
    int rows = grid.size();
    int cols = grid[0].size();
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            int left = (j - 1 >= 0) ? grid[i][j - 1] : 0;
            int top = (i - 1 >= 0) ? grid[i - 1][j] : 0;
            int top_left = (i - 1 >= 0 && j - 1 >= 0) ? grid[i - 1][j - 1] : 0;
            grid[i][j] += (left + top - top_left);
        }
    }
}

bool validRectangle(const std::vector<std::vector<int>>& prefix,
    const std::unordered_map<int, int>& xmap,
    const std::unordered_map<int, int>& ymap,
    const std::pair<int, int>& p1, const std::pair<int, int>& p2) {
    int cx1 = xmap.at(p1.first) * 2;
    int cx2 = xmap.at(p2.first) * 2;
    int cy1 = ymap.at(p1.second) * 2;
    int cy2 = ymap.at(p2.second) * 2;
    if (cx1 > cx2) std::swap(cx1, cx2);
    if (cy1 > cy2) std::swap(cy1, cy2);
    int left = (cx1 - 1 >= 0) ? prefix[cx1 - 1][cy2] : 0;
    int top = (cy1 - 1 >= 0) ? prefix[cx2][cy1 - 1] : 0;
    int top_left = (cx1 - 1 >= 0 && cy1 - 1 >= 0) ? prefix[cx1 - 1][cy1 - 1] : 0;
    int count = prefix[cx2][cy2] - left - top + top_left;
    return (count == (cx2 - cx1 + 1) * (cy2 - cy1 + 1));
}

double calcAreaRectangle(int x1, int x2, int y1, int y2) {
    double length = static_cast<double>(abs(x1 - x2) + 1);
    double breadth = static_cast<double>(abs(y1 - y2) + 1);
    return (length * breadth);
}

double findMax(const std::vector<std::pair<int, int>>& points, const std::vector<std::vector<int>>& prefix,
    const std::unordered_map<int, int>& xmap, const std::unordered_map<int, int>& ymap) {
    double max_area = 0;
    int n{ (int)points.size() };
    for (int i = 0; i < n-1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (validRectangle(prefix, xmap, ymap, points[i], points[j])) {
                //std::cout << "Valid rectangle: (" << points[i].first << "," << points[i].second << ")" << " (" << points[j].first << "," << points[j].second << std::endl;
                double curr_area = calcAreaRectangle(points[i].first, points[j].first, points[i].second, points[j].second);
                max_area = std::max(curr_area, max_area);
            }
        }
    }
    return max_area;
}

double runOnce() {
    std::ifstream infile("day9.txt");
    if (!infile.is_open()) {
        std::cerr << "Failed to open file." << std::endl;
        return -1;
    }
    std::string line;
    std::set<int> xset, yset;
    std::vector<std::pair<int, int>> points;
    while (std::getline(infile, line)) {
        size_t comma = line.find(',');
        int x = std::stoi(line.substr(0, comma));
        int y = std::stoi(line.substr(comma + 1));
        xset.insert(x);
        yset.insert(y);
        points.push_back({ x,y });
    }

    std::vector<int> xs(xset.begin(), xset.end());
    std::vector<int> ys(yset.begin(), yset.end());
    std::unordered_map<int, int> xmap, ymap;
    int i{};
    for (auto& x : xs) xmap[x] = i++;
    i = 0;
    for (auto& y : ys) ymap[y] = i++;

    std::unordered_map<int, int> cxsizes = compressSizes(xs);
    std::unordered_map<int, int> cysizes = compressSizes(ys);

    std::vector<std::vector<int>> comp_grid(xs.size() * 2 - 1, std::vector<int>(ys.size() * 2 - 1, 0));
    makeCompressedGrid(comp_grid, xmap, ymap, points);

    /*for (auto& el : comp_grid) {
        for (auto& e : el) std::cout << e << " ";
        std::cout << std::endl;
    }
    std::cout << std::endl;*/
    fillGrid(comp_grid);
    /*for (auto& el : comp_grid) {
        for (auto& e : el) std::cout << e << " ";
        std::cout << std::endl;
    }*/
    std::vector<std::vector<int>> prefix_grid = comp_grid;
    findPrefix(prefix_grid);
    /*for (auto& el : prefix_grid) {
        for (auto& e : el) std::cout << e << " ";
        std::cout << std::endl;
    }*/

    double max_area = findMax(points, prefix_grid, xmap, ymap);
    infile.close();
    return max_area;
}

int main() {
    using namespace std::chrono;

    const int RUNS = 5;
    double totalTime = 0;
    std::cout << std::fixed << std::setprecision(0);

    for (int i = 1; i <= RUNS; i++) {
        auto start = high_resolution_clock::now();
        double result = runOnce();
        auto end = high_resolution_clock::now();
        double ms = duration_cast<milliseconds>(end - start).count();
        std::cout << "Run " << i << " time: " << ms << " ms, result=" << result << std::endl;
        totalTime += ms;
    }

    std::cout << "\nAverage time = " << (totalTime / RUNS) << " ms\n";
    return 0;
}
