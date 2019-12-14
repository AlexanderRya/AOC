#include "../util.hpp"

enum class op_codes : short {
	add = 1,
	mul = 2,
	hlt = 99
};

int main() {
	std::ifstream f("../day2/day2.txt");
	std::vector<int> orig_prog = util::split<int>(std::string{ std::istreambuf_iterator<char>{ f }, {} }, ",");
	auto prog = orig_prog;
	for (int i = 0; i < 99; ++i) {
		for (int j = 0; j < 99; ++j) {
			prog[1] = i;
			prog[2] = j;
			auto op = op_codes(prog[0]);
			int ip = 0;
			while (op != op_codes::hlt) {
				switch (op) {
					case op_codes::add:
						prog[prog[ip + 3]] = prog[prog[ip + 1]] + prog[prog[ip + 2]];
						op = op_codes(prog[ip += 4]);
						break;
					case op_codes::mul:
						prog[prog[ip + 3]] = prog[prog[ip + 1]] * prog[prog[ip + 2]];
						op = op_codes(prog[ip += 4]);
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