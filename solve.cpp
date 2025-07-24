#include "inte/e.hpp"
#include "inte/e_power_q.hpp"
#include "inte/pi.hpp"
#include "inte/pi_power_n.hpp"
#include <iostream>

// Test: solve pi -4738167652 14885392687
//       solve e -71 193
//       solve pi_power_2 5 -49
//       solve pi_power_3 1 -31
//       solve e_power_3 1 -20
//       solve e_power_-1 25 -9
//       solve e_power_1/2 25 -41

std::string match_sint(const std::string &pattern, const std::string &input) {
  if (input.length() <= pattern.length())
    return "";
  if (input.substr(0, pattern.length()) != pattern)
    return "";
  size_t pos = pattern.length();
  if (input[pos] == '-' || (input[pos] >= '0' && input[pos] <= '9'))
    return input.substr(pos);
  return "";
}

std::string match_uint(const std::string &pattern, const std::string &input) {
  if (input.length() <= pattern.length())
    return "";
  if (input.substr(0, pattern.length()) != pattern)
    return "";
  size_t pos = pattern.length();
  if (input[pos] >= '0' && input[pos] <= '9')
    return input.substr(pos);
  return "";
}

int main(int argc, char *argv[]) {
  using namespace std;

  try {
    size_t limit = 64;
    string tp;

    switch (argc) {
    case 5:
      limit = stoul(argv[4]);
      [[fallthrough]];
    case 4:
      tp = argv[1];
      break;
    default:
      cerr << "Usage: solve <type> <B> <A> [<limit=64>]" << endl;
      return 1;
    }

    BigInt A(argv[3]), B(argv[2]);

    if (tp == "pi") {
      auto [n, a, b, c] = solve_pi(A, B, limit);
      cout << "Bounds   : " << bound_pi.first << ", " << bound_pi.second << endl;
      cout << "Function : " << ans_to_sympy_pi(n, n, a, b, c) << endl;
    } else if (tp == "e") {
      auto [n, a, b] = solve_e(A, B, limit);
      cout << "Bounds   : " << bound_e.first << ", " << bound_e.second << endl;
      cout << "Function : " << ans_to_sympy_e(n, n, a, b) << endl;
    } else if (const std::string str = match_uint("pi_power_", tp); !str.empty()) {
      size_t n = stoull(str);
      auto [m, a, b] = solve_pi_power_n(A, B, n, limit);
      cout << "Bounds   : " << bound_pi_power_n.first << ", " << bound_pi_power_n.second << endl;
      cout << "Function : " << ans_to_sympy_pi_power_n(n, m, a, b) << endl;
    } else if (const std::string str = match_sint("e_power_", tp); !str.empty()) {
      Fraction q(str);
      auto [n, a, b] = solve_e_power_q(A, B, q, limit);
      cout << "Bounds   : " << bound_e_power_q.first << ", " << bound_e_power_q.second << endl;
      cout << "Function : " << ans_to_sympy_e_power_q(n, n, a, b, q) << endl;
    } else {
      cerr << "Unknown type: " << tp << endl;
      return 1;
    }

  } catch (const std::runtime_error &e) {
    cerr << "std::runtime_error: " << e.what() << endl;
    return 1;
  } catch (const std::invalid_argument &e) {
    cerr << "std::invalid_argument: " << e.what() << endl;
    return 2;
  } catch (const std::out_of_range &e) {
    cerr << "std::out_of_range: " << e.what() << endl;
    return 2;
  } catch (const std::domain_error &e) {
    cerr << "std::domain_error: " << e.what() << endl;
    return 2;
  } catch (const not_implemented &e) {
    cerr << "not_implemented: " << e.what() << endl;
    return 3;
  } catch (const std::logic_error &e) {
    cerr << "std::logic_error: " << e.what() << endl;
    return 3;
  } catch (const std::bad_alloc &e) {
    cerr << "std::bad_alloc: " << e.what() << endl;
    return 3;
  } catch (const std::exception &e) {
    cerr << "std::exception: " << e.what() << endl;
    return 3;
  } catch (...) {
    cerr << "An unexpected error occurred." << endl;
    return 3;
  }

  return 0;
}
