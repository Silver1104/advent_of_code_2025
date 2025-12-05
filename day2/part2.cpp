//#include <iostream>
//#include <fstream>
//#include <string>
//#include <sstream>
//#include <vector>
//
//typedef long long ll;
//
//ll ipow10(int x) {
//    ll r = 1;
//    while (x--) r *= 10;
//    return r;
//}
//
////Total invalid operations will always be equal to number of digits with half of the digits in the original number
//ll beginAt(int dig, ll& n) {
//    ll factor = ipow10(dig);
//    ll firstpart = n / factor;
//    ll secondpart = n % factor;
//    if (firstpart >= secondpart) return firstpart;
//    else return (firstpart + 1);
//}
//
//ll endAt(int dig, ll& n) {
//    ll factor = ipow10(dig);
//    ll firstpart = n / factor;
//    ll secondpart = n % factor;
//    if (firstpart <= secondpart) return firstpart;
//    else return (firstpart - 1);
//}
//
//ll findSum(ll begin, ll end, int dig) {
//    ll num = ipow10(dig);
//    //std::cout << begin << "," << end << std::endl;
//    ll sum = 0;
//    for (ll i = begin; i <= end; i++) {
//        ll curr_num = (i * num) + i;
//        sum += curr_num;
//    }
//    return sum;
//
//}
//
//ll findInvalid(std::vector<ll>& nums) {
//    ll n1 = nums[0];
//    ll n2 = nums[1];
//    int dig1 = (n1 == 0) ? 1 : (floor(log10(n1)) + 1);
//    int dig2 = (n2 == 0) ? 1 : (floor(log10(n2)) + 1);
//    ll begin, end;
//    ll total = 0;
//    // Answer only possible for number with even number of digits.
//    if (dig1 % 2) { //Promoting beginning to next space with even digits.
//        dig1++;
//        dig1 /= 2;
//        begin = ipow10(dig1 - 1);
//    }
//    else {  // If even just finding where to start from
//        dig1 /= 2;
//        begin = beginAt(dig1, n1);
//    }
//    //std::cout << dig1 << " " << begin << std::endl;
//    if (dig2 % 2) {  //Promoting end to previous space with even digits.
//        dig2--; 
//        dig2 /= 2;
//        end = ipow10(dig2) - 1;
//    }
//    else {   // If even, just finding where to end
//        dig2 /= 2;
//        end = endAt(dig2, n2);
//    }
//    //std::cout << dig2 << " " << end << std::endl;
//    if (dig1 > dig2) return 0; // if digit1 is promoted above digit2 or digit2 below dig1, the space was invalid to begin with. No answer
//    if (dig1 == dig2) return findSum(begin, end, dig1); //If both in same digit range, can be checked at once together
//    else {
//        int ind = dig1 + 1;
//        while (ind < dig2) {
//            ll curr_begin = ipow10(ind);
//            ll curr_end = ipow10(ind+1) - 1;
//            total += findSum(curr_begin, curr_end, ind);
//            ind++;
//        }
//        ll first_part_space = ipow10(dig1) - 1;
//        total += findSum(begin, first_part_space, dig1);
//        ll second_part_space = ipow10(dig2);
//        total += findSum(second_part_space, end, dig2);
//    }
//    return total;
//}
//
//int main() {
//    std::ifstream infile("day2.txt");
//    if (!infile.is_open()) {
//        std::cerr << "Failed to open file." << std::endl;
//        return 1;
//    }
//    std::string line;
//    std::getline(infile, line);
//    std::stringstream ss(line);
//    std::string temp;
//    ll total{};
//    while (std::getline(ss, temp, ',')) {
//        std::vector<ll> nums;
//        std::stringstream stemp(temp);
//        std::string num;
//        while (std::getline(stemp, num, '-')) {
//            nums.push_back(stoll(num));
//        }
//        //std::cout << "For numbers: " << nums[0] << " " << nums[1] << ": ";
//        ll ans = findInvalid(nums);
//        //std::cout << ans << std::endl;
//        total += ans;
//    }
//    std::cout << "Total: " << total << std::endl;
//    return 0;
//}

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_set>

typedef long long ll;
std::unordered_set<ll> st;

ll ipow10(int x) {
    ll r = 1;
    while (x--) r *= 10;
    return r;
}

//Total invalid operations will always be equal to number of digits with half of the digits in the original number
ll beginAt(int dig, ll n, int& divs) {
    ll factor = ipow10(dig);
    std::vector<ll> parts(divs);

    for (int i = divs - 1; i >= 0; i--) {
        parts[i] = n % factor;
        n /= factor;
    }

    // Check if we need to increment
    // If all parts equal, or parts[0] >= all others, we can use parts[0]
    bool needIncrement = false;
    for (int i = 1; i < divs; i++) {
        if (parts[0] < parts[i]) {
            needIncrement = true;
            break;
        }
        else if (parts[0] > parts[i]) {
            // If first part is already larger, we're good
            needIncrement = false;
            break;
        }
    }

    // If all parts are equal, no increment needed
    if (!needIncrement) {
        bool allEqual = true;
        for (int i = 1; i < divs; i++) {
            if (parts[i] != parts[0]) {
                allEqual = false;
                break;
            }
        }
        if (allEqual) return parts[0];
    }

    return needIncrement ? parts[0] + 1 : parts[0];
}

ll endAt(int dig, ll n, int& divs) {
    ll factor = ipow10(dig);
    std::vector<ll> parts(divs);

    for (int i = divs - 1; i >= 0; i--) {
        parts[i] = n % factor;
        n /= factor;
    }

    // Check if we need to decrement
    bool needDecrement = false;
    for (int i = 1; i < divs; i++) {
        if (parts[0] > parts[i]) {
            needDecrement = true;
            break;
        }
        else if (parts[0] < parts[i]) {
            needDecrement = false;
            break;
        }
    }

    // If all parts are equal, no decrement needed
    if (!needDecrement) {
        bool allEqual = true;
        for (int i = 1; i < divs; i++) {
            if (parts[i] != parts[0]) {
                allEqual = false;
                break;
            }
        }
        if (allEqual) return parts[0];
    }

    return needDecrement ? parts[0] - 1 : parts[0];
}

void findSum(ll begin, ll end, int dig, int divs) {
    ll num = ipow10(dig);
    //std::cout << begin << "," << end << std::endl;
    for (ll i = begin; i <= end; i++) {
        ll currnum = 0;
        for (int j = 0; j < divs; j++) {
            currnum = (currnum * num) + i;
        }
        std::cout << "Valid answer: " << currnum << std::endl;
        st.insert(currnum);
    }
}

ll findInvalid(std::vector<ll>& nums, int divs) {
    ll n1 = nums[0];
    ll n2 = nums[1];
    int dig1 = (n1 == 0) ? 1 : (floor(log10(n1)) + 1);
    int dig2 = (n2 == 0) ? 1 : (floor(log10(n2)) + 1);
    
    ll begin, end;
    if (divs > dig1 && divs > dig2) return -1;
    else if (divs > dig1 && divs <= dig2) {
        dig1 = divs;
        n1 = ipow10(dig1 - 1);
    }
    int bkdig1 = dig1, bkdig2 = dig2;
    // Answer only possible for number with even number of digits.
    if (dig1 % divs) { //Promoting beginning to next space with even digits.
        dig1 += (divs - (dig1 % divs));
        dig1 /= divs;
        begin = ipow10(dig1 - 1);
        
    }
    else {  // If even just finding where to start from
        dig1 /= divs;
        begin = beginAt(dig1, n1, divs);
    }
    std::cout << "Begin: "<< dig1 << " " << begin << std::endl;
    if (dig2 % divs) {  //Promoting end to previous space with even digits.
        dig2 -= (dig2 % divs);
        dig2 /= divs;
        end = ipow10(dig2) - 1;
    }
    else {   // If even, just finding where to end
        dig2 /= divs;
        end = endAt(dig2, n2, divs);
    }
    std::cout << dig2 << " " << end << std::endl;
    if (dig1 > dig2) return 0; // if digit1 is promoted above digit2 or digit2 below dig1, the space was invalid to begin with. No answer
    if (dig1 == dig2) findSum(begin, end, dig1, divs); //If both in same digit range, can be checked at once together
    else {
        int ind = dig1 + 1;
        while (ind < dig2) {
            ll curr_begin = ipow10(ind);
            ll curr_end = ipow10(ind + 1) - 1;
            findSum(curr_begin, curr_end, ind, divs);
            ind++;
        }
        ll first_part_space = ipow10(dig1) - 1;
        findSum(begin, first_part_space, dig1, divs);
        ll second_part_space = ipow10(dig2);
        findSum(second_part_space, end, dig2, divs);
    }
    return 1;
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
        std::cout << "For numbers: " << nums[0] << " " << nums[1] << ": " << std::endl;
        int divs{ 2 };
        ll ans{};
        st.clear();
        while (true) {
            std::cout << "For divs: " << divs << std::endl;
            int res = findInvalid(nums, divs);
            std::cout << " Res: " << res << std::endl;
            if (res == -1) break;
            divs++;
        }
        for (auto& el : st) ans += el;
        std::cout << ans << std::endl;
        total += ans;
        //return 0;
    }
    std::cout << "Total: " << total << std::endl;
    return 0;
}