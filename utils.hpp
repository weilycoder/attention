#ifndef UTILS_HPP
#define UTILS_HPP

#include "equation.hpp"
#include "poly.hpp"
#include "symbol.hpp"

using Poly_s = Poly<Symbol>;

std::pair<Fraction, Fraction> solve_ab(const Symbol &eq1, const Symbol &eq2) {
  Fraction a1 = eq1.get_coefficient('a');
  Fraction b1 = eq1.get_coefficient('b');
  Fraction a2 = eq2.get_coefficient('a');
  Fraction b2 = eq2.get_coefficient('b');
  Fraction c1 = eq1.get_coefficient(0);
  Fraction c2 = eq2.get_coefficient(0);

  return solve2(a1, a2, b1, b2, c1, c2);
}

std::tuple<Fraction, Fraction, Fraction> solve_abc(const Symbol &eq1, const Symbol &eq2, const Symbol &eq3) {
  Fraction a1 = eq1.get_coefficient('a');
  Fraction b1 = eq1.get_coefficient('b');
  Fraction c1 = eq1.get_coefficient('c');
  Fraction a2 = eq2.get_coefficient('a');
  Fraction b2 = eq2.get_coefficient('b');
  Fraction c2 = eq2.get_coefficient('c');
  Fraction a3 = eq3.get_coefficient('a');
  Fraction b3 = eq3.get_coefficient('b');
  Fraction c3 = eq3.get_coefficient('c');
  Fraction d1 = eq1.get_coefficient(0);
  Fraction d2 = eq2.get_coefficient(0);
  Fraction d3 = eq3.get_coefficient(0);

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

#endif // UTILS_HPP
