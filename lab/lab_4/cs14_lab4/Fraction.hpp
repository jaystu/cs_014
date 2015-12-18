//
//  Fraction.hpp
//  cs14_lab4
//
//  Created by John Stuart on 11/9/15.
//  Copyright © 2015 john. All rights reserved.
//

#ifndef Fraction_h
#define Fraction_h

#include <iostream>
#include <list>

using namespace std;

class Fraction {
    int gcd(int a, int b) {return b==0 ? a : gcd(b,a%b); }
    int n, d;
public:
    Fraction(int n, int d) : n(n/gcd(n,d)), d(d/gcd(n,d)) {}
    int num() const { return n; }
    int den() const { return d; }
    Fraction& operator*=(const Fraction& rhs);
};
std::ostream& operator<<(std::ostream& , const Fraction& );
bool operator==(const Fraction& , const Fraction& );
bool operator<(const Fraction&, const Fraction& );
bool operator>(const Fraction& , const Fraction& );
Fraction operator*(Fraction, const Fraction&);

#endif /* Fraction_hpp */
