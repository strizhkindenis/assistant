#include <stdexcept>
#include <limits>

int* concat_rows(
	const int* a, size_t n, size_t m1, 
	const int* b, size_t m2
) {
	if (a == nullptr or b == nullptr or n == 0) {
		throw std::invalid_argument("nullptr");
	}
	if (m1 > std::numeric_limits<size_t>::max() - m2) {
		throw std::overflow_error("m1 + m2");
	}	
	const auto new_m = m1 + m2;
	if (new_m > std::numeric_limits<size_t>::max() / n) {
		throw std::overflow_error("(m1 + m2) * n");
	}	
	auto c = new int[new_m * n]{};
	for (size_t i = 0; i < n; i++) {
		for (size_t j = 0; j < m1; j++) {
			c[new_m * i + j] = a[i * m1 + j];
		}
		for (size_t j = m1; j < new_m; j++) {
			c[new_m * i + j] = b[i * m2 + (j - m1)];
		}
	}
	return c;	
}

int main() {}
