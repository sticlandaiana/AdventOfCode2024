//https://adventofcode.com/2024/day/4
//ANSWER PART 1: 2370
//ANSWER PART 2: 1908

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

void verifyContent(vector<vector<char>> christmases);
int countLineXMAS( vector<vector<char>> christmases, string word);
int countColumnXMAS(vector<vector<char>> christmases, string word);
int countDiagonalXMAS(vector<vector<char>> christmases, string word);
int counterX_MAS(vector<vector<char>> christmases, char a00, char a02, char a11, char a20, char a22);

int main() {
    ifstream fin1("input2.txt");
    int counter1{ 0 };
    int counter2{ 0 };

    if (!fin1.is_open()) {
        cerr << "Error opening file" << endl;
        return 1;
    }

    vector<vector<char>> christmases;
    string line{};

    while (getline(fin1, line)) {
        vector<char> vectorTemp(line.begin(), line.end());
        christmases.push_back(vectorTemp);
    }

    /*verifyContent(christmases);*/
    int nWordL = countLineXMAS(christmases, "XMAS");
    int nWordReversedL = countLineXMAS(christmases, "SAMX");
    int nWordC = countColumnXMAS(christmases, "XMAS");
    int nWordReversedC = countColumnXMAS(christmases, "SAMX");
    int nWordD = countDiagonalXMAS(christmases, "XMAS");
    int nWordReversedD = countDiagonalXMAS(christmases, "SAMX");

    cout << "Line: " << nWordL << endl;
    cout << "Reversed Line: " << nWordReversedL << endl;
    cout << "Column: " << nWordC << endl;
    cout << "Reversed Column: " << nWordReversedC << endl;
    cout << "Diagonal: " << nWordD << endl;
    cout << "Reversed Diagonal: " << nWordReversedD << endl;

    counter1 = nWordL + nWordReversedL + nWordReversedC + nWordC + nWordD + nWordReversedD;
    cout << "XMAS counter: " << counter1 << endl;

    int nX_MAS1 = counterX_MAS(christmases, 'M', 'S', 'A', 'M', 'S');
    int nX_MAS2 = counterX_MAS(christmases, 'M', 'M', 'A', 'S', 'S');
    int nX_MAS3 = counterX_MAS(christmases, 'S', 'S', 'A', 'M', 'M');
    int nX_Mas4 = counterX_MAS(christmases, 'S', 'M', 'A', 'S', 'M');
    counter2 = nX_MAS1 + nX_MAS2 + nX_MAS3 + nX_Mas4;
   
    cout << "X-Mas counter: " << counter2 << endl;
    return 0;
}

void verifyContent(vector<vector<char>> christmases) {
    cout << endl;
    for ( auto& row : christmases) {
        for (char c : row) {
            cout << c;
        }
        cout << endl;
    }
}

int countLineXMAS( vector<vector<char>> christmases,  string word) {
    int counter{ 0 };
    for (const auto& row : christmases) {
        //I want to build a string from the vector<char> in order to be able to use .substr()
        string copyS(row.begin(), row.end());
        for (size_t i{ 0 }; i <= row.size() - word.size(); i++) {
            if (copyS.substr(i, word.size()) == word) {
                counter++;
            }
        }
    }
    return counter;
}

int countColumnXMAS(vector<vector<char>> christmases, string word) {
    int counter{ 0 };
    size_t numCols = christmases[0].size();
    for (size_t j{ 0 }; j < numCols; j++) {
        string copyS{};
        for ( auto& row : christmases) {
            if (j < row.size()) {
                copyS += row[j];
            }
        }
        for (size_t i{ 0 }; i <= copyS.size() - word.size(); i++) {
            if (copyS.substr(i, word.size()) == word) {
                counter++;
            }
        }
    }
    return counter;
}

int countDiagonalXMAS(vector<vector<char>> christmases, string word) {
    int counter = 0;
    size_t numRows = christmases.size();
    size_t numCols = christmases[0].size();

    // Principal diagonal, the top
    for (size_t startRow = 0; startRow < numRows; startRow++) {
        string diagonalString;
        for (size_t i = 0, j = startRow; i < numCols && j < numRows; i++, j++) {
            diagonalString += christmases[j][i];
        }
        for (size_t i = 0; i + word.size() <= diagonalString.size(); i++) {
            if (diagonalString.substr(i, word.size()) == word) {
                counter++;
            }
        }
    }

    // Principal diagonal, the bottom
    for (size_t startCol = 1; startCol < numCols; startCol++) {
        string diagonalString;
        for (size_t i = startCol, j = 0; i < numCols && j < numRows; i++, j++) {
            diagonalString += christmases[j][i];
        }
        for (size_t i = 0; i + word.size() <= diagonalString.size(); i++) {
            if (diagonalString.substr(i, word.size()) == word) {
                counter++;
            }
        }
    }

    // Secondary diagonal, the top
    for (size_t startRow = 0; startRow < numRows; startRow++) {
        string diagonalString;
        for (size_t i = numCols - 1, j = startRow; j < numRows && i < numCols; i--, j++) {
            diagonalString += christmases[j][i];
        }
        for (size_t i = 0; i + word.size() <= diagonalString.size(); i++) {
            if (diagonalString.substr(i, word.size()) == word) {
                counter++;
            }
        }
    }

    // Secondary diagonal, the bottom
    for (int startCol = numCols - 2; startCol >= 0; startCol--) { //int when decreasing 
        string diagonalString;
        for (int i = startCol, j = 0; i >= 0 && j < numRows; i--, j++) {
            diagonalString += christmases[j][i];
        }
        for (size_t i = 0; i + word.size() <= diagonalString.size(); i++) {
            if (diagonalString.substr(i, word.size()) == word) {
                counter++;
            }
        }
    }

    return counter;
}

int counterX_MAS(vector<vector<char>> christmases, char a00, char a02, char a11, char a20, char a22) {
    int counter{ 0 };

    
    size_t numRows = christmases.size();
    size_t numCols = christmases[0].size();

    //we will check every 3x3 subvector
    for (size_t i = 0; i <= numRows - 3; i++) {
        for (size_t j = 0; j <= numCols - 3; j++) {
            
            if (christmases[i][j] == a00 &&     
                christmases[i][j + 2] == a02 && 
                christmases[i + 1][j + 1] == a11 && 
                christmases[i + 2][j] == a20 && 
                christmases[i + 2][j + 2] == a22) { 
                counter++;
            }
        }
    }

    return counter;
}
