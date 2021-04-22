#include <algorithm>
#include <iostream>
#include <cmath>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include <set>
#include <exception>
using namespace std;

int NOD(int a, int b) {
    a = abs(a);
    b = abs(b);
    while (a != 0 && b != 0)
    {
        if (a > b)
            a = a % b;
        else
            b = b % a;
    }
    return a + b;
}


class Rational
{
private:
    int numerator;
    int denominator;

public:
    Rational();
    Rational(int num, int den);
    Rational(pair<int, int>pair);
    ~Rational();

    int Numerator() const { return numerator; }
    int Denominator() const { return denominator; }

    void Reverse() {
        int tmp = denominator;
        denominator = numerator;
        numerator = tmp;
    }

    void Check() {
        if (denominator == 0) {
            invalid_argument a("division by zero");
            throw (a);
        }
        int n = NOD(numerator, denominator);
        if ((numerator < 0 && denominator < 0) || (numerator > 0 && denominator < 0)) {
            numerator *= -1;
            denominator *= -1;
        }
        numerator /= n;
        denominator /= n;
        if (numerator == 0)
            denominator = 1;
    }

    const Rational operator*(Rational& r) const {
        int a = this->denominator * r.denominator;
        int b = this->numerator * r.numerator;
        Rational c(b, a);
        return c;
    }
    /*const Rational operator/(Rational& r) const {
        r.Reverse();
        int a = this->denominator * r.denominator;
        int b = this->numerator * r.numerator;
        Rational c(b, a);
        return c;
    }*/
    friend Rational operator/(Rational l, Rational r) {
        r.Reverse();
        if (r.denominator == 0) {
            domain_error b("divident is 0");
            throw(b);
        }
        else {
            int a = l.denominator * r.denominator;
            int b = l.numerator * r.numerator;
            Rational c(b, a);
            return c;
        }
    }
    const Rational operator+(Rational r) const {
        int a = (this->numerator * r.denominator)
            + (r.numerator * this->denominator);
        int b = this->denominator * r.denominator;
        Rational c(a, b);
        return c;
    }
    const Rational operator-(Rational r) const {
        int a = (this->numerator * r.denominator)
            - (r.numerator * this->denominator);
        int b = this->denominator * r.denominator;
        Rational c(a, b);
        return c;
    }
    const bool operator==(Rational r) const {
        if ((this->denominator == r.denominator) && (this->numerator == r.numerator))
            return true;
        else return false;
    }
    friend std::ostream& operator<<(ostream& out, const Rational& r) {
        out << r.numerator << '/' << r.denominator;
        return out;
    }
    friend istream& operator>> (istream& in, Rational& r) {
        char c;
        in >> r.numerator;
        in >> c;
        in >> r.denominator;
        r.Check();
        return in;
    }
    const bool operator<(Rational r) const {
        int a = (this->numerator * r.denominator);
        int b = (r.numerator * this->denominator);
        return (a < b);
    }
};

Rational::Rational()
{
    numerator = 0;
    denominator = 1;
}

Rational::Rational(int num, int den)
{
    if (den == 0) {
        invalid_argument a("division by zero");
        throw (a);
    }
    else {
        int n = NOD(num, den);
        if ((num < 0 && den < 0) || (num > 0 && den < 0)) {
            num *= -1;
            den *= -1;
        }
        numerator = num / n;
        denominator = den / n;
        if (num == 0)
            denominator = 1;
    }

}

Rational::Rational(pair<int, int> pair)
{

    int n = NOD(pair.first, pair.second);
    if ((pair.first < 0 && pair.second < 0) || (pair.first > 0 && pair.second < 0)) {
        pair.first *= -1;
        pair.second *= -1;
    }
    numerator = pair.first / n;
    denominator = pair.second / n;
    if (pair.first == 0)
        denominator = 1;

}

Rational::~Rational()
{
}

int main() {
    try {
        Rational a;
        Rational b;
        char op;
        cin >> a >> op >> b;
        if (op == '+')
            cout << a + b;
        if (op == '-')
            cout << a - b;
        if (op == '*')
            cout << a * b;
        if (op == '/')
            cout << a / b;
    }
    catch (domain_error&) {
        cout << "Division by zero";
    }
    catch (invalid_argument&) {
        cout << "Invalid argument";
    }
    //cout << "OK" << endl;
    return 0;
}
