#include "../util.hpp"

int main() {
	std::ifstream in("../day5/day5.txt");
	std::vector<int> prog{ util::split<int>(std::string{ std::istreambuf_iterator{ in }, {} }, ",") };
	int ip = 0;
	auto op_code = (prog[ip] % 10) + (((prog[ip] / 10) % 10) * 10);
	while (op_code != 99) {
		int mode_1 = (prog[ip] / 100) % 10;
		int mode_2 = (prog[ip] / 1000) % 10;
		switch (op_code) {
			case 1: {
				prog[prog[ip + 3]] = prog[mode_1 == 1 ? ip + 1 : prog[ip + 1]] + prog[mode_2 == 1 ? ip + 2 : prog[ip + 2]];
				ip += 4;
				break;
			}
			case 2: {
				prog[prog[ip + 3]] = prog[mode_1 == 1 ? ip + 1 : prog[ip + 1]] * prog[mode_2 == 1 ? ip + 2 : prog[ip + 2]];
				ip += 4;
				break;
			}
			case 3: {
				prog[prog[ip + 1]] = 5;
				ip += 2;
				break;
			}
			case 4: {
				std::cout << prog[mode_1 == 1 ? ip + 1 : prog[ip + 1]] << "\n";
				ip += 2;
				break;
			}
			case 5: {
				if (prog[mode_1 == 1 ? ip + 1 : prog[ip + 1]] != 0) {
					ip = prog[mode_2 == 1 ? ip + 2 : prog[ip + 2]];
				} else {
					ip += 3;
				}
				break;
			}
			case 6: {
				if (prog[mode_1 == 1 ? ip + 1 : prog[ip + 1]] == 0) {
					ip = prog[mode_2 == 1 ? ip + 2 : prog[ip + 2]];
				} else {
					ip += 3;
				}
				break;
			}
			case 7: {
				if (prog[mode_1 == 1 ? ip + 1 : prog[ip + 1]] < prog[mode_2 == 1 ? ip + 2 : prog[ip + 2]]) {
					prog[prog[ip + 3]] = 1;
				} else {
					prog[prog[ip + 3]] = 0;
				}
				ip += 4;
				break;
			}
			case 8: {
				if (prog[mode_1 == 1 ? ip + 1 : prog[ip + 1]] == prog[mode_2 == 1 ? ip + 2 : prog[ip + 2]]) {
					prog[prog[ip + 3]] = 1;
				} else {
					prog[prog[ip + 3]] = 0;
				}
				ip += 4;
				break;
			}
			default:
				__builtin_unreachable();
		}
		op_code = (prog[ip] % 10) + (((prog[ip] / 10) % 10) * 10);
	}
	return 0;
}

