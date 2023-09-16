// uses a vector to store parts of the numbers, in a little-endian style
#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>
using namespace std;

#define MODDER 1000000000
#define DIGITSIZE 9

class BigInteger
{
    vector<int> digit;
    short signum;
    int setSignumInt(long long &);
    char* trim(char *);
    BigInteger add(BigInteger &);
    BigInteger subtract(BigInteger &);
    BigInteger multiply(int &);
    BigInteger multiply(BigInteger &);
    BigInteger getLower(int) const;
    BigInteger getUpper(int) const;
    void checkLength();
    static char *ZERO;
    static char *ONE;
public:
    BigInteger() { signum = 0; }
    BigInteger(long long);
    BigInteger(char*);
    BigInteger(string &);
    BigInteger(const BigInteger &);
    BigInteger operator = (long long);
    BigInteger operator = (char *);
    BigInteger operator = (string &);
    BigInteger operator + (BigInteger &);
    BigInteger operator - (BigInteger &);
    BigInteger operator * (int);
    BigInteger operator * (BigInteger &);
    bool operator == (const BigInteger &) const;
    bool operator < (const BigInteger &) const;
    bool operator <= (const BigInteger &) const;
    int getSignum();
    string toString();
};

char* BigInteger::ZERO = "0";
char* BigInteger::ONE = "1";

inline int BigInteger::setSignumInt(long long &n)
{
    if (n == 0)
        signum = 0;
    else if (n > 0)
        signum = 1;
    else
    {
        signum = -1;
        n = -n;
    }
    return signum;
}

BigInteger BigInteger::add(BigInteger &b)
{
    BigInteger temp;
    int len1 = digit.size();
    int len2 = b.digit.size();
    int minLen = len1 < len2 ? len1 : len2;
    int i, digitSum = 0, carry = 0;
    for (i = 0; i < minLen; i++)
    {
        digitSum = carry + digit[i] + b.digit[i];
        temp.digit.push_back(digitSum % MODDER);
        carry = digitSum / MODDER;
    }
    if (len1 == len2 && carry)
        temp.digit.push_back(carry);
    else if (len1 > len2)
    {
        while (i < len1)
        {
            digitSum = carry + digit[i++];
            temp.digit.push_back(digitSum % MODDER);
            carry = digitSum / MODDER;
        }
        if (carry)
            temp.digit.push_back(carry);
    }
    else
    {
        while (i < len2)
        {
            digitSum = carry + b.digit[i++];
            temp.digit.push_back(digitSum % MODDER);
            carry = digitSum / MODDER;
        }
        if (carry)
            temp.digit.push_back(carry);
    }
    temp.signum = 1;
    return temp;
}

BigInteger BigInteger::subtract(BigInteger &b)
{
    BigInteger temp;
    temp.signum = 1;
    int size = b.digit.size();
    int borrow = 0, prevBorrow = 0, i;
    for (i = 0; i < size; i++)
    {
        borrow = (digit[i] - prevBorrow) < b.digit[i] ? 1 : 0;
        temp.digit.push_back((digit[i] - prevBorrow) + borrow*MODDER - b.digit[i]);
        prevBorrow = borrow ? 1 : 0;
    }
    int biggerSize = digit.size();
    if (size == biggerSize)
        return temp;
    while (prevBorrow)
    {
        if (digit[i] == 0)
            temp.digit.push_back(MODDER - 1);
        else
        {
            temp.digit.push_back(digit[i] - 1);
            prevBorrow = 0;
        }
        i++;
    }
    while (i < biggerSize)
    {
        temp.digit.push_back(digit[i]);
        i++;
    }
    temp.checkLength();
    return temp;
}

BigInteger BigInteger::multiply(int &n)
{
    int size = digit.size();
    if (size == 0)
        return ZERO;
    if (digit.size() == 1)
        return (BigInteger)((long long)digit[0] * n);

    BigInteger temp;
    int overflow = 0;
    long long digitProduct;
    for (int i = 0; i < size; i++)
    {
        temp.digit.push_back((digitProduct = ((long long)digit[i] * n) + overflow) % MODDER);
        overflow = digitProduct / MODDER;
    }
    if (overflow)
        temp.digit.push_back(overflow);
    temp.signum = 1;
    return temp;
}

BigInteger BigInteger::multiply(BigInteger &b)
{
    int size1 = digit.size();
    int size2 = b.digit.size();
    int half = size1 > size2 ? (size1 + 1) / 2 : (size2 + 1) / 2;

    BigInteger al = (*this).getLower(half);
    BigInteger ah = (*this).getUpper(half);
    BigInteger bl = b.getLower(half);
    BigInteger bh = b.getUpper(half);

    BigInteger p1 = ah * bh;
    BigInteger p2 = al * bl;
    BigInteger aDigitSum = ah.add(al);
    BigInteger bDigitSum = bh.add(bl);
    BigInteger p3 = aDigitSum * bDigitSum;
    BigInteger p1plusp2 = p1.add(p2);
    p3 = p3 - p1plusp2;

    int i;
    size1 = p1.digit.size();
    size2 = p3.digit.size();
    for (i = 1; i <= half; i++)
    {
        p1.digit.push_back(0);
        p1.digit.push_back(0);
        p3.digit.push_back(0);
    }
    for (i = size1 - 1; i >= 0; i--)
    {
        p1.digit[i + half * 2] = p1.digit[i];
        p1.digit[i] = 0;
    }
    for (i = size2 - 1; i >= 0; i--)
    {
        p3.digit[i + half] = p3.digit[i];
        p3.digit[i] = 0;
    }
    return p1.add(p2).add(p3);
}

char* BigInteger::trim(char *n)
{
    int len = strlen(n);
    int index = 0, i;
    char *nnew = new char[len];

    if (n[0] == '-' || n[0] == '+')
    {
        nnew[0] = n[0];
        index++;
    }
    for (i = index; n[i] == '0'; i++);
    if (i == len)
        return ZERO;
    if (i != index)
    {
        while (i != len)
            nnew[index++] = n[i++];
    }
    nnew[index] = 0;
    return nnew;
}

BigInteger BigInteger::getLower(int half) const
{
    int len = digit.size();
    if (len <= half)
        return *this;

    BigInteger lowerHalf;
    for (int i = 0; i < half; i++)
        lowerHalf.digit.push_back(digit[i]);
    lowerHalf.checkLength();
    return lowerHalf;
}

BigInteger BigInteger::getUpper(int half) const
{
    int len = digit.size();
    if (len <= half)
        return ZERO;
    BigInteger upperHalf;
    for (int i = half; i < len; i++)
        upperHalf.digit.push_back(digit[i]);
    upperHalf.checkLength();
    return upperHalf;
}

void BigInteger::checkLength()
{
    int size = digit.size();
    if (size)
    {
        while (digit[size - 1] == 0)
        {
            digit.pop_back();
            if ((size = digit.size()) == 0)
                break;
        }
        signum = size ? 1 : 0;
    }
}
// END OF PRIVATE FUNCTION-DEFINITIONS

// START OF PUBLIC FUNCTION-DEFINITIONS

BigInteger::BigInteger(long long n)
{
    int status = setSignumInt(n);
    while (n)
    {
        digit.push_back(n % MODDER);
        n /= MODDER;
    }
}

BigInteger::BigInteger(char *n)
{
    if (n[0] == '0' || ((n[0] == '+' || n[0] == '-') && n[1] == '0'))
        n = trim(n);

    int length, msb;
    char tempDigit[DIGITSIZE + 1];
    for (length = msb = 0; n[length] != 0; length++)
    {
        if (n[length] == '0')
            msb++;
    }
    if (msb == length)
    {
        signum = 0;
        return;
    }
    if (n[0] == '-')
    {
        signum = -1;
        length--;
        msb = 1;
    }
    else if (n[0] == '+')
    {
        signum = 1;
        length--;
        msb = 1;
    }
    else
    {
        signum = 1;
        msb = 0;
    }
    if (length <= DIGITSIZE)
    {
        memcpy(tempDigit, n + msb, length);
        tempDigit[length] = '\0';
        digit.push_back(stoi(tempDigit));
    }
    else
    {
        int k = length, chunkLen;
        while (k != 0)
        {
            k -= DIGITSIZE;
            chunkLen = k >= 0 ? DIGITSIZE : k + DIGITSIZE;
            k = k < 0 ? 0 : k;

            memcpy(tempDigit, n + msb + k, chunkLen);
            tempDigit[chunkLen] = '\0';
            digit.push_back(stoi(tempDigit));
        }
    }
}

BigInteger::BigInteger(string &n)
{
    char *num = new char[n.length() + 1];
    strcpy(num, n.c_str());
    (*this) = num;
}

BigInteger::BigInteger(const BigInteger &n)
{
    digit = n.digit;
    signum = n.signum;
}

BigInteger BigInteger::operator=(long long n)
{
    digit.clear();
    if (setSignumInt(n) == 0)
        return ZERO;
    while (n)
    {
        digit.push_back(n % MODDER);
        n /= MODDER;
    }
    return *this;
}

BigInteger BigInteger::operator=(char *n)
{
    BigInteger temp(n);
    (*this) = temp;
    return *this;
}

BigInteger BigInteger::operator=(string &n)
{
    BigInteger temp(n);
    (*this) = temp;
    return *this;
}

BigInteger BigInteger::operator+(BigInteger &b)
{
    if (b.signum == 0)
        return *this;
    if (signum == 0)
        return b;
    BigInteger temp;
    if (signum == b.signum)
    {
        temp = (*this).add(b);
        temp.signum = signum == 1 ? 1 : -1;
    }
    else
        temp = (*this) - b; // "operator-" manages the signs of the operands, hence (*this) - b, directly!
    return temp;
}

BigInteger BigInteger::operator-(BigInteger &b)
{
    if ((*this) == b)
        return ZERO;
    BigInteger temp;
    if (signum == 1 && b.signum == 1)
    {
        if (*this < b)
        {
            temp = b.subtract((*this));
            temp.signum = -1;
        }
        else
            temp = (*this).subtract(b);
    }
    else if (signum == -1 && b.signum == -1)
    {
        if (*this < b)
        {
            temp = (*this).subtract(b);
            temp.signum = -1;
        }
        else
            temp = b.subtract((*this));
    }
    else
    {
        temp = (*this).add(b);
        if (signum == -1)	// i.e. if (signum == -1 && b.signum == 1)
            temp.signum = -1;
    } 
    return temp;	// temp returns with signum = 1, hence does not require re-asignment of 1
}

BigInteger BigInteger::operator*(int num)
{
    if (signum == 0 || num == 0)
        return ZERO;

    int n = num > 0 ? num : -num;
    BigInteger temp = (*this).multiply(n);

    if ((signum == 1 && num < 0) || (signum == -1 && num > 0))
        temp.signum = -1;
    else
        temp.signum = 1;
    return temp;
}

BigInteger BigInteger::operator*(BigInteger &b)
{
    if (signum == 0 || b.signum == 0)
        return ZERO;

    BigInteger product;
    if (digit.size() == 1)
        product = b.multiply(digit[0]);
    else if (b.digit.size() == 1)
        product = (*this).multiply(b.digit[0]);
    else
        product = (*this).multiply(b);
    product.signum = signum == b.signum ? 1 : -1;
    product.checkLength();
    return product;
}

bool BigInteger::operator==(const BigInteger &b) const
{
    if (signum != b.signum)
        return false;
    if (signum == 0)
        return true;
    int size1 = digit.size();
    int size2 = b.digit.size();
    if (size1 == size2)
    {
        int i = 0;
        while (i < size1)
        {
            if (digit[i] == b.digit[i])
                i++;
            else
                return false;
        }
        if (i == size1)
            return true;
    }
    return false;
}

bool BigInteger::operator<(const BigInteger &b) const
{
    if (signum != b.signum)
        return signum < b.signum;
    int size1 = digit.size();
    int size2 = b.digit.size();
    switch (signum)
    {
    case 1:
        if (size1 == size2)
        {
            int i = size1 - 1;
            while (i >= 0)
            {
                if (digit[i] == b.digit[i])
                    i--;
                else
                    return digit[i] < b.digit[i];
            }
            if (i == size1)
                return false;
        }
        return size1 < size2;
    case -1:
        if (size1 == size2)
        {
            int i = size1 - 1;
            while (i >= 0)
            {
                if (digit[i] == b.digit[i])
                    i--;
                else
                    return digit[i] > b.digit[i];
            }
            if (i == size1)
                return false;
        }
        return size1 > size2;
    }
}

bool BigInteger::operator<=(const BigInteger &b) const
{
    if (*this < b || *this == b)
        return true;
    return false;
}

int BigInteger::getSignum()
{
    return signum;
}

string BigInteger::toString()
{
    if (signum == 0)
        return "0";

    int length = digit.size();
    string number, temp;
    int len;

    number = to_string(digit[length - 1]);

    for (int i = length - 2; i >= 0; i--)
    {
        temp = to_string(digit[i]);
        len = temp.length();
        if (len != DIGITSIZE)
            temp.insert(0, DIGITSIZE - len, '0');
        number += temp;
    }
    if (signum == -1)
        return "-" + number;
    return number;
}

int main()
{
    string n = "1233423423523582379238745982739845723984759283049580594683903679834981723847816324817984798179417917923412334234235235823792387459827398457239847592830495805946839036798349817238478163248179847981794179179234123342342352358237923874598273984572398475928304958059468390367983498172384781632481798479817941791792341233423423523582379238745982739845723984759283049580594683903612334234235235823792387459827398457239847592830495805946839036798349817238478163248179847981794179179234798349817238478163248179847981794179179234";
    BigInteger b(n);
    cout << b.toString();
    return 0;
}
