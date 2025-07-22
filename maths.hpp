#ifndef MATHS_HPP
#define MATHS_HPP

#include <cstddef>
#include <cstdint>
#include <vector>

#include "bigint.hpp"
#include "except.hpp"
#include "fraction.hpp"

BigInt fast_pow(BigInt base, uint64_t exp) {
  BigInt result(1);
  for (; exp; exp >>= 1, base *= base)
    if (exp & 1)
      result *= base;
  return result;
}

const BigInt &two_power(uint64_t n) {
  static std::vector<BigInt> cache{1_big};
  while (cache.size() <= n)
    cache.emplace_back(cache.back() * 2_big);
  return cache[n];
}

const BigInt &minus_one_power(uint64_t n) {
  static const BigInt one(1), minus_one(-1);
  return (n & 1) ? minus_one : one;
}

const BigInt &gamma(int64_t n) {
  if (n <= 0)
    throw std::domain_error("Gamma function is not defined for non-positive integers.");
  static std::vector<BigInt> cache{1_big, 1_big};
  if (n <= cache.size())
    return cache[n - 1];
  while (cache.size() < n)
    cache.emplace_back(cache.back() * BigInt((uintmax_t)cache.size()));
  return cache[n - 1];
}

const BigInt &factorial(int64_t n) {
  if (n < 0)
    throw std::domain_error("Factorial is not defined for negative integers.");
  return gamma(n + 1);
}

// Zeta function for even integers (the result won't contain pi^n)
const Fraction &zeta(int64_t n) {
  if (n <= 1)
    throw std::domain_error("Zeta function is not defined for n <= 1.");
  if (n & 1)
    throw not_implemented("Zeta function for odd n");
  n >>= 1; // n is now even
  static std::vector<Fraction> cache{Fraction(1)};
  if (n < cache.size())
    return cache[n];
  for (size_t k = cache.size(); k <= n; ++k) {
    cache.emplace_back(minus_one_power(k + 1));
    cache.back() *= Fraction((uintmax_t)k);
    cache.back() /= factorial(2 * k + 1);
    for (size_t i = 1; i < k; ++i) {
      switch (i & 1) {
      case 0:
        cache.back() -= cache[k - i] / factorial(2 * i + 1);
        break;
      case 1:
        cache.back() += cache[k - i] / factorial(2 * i + 1);
        break;
      default:
        __builtin_unreachable();
      }
    }
  }
  return cache[n];
}

// Dirichlet beta function for odd integers (the result won't contain pi^n)
const Fraction &beta(int64_t n) {
  if (n <= 0)
    throw std::domain_error("Beta function is not defined for non-positive integers.");
  if (!(n & 1))
    throw not_implemented("Beta function for even n");
  n >>= 1; // Beta(2n + 1)
  static std::vector<Fraction> cache{Fraction(1, 4)};
  if (n < cache.size())
    return cache[n];
  for (size_t k = cache.size(); k <= n; ++k) {
    cache.emplace_back();
    for (size_t m = 1; m <= k; ++m) {
      switch (m & 1) {
      case 0:
        cache.back() -= cache[k - m] / (factorial(2 * m) * two_power(2 * m));
        break;
      case 1:
        cache.back() += cache[k - m] / (factorial(2 * m) * two_power(2 * m));
        break;
      default:
        __builtin_unreachable();
      }
    }
  }
  return cache[n];
}

#endif // MATHS_HPP
