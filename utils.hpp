#ifndef UTILS_HPP
#define UTILS_HPP

#include "equation.hpp"
#include "poly.hpp"
#include "symbol.hpp"

using Poly_s = Poly<Symbol>;

std::tuple<Fraction, Fraction, Fraction> solve_abc(const Symbol &eq1, const Symbol &eq2, const Symbol &eq3) {
  Fraction a1 = eq1.get_coefficient("a");
  Fraction b1 = eq1.get_coefficient("b");
  Fraction c1 = eq1.get_coefficient("c");
  Fraction a2 = eq2.get_coefficient("a");
  Fraction b2 = eq2.get_coefficient("b");
  Fraction c2 = eq2.get_coefficient("c");
  Fraction a3 = eq3.get_coefficient("a");
  Fraction b3 = eq3.get_coefficient("b");
  Fraction c3 = eq3.get_coefficient("c");
  Fraction d1 = eq1.get_coefficient("");
  Fraction d2 = eq2.get_coefficient("");
  Fraction d3 = eq3.get_coefficient("");

  return solve3(a1, a2, a3, b1, b2, b3, c1, c2, c3, d1, d2, d3);
}

// Ensure a + b*x >= 0 on [0, 1]
bool ensure_nonegative(const Fraction &a, const Fraction &b) { return a >= 0 && a + b >= 0; }

// Ensure a + bx + cx^2 >= 0 on [0, 1]
bool ensure_nonegative(const Fraction &a, const Fraction &b, const Fraction &c) {
  if (c.is_zero())
    return ensure_nonegative(a, b);
  if (a < 0 || a + b + c < 0)
    return false;
  Fraction peak = -b / (2_frac * c);
  return (peak <= 0 || peak >= 1) || (a + b * peak + c * peak * peak >= 0);
}

std::string power_latex(const std::string &base, size_t power) {
  if (power == 0)
    return "";
  if (power == 1)
    return base;
  return base + "^{" + std::to_string(power) + "}";
}

std::string quadratic_latex(const Fraction &a, const Fraction &b, const Fraction &c,
                            const std::string &var = "x") {
  std::vector<std::string> parts;
  if (!a.is_zero())
    parts.push_back(a.to_latex("\\dfrac"));
  if (!b.is_zero()) {
    if (parts.empty())
      parts.push_back(b.to_latex_coeff(var, "\\dfrac"));
    else
      parts.push_back(b.to_latex_sign_coeff(var, "\\dfrac"));
  }
  if (!c.is_zero()) {
    if (parts.empty())
      parts.push_back(c.to_latex_coeff(power_latex(var, 2), "\\dfrac"));
    else
      parts.push_back(c.to_latex_sign_coeff(power_latex(var, 2), "\\dfrac"));
  }
  switch (parts.size()) {
  case 0:
    throw std::runtime_error("All coefficients are zero.");
  case 1:
    return parts[0];
  case 2:
    return "\\left(" + parts[0] + parts[1] + "\\right)";
  case 3:
    return "\\left(" + parts[0] + parts[1] + parts[2] + "\\right)";
  default:
    break; // Should not happen
  }
  throw std::runtime_error("Unexpected number of parts: " + std::to_string(parts.size()));
}

#endif // UTILS_HPP
