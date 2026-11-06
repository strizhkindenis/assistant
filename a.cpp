#include <iostream>

struct A {
  int n;
};

int main() {
	auto a = new A { 37 };
	std::cout << a->n << std::endl;
	delete a;
}
