#include "../util.hpp"

int main() {
	std::ifstream f("../day8/day8.txt");
	std::string raw_data{ std::istreambuf_iterator{ f }, {}};
	std::array<u8, 150> final_image{};
	std::fill(final_image.begin(), final_image.end(), '2');
	for (auto i = 0; i < raw_data.size() / 150; ++i) {
		for (auto j = 0; j < 150; ++j) {
			if (final_image[j] == '2') {
				final_image[j] = raw_data[i * 150 + j];
			}
		}
	}
	for (auto i = 0; i < 150; ++i) {
		if (i % 25 == 0) {
			std::cout << "\n";
		}
		std::cout << char((final_image[i] == '1') ? final_image[i] : ' ');
	}
	return 0;
}