//
//  main.cpp
//  test
//
//  Created by John Stuart on 10/9/15.
//  Copyright © 2015 John Stuart. All rights reserved.
//

#include <iostream>
#include <vector>
#include <cmath>
#include "Whopper.h"
using namespace std;
    
int main(int argc, const char * argv[]) {
    
    bool validInput = true;
    
    while (validInput == true) {
        int num1;
        int num2;
        char symbol;
        cout << "Input command: ";
        cin >> num1 >> symbol >> num2;
        if (cin.fail()) {
            validInput = false;
        }
        else {
            whopper foo(num1);
            whopper bar(num2);
            whopper result;
            bool isGreater;
            cout << "result: ";

            if (symbol == '+') {
                result = foo + bar;
                result.print();
            }
            else if (symbol == '-') {
                result = foo - bar;
                result.print();
            }
            else if (symbol == '>') {
                isGreater = foo > bar;
            }
            else if (symbol == '*') {
                result = foo * bar;
                result.print();
            }
        }
    }
    
    return 0;
    
}