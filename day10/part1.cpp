#include "../util.hpp"

struct point {
	int x, y;
};
int main() {
	std::ifstream f("../day10/day10.txt");
	std::vector<std::string> map = util::split(std::string{ std::istreambuf_iterator{ f }, {}}, "\n");
	std::vector<point> asteroids;
	point p{};
	for (const auto& line : map) {
		for (const auto each : line) {
			if (each == '#') {
				asteroids.emplace_back(p);
			}
			++p.x;
		}
		++p.y;
		p.x = 0;
	}
	auto max = 0;
	for (const auto&[x, y] : asteroids) {
		auto current = 0;
		for (const auto&[sx, sy] : asteroids) {
			if (x == sx && y == sy) {
				continue;
			}
			bool is_clear = true;
			auto dist_x = sx - x, dist_y = sy - y;
			auto gcd = std::gcd(dist_x, dist_y);
			auto step_x = dist_x / gcd, step_y = dist_y / gcd;
			auto act_x = sx - step_x, act_y = sy - step_y;
			std::cout << util::format("(%, %) -> (%, %) steps: (%, %)\n", act_x, act_y, x, y, step_x, step_y);
			while (act_x != x || act_y != y) {
				if (!(is_clear = (std::find_if(asteroids.begin(), asteroids.end(), [&](const auto pt) {
					return act_x == pt.x && act_y == pt.y;
				}) == asteroids.end()))) {
					break;
				}
				act_x -= step_x;
				act_y -= step_y;
			}
			if (is_clear) {
				++current;
			}
		}
		if (max < current) {
			max = current;
		}
	}
	std::cout << "Result: " << max;
	return 0;
}