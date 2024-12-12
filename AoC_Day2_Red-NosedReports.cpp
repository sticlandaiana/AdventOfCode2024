//https://adventofcode.com/2024/day/2
//PART ONE: 564
//PART TWO: 604

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm> // for is_sorted
using namespace std;

//check if a vector is increasing or decreasing
bool is_sorted_or_reversed(const vector<int>& v);

//verify if the report is safe
bool verify(const vector<int>& v);

int main() {
    vector<string> reports;
    vector<int> numbersValue;
    ifstream file("input1.txt");
    string line{};

    if (file.is_open()) {
        while (getline(file, line)) {
            reports.push_back(line);
        }
        file.close();
    }
    else {
        cout << "ERROR" << endl;
        return 1;
    }

    int part1{ 0 }, part2{ 0 };

    for ( auto report : reports) {
        numbersValue.clear();
        string tempNumber;
        for (char c : report) {
            if (c != ' ') {
                tempNumber += c;
            }
            else {
                if (!tempNumber.empty()) {
                    numbersValue.push_back(stoi(tempNumber));
                    tempNumber = "";
                }
            }
        }
        if (!tempNumber.empty()) {
            numbersValue.push_back(stoi(tempNumber));
        }

        //count how many safe reports are
        if (verify(numbersValue)) {
            part1++;
        }

        //we create a temporary copy of the vector and delete every element
        //and then we check if the report is safe without that specific element
        bool ok = false;
        for (size_t j = 0; j < numbersValue.size(); j++) {
            vector<int> temp = numbersValue;
            temp.erase(temp.begin() + j);  // delete current element

            //if by deleting one element, our report is suddenly safe, ok is true
            if (verify(temp)) {
                ok = true;
                break;
            }
        }

        if (ok) {
            part2++;
        }
    }

    cout << "Part 1: " << part1 << endl;
    cout << "Part 2: " << part2 << endl;
    return 0;
}
//check if a vector is increasing or decreasing
bool is_sorted_or_reversed(const vector<int>& v) {
    if (is_sorted(v.begin(), v.end()))
        return true;

    if (is_sorted(v.rbegin(), v.rend()))
        return true;

    return false;
}

//verify if the report is safe
bool verify(const vector<int>& v) {
    bool sorted = is_sorted_or_reversed(v);
    bool ok = true;

    // verify the difference beetween two consecutive numbers
    for (size_t i = 0; i < v.size() - 1; i++) {
        int diff = abs(v[i] - v[i + 1]);
        if (diff < 1 || diff > 3) {
            ok = false;
            break;
        }
    }

    return sorted && ok;
}
//#include <iostream>
//#include <vector>
//#include <fstream>
//#include <string>
//#include <algorithm> //for the is_sorted function
//using namespace std;
//bool is_sorted_or_reversed(vector<int> v);
//
//int main() {
//    vector<string> reports;
//    vector<int> numbersValue;
//    ifstream file("input2.txt");
//    string line{};
//
//    if (file.is_open()) {
//        while (getline(file, line)) {
//            reports.push_back(line);
//        }
//        file.close();
//    }
//    else {
//        cerr << "ERROR" << endl;
//        return 1;
//    }
//
//    string tempNumber{};
//    int effectiveNumber{};
//    bool sorted{};
//    bool safe{};
//    int safeReports{ 0 };
//    int numbersDeleted = 0;
//
//    for (auto& report : reports) {
//        tempNumber = "";
//        numbersValue.clear();  
//
//        for (char& c : report) {
//            if (c != ' ') {
//                tempNumber += c;
//            }
//            else {
//                if (!tempNumber.empty()) {
//                    effectiveNumber = stoi(tempNumber);
//                    numbersValue.push_back(effectiveNumber);
//                    tempNumber = "";
//                }
//            }
//        }
//
//        
//        if (!tempNumber.empty()) {
//            effectiveNumber = stoi(tempNumber);
//            numbersValue.push_back(effectiveNumber);
//        }
//
//        if (numbersValue.size() < 2) {
//            continue;  
//        }
//
//        sorted = is_sorted_or_reversed(numbersValue);
//
//        safe = true;
//        numbersDeleted = 0;
//        /*for (size_t i{ 0 }; i < numbersValue.size() - 1; i++) {
//            int difference = numbersValue[i+1] - numbersValue[i];
//            if ((shouldIncrease && difference < 0) || (!shouldIncrease && difference > 0) ||
//                abs(difference) != 1 && abs(difference) != 2 && abs(difference) != 3) {
//                safe = false;
//                numbersDeleted++;
//                
//                break;
//            }
//        }*/
//        size_t i = 0;
//        while (i < numbersValue.size() - 1) {
//            int difference = numbersValue[i + 1] - numbersValue[i];
//            if (abs(difference) != 1 && abs(difference) != 2 && abs(difference) != 3) {
//                safe = false;
//                numbersValue.erase(numbersValue.begin() + i);
//                numbersDeleted++;
//                
//                i--;
//            }
//            else {
//                i++;
//            }
//        }
//        cout << "NumberDeletes" << numbersDeleted << endl;
//        if ((safe&&sorted)||numbersDeleted==1) {
//            safeReports++;
//        }
//    }
//
//    cout << "Number of safe reports: " << safeReports << endl;
//    return 0;
//}
//
//bool is_sorted_or_reversed(vector<int> v) {
//    if (is_sorted(v.begin(), v.end())) {
//        return true;
//    }
//
//    if (is_sorted(v.rbegin(), v.rend())) {
//        return true;
//    }
//
//    return false;
//
//}