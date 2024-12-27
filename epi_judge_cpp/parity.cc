#include "test_framework/generic_test.h"
short Parity(unsigned long long x) {
  // Hemmingway sum
  // 0101 = x5
  // 1010 = xa
  unsigned long long l = (x >> 1) & 0x5555555555555555;
  unsigned long long r = x & 0x5555555555555555;
  x = l + r;
  // 0011 = x3
  // 1100 = xc
  l = (x >> 2) & 0x3333333333333333;
  r = x & 0x3333333333333333;
  x = l + r;
  // 0000 1111 = x0f
  l = (x >> 4) & 0x0f0f0f0f0f0f0f0f;
  r = x & 0x0f0f0f0f0f0f0f0f;
  x = l + r;
  // x00ff
  l = (x >> 8) & 0x00ff00ff00ff00ff;
  r = x & 0x00ff00ff00ff00ff;
  x = l + r;
  // x0000ffff
  l = (x >> 16) & 0x0000ffff0000ffff;
  r = x & 0x0000ffff0000ffff;
  x = l + r;
  // x00000000ffffffff
  l = (x >> 32) & 0x00000000ffffffff;
  r = x & 0x00000000ffffffff;
  x = l + r;

  return x & 1;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x"};
  return GenericTestMain(args, "parity.cc", "parity.tsv", &Parity,
                         DefaultComparator{}, param_names);
}
