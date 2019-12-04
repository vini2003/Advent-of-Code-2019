#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <map>

std::vector<std::pair<bool, int>> trace(std::string input) {
	std::string buffer;
	std::vector<std::pair<bool, int>> directions;

	for (int i = 0; i <= input.size(); ++i) {
		if (input[i] != ',') {
			buffer.push_back(input[i]);
		}
		else {
			std::pair<bool, int> direction;
			switch (buffer[0]) {
				case 'R':
					buffer[0] = '+';
					direction.first = true;
					break;
				case 'L':
					buffer[0] = '-';
					direction.first = true;
					break;
				case 'U':
					buffer[0] = '+';
					direction.first = false;
					break;
				case 'D':
					buffer[0] = '-';
					direction.first = false;
					break;
			}
			direction.second = std::stoi(buffer);
			directions.push_back(direction);
			buffer.clear();
		}
	}
	return directions;
}

int main() {
	std::string lines[2];

	std::ifstream("input") >> lines[0] >> lines[1];

	std::vector<std::pair<bool, int>> directions[] = { trace(lines[0]), trace(lines[1]) };

	std::set<int> distances, steps;

	std::set<std::pair<int, int>> intersections;

	std::map<std::pair<int, int>, int[2]> grid;

	for (int pos = 0; pos <= 1; ++pos) {
		int tX = 0, tY = 0, tS = 0;
		for (std::pair<bool, int> dir : directions[pos]) {
			int dX = dir.first ? dir.second : 0;
			int dY = dir.first ? 0 : dir.second;

			while (dX != 0 || dY != 0) {
				if (dX != 0) {
					tX += dX > 0 ? +1 : dX < 0 ? -1 : 0;
					dX += dX > 0 ? -1 : dX < 0 ? +1 : 0;
					++tS;
					grid[{tX, tY}][pos] = grid[{tX, tY}][pos] == 0 ? tS : grid[{tX, tY}][pos];
				}
				if (dY != 0) {
					tY += dY > 0 ? +1 : dY < 0 ? -1 : 0;
					dY += dY > 0 ? -1 : dY < 0 ? +1 : 0;
					++tS;
					grid[{tX, tY}][pos] = grid[{tX, tY}][pos] == 0 ? tS : grid[{tX, tY}][pos];
				}
				if (grid[{tX, tY}][0] != 0 && pos == 1) {
					intersections.insert({tX, tY});
					distances.insert(abs(tX) + abs(tY));
					steps.insert(grid[{tX, tY}][0] + grid[{tX, tY}][1]);
				}
			}
		}
	}

	std::cout << "Part I: " << *std::min_element(distances.begin(), distances.end()) << std::endl;

	std::cout << "Part II: " << *std::min_element(steps.begin(), steps.end()) << std::endl;
}