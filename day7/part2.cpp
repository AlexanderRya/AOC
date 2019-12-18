#include "../util.hpp"

std::vector<std::array<i32, 5>> gen_combinations() {
	std::vector<std::array<i32, 5>> res;
	std::array<i32, 5> arr{
			5, 6, 7, 8, 9
	};
	do {
		res.emplace_back(arr);
	} while (std::next_permutation(arr.begin(), arr.end()));
	return res;
}
class program {
	std::vector<int> prog;
public:
	bool halt = false;
	explicit program(const std::vector<int>& prog) : prog(prog) {}
	i32& get_val(const i32 mode, const size_t ip) {
		return mode == 1 ? prog[ip] : prog[prog[ip]];
	}
	i64 run(std::vector<i64> settings) {
		u32 ip = 0;
		i64 out = 0;
		int p = 0;
		while (ip < prog.size()) {
			int mode_1 = prog[ip] / 100 % 10;
			int mode_2 = prog[ip] / 1000 % 10;
			switch (prog[ip] % 100) {
				case 1: {
					prog[prog[ip + 3]]
						= get_val(mode_1, ip + 1) + get_val(mode_2, ip + 2);
					ip += 4;
					break;
				}
				case 2: {
					prog[prog[ip + 3]]
						= get_val(mode_1, ip + 1) * get_val(mode_2, ip + 2);
					ip += 4;
					break;
				}
				case 3: {
					if (settings.empty()) {
						return out;
					}
					prog[prog[ip + 1]] = settings.back();
					settings.pop_back();
					ip += 2;
					break;
				}
				case 4: {
					out = get_val(mode_1, ip + 1);
					ip += 2;
					break;
				}
				case 5: {
					if (get_val(mode_1, ip + 1) != 0) {
						ip = get_val(mode_2, ip + 2);
					} else {
						ip += 3;
					}
					break;
				}
				case 6: {
					if (get_val(mode_1, ip + 1) == 0) {
						ip = get_val(mode_2, ip + 2);
					} else {
						ip += 3;
					}
					break;
				}
				case 7: {
					if (get_val(mode_1, ip + 1) < get_val(mode_2, ip + 2)) {
						prog[prog[ip + 3]] = 1;
					} else {
						prog[prog[ip + 3]] = 0;
					}
					ip += 4;
					break;
				}
				case 8: {
					if (get_val(mode_1, ip + 1) == get_val(mode_2, ip + 2)) {
						prog[prog[ip + 3]] = 1;
					} else {
						prog[prog[ip + 3]] = 0;
					}
					ip += 4;
					break;
				}
				case 99: {
					halt = true;
					return out;
				}
				default:
					std::cout << "Error, unknown opcode";
			}
		}
		return out;
	}
};
int main() {
	std::ifstream f("../day7/day7.txt");
	std::vector<int> prog = util::split<int>(std::string{ std::istreambuf_iterator{ f }, {}}, ",");
	std::vector<program> v(5, program(prog));
	std::array<int, 5> amps{
			9, 8, 7, 6, 5
	};
	i64 out = 0;
	for (int i = 0; i < 5; ++i) {
		out = v[i].run({ amps[i], out });
	}
	while (!v[4].halt) {
		for (int i = 0; i < 5; ++i) {
			out = v[i].run({ out });
		}
	}
	std::cout << out << "\n";
	return 0;
}
