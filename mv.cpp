#include <algorithm>
#include <cstddef>
#include <iostream>

class Vec {
public:
  Vec(size_t size) : data_(new int[size]{}), size_(size), len_(0) {
    std::cerr << "base ctr Vec(" << size << ")\n";
  }
  Vec(const Vec& other) : Vec(other.size()) {
	extend(other);
    std::cerr << "copy ctr Vec(" << other << ")\n";
  } 

  ~Vec() {
    delete[] data_;
    std::cerr << "~Vec()\n";
  }

  size_t size() const { return size_; }
  size_t len() const { return len_; }
  bool filled() const { return size() == len(); }

  int* begin() { return data_; };
  const int* begin() const { return data_; };
  int* end() { return begin() + len(); };
  const int* end() const { return begin() + len(); }; 

  int &get(size_t i) { return data_[i]; }
  const int &get(size_t i) const { return data_[i]; }
  int &first() { return get(0); }
  const int &first() const { return get(0); }
  int &last() { return get(len() - 1); };
  const int &last() const { return get(len() - 1); };

  void push(int x) {
    if (filled()) {
      grow();
    }
    len_inc();
    last() = x;
  }

  void grow() {
    const auto nsize = size_ == 0 ? 10 : size_ * 2;
    auto ndata = new int[nsize];
    std::copy(begin(), end(), ndata);
    delete[] data_;
    data_ = ndata;
    size_ = nsize;
  }

  void extend(const Vec& other) {
	const auto nsize = len() + other.len();
    if (nsize >= size()) {
		grow(); // TODO: up to size
    }
    std::copy(end(),end()+other.len(),other.begin());
  }

  Vec concat(const Vec &other) {
	return Vec(0)	;
  }

  friend std::ostream &operator<<(std::ostream &os, const Vec &v) { 
	os << "Vec { size : " << v.size() << " , len : " << v.len() << " , { ";
	if (v.len() == 0) {
		return os << "} }";
	}
    for (auto p = v.begin(); p < v.end() - 1; p++) {
		os << *p << ", ";
	}
	return os << *(v.end() - 1);
}

private:
  int *data_;
  size_t len_;
  size_t size_;

  void len_inc() { len_ += 1; }
};

int main() {
  auto v = Vec(2);
  std::cout << v;
  v.push(5);
  std::cout << v;
  v.push(6);
  std::cout << v;
  // закончилась память
  v.push(7);
  std::cout << v;
}
