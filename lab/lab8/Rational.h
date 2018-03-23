#ifndef RATIONAL_H
#define RATIONAL_H
#include <iostream>

namespace CS2124 {
    class Rational {
        friend std::ostream& operator<< (std::ostream& os, const Rational& num);
        friend std::istream& operator>> (std::istream& is, Rational& num);
        friend bool operator== (const Rational& lhs, const Rational& rhs);
        private:
            int numer;
            int denom;
        public:
            Rational ();
            Rational (int num);
            Rational (int numer, int denom);
            void normalize();
            Rational& operator+= (const Rational& rhs);
            void add_two_rational(Rational& lhs, const Rational& rhs);
            Rational& operator++();
            Rational operator++ (int);
            explicit operator bool() const;
    };
    std::ostream& operator<< (std::ostream& os, const Rational& num);     //all functions defined must be declared
    std::istream& operator>> (std::istream& is, Rational& num);
    Rational operator+ (const Rational& lhs, const Rational& rhs);
    bool operator== (const Rational& lhs, const Rational& rhs);
    bool operator!= (const Rational& lhs, const Rational& rhs);
    Rational& operator-- (Rational& lhs);
    Rational operator-- (Rational& lhs, int);
    int gcd(int numer, int denom);
}

#endif