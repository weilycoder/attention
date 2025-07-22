#ifndef SYMBOL_HPP
#define SYMBOL_HPP

#include <map>
#include <stdexcept>
#include <string>
#include <utility>

#include "fraction.hpp"

class not_implemented : public std::logic_error {
public:
  explicit not_implemented(const std::string &feature) : logic_error(feature + " not implemented") {}
};

struct Symbol {
  std::map<char, Fraction> variables;

  Symbol() = default;
  Symbol(const Fraction &value) { variables[0] = value; }
  Symbol(const char name) { variables[name] = Fraction(1); }
  Symbol(const char name, const Fraction &coefficient) {
    if (!coefficient.is_zero())
      variables[name] = coefficient;
  }

  void add_variable(const char name, const Fraction &coefficient) {
    if (coefficient.is_zero())
      return; // Ignore zero coefficients
    if (variables.find(name) != variables.end())
      variables[name] += coefficient;
    else
      variables[name] = coefficient;
    if (variables[name].is_zero())
      variables.erase(name); // Remove zero coefficients
  }

  bool is_number() const {
    if (variables.size() == 0)
      return true;
    if (variables.size() == 1 && variables.begin()->first == 0)
      return true;
    return false;
  }

  Fraction get_coefficient(const char name) const {
    auto it = variables.find(name);
    if (it != variables.end())
      return it->second;
    return Fraction(0); // Return zero if variable not found
  }

  Fraction get_value() const {
    if (variables.size() == 0)
      return Fraction(0);
    if (variables.size() == 1 && variables.begin()->first == 0)
      return variables.begin()->second;
    throw std::runtime_error("Symbol is not a number.");
  }

  bool is_zero() const { return variables.size() == 0; }

  const std::map<char, Fraction> &get_variables() const { return variables; }

  Symbol operator+() const {
    return *this; // Unary plus does not change the symbol
  }

  Symbol operator-() const {
    Symbol result;
    for (const auto &pair : variables)
      result.add_variable(pair.first, -pair.second);
    return result;
  }

  Symbol operator+(const Symbol &other) const {
    Symbol result = *this;
    for (const auto &pair : other.variables)
      result.add_variable(pair.first, pair.second);
    return result;
  }
  Symbol operator-(const Symbol &other) const {
    Symbol result = *this;
    for (const auto &pair : other.variables)
      result.add_variable(pair.first, -pair.second);
    return result;
  }

  Symbol operator*(const Fraction &other) const {
    Symbol result;
    for (const auto &pair : variables)
      result.add_variable(pair.first, pair.second * other);
    return result;
  }
  Symbol operator*(const Symbol &other) const {
    if (other.is_number())
      return *this * other.get_value();
    if (this->is_number())
      return other * this->get_value();
    throw not_implemented("Multiplication of two symbols");
  }

  Symbol operator/(const Fraction &other) const {
    if (other.is_zero())
      throw std::domain_error("Division by zero.");
    Symbol result;
    for (const auto &pair : variables)
      result.add_variable(pair.first, pair.second / other);
    return result;
  }
  Symbol operator/(const Symbol &other) const {
    if (other.is_number())
      return *this / other.get_value();
    throw not_implemented("Division by a symbol");
  }

  Symbol &operator+=(const Symbol &other) {
    for (const auto &pair : other.variables)
      add_variable(pair.first, pair.second);
    return *this;
  }
  Symbol &operator-=(const Symbol &other) {
    for (const auto &pair : other.variables)
      add_variable(pair.first, -pair.second);
    return *this;
  }

  Symbol &operator*=(const Fraction &other) {
    if (other.is_zero())
      return variables.clear(), *this; // Clear all variables if multiplied by zero
    if (other.is_one())
      return *this; // No change if multiplied by one
    for (auto &pair : variables)
      pair.second *= other;
    return *this;
  }
  Symbol &operator*=(const Symbol &other) {
    if (other.is_number())
      return *this *= other.get_value();
    if (this->is_number())
      return *this = other * this->get_value();
    throw not_implemented("Multiplication of two symbols");
  }

  Symbol &operator/=(const Fraction &other) {
    if (other.is_zero())
      throw std::domain_error("Division by zero.");
    if (other.is_one())
      return *this; // No change if divided by one
    for (auto &pair : variables)
      pair.second /= other;
    return *this;
  }
  Symbol &operator/=(const Symbol &other) {
    if (other.is_number())
      return *this /= other.get_value();
    throw not_implemented("Division by a symbol");
  }

  static std::string to_string(const std::pair<char, Fraction> &pair) {
    if (pair.first == 0) // Special case for constant term
      return pair.second.to_string();
    if (pair.second.is_one())
      return std::string(1, pair.first); // Just the variable name if coefficient is 1
    if (pair.second.is_minus_one())
      return "-" + std::string(1, pair.first); // Just the negative variable name if coefficient is -1
    return pair.second.to_string() + " * " + pair.first; // Coefficient and variable name
  }

  std::string to_string() const {
    if (variables.empty())
      return "0"; // No variables means it's zero
    std::string result;
    for (const auto &pair : variables) {
      if (!result.empty())
        result += " + "; // Add separator for multiple terms
      result += to_string(pair);
    }
    return result;
  }

  explicit operator bool() const { return !is_zero(); }
};

Symbol operator""_sym(char c) { return Symbol(c); }
Symbol operator""_sym(const char *s, size_t) { return Symbol(BigInt(s)); }
Symbol operator""_sym(unsigned long long v) { return Symbol(BigInt(v)); }

namespace std {
std::string to_string(const Symbol &symbol) { return symbol.to_string(); }
} // namespace std

#endif // SYMBOL_HPP
