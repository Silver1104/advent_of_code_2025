#include <iostream>
#include <fstream>
#include <string>

namespace d1p1{
    int left_rotate(int& prev, int& amt, int& tot) {
        amt %= 100;
        int curr = (prev - amt);
        if (curr < 0) curr += 100;
        if (curr == 0) tot++;
        return curr;
    }

    int right_rotate(int& prev, int& amt, int& tot) {
        amt %= 100;
        int curr = (prev + amt) % 100;
        if (curr == 0) tot++;
        return curr;
    }
    int take_input()
    {
        std::ifstream infile("day1.txt");
        if (!infile.is_open()) {
            std::cerr << "Failed to open file." << std::endl;
            return 1;
        }
        std::string line;
        int curr{ 50 }, tot{};
        while (std::getline(infile, line)) {
            char dir = line[0];
            int amt = std::stoi(line.substr(1));
            switch (dir) {
            case 'L': curr = left_rotate(curr, amt, tot);
                break;
            case 'R': curr = right_rotate(curr, amt, tot);
                break;
            default: std::cout << "Invalid input";
                return -1;
            }
        }
        std::cout << "Total: " << tot << std::endl;
        return 0;
    }
}