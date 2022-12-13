#include "./Constants/pch.h"
#include "./Utils/optimize.cpp"

using namespace std;

int main(int argc, char** argv) {
  cout << "running with " << argc << " arguments\n";
  if (argc != 2) {
    cout << "Usage: " << argv[0] << " <input file>";
    return 0;
  }
  const char* input_file_path = argv[1];
  Character x(PYRO);
  Enemy y;
  Optimize::optimize(x, y);

  /**
   * TODO:
   * Parse input to unordered_map representing JSON
   * Pass unordered_map into optimizer
   * Optimizer returns a JSON representation of the result
   * Print out JSON result
   */

  return 0;
}