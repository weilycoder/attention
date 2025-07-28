#ifndef E_POWER_PI_Q_HPP
#define E_POWER_PI_Q_HPP

#include "../utils.hpp"

const std::pair<std::string, std::string> bound_e_power_pi_q = {"0", "pi"};

// Integrate[P(sin[x]) * exp[q * x], {x, 0, pi}] = A + B*e^(q*pi)
std::pair<Symbol, Symbol> get_coeffs_e_power_pi_q(const Poly_s &func, const Fraction &q) {
  static const BigInt one(1);
  const Fraction q_inv = ~q; // Inverse of q
  const Fraction q_sq = q * q;
  Fraction a[2] = {-q_inv, ~(q_sq + one)};
  Fraction b[2] = {q_inv, ~(q_sq + one)};
  Symbol A, B;
  for (size_t i = 0; i < func.coeffs.size(); ++i) {
    if (i >> 1) {
      BigInt n(i), n_sq = n * n;
      Fraction k = Fraction(n * (n - 1)) / (q_sq + n * n);
      a[i & 1] *= k, b[i & 1] *= k;
    }
    A += func.coeffs[i] * a[i & 1], B += func.coeffs[i] * b[i & 1];
  }
  return {A, B};
}

// a + b*e^(q*pi) >= 0
std::tuple<size_t, Fraction, Fraction> solve_e_power_pi_q(const Fraction &a, const Fraction &b,
                                                          const Fraction &q, size_t limit = 64) {
  Poly_s func{'a'_sym, 'b'_sym}; // a + b*x
  for (size_t i = 0; i <= limit; ++i) {
    // A + B*e^(q*pi)
    auto [A, B] = get_coeffs_e_power_pi_q(func, q);
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

// sin(x)**n * (1 - sin(x))**m * (a + b*sin(x)) * exp(q * x)
std::string ans_to_sympy_e_power_pi_q(size_t n, size_t m, const Fraction &a, const Fraction &b,
                                      const Fraction &q) {
  return "sin(x)**" + std::to_string(n) + " * (1-sin(x))**" + std::to_string(m) + " * (" + a.to_str() +
         " + " + b.to_str() + "*sin(x)) * exp(" + q.to_str() + "*x)";
}

#endif
