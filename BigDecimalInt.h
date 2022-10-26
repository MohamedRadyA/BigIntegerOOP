#ifndef OOP_ASSIGNMENT_1_BIGDECIMALINT_H
#define OOP_ASSIGNMENT_1_BIGDECIMALINT_H

#include <bits/stdc++.h>
using namespace std;

class BigDecimalInt {
    private:
        int sign;
        string bigInt;
    public:
        BigDecimalInt();
        BigDecimalInt (string decStr); // Initializes from string & rejects bad input
        BigDecimalInt (int decInt); // Initialize from integer
        BigDecimalInt operator+ (BigDecimalInt anotherDec); // member fn
        BigDecimalInt operator- (const BigDecimalInt &anotherDec) const; // member fn
        bool operator< (const BigDecimalInt &anotherDec) const; // member fn
        bool operator> (const BigDecimalInt &anotherDec) const; // member fn
        bool operator==(const BigDecimalInt &anotherDec) const; // member fn
        BigDecimalInt operator= (BigDecimalInt anotherDec); // member fn
        int size() const; // member fn
        int getSign() const; // member fn
        string getBigInt() const;
        friend ostream& operator << (ostream& out, BigDecimalInt b);
};


#endif
