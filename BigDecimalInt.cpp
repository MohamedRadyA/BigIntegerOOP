#include "BigDecimalInt.h"

BigDecimalInt::BigDecimalInt (): sign(1), bigInt("0") {}

BigDecimalInt::BigDecimalInt (string decStr) {
    regex ValidString ("^[-+]?[0-9]\\d*$");
    string new_input;
    bool isValid = regex_match(decStr,ValidString);
    if (!isValid){
        do {
            cout << "Invalid String\nenter a valid string :\n";
            cin >> new_input;
            isValid = regex_match(new_input,ValidString);
        }
        while(!isValid);
        decStr = new_input;
    }
    if(decStr[0] == '-'){
        sign = 0;
    }
    else sign = 1;
    if (decStr[0] == '-' || decStr[0] == '+')
        bigInt = decStr.substr(1, decStr.size());
    else bigInt = decStr;
}

BigDecimalInt::BigDecimalInt (int decInt) {
    bigInt = to_string(decInt);
}

BigDecimalInt BigDecimalInt::operator+ (BigDecimalInt anotherDec){
    BigDecimalInt left = *this, right = anotherDec, ret;
    if (left.sign != right.sign){
        if (left.sign){
            right.sign = 1;
            return left - right;
        }
        left.sign = 1;
        return right - left;
    }
    if (left.sign == 0) {
        ret.sign = 0;
        left.sign = 1;
        right.sign = 1;
    }

    string left_bigInt = left.bigInt, right_bigInt = right.bigInt;
    if (left_bigInt.size() > right_bigInt.size()){
        swap(left_bigInt,right_bigInt);
    }
    string result = "";
    int carry = 0;
    reverse(left_bigInt.begin(),left_bigInt.end());
    reverse(right_bigInt.begin(),right_bigInt.end());

    for (int i = 0; i < left_bigInt.size(); ++i) {
        int d1 = left_bigInt[i] - '0', d2 = right_bigInt[i] - '0';
        int sum = d1 + d2 + carry;
        int out = sum % 10;
        carry = sum / 10;
        result += (out + '0');
    }

    for (int i = left_bigInt.size(); i < right_bigInt.size(); ++i) {
        int sum = (right_bigInt[i] - '0') + carry;
        carry = sum / 10;
        result += ((sum % 10) + '0');
    }
    if (carry) result += ('1');

    reverse(result.begin(),result.end());

    ret.bigInt = result;
    return ret;
}

BigDecimalInt BigDecimalInt::operator- (const BigDecimalInt &anotherDec) const {
    BigDecimalInt left = *this, right = anotherDec;
    if(sign != anotherDec.sign){ // if(signs was not the same we can use + operator exp: ( (+x) - (-y) = x + y ), ( (-x) - (+y) = (-x) - y = -(x + y) )
        if(sign){
            right.sign = 1;
            return left + right;
        }
        right.sign = 0;
        return left + right;
    }
    BigDecimalInt ret;
    left.sign = 1;
    right.sign = 1;
    if(*this == anotherDec) return ret;
    ret.sign = this->sign;
    if(left < right) {
        BigDecimalInt temp;
        temp = left;
        left = right;
        right = temp;
        ret.sign = !ret.sign;
    }

    if(left.size() != right.size()) right.bigInt = string(left.size() - right.size(), '0') + right.bigInt; // make the two string the same size
    ret.bigInt = string(left.size(), '0');
    for(int i = left.bigInt.size() - 1; i >= 0; i--){
        if(left.bigInt[i] < right.bigInt[i]){
            left.bigInt[i - 1] -= 1;
            left.bigInt[i] += 10;
        }
        ret.bigInt[i] = ((left.bigInt[i] - '0') - (right.bigInt[i] - '0')) + '0';
    }

    // removing the zeros in the left of the number
    string temp = "";
    bool foundDigit = 0;
    for(int i = 0; i < ret.bigInt.size(); i++){
        if(ret.bigInt[i] != '0') foundDigit = 1;
        if(foundDigit) temp += ret.bigInt[i];
    }
    ret.bigInt = temp;

    return ret;
}

bool BigDecimalInt::operator< (const BigDecimalInt &anotherDec) const {
    if(sign != anotherDec.sign){
        return sign < anotherDec.sign;
    }
    if(bigInt.size() != anotherDec.bigInt.size()){
        if(sign) return bigInt.size() < anotherDec.bigInt.size();
        else return anotherDec.bigInt.size() < bigInt.size();
    }
    for(int i = 0; i < bigInt.size(); i++){
        if(bigInt[i] != anotherDec.bigInt[i]){
            return bigInt[i] < anotherDec.bigInt[i];
        }
    }
}

bool BigDecimalInt::operator> (const BigDecimalInt &anotherDec) const {
    return !(anotherDec < *this || anotherDec==*this);
}

bool BigDecimalInt::operator==(const BigDecimalInt &anotherDec) const{
    return getBigInt() == anotherDec.getBigInt();
}

BigDecimalInt BigDecimalInt::operator= (BigDecimalInt anotherDec) {
    sign=anotherDec.getSign();
    bigInt = anotherDec.getBigInt();
    return *this;
}

int BigDecimalInt::size() const {
    return getBigInt().size();
}

//0 negative, 1 positive
int BigDecimalInt::getSign() const {
    return sign;
}

string BigDecimalInt::getBigInt() const {
    return bigInt;
}

ostream& operator << (ostream& out, BigDecimalInt b) {
    if(!b.getSign())
        out << '-';
    out << b.getBigInt();
    return out;
}
