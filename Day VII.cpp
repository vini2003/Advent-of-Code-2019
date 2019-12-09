#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <charconv>
#include <array>
#include <algorithm>
#include <chrono>

#define ADD 1
#define MULTIPLY 2
#define INPUT 3
#define OUTPUT 4
#define JUMP_IF_TRUE 5
#define JUMP_IF_FALSE 6
#define LESS_THAN 7
#define EQUAL 8
#define HALT 99

using instruction_set = std::vector<int>;

class intcode_computer {
private:
	int instruction_pointer = 0;
	bool has_halted;
	std::vector<int> input_data, output_data;
	instruction_set instructions_immutable = {}, instructions_mutable = {};

public:
	void add_input(std::vector<int> input) {
		input_data.insert(input_data.end(), input.begin(), input.end());
	}

	int get_input() {
		if (has_input()) {
			int input = input_data.front();
			input_data.erase(input_data.begin());
			return input;
		}
	}

	void clear_input() {
		input_data.clear();
	}

	bool has_input() {
		return !input_data.empty();
	}

	void add_output(std::vector<int> output) {
		output_data.insert(output_data.end(), output.begin(), output.end());
	}

	int get_output() {
		if (has_output()) {
			int output = output_data.front();
			output_data.erase(output_data.begin());
			return output;
		}
	}

	void clear_output() {
		output_data.clear();
	}

	bool has_output() {
		return !output_data.empty();
	}

	bool has_finished() {
		return has_halted;
	}


	void set_immutable(instruction_set instructions) {
		instructions_immutable = instructions;
	}

	void reset_mutable() {
		instruction_pointer = 0;
		has_halted = false;
		instructions_mutable = instructions_immutable;
	}

	void run_mutable() {
		std::string str, inst;
		std::vector<bool> args;
		int size = 0, * p1 = &size, * p2 = &size, * p3 = &size;
		while (instruction_pointer < instructions_mutable.size()) {
			str.clear();
			args.clear();
			inst.clear();

			str = std::to_string(instructions_mutable[instruction_pointer]);
			size = str.size();

			for (int k = size - 1; k >= 0; --k) {
				if (size == 1 || k > size - 3) {
					inst += str[k];
				}
				else if (size > 1 && k < size - 2) {
					args.push_back(str[k] == '1');
				}
			}

			std::reverse(inst.begin(), inst.end());

			if (args.size() == 0) {
				args = { false, false };
			}

			p1 = !args[0] ? &instructions_mutable[instructions_mutable[instruction_pointer + 1]] : &instructions_mutable[instruction_pointer + 1];
			p2 = !args[1] ? &instructions_mutable[instructions_mutable[instruction_pointer + 2]] : &instructions_mutable[instruction_pointer + 2];
			p3 = &instructions_mutable[instructions_mutable[instruction_pointer + 3]];

			switch (std::stoi(inst)) {
			case INPUT:
				if (!has_input()) {
					return;
				}
				*p1 = get_input();
				instruction_pointer += 2;
				break;
			case OUTPUT:
				add_output({ *p1 });
				instruction_pointer += 2;
				break;
			case JUMP_IF_TRUE:
				instruction_pointer = *p1 != 0 ? *p2 : instruction_pointer + 3;
				break;
			case JUMP_IF_FALSE:
				instruction_pointer = *p1 == 0 ? *p2 : instruction_pointer + 3;
				break;
			case ADD:
				*p3 = *p1 + *p2;
				instruction_pointer += 4;
				break;
			case MULTIPLY:
				*p3 = *p1 * *p2;
				instruction_pointer += 4;
				break;
			case LESS_THAN:
				*p3 = *p1 < *p2;
				instruction_pointer += 4;
				break;
			case EQUAL:
				*p3 = *p1 == *p2;
				instruction_pointer += 4;
				break;
			case HALT:
				has_halted = true;
				return;
			}
		}
	}

	static void add_input_sequentially(std::vector<intcode_computer>& intcode_computers, std::vector<int> sequences) {
		for (int i = 0; i < intcode_computers.size() && i < sequences.size(); ++i) {
			intcode_computers[i].add_input({ sequences[i] });
		}
	}

	static void set_immutable_sequentially(std::vector<intcode_computer>& intcode_computers, instruction_set basecodes) {
		for (int i = 0; i < intcode_computers.size(); ++i) {
			intcode_computers[i].set_immutable({ basecodes });
		}
	}

	static void reset_mutable_sequentially(std::vector<intcode_computer>& intcode_computers) {
		for (int i = 0; i < intcode_computers.size(); ++i) {
			intcode_computers[i].reset_mutable();
		}
	}
};



int main() {
	std::string line, buffer;
	std::vector<int> basecodes;
	std::ifstream("C:\\Advent-of-Code-2019\\Input VII") >> line;
	for (int i = 0; i <= line.size(); ++i) {
		if (line[i] != ',') {
			buffer += line[i];
		}
		else if (!std::isdigit(line[i])) {
			basecodes.push_back(std::stoi(buffer));
			buffer.clear();
		}
	}

	std::vector<std::vector<int>> sequences_one, sequences_two;

	std::vector<int> base_sequence_one = { 0, 1, 2, 3, 4 }, base_sequence_two = { 5, 6, 7, 8, 9 }, output_cache_one, output_cache_two, input_cache(5);

	do {
		sequences_one.push_back(base_sequence_one);
		sequences_two.push_back(base_sequence_two);
	} while (std::next_permutation(base_sequence_two.begin(), base_sequence_two.end()) && std::next_permutation(base_sequence_one.begin(), base_sequence_one.end()));

	std::vector<intcode_computer> virtual_machines(5);

	intcode_computer::set_immutable_sequentially(virtual_machines, basecodes);

	for (std::vector<int> sequence : sequences_one) {
		std::fill(input_cache.begin(), input_cache.begin() + 5, 0);

		intcode_computer::reset_mutable_sequentially(virtual_machines);
		intcode_computer::add_input_sequentially(virtual_machines, sequence);

		for (int i = 0; !virtual_machines[4].has_finished(); ++i) {
			virtual_machines[i].add_input({ i == 0 ? 0 : input_cache[i - 1] });
			virtual_machines[i].run_mutable();
			input_cache[i] = virtual_machines[i].get_output();
		}

		output_cache_one.push_back(input_cache[4]);
	}

	for (std::vector<int> sequence : sequences_two) {
		std::fill(input_cache.begin(), input_cache.begin() + 5, 0);

		intcode_computer::reset_mutable_sequentially(virtual_machines);
		intcode_computer::add_input_sequentially(virtual_machines, sequence);

		for (int i = 0; !virtual_machines[4].has_finished(); ++i) {
			virtual_machines[i].add_input({ i == 0 ? input_cache[4] : input_cache[i - 1] });
			virtual_machines[i].run_mutable();
			input_cache[i] = virtual_machines[i].get_output();
			i = i == 4 ? -1 : i;
		}

		output_cache_two.push_back(input_cache[4]);
	}

	std::cout << "Part I: " << *std::max_element(output_cache_one.begin(), output_cache_one.end()) << std::endl;

	std::cout << "Part II: " << *std::max_element(output_cache_two.begin(), output_cache_two.end()) << std::endl;
}