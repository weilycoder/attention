#ifndef INTE_PI_HPP
#define INTE_PI_HPP

#include "utils.hpp"

// Integrate[P(x) / (1 + x^2), {x, 0, 1}] = A + B*ln(2) + C*pi
std::tuple<Symbol, Symbol, Symbol> get_coeffs_pi(const Poly_s &func) {
  Poly_s deno = Poly_s({1_sint, 0_sint, 1_sint}); // 1 + x^2
  auto [q, r] = func.divmod(deno);
  Symbol A, B, C;
  for (size_t i = 0; i < q.coeffs.size(); ++i)
    // Integrate[q * x^i, {x, 0, 1}]
    A += q.coeffs[i] / (i + 1);
  for (size_t i = 0; i < r.coeffs.size(); ++i) {
    switch (i) {
    case 0:
      // Integrate[r / (1 + x^2), {x, 0, 1}]
      C = r.coeffs[0] / 4;
      break;
    case 1:
      // Integrate[r * x / (1 + x^2), {x, 0, 1}]
      B = r.coeffs[1] / 2;
      break;
    default:
      throw std::runtime_error("Unexpected coefficient index: " + std::to_string(i));
    }
  }
  return {A, B, C};
}

// a + b*pi >= 0
std::tuple<size_t, Fraction, Fraction, Fraction> solve_pi(const Fraction &a, const Fraction &b,
                                                          size_t limit = 32) {
  Poly_s func{"a"_sym, "b"_sym, "c"_sym}; // a + b*x + c*x^2
  for (size_t n = 0; n <= limit; ++n) {
    // A + B*ln(2) + C*pi
    auto [A, B, C] = get_coeffs_pi(func);
    A -= Symbol(a), C -= Symbol(b);
    try {
      auto [a, b, c] = solve_abc(A, B, C);
      if (ensure_nonegative(a, b, c))
        return {n, a, b, c};
    } catch (const std::runtime_error &e) {
      // Ignore errors, continue searching
    }
    func = Poly_s{1_sint, -1_sint} * func, func.lshift();
  }
  throw std::runtime_error("No solution found within the limit of " + std::to_string(limit));
}

// \int_{0}^{1}\dfrac{x^{n}\left(1-x\right)^{m}\left(a+bx+cx^{2}\right)}{1+x^{2}}\mathrm{d}x
std::string ans_to_latex_pi(size_t n, size_t m, const Fraction &a, const Fraction &b, const Fraction &c) {
  std::string quadratic;
  if (!a.is_zero())
    quadratic += a.to_latex("\\dfrac");
  if (!b.is_zero()) {
    if (quadratic.empty())
      quadratic += b.to_latex_coeff("x", "\\dfrac");
    else
      quadratic += b.to_latex_sign_coeff("x", "\\dfrac");
  }
  if (!c.is_zero()) {
    if (quadratic.empty())
      quadratic = c.to_latex_coeff("x^{2}", "\\dfrac");
    else
      quadratic += c.to_latex_sign_coeff("x^{2}", "\\dfrac");
  }

  return "\\int_{0}^{1}\\dfrac{" + power_latex("x", n) + power_latex("\\left(1-x\\right)", m) + "\\left(" +
         quadratic + "\\right)}{1+x^{2}}\\mathrm{d}x";
}

#endif // INTE_PI_HPP
