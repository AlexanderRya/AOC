#include "../util.hpp"
std::vector<std::array<i64, 5>> gen_combinations() {
	std::vector<std::array<i64, 5>> res;
	std::array<i64, 5> arr{
			5, 6, 7, 8, 9
	};
	do {
		res.emplace_back(arr);
	} while (std::next_permutation(arr.begin(), arr.end()));
	return res;
}
int main() {
	std::ifstream in("../day7/day7.txt");
	std::vector<int> prog{ util::split<int>(std::string{ std::istreambuf_iterator{ in }, {}}, ",") };
	auto orig_prog = prog;
	auto combinations = gen_combinations();
	i64 max = 0;
	i64 out = 0;
	u32 ip = 0;
	auto op_code = 0;
	for (const auto& amps : combinations) {
		for (int i = 0; i < 5; ++i) {
			std::stack<i64> settings{
					{ out, amps[i] }
			};
			while (op_code != 99) {
				op_code = (prog[ip] % 10) + (((prog[ip] / 10) % 10) * 10);
				int mode_1 = (prog[ip] / 100) % 10;
				int mode_2 = (prog[ip] / 1000) % 10;
				std::cout << ip << "\n";
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
						if (settings.empty()) {
							prog[prog[ip + 1]] = out;
							ip += 2;
							break;
						}
						prog[prog[ip + 1]] = settings.top();
						settings.pop();
						ip += 2;
						break;
					}
					case 4: {
						out = prog[mode_1 == 1 ? ip + 1 : prog[ip + 1]];
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
					case 99: {
						if (i == 4) {
							i = 5;
						}
						break;
					}
					default:
						__builtin_unreachable();
				}
			}
			prog = orig_prog;
			if (out > max) {
				max = out;
			}
		}
	}
	std::cout << "Output: " << max;
	return 0;
}
