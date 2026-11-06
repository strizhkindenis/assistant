#include <cstddef>
#include <iostream>

int parse_int(const char *s) {
  int n = 0;
  for (size_t i = 0; s[i] != '\0'; i++) {
    if (s[i] < '0' || s[i] > '9') {
      throw 1;
    }
    n = n * 10 + static_cast<int>(s[i] - '0');
  }
  return n;
}

int main(int argc, char **argv) {
  std::cout << (3 == 5 ? "yes" : "no") << std::endl;
  if (argc != 3) {
    return 1;
  }
  try {
    std::cout << parse_int(argv[1]) + parse_int(argv[2]) << std::endl;
  } catch (const int e) {
    return e;
  }
}
