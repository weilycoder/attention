#ifndef INTE_E_POWER_Q_HPP
#define INTE_E_POWER_Q_HPP

#include "utils.hpp"

// Integrate[P(x) * exp[x^q], {x, 0, 1}] = A + B*e^q
std::pair<Symbol, Symbol> get_coeffs_e_power_q(const Poly_s &func, const Fraction &q) {
  const Fraction q_inv = ~q; // Inverse of q
  Fraction a = -q_inv, b = q_inv;
  Symbol A, B;
  for (size_t i = 0; i < func.coeffs.size(); ++i) {
    if (i != 0) {
      const Fraction n(i);
      a *= -n * q_inv, b = q_inv - n * q_inv * b;
    }
    A += func.coeffs[i] * a, B += func.coeffs[i] * b;
  }
  return {A, B};
}

// a + b*e^q >= 0
std::tuple<size_t, Fraction, Fraction> solve_e_power_q(const Fraction &a, const Fraction &b,
                                                       const Fraction &q, size_t limit = 64) {
  Poly_s func{'a'_sym, 'b'_sym}; // a + b*x
  for (size_t i = 0; i <= limit; ++i) {
    // A + B*e^q
    auto [A, B] = get_coeffs_e_power_q(func, q);
    A -= Symbol(a), B -= Symbol(b);
    try {
      auto [a, b] = solve_ab(A, B);
      if (ensure_nonegative(a, b))
        return {i, a, b};
    } catch (const std::domain_error &e) {
      // Ignore errors, continue searching
    }
    func = Poly_s{1_sym, -1_sym} * func, func.lshift();
  }
  throw std::domain_error("No solution found within the limit of " + std::to_string(limit));
}

// x**n * (1-x)**m * (a + b*x) * exp(q * x)
std::string ans_to_sympy_e_power_q(size_t n, size_t m, const Fraction &a, const Fraction &b, const Fraction &q) {
  return "x**" + std::to_string(n) + " * (1-x)**" + std::to_string(m) + " * (" + a.to_str() + " + " +
         b.to_str() + "*x) * exp(" + q.to_str() + " * x)";
}

#endif // INTE_E_POWER_Q_HPP
