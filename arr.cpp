#include <cstddef>
#include <iostream>

const std::size_t max_size = 100;

void read_n(int *arr, const std::size_t arr_len) {
  for (std::size_t i = 0; i < arr_len; i++) {
    if (not(std::cin >> arr[i])) {
      throw 1;
    }
  }
}

void print_n(int *arr, const std::size_t arr_len) {
  for (std::size_t i = 0; i < arr_len; i++) {
    std::cout << arr[i] << " ";
  }
  std::cout << std::endl;
}

int main() {
  int a[max_size]{};
  int *b = nullptr;
  try {
    b = new int[max_size]{};
    std::cout << "reading free store" << std::endl;
    read_n(b, 3);
    std::cout << "reading stack" << std::endl;
    read_n(a, 3);
  } catch (const int e) {
    delete[] b;
    return e;
  }
  std::cout << "printing free store" << std::endl;
  print_n(b, 3);
  std::cout << "printing stack" << std::endl;
  print_n(a, 3);
  delete[] b;
}
