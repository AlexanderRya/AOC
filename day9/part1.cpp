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
template <typename Ty>
class res_vector {
	Ty* ptr = nullptr;
	usize sze = 0;
public:
	explicit res_vector(const std::vector<Ty>& vec) {
		ptr = static_cast<Ty*>(::operator new[]((sze = vec.size()) * sizeof(Ty)));
		for (auto i = 0; i < vec.size(); ++i) {
			*static_cast<Ty*>(::operator new[](sizeof(Ty), &ptr[i])) = Ty(vec[i]);
		}
	}
	res_vector(res_vector& vec) {
		ptr = static_cast<Ty*>(::operator new[]((sze = vec.size()) * sizeof(Ty)));
		for (auto i = 0; i < vec.size(); ++i) {
			*static_cast<Ty*>(::operator new[](sizeof(Ty), &ptr[i])) = Ty(vec[i]);
		}
	}
	usize size() const {
		return sze;
	}
	Ty& operator [](const usize idx) {
		if (idx >= sze) {
			auto temp = static_cast<Ty*>(::operator new[]((idx + 1024) * sizeof(Ty)));
			std::uninitialized_copy(ptr, ptr + sze, temp);
			std::fill(temp + sze, temp + idx + 1024, Ty{});
			for (auto i = 0; i < sze; ++i) {
				std::destroy_at(ptr + i);
			}
			::operator delete[](ptr);
			ptr = temp;
			sze = idx + 1024;
			std::cout << "out of bounds, new size: " << sze << " | index was: " << idx << "\n";
		}
		return ptr[idx];
	}
	~res_vector() {
		for (auto i = 0; i < sze; ++i) {
			std::destroy_at(ptr + i);
		}
		::operator delete[](ptr);
	}
	Ty* begin() {
		return ptr;
	}
	Ty* end() {
		return ptr + sze;
	}
};
class program {
	u32 ip = 0;
	u32 rel_base = 0;
	std::vector<i64> prog;
public:
	bool halt = false;
	explicit program(std::vector<i64> prog) : prog(prog) {}
	i64& get_val(const i64 mode, const size_t i) {
		switch (mode) {
			case 0: {
				return prog[prog[i]];
			}
			case 1: {
				return prog[i];
			}
			case 2: {
				return prog[prog[i] + rel_base];
			}
			default: {
				std::cout << "Unknown mode: " << mode << "\n";
				throw std::runtime_error("Unknown mode");
			}
		}
	}
	i64 run(std::vector<i64> settings) {
		i64 out = 0;
		while (ip < prog.size()) {
			i64 mode_1 = prog[ip] / 100 % 10;
			i64 mode_2 = prog[ip] / 1000 % 10;
			i64 mode_3 = prog[ip] / 10000 % 10;
			switch (prog[ip] % 100) {
				case 1: {
					get_val(mode_3, ip + 3) = get_val(mode_1, ip + 1) + get_val(mode_2, ip + 2);
					ip += 4;
					break;
				}
				case 2: {
					get_val(mode_3, ip + 3) = get_val(mode_1, ip + 1) * get_val(mode_2, ip + 2);
					ip += 4;
					break;
				}
				case 3: {
					if (settings.empty()) {
						return out;
					}
					get_val(mode_1, ip + 1) = settings.back();
					settings.pop_back();
					ip += 2;
					break;
				}
				case 4: {
					std::cout << (out = get_val(mode_1, ip + 1)) << "\n";
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
						get_val(mode_3, ip + 3) = 1;
					} else {
						get_val(mode_3, ip + 3) = 0;
					}
					ip += 4;
					break;
				}
				case 8: {
					if (get_val(mode_1, ip + 1) == get_val(mode_2, ip + 2)) {
						get_val(mode_3, ip + 3) = 1;
					} else {
						get_val(mode_3, ip + 3) = 0;
					}
					ip += 4;
					break;
				}
				case 9: {
					rel_base += get_val(mode_1, ip + 1);
					ip += 2;
					break;
				}
				case 99: {
					halt = true;
					return out;
				}
				default: {
					std::cout << "Error, unknown opcode " << prog[ip] % 100 << "\n";
					return -1;
				}
			}
		}
		return out;
	}
};
int main() {
	std::ifstream f("../day9/day9.txt");
	std::vector<i64> prog = util::split<i64>(std::string{ std::istreambuf_iterator{ f }, {}}, ",");
	prog.resize(20000, 0);
	program(prog).run({ 2 });
	return 0;
}
