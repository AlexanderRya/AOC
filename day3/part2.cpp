#include "../util.hpp"

struct point {
	int x, y;
	bool operator ==(const point& rhs) const {
		return x == rhs.x && y == rhs.y;
	}
};

struct hash_point {
	size_t operator() (const point& p) const {
		return std::hash<int>()(p.x) ^ std::hash<int>()(p.y);
	}
};

int main() {
	std::ifstream f("../day3/day3.txt");
	std::vector<std::tuple<char, int>> wire1, wire2;
	auto wires = util::split(std::string{ std::istreambuf_iterator<char>{ f }, {} }, "\n");
	for (const auto& wire : util::split(wires[0], ",")) {
		wire1.emplace_back(wire[0], std::stoi(std::string{ wire.begin() + 1, wire.end() }));
	}
	for (const auto& wire : util::split(wires[1], ",")) {
		wire2.emplace_back(wire[0], std::stoi(std::string{ wire.begin() + 1, wire.end() }));
	}
	std::unordered_map<point, int, hash_point> wirev1, wirev2;
	point p1{}, p2{};
	int steps = 0;
	for (const auto& [dir, length] : wire1) {
		switch (dir) {
			case 'R':
				for (int i = 0; i < length; ++i) {
					wirev1[point{ ++p1.x, p1.y }] = ++steps;
				}
				break;
			case 'L':
				for (int i = 0; i < length; ++i) {
					wirev1[point{ --p1.x, p1.y }] = ++steps;
				}
				break;
			case 'U':
				for (int i = 0; i < length; ++i) {
					wirev1[point{ p1.x, ++p1.y }] = ++steps;
				}
				break;
			case 'D':
				for (int i = 0; i < length; ++i) {
					wirev1[point{ p1.x, --p1.y }] = ++steps;
				}
				break;
			default:
				__builtin_unreachable();
		}
	}
	steps = 0;
	for (const auto& [dir, length] : wire2) {
		switch (dir) {
			case 'R':
				for (int i = 0; i < length; ++i) {
					wirev2[point{ ++p2.x, p2.y }] = ++steps;
				}
				break;
			case 'L':
				for (int i = 0; i < length; ++i) {
					wirev2[point{ --p2.x, p2.y }] = ++steps;
				}
				break;
			case 'U':
				for (int i = 0; i < length; ++i) {
					wirev2[point{ p2.x, ++p2.y }] = ++steps;
				}
				break;
			case 'D':
				for (int i = 0; i < length; ++i) {
					wirev2[point{ p2.x, --p2.y }] = ++steps;
				}
				break;
			default:
				__builtin_unreachable();
		}
	}
	int closest = wirev1.size() + wirev2.size(), least = wirev1.size() + wirev2.size();
	for (const auto& [pos, steps] : wirev1) {
		if (wirev2.count(pos) != 0) {
			closest = std::min(closest, std::abs(pos.x) + std::abs(pos.y));
			least = std::min(least, wirev1[pos] + wirev2[pos]);
		}
	}
	std::cout << "Least steps to intersection: " << least << "\n";
	return 0;
}