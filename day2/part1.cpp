#include "../util.hpp"

int main() {
	std::ifstream f("../day2/day2.txt");
	std::vector<int> prog = util::split<int>(std::string{ std::istreambuf_iterator<char>{ f }, {}}, ",");
	prog[1] = 12;
	prog[2] = 2;
	auto op = prog[0], ip = 0;
	while (op != 99) {
		switch (op) {
			case 1:
				prog[prog[ip + 3]] = prog[prog[ip + 1]] + prog[prog[ip + 2]];
				op = prog[ip += 4];
				break;
			case 2:
				prog[prog[ip + 3]] = prog[prog[ip + 1]] * prog[prog[ip + 2]];
				op = prog[ip += 4];
				break;
			default:
				return -1;
		}
	}
	std::cout << "Result: " << prog[0];
	return 0;
}