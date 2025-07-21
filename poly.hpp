#ifndef POLY_HPP
#define POLY_HPP

#include <algorithm>
#include <initializer_list>
#include <string>
#include <utility>
#include <vector>

template <typename T> struct Poly {
  std::vector<T> coeffs;

  Poly() = default;
  Poly(const std::vector<T> &c) : coeffs(c) {}
  Poly(std::initializer_list<T> c) : coeffs(c) {}
  Poly(const T &coeff, size_t degree = 0) { coeffs.resize(degree + 1), coeffs[degree] = coeff; }

  void simplify() {
    while (!coeffs.empty() && !(bool)coeffs.back())
      coeffs.pop_back();
  }

  Poly operator+(const Poly &other) const {
    Poly result;
    result.coeffs.resize(std::max(coeffs.size(), other.coeffs.size()));
    for (size_t i = 0; i < result.coeffs.size(); ++i) {
      if (i < coeffs.size())
        result.coeffs[i] += coeffs[i];
      if (i < other.coeffs.size())
        result.coeffs[i] += other.coeffs[i];
    }
    return result.simplify(), result;
  }
  Poly operator-(const Poly &other) const {
    Poly result;
    result.coeffs.resize(std::max(coeffs.size(), other.coeffs.size()));
    for (size_t i = 0; i < result.coeffs.size(); ++i) {
      if (i < coeffs.size())
        result.coeffs[i] += coeffs[i];
      if (i < other.coeffs.size())
        result.coeffs[i] -= other.coeffs[i];
    }
    return result.simplify(), result;
  }
  Poly operator*(const Poly &other) const {
    Poly result;
    result.coeffs.resize(coeffs.size() + other.coeffs.size() - 1);
    for (size_t i = 0; i < coeffs.size(); ++i)
      if (bool(coeffs[i]))
        for (size_t j = 0; j < other.coeffs.size(); ++j)
          result.coeffs[i + j] += coeffs[i] * other.coeffs[j];
    return result.simplify(), result;
  }

  std::pair<Poly, Poly> divmod(const Poly &other) const {
    Poly quotient, remainder = *this;
    quotient.coeffs.reserve(remainder.coeffs.size() - other.coeffs.size() + 1);
    remainder.simplify();
    while (remainder.coeffs.size() >= other.coeffs.size()) {
      T coeff = remainder.coeffs.back() / other.coeffs.back();
      for (size_t i = 0; i < other.coeffs.size(); ++i)
        remainder.coeffs[remainder.coeffs.size() - 1 - i] -=
            coeff * other.coeffs[other.coeffs.size() - 1 - i];
      quotient.coeffs.emplace_back(coeff);
      remainder.simplify();
    }
    std::reverse(quotient.coeffs.begin(), quotient.coeffs.end());
    return {quotient, remainder};
  }

  Poly &lshift() { return coeffs.emplace(coeffs.begin()), *this; }
  Poly &lshift(size_t shift) { return coeffs.insert(coeffs.begin(), shift, T{}), *this; }
  Poly &operator<<=(size_t shift) { return lshift(shift); }

  std::string to_string(const std::string &var = "") const {
    if (var.empty()) {
      std::string result = "Poly([";
      for (size_t i = 0; i < coeffs.size(); ++i) {
        if (i > 0)
          result += ", ";
        result += std::to_string(coeffs[i]);
      }
      return result += "])";
    } else {
      std::string result;
      for (size_t i = 0; i < coeffs.size(); ++i) {
        if (!(bool)coeffs[i])
          continue;
        if (!result.empty())
          result += " + ";
        if (i == 0)
          result += std::to_string(coeffs[i]);
        else if (i == 1)
          result += std::to_string(coeffs[i]) + " * " + var;
        else
          result += std::to_string(coeffs[i]) + " * " + var + "^" + std::to_string(i);
      }
      return result.empty() ? "0" : result;
    }
  }
};

#endif // POLY_HPP
