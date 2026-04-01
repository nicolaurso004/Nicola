#ifndef RATIONAL_HPP
#define RATIONAL_HPP

#include <iostream>
#include <concepts>
#include <numeric>

template<typename I> requires std::integral<I>
class rational {
    I num_;
    I den_;


    void simplify() {
        // Gestione divisione per zero (Inf e NaN)
        if (den_ == 0) {
            if (num_ != 0) {
                num_ = (num_ > 0) ? 1 : -1;
            }
            return;
        }


        if (num_ == 0) {
            den_ = 1;
            return;
        }


        I mcd = std::gcd(num_, den_);
        num_ /= mcd;
        den_ /= mcd;


        if (den_ < 0) {
            num_ = -num_;
            den_ = -den_;
        }
    }

public:

    rational() : num_(0), den_(1) {}


    rational(const I& n, const I& d) : num_(n), den_(d) {
        simplify();
    }


    I num() const { return num_; }
    I den() const { return den_; }




    rational& operator+=(const rational& other) {
        
        if ((den_ == 0 && num_ == 0) || (other.den_ == 0 && other.num_ == 0)) {
            num_ = 0; den_ = 0; 
            return *this;
        }

        if (other.den_ == 0 && den_ != 0) {
            num_ = other.num_; den_ = 0; 
            return *this;
        }

        if (den_ == 0) return *this;


        I new_num = num_ * other.den_ + other.num_ * den_;
        I new_den = den_ * other.den_;
        num_ = new_num;
        den_ = new_den;
        simplify();
        return *this;
    }


    rational& operator-=(const rational& other) {

        rational neg_other(-other.num_, other.den_);
        *this += neg_other;
        return *this;
    }


    rational& operator*=(const rational& other) {
        num_ *= other.num_;
        den_ *= other.den_;
        simplify();
        return *this;
    }


    rational& operator/=(const rational& other) {
        num_ *= other.den_;
        den_ *= other.num_;
        simplify();
        return *this;
    }



    
    rational operator+(const rational& other) const {
        rational ret = *this;
        ret += other;
        return ret;
    }

    rational operator-(const rational& other) const {
        rational ret = *this;
        ret -= other;
        return ret;
    }

    rational operator*(const rational& other) const {
        rational ret = *this;
        ret *= other;
        return ret;
    }

    rational operator/(const rational& other) const {
        rational ret = *this;
        ret /= other;
        return ret;
    }
};


template<typename I>
std::ostream& operator<<(std::ostream& os, const rational<I>& r) {
    if (r.den() == 0) {
        if (r.num() == 0) os << "NaN";
        else if (r.num() > 0) os << "+Inf";
        else os << "-Inf";
    } else if (r.den() == 1) {

        os << r.num();
    } else {
        os << r.num() << "/" << r.den();
    }
    return os;
}

#endif