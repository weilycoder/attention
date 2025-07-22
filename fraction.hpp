#ifndef FRACTION_HPP
#define FRACTION_HPP

#include <stdexcept>
#include <string>

#include "bigint.hpp"

struct Fraction {
  BigInt numerator;
  BigInt denominator;

  Fraction() : numerator(0), denominator(1) {}
  Fraction(const int &num) : numerator(num), denominator(1) {}
  Fraction(const intmax_t num) : numerator(num), denominator(1) {}
  Fraction(const uintmax_t num) : numerator(num), denominator(1) {}
  Fraction(const BigInt &num) : numerator(num), denominator(1) {}
  Fraction(const BigInt &num, const BigInt &den) : numerator(num), denominator(den) {
    if (denominator.is_zero())
      throw std::domain_error("Denominator cannot be zero.");
    simplify();
  }

  void simplify() {
    BigInt gcd = find_gcd(numerator, denominator);
    numerator /= gcd, denominator /= gcd;
    if (denominator.is_negative())
      numerator = -numerator, denominator = -denominator;
  }

  static BigInt find_gcd(BigInt a, BigInt b) {
    BigInt *x = &a, *y = &b;
    for (; !y->is_zero(); std::swap(x, y))
      *x %= *y;
    return *x;
  }

  Fraction operator+(const Fraction &other) const {
    return Fraction(numerator * other.denominator + other.numerator * denominator,
                    denominator * other.denominator);
  }
  Fraction operator-(const Fraction &other) const {
    return Fraction(numerator * other.denominator - other.numerator * denominator,
                    denominator * other.denominator);
  }
  Fraction operator*(const Fraction &other) const {
    return Fraction(numerator * other.numerator, denominator * other.denominator);
  }
  Fraction operator/(const Fraction &other) const {
    return Fraction(numerator * other.denominator, denominator * other.numerator);
  }

  bool operator==(const Fraction &other) const {
    return numerator == other.numerator && denominator == other.denominator;
  }
  bool operator!=(const Fraction &other) const { return !(*this == other); }
  bool operator<(const Fraction &other) const {
    return numerator * other.denominator < other.numerator * denominator;
  }
  bool operator<=(const Fraction &other) const {
    return numerator * other.denominator <= other.numerator * denominator;
  }
  bool operator>(const Fraction &other) const {
    return numerator * other.denominator > other.numerator * denominator;
  }
  bool operator>=(const Fraction &other) const {
    return numerator * other.denominator >= other.numerator * denominator;
  }

  Fraction &operator+=(const Fraction &other) { return *this = *this + other; }
  Fraction &operator-=(const Fraction &other) { return *this = *this - other; }
  Fraction &operator*=(const Fraction &other) { return *this = *this * other; }
  Fraction &operator/=(const Fraction &other) { return *this = *this / other; }
  Fraction operator-() const { return Fraction(-numerator, denominator); }

  bool is_zero() const { return numerator.is_zero(); }
  bool is_one() const { return numerator.is_one() && denominator.is_one(); }
  bool is_minus_one() const { return numerator.is_minus_one() && denominator.is_one(); }
  bool is_negative() const { return numerator.is_negative(); }

  explicit operator bool() const { return !is_zero(); }

  std::string to_string() const {
    if (denominator.is_one())
      return numerator.to_str();
    return numerator.to_str() + "/" + denominator.to_str();
  }
  std::string to_str() const { return to_string(); }
  std::string to_astr() const {
    if (denominator.is_one())
      return numerator.to_astr();
    return numerator.to_astr() + "/" + denominator.to_astr();
  }

  std::string to_alatex(const std::string &frac = "\\frac") const {
    if (denominator.is_one())
      return numerator.to_astr();
    return frac + "{" + numerator.to_astr() + "}{" + denominator.to_astr() + "}";
  }
  std::string to_latex(const std::string &frac = "\\frac") const {
    return (is_negative() ? "-" : "") + to_alatex(frac);
  }
  std::string to_latex_sign(const std::string &frac = "\\frac") const {
    return (is_negative() ? "-" : "+") + to_alatex(frac);
  }
  std::string to_latex_coeff(const std::string &var, const std::string &frac = "\\frac") const {
    if (this->is_zero())
      return "";
    if (this->is_one())
      return var;
    if (this->is_minus_one())
      return "-" + var;
    return this->to_latex(frac) + var;
  }
  std::string to_latex_sign_coeff(const std::string &var, const std::string &frac = "\\frac") const {
    if (this->is_zero())
      return "";
    if (this->is_one())
      return "+" + var;
    if (this->is_minus_one())
      return "-" + var;
    return (is_negative() ? "-" : "+") + this->to_alatex(frac) + var;
  }
};

Fraction operator""_frac(unsigned long long num) { return Fraction(BigInt((uintmax_t)num)); }

namespace std {
std::string to_string(const Fraction &f) { return f.to_string(); }
} // namespace std

#endif // FRACTION_HPP
