#ifndef INTE_E_HPP
#define INTE_E_HPP

#include "utils.hpp"

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

// \int_{0}^{1}x^{n}\left(1-x\right)^{m}\left(a+bx\right)\mathrm{e}^{x}\mathrm{d}x
std::string ans_to_latex_e(size_t n, size_t m, const Fraction &a, const Fraction &b) {
  std::string F0 = power_latex("x", n) + power_latex("\\left(1-x\\right)", m);
  std::string F1 = linear_latex(a, b, "x");
  if (F1.length() < F0.length())
    std::swap(F0, F1);
  return "\\int_{0}^{1}" + F0 + F1 + "\\mathrm{e}^{x}\\mathrm{d}x";
}

#endif // INTE_E_HPP
