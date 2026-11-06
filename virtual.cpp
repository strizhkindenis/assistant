#include <cstddef>
#include <iostream>
#include <limits>
#include <stdexcept>

class Parser {
public:
  virtual void next_n(const int n) noexcept = 0;
  virtual bool is_err() const noexcept = 0;
  virtual void print(std::ostream &out, std::ostream &err) const noexcept = 0;
};

class CounterSubMax : public Parser {
public:
  CounterSubMax() noexcept
      : max_(std::numeric_limits<int>::min()), max_count_(0), sub_max_(0),
        sub_max_count_(0), is_overflow_(false) {}

  void next_n(const int n) noexcept override {
    if (n == max_) {
      max_increment();
    } else if (n > max_) {
      sub_max_count_ = max_count_;
      max_count_ = 1;
      sub_max_ = max_;
      max_ = n;
    } else if (n > sub_max_) {
      sub_max_ = n;
      sub_max_count_ = 1;
    } else if (n == sub_max_) {
      sub_max_increment();
    }
  }

  bool is_err() const noexcept override { return is_overflow_; }

  void print(std::ostream &out, std::ostream &err) const noexcept override {
    if (is_err()) {
      err << "CountSubMax: overflow" << std::endl;
    } else {
      out << sub_max_count_ << std::endl;
    }
  }

private:
  int max_;
  size_t max_count_;
  int sub_max_;
  size_t sub_max_count_;
  bool is_overflow_;

  void increment(size_t &n) noexcept {
    if (is_overflow_) {
      return;
    }
    if (n == std::numeric_limits<size_t>::max()) {
      is_overflow_ = true;
      return;
    }
    n++;
  }

  void max_increment() noexcept { increment(max_count_); }

  void sub_max_increment() noexcept { increment(sub_max_count_); }
};

class Runner {
public:
  Runner(Parser &a, Parser &b) : a_(a), b_(b) {}

  int run(std::istream &in, std::ostream &out, std::ostream &err) {
    int n = 0;
    while (std::cin >> n && n != 0) {
      a_.next_n(n);
      b_.next_n(n);
      if (a_.is_err() and b_.is_err()) {
        break;
      }
    }
    if (not std::cin) {
      err << "invalid input" << std::endl;
      return 1;
    }
    a_.print(out, err);
    b_.print(out, err);
    if (a_.is_err() or b_.is_err()) {
      return 2;
    }
    return 0;
  }

private:
  Parser &a_;
  Parser &b_;
};

int main() {
  auto smc_a = CounterSubMax();
  auto smc_b = CounterSubMax();
  return Runner(smc_a, smc_b).run(std::cin, std::cout, std::cerr);
}
