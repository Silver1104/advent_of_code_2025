#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <string_view>

typedef long long ll;

int findPower(std::string_view bank) {
    int max_power = INT_MIN;
    int bestTens = -1;
    for(auto &ch: bank) {
        int dig = ch - '0';
        if (bestTens != -1) {
            int curr_power = bestTens * 10 + dig;
            max_power = std::max(max_power, curr_power);
        }
        if (dig > bestTens) bestTens = dig;
    }
    return max_power;

}

int main() {
    std::ifstream infile("day3.txt");
    if (!infile.is_open()) {
        std::cerr << "Failed to open file." << std::endl;
        return 1;
    }
    std::string bank;
    ll tot{};
    while (std::getline(infile, bank)) {
        //std::cout << bank << std::endl;
        int res = findPower(bank);
        tot += res;
    }
    std::cout << tot << std::endl;
    return 0;
}