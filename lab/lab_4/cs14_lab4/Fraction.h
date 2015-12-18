//
//  Fraction.h
//  cs14_lab4
//
//  Created by John Stuart on 10/27/15.
//  Copyright © 2015 john. All rights reserved.
//

#ifndef Fraction_h
#define Fraction_h

#include <stdio.h>
#include <iostream>
using namespace std;
class Fraction
{
    int gcd(int a, int b) {return b==0 ? a : gcd(b,a%b); }
    int n, d;
public:
    Fraction(int n, int d = 1);
    int num();
    int den();
    Fraction& operator*=(const Fraction &);
};

ostream& operator<<(ostream &, const Fraction &);
bool operator==(const Fraction &, const Fraction &);
bool operator<(const Fraction &, const Fraction &);
bool operator>(const Fraction &, const Fraction &);
Fraction operator*(Fraction, const Fraction &);

#endif /* Fraction_h */
