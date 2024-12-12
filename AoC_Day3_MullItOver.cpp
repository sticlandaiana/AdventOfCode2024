//https://adventofcode.com/2024/day/3
//ANSWER PART 1: 181345830
//ANSWER PART 2: 98729041
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    ifstream fin("input2.txt");

    if (!fin.is_open()) {
        cerr << "Eroare" << endl;
        return 1;
    }

    long long result1{ 0 }; //result for part 1
    long long result2{ 0 }; //result for part 2
    char c{};        //the character we read from the file
    string s{ "mul(" }; // the string we should identify
    string numbers{ "1234567890" }; //numeric characters
    int i{ 0 };
    string a{}, b{};  // identified numbers in the form of strings
    bool commaFound{ false }; // mark comma as found

    string enable{ "do()" }, disable{ "don't()" };
    bool enabled{ true }; //we enable the multiplications by default
    string temporary{};

    while (fin.get(c)) {

        temporary += c; //concatenate the current character to the buffer

        //if the length of the temporary is at least equal to the enable string
        //we will search for the substring equal to enable
        if (temporary.size() >= enable.size() && temporary.substr(temporary.size() - enable.size()) == enable) {
            enabled = true;
            temporary.clear();
            continue;
        }
        if (temporary.size() >= disable.size() && temporary.substr(temporary.size() - disable.size()) == disable) {
            enabled = false;
            temporary.clear();
            continue;
        }

        //identifying "mul("
        if (i < 4) {
            if (c == s[i]) {
                i++;
            }
            else {
                i = 0;
            }


            continue;
        }
        
 

        //find numeric values, the ',' and the final ')'
        if (numbers.find(c) != string::npos) {
            if (!commaFound) {
                a += c;
            }
            else {
                b += c;
            }
        }
        else if (c == ',') { //if we find a comma
            if (!commaFound && !a.empty()) { //if we don't have a comma and a is not empty, we set comma as found
                commaFound = true;
            }
            else { //the comma is placed incorrectly
                i = 0;
                a.clear();
                b.clear();
                commaFound = false;
            }
        }
        else if (c == ')') { //if we find round bracket 
            if (!a.empty() && !b.empty() && commaFound) { //if we have our numbers a and b and the commaFound, we compute the sum
                
                std::cout << "Found pair: " << a << ", " << b << endl; // debug output
                result1 += stoll(a) * stoll(b);
                if (enabled) {
                    result2 += stoll(a) * stoll(b);
                }
                
            }
            //reset our variables for the next product
            i = 0;
            a.clear();
            b.clear();
            commaFound = false;
        }
        else {
            //if we identify an invalid character, we reset all
            i = 0;
            a.clear();
            b.clear();
            commaFound = false;
        }
    }

    std::cout << "The result is: " << result1 << endl;
    std::cout << "The restricted result is: " << result2 << endl;
    return 0;
}

//if (j < 7) {
//    if (j < 2) {
//        if (c == enable[j]) {
//            j++;
//        }
//        else {
//            j = 0;
//        }
//    }
//    else
//        if (j < 4) {
//            if (c == enable[j]) {
//                j++;
//            }
//
//            if (j == 4) {
//                enable = true;
//            }
//
//            if (c == disable[j]) {
//                j++;
//            }
//            else {
//                j = 0;
//            }
//
//        }
//        else {
//            if (j < 7) {
//                if (disable[i] == j) {
//                    j++;
//                }
//                else {
//                    j = 0;
//                }
//            }
//            if (j == 7) {
//                enabled = false;
//            }
//        }
//    continue;
//}