#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

typedef long long ll;

ll ipow10(int x) {
    ll r = 1;
    while (x--) r *= 10;
    return r;
}

//Total invalid operations will always be equal to number of digits with half of the digits in the original number
ll beginAt(int dig, ll& n) {
    ll factor = ipow10(dig);
    ll firstpart = n / factor;
    ll secondpart = n % factor;
    if (firstpart >= secondpart) return firstpart;
    else return (firstpart + 1);
}

ll endAt(int dig, ll& n) {
    ll factor = ipow10(dig);
    ll firstpart = n / factor;
    ll secondpart = n % factor;
    if (firstpart <= secondpart) return firstpart;
    else return (firstpart - 1);
}

ll findSum(ll begin, ll end, int dig) {
    ll num = ipow10(dig);
    //std::cout << begin << "," << end << std::endl;
    ll sum = 0;
    for (ll i = begin; i <= end; i++) {
        ll curr_num = (i * num) + i;
        sum += curr_num;
    }
    return sum;

}

ll findInvalid(std::vector<ll>& nums) {
    ll n1 = nums[0];
    ll n2 = nums[1];
    int dig1 = (n1 == 0) ? 1 : (floor(log10(n1)) + 1);
    int dig2 = (n2 == 0) ? 1 : (floor(log10(n2)) + 1);
    ll begin, end;
    ll total = 0;
    // Answer only possible for number with even number of digits.
    if (dig1 % 2) { //Promoting beginning to next space with even digits.
        dig1++;
        dig1 /= 2;
        begin = ipow10(dig1 - 1);
    }
    else {  // If even just finding where to start from
        dig1 /= 2;
        begin = beginAt(dig1, n1);
    }
    //std::cout << dig1 << " " << begin << std::endl;
    if (dig2 % 2) {  //Promoting end to previous space with even digits.
        dig2--; 
        dig2 /= 2;
        end = ipow10(dig2) - 1;
    }
    else {   // If even, just finding where to end
        dig2 /= 2;
        end = endAt(dig2, n2);
    }
    //std::cout << dig2 << " " << end << std::endl;
    if (dig1 > dig2) return 0; // if digit1 is promoted above digit2 or digit2 below dig1, the space was invalid to begin with. No answer
    if (dig1 == dig2) return findSum(begin, end, dig1); //If both in same digit range, can be checked at once together
    else {
        int ind = dig1 + 1;
        while (ind < dig2) {
            ll curr_begin = ipow10(ind);
            ll curr_end = ipow10(ind+1) - 1;
            total += findSum(curr_begin, curr_end, ind);
            ind++;
        }
        ll first_part_space = ipow10(dig1) - 1;
        total += findSum(begin, first_part_space, dig1);
        ll second_part_space = ipow10(dig2);
        total += findSum(second_part_space, end, dig2);
    }
    return total;
}

int main() {
    std::ifstream infile("day2.txt");
    if (!infile.is_open()) {
        std::cerr << "Failed to open file." << std::endl;
        return 1;
    }
    std::string line;
    std::getline(infile, line);
    std::stringstream ss(line);
    std::string temp;
    ll total{};
    while (std::getline(ss, temp, ',')) {
        std::vector<ll> nums;
        std::stringstream stemp(temp);
        std::string num;
        while (std::getline(stemp, num, '-')) {
            nums.push_back(stoll(num));
        }
        //std::cout << "For numbers: " << nums[0] << " " << nums[1] << ": ";
        ll ans = findInvalid(nums);
        //std::cout << ans << std::endl;
        total += ans;
    }
    std::cout << "Total: " << total << std::endl;
    return 0;
}