#include "../util.hpp"

bool meets_criteria(int n) {
	std::array<int, 6> digits{};
	std::array<int, 10> pairs{};
	for (auto i = 5; i >= 0; --i) {
		digits[i] = n % 10;
		n /= 10;
	}
	bool pair = false;
	for (auto i = 0; i < digits.size() - 1; ++i) {
		if (digits[i] > digits[i + 1]) {
			return false;
		}
	}
	for (const auto digit : digits) {
		++pairs[digit % 10];
	}
	for (const auto p : pairs) {
		if (p == 2) {
			pair = true;
		}
	}
	return pair;
}
int main() {
	int count = 0;
	for (int i = 353096; i < 843212; ++i) {
		if (meets_criteria(i)) {
			++count;
		}
	}
	std::cout << "Result: " << count;
	return 0;
}