//
//  main.cpp
//  cs014_lab1
//
//  Created by John Stuart on 9/29/15.
//  Copyright (c) 2015 John Stuart. All rights reserved.
//

#include <iostream>
#include <vector>

using namespace std;

vector<int> fibmod(int, int, int);
vector<int> findbase(vector<int> &);
void findFreq(vector<int> &, int);
bool findPairs(vector<int> &, int, vector<vector<int>> &);
void printVect(vector<int> &);
void printFreq(vector<vector<int>> &, int);
void printMatrix(vector<vector<int>> &, int);

int main(int argc, const char * argv[]) {
    //lab 1 fibmod
    //vector 1 will strore series
    //vector 2 (size of mod) will store frequency
    
    int firstEl, secondEl, newEl1, newEl2, modulus;
    vector<int> longVect;
    vector<int> baseVect;
    bool allPairsFound = false;
    char choice;
    
    cout << "Insert element 1: ";
    cin >> firstEl;
    cout << "Insert element 2: ";
    cin >> secondEl;
    cout << "Insert modulus: ";
    cin >> modulus;
    longVect = fibmod(firstEl, secondEl, modulus);
    baseVect = findbase(longVect);
    vector<vector<int>> markMatrix(modulus, vector<int> {0, 0, 0, 0});
    
    printVect(baseVect);
    
    findFreq(baseVect, modulus);
    
    cout << "Continue to find all pairs? (\"y\" or \"n\")";
    cin >> choice;
    if (choice == 'y') {
        allPairsFound = findPairs(baseVect, modulus, markMatrix);
        while (allPairsFound == false) {
            longVect.clear();
            baseVect.clear();
            cout << "Insert new element 1: ";
            cin >> newEl1;
            cout << "Insert new element 2: ";
            cin >> newEl2;
            longVect = fibmod(newEl1, newEl2, modulus);
            baseVect = findbase(longVect);
            allPairsFound = findPairs(baseVect, modulus, markMatrix);
        }
        cout << "ALL BASE PAIRS FOUND";
    }
    else if (choice == 'n') {
        cout << "bye";
    }
    else {
        cout << "error";
    }
    
    return 0;
}

vector<int> fibmod(int el1, int el2, int mod) {
    vector<int> series;
    series.push_back(el1);
    series.push_back(el2);
    int modulus = mod;
    int nextEl;
    for (int i = 2; i < 10000; i++) {
        nextEl = (series[i - 1] + series[i - 2]) % modulus;
        series.push_back(nextEl);
    }
    //modify series in case the one or both first elements are larger than modulus
    if (series[1] > mod) {
        series.erase(series.begin());
        series.erase(series.begin());
    }
    else if (series[0] > mod && series[1] <= mod) {
        series.erase(series.begin());
    }
    cout << endl;
    return series;
}
vector<int> findbase(vector<int> &startVect) {
    //tempVect will be compared to compVect
    //once correct tempVect has been found then foundBase turns true exiting function
    vector<int> tempBase;
    vector<int> compBase;
    bool foundBase = false;
    
    //try to visualize: tempBase is being copied element by element until it reaches a repeating element
    //skips first 2 elements because starting off with 2 same elements causes issues
    //once a repeating element will be found then possible base pattern has been found
    //sent then to compare tempVect with next set of elements of startVect (same number of elements as tempVect)
    //falseBase and skips keep track of how many elements that are the same as the 0th element and should be skipped over
    int skips = 0;
    int falseBase = 0;
    for (int i = 0; i < startVect.size(); i++) {
        tempBase.push_back(startVect[i]);
        if (tempBase[0] == startVect[i + 1] && i != 0) {
            if (skips != 0) {
                skips--;
            }
            else if (skips == 0) {
                for (int j = i + 1; j <= i + tempBase.size(); j++) {
                    compBase.push_back(startVect[j]);
                }
                //compare tempBase w/ compBase
                if (tempBase == compBase) {
                    foundBase = true;
                    break;
                }
                else {
                    falseBase++;
                    skips = falseBase;
                    tempBase.clear();
                    compBase.clear();
                    i = -1;
                }
            }
            
        }
        
    }

    return tempBase;
}

void findFreq(vector<int> &base, int m) {
    vector<vector<int>> matrix (m, vector<int> {0,0});
    
    for (int h = 1; h < m; h++) {
        matrix[h][0] = h;
    }

    for (int i = 0; i < base.size(); i++) {
        matrix[base[i]][1]++;
    }
    
    /*for (vector<int>::iterator its = base.begin(); its != base.end(); its++) {
        matrix[*its][1]++;
    }*/
    
    cout << "Number | Frequency" << endl;
    printFreq(matrix, 2);
}

bool findPairs(vector<int> &baseVect, int m, vector<vector<int>> &markMatrix) {
    
    bool solved = false;
    
    baseVect.push_back(baseVect[0]);
    
    for (int i = 0; i < baseVect.size(); i++) {
        markMatrix[baseVect[i]][baseVect[i + 1]] = 1;
    }
    
    /*for (vector<int>::iterator it = baseVect.begin(); it != baseVect.end(); it++) {
        markMatrix[*it][*(it + 1)] = 1;
    }*/
    
    bool leaveLoop = false;
    for (int i = 0; i < markMatrix.size(); i++) {
        for (int j = 0; j < m; j++) {
            if (markMatrix[i][j] == 0) {
                leaveLoop = true;
            }
        }
        if (leaveLoop == false) {
            solved = true;
        }
    }
    printMatrix(markMatrix, m);
    return solved;
}

void printVect (vector<int> &vector) {
    cout << "Base Pattern is: ";
    for (int x : vector) {
        cout << x << " ";
    }
    cout << endl << endl;
}

void printFreq (vector<vector<int>> &matrix, int m) {
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < m; j++) {
        cout << "   " << matrix[i][j] << "   ";
        }
        cout << endl;
    }
        cout << endl;
}

void printMatrix (vector<vector<int>> &matrix, int m) {
    cout << endl;
    for (int i = 0; i < m; i ++) {
        cout << "   " << i;
    }

    cout << endl;
    cout << "-----------------------" << endl;
    for (int i = 0; i < matrix.size(); i++) {
        cout << i << "| ";
        for (int j = 0; j < m; j++) {
            if (matrix[i][j] == 0) {
                cout << 'o' << "   ";
            }
            else if (matrix[i][j] == 1) {
                cout << 'x' << "   ";
            }
            else {
                cout << "error";
            }
        }
        cout << endl;
    }
    cout << endl;
}










