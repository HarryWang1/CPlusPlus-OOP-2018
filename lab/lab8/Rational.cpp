#include "Rational.h"
#include <iostream>
using namespace std;

namespace CS2124 {
    Rational::Rational () {
        this->numer = 0;
        this->denom = 0;
    }
    Rational::Rational (int num) {
        this->numer = num;
        this->denom = 1;
    }
    Rational::Rational (int numer, int denom) {
        this->numer = numer;
        this->denom = denom;
        normalize();
    }
    
    //convert to lowest terms and only top numerator should be negative.
    void Rational::normalize() {
        //1. reduce to lowest terms
        int common_factor = gcd(numer, denom);
        numer /= common_factor;
        denom /= common_factor; 
        //2. simplify negatives
        if (numer < 0 && denom < 0) {
            numer *= -1;
            denom *= -1;
        } else if (numer > 0 && denom < 0) {
            numer *= -1;
            denom *= -1;
        }
    }

    //+= operator.
    Rational& Rational::operator+= (const Rational& rhs) {
        add_two_rational(*this, rhs);
        this->normalize();
        return *this;
    }

    void Rational::add_two_rational(Rational& lhs, const Rational& rhs) {
        int common_factor = gcd(lhs.denom, rhs.denom);
        int lcm = (lhs.denom * rhs.denom)/common_factor;
        lhs.numer = lhs.numer*(lcm/lhs.denom) + rhs.numer*(lcm/rhs.denom);
        lhs.denom = lcm;
    }

    //prefix ++ operator
    Rational& Rational::operator++() {
        Rational rhs = Rational(1);
        add_two_rational(*this, rhs);
        this->normalize();
        return *this;
    }

    ///postfix ++ operator. Don't return local objects by reference.
    Rational Rational::operator++ (int) {
        Rational lhs = *this;
        operator++();
        return lhs;
    }

    //convert object to bool. Explicit solves errors and makes it so only use when just a number by itself. No ambiguity when number and rational object.
    Rational::operator bool() const {
        return !(this->numer == 0);
    }

    // ##############################################################3

    //output operator
    ostream& operator<< (ostream& os, const Rational& num) {
        os << num.numer << '/' << num.denom << endl;
    }

    //input operator
    istream& operator>> (istream& is, Rational& num) {
        char slash;
        is >> num.numer >> slash >> num.denom;
        num.normalize();
        return is;
    }

    // + operator that calls += operator. Not a friend. Don't return references to local objects.
    Rational operator+ (const Rational& lhs, const Rational& rhs) {
        Rational sum = lhs;
        sum += rhs;
        return sum;
    } 

    //equality operator
    bool operator== (const Rational& lhs, const Rational& rhs) {
        return (lhs.numer == rhs.numer && lhs.denom == rhs.denom);
    }

    //inequality operator. Not a friend
    bool operator!= (const Rational& lhs, const Rational& rhs) {
        return !(lhs==rhs);
    }

    //the below two function calls are operator--(object). Not part of the class definition so the object is passed in as a parameter, whereas in the class's definition you use (this).
    //prefix --operator. Not a friend
    Rational& operator-- (Rational& lhs) {
        Rational rhs = Rational(-1);
        lhs.operator+=(rhs);    //able to call the class Rational's functions
        return lhs;
    }

    //postfix --operator. Not a friend. Don't return local objects by reference.
    Rational operator-- (Rational& lhs, int) {
        Rational copy = lhs;
        operator--(lhs);
        return copy;
    }

    int gcd(int numer, int denom) {
        int common_factor = 1;
        int top = (numer > 0) ? numer:numer*(-1);
        int bot = (denom > 0) ? denom:denom*-1;
        int minimum = (top < bot) ? top:bot;
        for (int i = minimum; i > 1; --i) {
            if (top % i == 0 && bot % i == 0) {
                common_factor = i;
                break;
            }
        }
        return common_factor;
    }
}