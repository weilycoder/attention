#ifndef INTE_E_HPP
#define INTE_E_HPP

#include "../utils.hpp"

const std::pair<std::string, std::string> bound_e = {"0", "1"};

// Integrate[P(x) * exp[x], {x, 0, 1}] = A + B*e
std::pair<Symbol, Symbol> get_coeffs_e(const Poly_s &func) {
  static const BigInt one(1);
  Symbol A, B;
  BigInt a(-1), b(1);
  for (size_t i = 0; i < func.coeffs.size(); ++i) {
    if (i != 0) {
      BigInt n(i);
      a *= -n, b = one - n * b;
    }
    A += func.coeffs[i] * a, B += func.coeffs[i] * b;
  }
  return {A, B};
}

// a + b*e >= 0
std::tuple<size_t, Fraction, Fraction> solve_e(const Fraction &a, const Fraction &b, size_t limit = 64) {
  Poly_s func{'a'_sym, 'b'_sym}; // a + b*x
  for (size_t n = 0; n <= limit; ++n) {
    // A + B*e
    auto [A, B] = get_coeffs_e(func);
    A -= Symbol(a), B -= Symbol(b);
    try {
      auto [a, b] = solve_ab(A, B);
      if (ensure_nonegative(a, b))
        return {n, a, b};
    } catch (const std::domain_error &e) {
      // Ignore errors, continue searching
    }
    func = Poly_s{1_sym, -1_sym} * func, func.lshift();
  }
  throw std::domain_error("No solution found within the limit of " + std::to_string(limit));
}

// x**n * (1-x)**m * (a + b*x) * exp(x)
std::string ans_to_sympy_e(size_t n, size_t m, const Fraction &a, const Fraction &b) {
  return "x**" + std::to_string(n) + " * (1-x)**" + std::to_string(m) + " * (" + a.to_str() + " + " +
         b.to_str() + "*x) * exp(x)";
}

#endif // INTE_E_HPP
