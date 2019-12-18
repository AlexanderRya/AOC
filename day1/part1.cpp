#include "../util.hpp"
int main() {
	std::ifstream f("../day1/day1.txt");
	std::vector<int> masses = util::split<int>(std::string{ std::istreambuf_iterator<char>{ f }, {}}, "\n");
	int total = 0;
	for (const auto& mass : masses) {
		total += int(std::ceil(mass / 3)) - 2;
	}
	std::cout << "Total: " << total;
	return 0;
}