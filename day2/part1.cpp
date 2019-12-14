#include "../util.hpp"

enum class op_codes : short {
	add = 1,
	mul = 2,
	hlt = 99
};

int main() {
	std::ifstream f("../day2/day2.txt");
	std::vector<int> prog = util::split<int>(std::string{ std::istreambuf_iterator<char>{ f }, {} }, ",");
	prog[1] = 12;
	prog[2] = 2;
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
	std::cout << "Result: " << prog[0];
	return 0;
}