#include "../util.hpp"

int main() {
	std::ifstream f("../day2/day2.txt");
	std::vector<int> orig_prog = util::split<int>(std::string{ std::istreambuf_iterator<char>{ f }, {}}, ",");
	auto prog = orig_prog;
	for (int i = 0; i < 99; ++i) {
		for (int j = 0; j < 99; ++j) {
			prog[1] = i;
			prog[2] = j;
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
			if (prog[0] == 19690720) {
				std::cout << "Result: " << 100 * i + j;
				return 0;
			}
			prog = orig_prog;
		}
	}
	return -1;
}