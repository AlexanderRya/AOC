#include "../util.hpp"

long calc_fuel(const long mass) {
	if (mass <= 0) {
		return 0;
	}
	return mass + calc_fuel(long(std::ceil(mass / 3)) - 2);
}

int main() {
	std::ifstream f("../day1/day1.txt");
	std::vector<int> masses = util::split<int>(std::string{ std::istreambuf_iterator<char>{ f }, {} }, "\n");
	long total = 0;
	for (const auto& mass : masses) {
		total += calc_fuel(long(std::ceil(mass / 3)) - 2);
	}
	std::cout << "Total: " << total;
	return 0;
}