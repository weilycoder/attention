#ifndef EQUATION_HPP
#define EQUATION_HPP

#include <stdexcept>
#include <tuple>
#include <utility>

template <typename T> inline T determinant2(const T &a1, const T &a2, const T &b1, const T &b2) {
  return a1 * b2 - a2 * b1;
}

template <typename T>
inline std::pair<T, T> solve2(const T &a1, const T &a2, const T &b1, const T &b2, const T &c1, const T &c2) {
  T D = determinant2(a1, a2, b1, b2);
  if (!bool(D))
    throw std::domain_error("No unique solution exists for the system of equations.");
  T A = determinant2(c1, c2, b1, b2);
  T B = determinant2(a1, a2, c1, c2);
  return {-A / D, -B / D};
}

template <typename T>
inline T determinant3(const T &a1, const T &a2, const T &a3, const T &b1, const T &b2, const T &b3,
                      const T &c1, const T &c2, const T &c3) {
  return a1 * b2 * c3 - a1 * b3 * c2 - a2 * b1 * c3 + a2 * b3 * c1 + a3 * b1 * c2 - a3 * b2 * c1;
}

template <typename T>
inline std::tuple<T, T, T> solve3(const T &a1, const T &a2, const T &a3, const T &b1, const T &b2,
                                  const T &b3, const T &c1, const T &c2, const T &c3, const T &d1,
                                  const T &d2, const T &d3) {
  T D = determinant3(a1, a2, a3, b1, b2, b3, c1, c2, c3);
  if (!bool(D))
    throw std::domain_error("No unique solution exists for the system of equations.");
  T A = determinant3(d1, d2, d3, b1, b2, b3, c1, c2, c3);
  T B = determinant3(a1, a2, a3, d1, d2, d3, c1, c2, c3);
  T C = determinant3(a1, a2, a3, b1, b2, b3, d1, d2, d3);
  return {-A / D, -B / D, -C / D};
}

#endif // EQUATION_HPP
