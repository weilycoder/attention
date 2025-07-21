#include "inte_pi.hpp"
#include <iostream>

// Test: solve_pi -4738167652 14885392687

int main(int argc, char *argv[]) {
  using namespace std;
  size_t limit = 32;
  switch (argc) {
  case 4:
    limit = stoul(argv[3]);
    [[fallthrough]];
  case 3:
    break;
  default:
    cerr << "Usage: solve_pi <B> <A> [<limit=32>]" << endl;
    return 1;
  }
  try {
    auto [n, a, b, c] = solve_pi(BigInt(argv[2]), BigInt(argv[1]), limit);
    cout << ans_to_latex_pi(n, n, a, b, c) << endl;
  } catch (const std::runtime_error &e) {
    cerr << "std::runtime_error: " << e.what() << endl;
    return 1;
  } catch (...) {
    cerr << "An unexpected error occurred." << endl;
    return 3;
  }
  return 0;
}
