#include <fstream>
#include <iostream>
#include <string>

int main() {
	std::string line;
	std::ifstream input("input");
	int totalFuelI = 0, totalFuelII = 0;
	while (std::getline(input, line)) {
		double moduleFuel = std::stod(line);
		totalFuelI += std::floor(moduleFuel / 3) - 2;
		while (std::floor(moduleFuel / 3) - 2 > 0) {
			moduleFuel = std::floor(moduleFuel / 3) - 2;
			totalFuelII += moduleFuel;
		}
	}
	std::cout << "Part I: " << totalFuelI << std::endl;
	std::cout << "Part II: " << totalFuelII << std::endl;
}