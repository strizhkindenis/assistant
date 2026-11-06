#include <cstddef>
#include <iostream>
#include <limits>
#include <stdexcept>

size_t checked_mul(size_t a, size_t b) {
  if (a != 0 && b > std::numeric_limits<size_t>::max() / a) {
    throw std::invalid_argument("");
  }
  return a * b;
}

class Matrix { // float
public:
  Matrix(size_t rows, size_t cols)
      : rows_(rows), cols_(cols), data_(new float[checked_mul(rows, cols)]{}) {}

  Matrix(const Matrix &m) : Matrix(m.rows_, m.cols_) {
    for (size_t i = 0; i < rows_ * cols_; i++) {
      data_[i] = m.data_[i];
    }
  }

  float &get(size_t i, size_t j) { return data_[get_checked_index(i, j)]; }

  const float &get(size_t i, size_t j) const {
    return data_[get_checked_index(i, j)];
  }

  friend std::ostream &operator<<(std::ostream &out, const Matrix &m) {
    const auto rows = m.rows();
    const auto cols = m.cols();
    out << "= " << rows << " x " << cols << " =\n";
    if (rows == 0 or cols == 0) {
      return out;
    }
    for (size_t i = 0; i < rows - 1; i++) {
      out << m.get(i, 0);
      for (size_t j = 1; j < cols; j++) {
        out << " " << m.get(i, j);
      }
      out << '\n';
    }
    out << m.get(rows - 1, 0);
    for (size_t j = 1; j < cols; j++) {
      out << " " << m.get(rows - 1, j);
    }
    return out;
  }

  size_t rows() const noexcept { return rows_; }
  size_t cols() const noexcept { return cols_; }

  ~Matrix() { delete[] data_; }

private:
  size_t get_checked_index(size_t i, size_t j) const {
    if (i >= rows_ or j >= cols_) {
      throw std::invalid_argument("");
    }
    return i * cols_ + j;
  }

  size_t rows_;
  size_t cols_;
  float *data_;
};

int main() {
  auto m1 = Matrix(2, 3);
  m1.get(1, 2) = 8;
  m1.get(0, 0) = 5;
  m1.get(0, 1) = 3;
  std::cout << m1 << std::endl;
}
