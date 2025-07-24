#ifndef INTE_PI_POW_N_HPP
#define INTE_PI_POW_N_HPP

#include "../maths.hpp"
#include "../utils.hpp"

// Integrate[P(x) * ln[1/x]^(n-1) / (1 + x^2), {x, 0, 1}] = A + B * pi^n
std::pair<Symbol, Symbol> get_coeffs_pi_pow_n(const Poly_s &func, size_t n) {
  if (n == 0)
    throw std::domain_error("n must be greater than 1 for this function.");
  if (n == 1)
    throw std::domain_error(
        "n must be greater than 1 for this function, please use `pi` instead of `pi_power_n`.");
  Poly_s deno = Poly_s({1_sym, 0_sym, 1_sym}); // 1 + x^2
  auto [q, r] = func.divmod(deno);
  Symbol A, B;
  for (size_t i = 0; i < q.coeffs.size(); ++i)
    // Integrate[q * x^i * ln[1/x]^(n-1), {x, 0, 1}]
    A += q.coeffs[i] / fast_pow(BigInt(i + 1), n);
  A *= factorial(n - 1);
  for (size_t i = 0; i < r.coeffs.size(); ++i) {
    if (r.coeffs[i].is_zero())
      continue;
    if (i != 1 - (n & 1))
      throw std::domain_error("Cannot integrate the function");
    switch (i) {
    case 0:
      // Integrate[r * ln[1/x]^(n-1) / (1 + x^2), {x, 0, 1}]
      B = r.coeffs[0] * beta(n) * factorial(n - 1);
      break;
    case 1:
      // Integrate[r * x * ln[1/x]^(n-1) / (1 + x^2), {x, 0, 1}]
      B = r.coeffs[1] * zeta(n) * Fraction((two_power(n - 1) - 1) * factorial(n - 1), two_power(2 * n - 1));
    }
  }
  return {A, B};
}

// a + b * pi^n >= 0
std::tuple<size_t, Fraction, Fraction> solve_pi_pow_n(const Fraction &a, const Fraction &b, size_t n,
                                                      size_t limit = 64) {
  Poly_s func{'a'_sym, 0_sym, 'b'_sym}; // a + b*x^2
  for (size_t m = 0; m <= limit; ++m, func.lshift()) {
    if (((m + n) & 1) == 0)
      continue; // Skip even m if n is odd, and vice versa
    // A + B * pi^n
    auto [A, B] = get_coeffs_pi_pow_n(func, n);
    A -= Symbol(a), B -= Symbol(b);
    try {
      auto [a, b] = solve_ab(A, B);
      if (ensure_nonegative(a, b))
        return {m, a, b};
    } catch (const std::domain_error &e) {
      // Ignore errors, continue searching
    }
  }
  throw std::domain_error("No solution found within the limit of " + std::to_string(limit));
}

// x**m * (a + b*x^2) * ln(1/x)**(n-1) / (1 + x^2)
std::string ans_to_sympy_pi_pow_n(size_t n, size_t m, const Fraction &a, const Fraction &b) {
  return "x**" + std::to_string(m) + " * (" + a.to_str() + " + " + b.to_str() + "*x**2) * ln(1/x)**" +
         std::to_string(n - 1) + " / (1 + x**2)";
}

#endif // INTE_PI_POW_N_HPP
