#include <string>

#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
using std::string;

string IntToString(int x) {
  // Note we could precompute the expected size here using the most significant bit and the fact that ln(10)/ln(2)=0.3010,
  // meaning that for each 1 binary digit we have 0.3010 decimal digits, which from a 64 bit number results in about 19.26
  // decimal digits. But it's probably not worth it for this.
  std::string rv;

  // Deal with the sign
  if (x < 0) {
    rv.push_back('-');
  }
  else
    rv.push_back('+');

  // Ensure we alwasy append a digit (even if zero)
  // Note: modulo preserves the sign, so ensure we take the absolute value.
  do {
    rv.push_back(std::abs(x % 10) + '0');
    x /= 10;
  } while (x != 0);

  // Reverse the digits as we've appended them in reverse order
  char* s = &rv[1];
  char* e = &rv[0] + rv.size() - 1;

  while (s < e) {
    std::swap(*s++, *e--);
  }

  return rv;
}
int StringToInt(const string& s) {
  int num = 0, sign = 1;

  const char* c = &s[0];
  const char* const e = c + s.size();

  if (*c == '-') {
    sign = -1; ++c;
  } else if (*c == '+') {
    sign = 1; ++c;
  }

  for (; c != e; ++c) {
    num *= 10;
    num += *c - '0';
  }

  return sign * num;
}
void Wrapper(int x, const string& s) {
  if (stoi(IntToString(x)) != x) {
    throw TestFailure("Int to string conversion failed");
  }

  if (StringToInt(s) != x) {
    throw TestFailure("String to int conversion failed");
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x", "s"};
  return GenericTestMain(args, "string_integer_interconversion.cc",
                         "string_integer_interconversion.tsv", &Wrapper,
                         DefaultComparator{}, param_names);
}
