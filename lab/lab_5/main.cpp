#include <iostream>
#include <ctype.h>
#include <list>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "SeparateChaining.h"
#include "QuadraticProbing.h"
using namespace std;

int main( int argc, char *argv[] ) {
    string dicType = argv[1];
    string hashType = argv[2];
    string filename = argv[3];
    
    HashTable<string> smallChain;
    HashTable<string> largeChain;
    HashTable2<string> smallProbe;
    HashTable2<string> largeProbe;
    
    int collission = 0;
    list<int> l;
    list<int> l2;
    
    ifstream myfile("small.txt");
    string line;
    while(getline(myfile, line)) {
        smallChain.insert(line);
    }
    myfile.close();
    ifstream myfile2("small.txt");
    while(getline(myfile2, line)) {
        smallProbe.insert(line);
        collission = smallProbe.countC(line);
        l.push_back(collission);
    }
    myfile2.close();
    ifstream myfile3("large.txt");
    while(getline(myfile3, line)) {
        largeChain.insert(line);
    }
    myfile3.close();
    ifstream myfile4("large.txt");
    while(getline(myfile4, line)) {
        largeProbe.insert(line);
        collission = largeProbe.countC(line);
        l2.push_back(collission);
    }
    myfile4.close();
    
    string outputFilename = filename;
    string outputFilename2 = filename;
    string outputFilename3 = filename;
    if(filename.find('.') != string::npos) {
        int index = filename.find('.');
        outputFilename.erase(index, outputFilename.size() - 1);
        outputFilename2.erase(index, outputFilename2.size() - 1);
        outputFilename3.erase(index, outputFilename3.size() - 1);
    }
    
    outputFilename += ".out";
    outputFilename2 += ".stats";
    outputFilename3 += "2.txt";
    
    ifstream myfile5(filename.c_str());
    ofstream outfile(outputFilename.c_str());
    ofstream outfile2(outputFilename2.c_str());
    ofstream outfile3(outputFilename3.c_str());
    
    while(getline(myfile5, line)) {
        istringstream ss(line);
        char value;
        while (ss >> value) {
            if ((value >= 97 && value <= 122) || (value >= 65 && value <= 90)) {
                value = tolower(value);
            }
            else {
                value = ' ';
            }
            outfile3 << value;
            if (ss.peek() == ' ') {
                outfile3 << ' ';
            }
        }
        outfile3 << endl;
    }
    myfile5.close();
    
    ifstream myfile6(outputFilename3.c_str()); //outfile3 is the processed text file
    
    if (dicType == "-1") {
        if (hashType == "-chain") {
            while(getline(myfile6, line)) {
                istringstream ss(line);
                string value;
                while (ss >> value) {
                    if (smallChain.contains(value) == false) {
                        outfile << value << endl;
                    }
                }
            }
            vector<int> a(50, 0);
            a = smallChain.countLists(a);
            for (int i = 0; i < a.size(); i++) {
                if (a[i] != 0) {
                    outfile2 << i << "  " << a[i] << endl;
                }
            }
        }
        else if (hashType == "-probe") {
            while(getline(myfile6, line)) {
                istringstream ss(line);
                string value;
                while (ss >> value) {
                    if (smallProbe.contains(value) == false) {
                        outfile << value << endl;
                    }
                 }
            }
            l.sort();
            list<int>::iterator itr = l.begin();
            int biggest = l.back();
            vector<int> v;
            v.resize(biggest + 1);
            for (int i = 0; i < l.size(); i++) {
                v[*itr]++;
                itr++;
            }
            for (int i = 0; i < v.size(); i++) {
                outfile2 << i << "  " << v[i] << endl;
            }
        }
        else {
            cout << "Invalid Argument.";
        }
    }
    else if (dicType == "-2") {
        if (hashType == "-chain") {
            while(getline(myfile6, line)) {
                istringstream ss(line);
                string value;
                while (ss >> value) {
                    if (largeChain.contains(value) == false) {
                        outfile << value << endl;
                    }
                 }
            } 
            vector<int> a(50, 0);
            a = largeChain.countLists(a);
            for (int i = 0; i < a.size(); i++) {
                if (a[i] != 0) {
                    outfile2 << i << "  " << a[i] << endl;
                }
            }
        }
        else if (hashType == "-probe") {
            while(getline(myfile6, line)) {
                istringstream ss(line);
                string value;
                while (ss >> value) {
                    if (largeProbe.contains(value) == false) {
                        outfile << value << endl;
                    }
                 }
            } 
            l2.sort();
            list<int>::iterator itr = l2.begin();
            int biggest = l2.back();
            vector<int> v2;
            v2.resize(biggest + 1);
            for (int i = 0; i < l2.size(); i++) {
                v2[*itr]++;
                itr++;
            }
            for (int i = 0; i < v2.size(); i++) {
                outfile2 << i << "  " << v2[i] << endl;
            }
        }
        else {
            cout << "Invalid Argument.";
        }
    }
    else {
        cout << "Invalid Argument.";
    }
    
    myfile6.close();
    outfile.close();
    outfile2.close();
    outfile3.close();
    return 0;
}
