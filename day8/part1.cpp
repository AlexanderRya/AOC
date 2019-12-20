#include "../util.hpp"

int main() {
	std::ifstream f("../day8/day8.txt");
	std::string raw_data{ std::istreambuf_iterator{ f }, {}};
	i32 result = 0;
	i32 min_0 = std::numeric_limits<i32>::max();
	for (auto i = 0; i < raw_data.size();) {
		std::array<int, 3> digits{};
		for (auto j = 0; j < 150; ++j, ++i) {
			++digits[raw_data[i] - '0'];
		}
		if (min_0 > digits[0]) {
			min_0 = digits[0];
			result = digits[1] * digits[2];
		}
	}
	std::cout << result;
	return 0;
}