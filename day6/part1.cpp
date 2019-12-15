#include "../util.hpp"

std::string find_orbits(const std::string& str,
						const std::vector<std::tuple<std::string, std::string>>& orbits) {
	return std::get<0>(*std::find_if(orbits.begin(), orbits.end(), [&str](const auto& obj) {
		return str == std::get<1>(obj);
	}));
}

u64 calc_orbits(const std::string& str,
				const std::vector<std::tuple<std::string, std::string>>& orbits,
				std::unordered_map<std::string, u64>& total) {
	if (str == "COM") {
		return 0;
	}
	if (total.contains(str)) {
		return total[str];
	}
	auto obj_orb = calc_orbits(find_orbits(str, orbits), orbits, total) + 1;
	total.emplace(str, obj_orb);
	return obj_orb;
}

int main() {
	std::ifstream in("../day6/day6.txt");
	std::vector<std::tuple<std::string, std::string>> orbits;
	std::unordered_map<std::string, u64> total;
	{
		std::vector<std::string> f{ util::split(std::string{ std::istreambuf_iterator{ in }, {}}, "\n") };
		for (const auto& each : f) {
			auto t = util::split(each, ")");
			orbits.emplace_back(t[0], t[1]);
		}
	}
	int direct = 0;
	for (const auto& [first, second] : orbits) {
		auto _ = calc_orbits(second, orbits, total);
	}
	std::cout << "Total: " << std::accumulate(total.begin(), total.end(), 0ull, [](const u64 lhs, const std::pair<std::string, u64> rhs) {
		return lhs + rhs.second;
	});
	return 0;
}