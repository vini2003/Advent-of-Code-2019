#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int run(std::vector<int> opcodes) {
	for (int i = 0; i < opcodes.size(); ++i) {
		switch (opcodes[i]) {
			case 1:
				opcodes[opcodes[i + 3]] = opcodes[opcodes[i + 1]] + opcodes[opcodes[i + 2]];
				i += 3;
				break;
			case 2:
				opcodes[opcodes[i + 3]] = opcodes[opcodes[i + 1]] * opcodes[opcodes[i + 2]];
				i += 3;
				break;
			case 99:
				i = INT32_MAX;
				break;
		}
	}
	return opcodes[0];
}

int main() {
	std::string line, buffer;
	std::vector<int> basecodes;
	std::getline(std::ifstream("input"), line);
	for (int i = 0; i <= line.size(); ++i) {
		if (line[i] != ',') {
			buffer.push_back(line[i]);
		} else if (!std::isdigit(line[i])) {
			basecodes.push_back(std::stoi(buffer));
			buffer.clear();
		}
	}
	std::cout << "Part I: " << run(basecodes) << std::endl;
	for (int noun = 0; noun <= 99; ++noun) {
		basecodes[1] = noun;
		for (int verb = 0; verb <= 99; ++verb) {
			basecodes[2] = verb;
			if (run(basecodes) == 19690720) {
				std::cout << "Part II: " << 100 * noun + verb << std::endl;
			}
		}
	}
}