#include <cstddef>
#include <iostream>
#include <limits>
#include <stdexcept>

size_t checked_mul(size_t a, size_t b) {
  if (b != 0 and a > std::numeric_limits<size_t>::max() / b) {
    throw std::overflow_error("");
  }
  return a * b;
}

class Matrix {
public:
  Matrix(size_t rows, size_t cols)
      : rows_(rows), cols_(cols), data_(new float[checked_mul(rows, cols)] {}) {}
  ~Matrix() { delete[] data_; }

  float& get(size_t i, size_t j) {
    check_index(i, j);
    return data_[get_index(i, j)];
  }

  float* operator[](size_t i) {
    return data_ + (i * cols_);
  }

  const float& get(size_t i, size_t j) const {
    check_index(i, j);
    return data_[get_index(i, j)];
  }

  const float* operator[](size_t i) const {
    return data_ + (i * cols_);
  }

  size_t rows() const noexcept { return rows_; }
  size_t cols() const noexcept { return cols_; }

private:
  void check_index(size_t i, size_t j) const {
    if (i >= rows() or j >= cols()) {
      throw std::invalid_argument("");
    }
  }

  size_t get_index(size_t i, size_t j) const noexcept {
		return i * cols_ + j;
  }

  size_t rows_;
  size_t cols_;
  float *data_;
};

int main() {
  auto m = Matrix(3, 4);
  std::cout << m.rows() << " x " << m.cols() << std::endl;
  std::cout << "m[1, 2]: " << m.get(1, 2) << std::endl;
  m.get(1,2) = 5;
  std::cout << "m[1, 2]: " << m[1][2] << std::endl;
  // std::cout << "m[1, 2]: " << m.get(1, 2) << std::endl;
}
