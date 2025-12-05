#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <string_view>
#include <queue>

typedef long long ll;

ll findPower(std::string_view bank) {
    std::vector<int> bv;
    for (auto& ch : bank) bv.push_back(ch - '0');
    int n{ (int)bv.size() };
    ll res{0};
    int prev_ind = -1;
    for (int i = 12; i > 0; i--) {
        int startind = prev_ind + 1;
        int maxnum = INT_MIN;
        for (int j = startind; j <= (n - i); j++) {
            if (bv[j] > maxnum) {
                maxnum = bv[j];
                prev_ind = j;
            }
        }
        res = res * 10 + maxnum;
    }
    return res;
}

int main() {
    std::ifstream infile("day3.txt");
    if (!infile.is_open()) {
        std::cerr << "Failed to open file." << std::endl;
        return 1;
    }
    std::string bank;
    ll tot{0};
    while (std::getline(infile, bank)) {
        //std::cout << bank << std::endl;
        ll res = findPower(bank);
        tot += res;
    }
    std::cout << tot << std::endl;
    return 0;
}