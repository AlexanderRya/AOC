#include "../util.hpp"

std::string find_orbits(const std::string& str,
						const std::vector<std::tuple<std::string, std::string>>& orbits) {
	return std::get<0>(*std::find_if(orbits.begin(), orbits.end(), [&str](const auto& obj) {
		return str == std::get<1>(obj);
	}));
}

void calc_orbits(
		const std::string& str,
		const std::vector<std::tuple<std::string, std::string>>& orbits,
		std::vector<std::tuple<std::string, std::string>>& system) {
	if (str == "COM") {
		return;
	}
	auto n_obj = find_orbits(str, orbits);
	system.emplace_back(str, find_orbits(str, orbits));
	calc_orbits(n_obj, orbits, system);
}

std::string find_common(
		const std::vector<std::tuple<std::string, std::string>>& you,
		const std::vector<std::tuple<std::string, std::string>>& san) {
	for (const auto& [key, val] : you) {
		for (const auto& [skey, sval] : san) {
			if (val == sval) {
				return val;
			}
		}
	}
	return {};
}

int main() {
	std::ifstream in("../day6/day6.txt");
	std::vector<std::tuple<std::string, std::string>> orbits, you, san;
	for (const auto& each : util::split(std::string{ std::istreambuf_iterator<char>{ in }, {} }, "\n")) {
		auto t = util::split(each, ")");
		orbits.emplace_back(t[0], t[1]);
	}
	calc_orbits(find_orbits("YOU", orbits), orbits, you);
	calc_orbits(find_orbits("SAN", orbits), orbits, san);
	auto common = find_common(you, san);
	int distance = 0;
	for (const auto& [key, val] : you) {
		if (key == common) {
			break;
		}
		++distance;
	}
	for (const auto& [key, val] : san) {
		if (key == common) {
			break;
		}
		++distance;
	}
	std::cout << distance;
	return 0;
}
