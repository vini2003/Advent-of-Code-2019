#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <charconv>
#include <array>

#define ADD 1
#define MULTIPLY 2
#define INPUT 3
#define OUTPUT 4
#define JUMP_IF_TRUE 5
#define JUMP_IF_FALSE 6
#define LESS_THAN 7
#define EQUAL 8

void run(std::vector<int> opcodes, int input) {
	std::string str, inst;
	std::vector<bool> args;
	int size = 0, * p1 = &size, * p2 = &size, * p3 = &size;
	for (int i = 0; i < opcodes.size();) {
		str.clear();
		args.clear();
		inst.clear();

		str = std::to_string(opcodes[i]);
		size = str.size();

		for (int k = size - 1; k >= 0; --k) {
			if (size == 1 || k > size - 3) {
				inst += str[k];
			} else if (size > 1 && k < size - 2) {
				args.push_back(str[k] == '1');
			}
		}

		std::reverse(inst.begin(), inst.end());

		if (args.size() == 0) {
			args = { false, false };
		}

		p1 = !args[0] ? &opcodes[opcodes[i + 1]] : &opcodes[i + 1];
		p2 = !args[1] ? &opcodes[opcodes[i + 2]] : &opcodes[i + 2];
		p3 = &opcodes[opcodes[i + 3]];

		switch (std::stoi(inst)) {
			case INPUT:
				*p1 = input;
				i += 2;
				break;
			case OUTPUT:
				std::cout << ":" << *p1 << std::endl;
				i += 2;
				break;
			case JUMP_IF_TRUE:
				i = *p1 != 0 ? *p2 : i + 3;
				break;
			case JUMP_IF_FALSE:
				i = *p1 == 0 ? *p2 : i + 3;
				break;
			case ADD:
				*p3 = *p1 + *p2;
				i += 4;
				break;
			case MULTIPLY:
				*p3 = *p1 * *p2;
				i += 4;
				break;
			case LESS_THAN:
				*p3 = *p1 < *p2;
				i += 4;
				break;
			case EQUAL:
				*p3 = *p1 == *p2;
				i += 4;
				break;
			case 99:
				i = INT32_MAX;
				break;
		}
	}
}

int main() {
	std::string line, buffer;
	std::vector<int> basecodes;
	std::ifstream("C:\\Advent-of-Code-2019\\Input V") >> line;
	for (int i = 0; i <= line.size(); ++i) {
		if (line[i] != ',') {
			buffer += line[i];
		} else if (!std::isdigit(line[i])) {
			basecodes.push_back(std::stoi(buffer));
			buffer.clear();
		}
	}

	std::cout << "Part I: " << std::endl;
	run(basecodes, 1);
	std::cout << std::endl;

	std::cout << "Part II: " << std::endl;
	run(basecodes, 5);
	std::cout << std::endl;
}