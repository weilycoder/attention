#ifndef E_POWER_PI_HPP
#define E_POWER_PI_HPP

#include "../utils.hpp"

const std::pair<std::string, std::string> bound_e_power_pi = {"0", "pi"};

// Integrate[P(sin[x]) * exp[x], {x, 0, pi}] = A + B*e^pi
std::pair<Symbol, Symbol> get_coeffs_e_power_pi(const Poly_s &func) {
  static const BigInt one(1);
  Symbol A, B;
  Fraction a[2] = {-1, {1, 2}};
  Fraction b[2] = {1, {1, 2}};
  for (size_t i = 0; i < func.coeffs.size(); ++i) {
    if (i >> 1) {
      BigInt n(i);
      Fraction k(n * (n - one), n * n + one);
      a[i & 1] *= k, b[i & 1] *= k;
    }
    A += func.coeffs[i] * a[i & 1], B += func.coeffs[i] * b[i & 1];
  }
  return {A, B};
}
// a + b*e^pi >= 0
std::tuple<size_t, Fraction, Fraction> solve_e_power_pi(const Fraction &a, const Fraction &b,
                                                        size_t limit = 64) {
  Poly_s func{'a'_sym, 'b'_sym}; // a + b*x
  for (size_t n = 0; n <= limit; ++n) {
    // A + B*e^pi
    auto [A, B] = get_coeffs_e_power_pi(func);
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

// sin(x)**n * (1-sin(x))**m * (a + b*sin(x)) * exp(x)
std::string ans_to_sympy_e_power_pi(size_t n, size_t m, const Fraction &a, const Fraction &b) {
  return "sin(x)**" + std::to_string(n) + " * (1-sin(x))**" + std::to_string(m) + " * (" + a.to_str() +
         " + " + b.to_str() + "*sin(x)) * exp(x)";
}

#endif // E_POWER_PI_HPP
