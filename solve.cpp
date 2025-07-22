#include "inte_e.hpp"
#include "inte_pi.hpp"
#include <iostream>

// Test: solve_pi -4738167652 14885392687

int main(int argc, char *argv[]) {
  using namespace std;
  size_t limit = 32;
  string tp;
  switch (argc) {
  case 5:
    limit = stoul(argv[4]);
    [[fallthrough]];
  case 4:
    tp = argv[1];
    break;
  default:
    cerr << "Usage: solve <type> <B> <A> [<limit=32>]" << endl;
    return 1;
  }
  try {
    if (tp == "pi") {
      auto [n, a, b, c] = solve_pi(BigInt(argv[3]), BigInt(argv[2]), limit);
      cout << ans_to_latex_pi(n, n, a, b, c) << endl;
    } else if (tp == "e") {
      auto [n, a, b] = solve_e(BigInt(argv[3]), BigInt(argv[2]), limit);
      cout << ans_to_latex_e(n, n, a, b) << endl;
    } else {
      cerr << "Unknown type: " << tp << endl;
      return 1;
    }
  } catch (const std::runtime_error &e) {
    cerr << "std::runtime_error: " << e.what() << endl;
    return 1;
  } catch (...) {
    cerr << "An unexpected error occurred." << endl;
    return 3;
  }
  return 0;
}
