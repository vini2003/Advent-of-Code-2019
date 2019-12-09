#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <charconv>
#include <array>
#include <algorithm>
#include <chrono>

struct image {
public:
	std::vector<int> pixels[6];
	int total_pixels[3];
};

int main() {
	std::string raw_pixels;
	std::ifstream("C:\\Advent-of-Code-2019\\Input VIII") >> raw_pixels;

	std::vector<image> images;
	image temporary_image;

	int pX = 0, pY = 0;

	for (int i = 0; i <= raw_pixels.size(); ++i) {
		char pixel = raw_pixels[i] - '0';
		if (pX == 25) {
			pX = 0;
			++pY;
			if (pY == 6) {
				pY = 0;
				images.push_back(temporary_image);
				temporary_image = image();
			}
		}
		temporary_image.pixels[pY].push_back(pixel);
		++temporary_image.total_pixels[pixel];
		++pX;
	}

	image* lowest = &images[0];
	for (image& new_image : images) {
		if (new_image.total_pixels[0] < lowest->total_pixels[0]) {
			lowest = &new_image;
		}
	}

	std::vector<int> decoded_pixels[6] = { {}, {}, {}, {}, {}, {} };

	std::fill(std::begin(decoded_pixels), std::end(decoded_pixels), std::vector<int>(25, 2));

	for (image t_image : images) {
		for (int y = 0; y <= 5; ++y) {
			for (int x = 0; x <= 24; ++x) {
				if (t_image.pixels[y][x] != 2 && decoded_pixels[y][x] == 2) {
					decoded_pixels[y][x] = t_image.pixels[y][x];
				}
			}
		}
	}
	
	std::cout << "Part I: " << (lowest->total_pixels[1]) * (lowest->total_pixels[2]) << std::endl;

	std::cout << "Part II: ";

	for (int y = 0; y <= 5; ++y) {
		for (int x = 0; x <= 24; ++x) {
			std::cout << (decoded_pixels[y][x] == 1 ? "O" : " ");
		}
	}
}