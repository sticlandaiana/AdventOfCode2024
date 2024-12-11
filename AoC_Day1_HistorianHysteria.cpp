
//https://adventofcode.com/2024/day/1
//Answer PART 1: 2066446
//Answer PART2: 24931009
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ifstream fin("input.txt");  
    vector<int> list1;
    vector<int> list2;

    int elementL1, elementL2;
    while (fin >> elementL1 >> elementL2) {
        list1.push_back(elementL1);
        list2.push_back(elementL2);
    }

    sort(list1.begin(), list1.end());
    sort(list2.begin(), list2.end());

    
    int totalDistance{ 0 };
    
    int minElementL1{ 0 }, minElementL2{ 0 };

    while (!list1.empty() && !list2.empty()) {
        minElementL1 = list1.front();
        minElementL2 = list2.front();

        if (minElementL1 > minElementL2) {
            totalDistance += (minElementL1 - minElementL2);
        }
        else {
            totalDistance += (minElementL2 - minElementL1);
        }

        list1.erase(list1.begin());
        list2.erase(list2.begin());
    }

    cout << "Total distance: " << totalDistance << endl;


    //~~~~~~~~~~~~~~~PART TWO~~~~~~~~~~~~~~~~~~~~~~~~~
    ifstream fin2("input2.txt");

    while (fin2 >> elementL1 >> elementL2) {
        list1.push_back(elementL1);
        list2.push_back(elementL2);
    }

    int similarityScore{0};
    int searchedElement{};
    int same{};

    for (auto element : list1) {
        searchedElement = element;
        same = 0;
        for (auto element2 : list2) {
            if (searchedElement == element2) {
                same++;
            }
        }
        similarityScore += element * same;
    }

    cout << "Similarity score: " << similarityScore << endl;

    return 0;
}






