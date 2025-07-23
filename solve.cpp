#include "inte_e.hpp"
#include "inte_pi.hpp"
#include "inte_pi_pow_n.hpp"
#include <iostream>

// Test: solve pi -4738167652 14885392687
//       solve e -71 193
//       solve pi_power_2 5 -49
//       solve pi_power_3 1 -31

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
      cout << "Bounds   : " << 0 << ", " << 1 << endl;
      cout << "Function : " << ans_to_sympy_pi(n, n, a, b, c) << endl;
    } else if (tp == "e") {
      auto [n, a, b] = solve_e(A, B, limit);
      cout << "Bounds   : " << 0 << ", " << 1 << endl;
      cout << "Function : " << ans_to_sympy_e(n, n, a, b) << endl;
    } else if (tp.length() > 9 && tp.substr(0, 9) == "pi_power_" && tp[9] > '0' && tp[9] <= '9') {
      size_t n = stoull(tp.substr(9));
      auto [m, a, b] = solve_pi_pow_n(A, B, n, limit);
      cout << "Bounds   : " << 0 << ", " << 1 << endl;
      cout << "Function : " << ans_to_sympy_pi_pow_n(n, m, a, b) << endl;
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
