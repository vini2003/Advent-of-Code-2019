#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>

struct node {
public:
	std::string name;
	node* orbiting = nullptr;
	std::vector<node*> orbitees;
	int orbits = 0;
};

std::map<std::string, node> nodes;
std::set<node*> node_cache;

int orbits, steps;

bool found = false;

void scan(node* new_node) {
	if (new_node != nullptr) {
		std::vector<node*> adjacent_nodes;

		adjacent_nodes.reserve(new_node->orbitees.size());
		adjacent_nodes.push_back(new_node->orbiting);
		adjacent_nodes.insert(adjacent_nodes.end(), new_node->orbitees.begin(), new_node->orbitees.end());

		for (node* adjacent_node : adjacent_nodes) {
			if (adjacent_node != nullptr && !found) {
				if (adjacent_node->name == "SAN") {
					found = true;
				} else if (node_cache.insert(adjacent_node).second) {
					scan(adjacent_node);
				}
			}
		}

		steps += found ? 1 : 0;
	}
}

void process(std::vector<std::string> raw_orbits) {
	for (std::string raw_orbit : raw_orbits) {

		std::string orbiting = raw_orbit.substr(0, 3);
		std::string orbitee = raw_orbit.substr(4, 3);

		nodes[orbitee].name = orbitee;
		nodes[orbiting].name = orbiting;

		nodes[orbitee].orbiting = &nodes[orbiting];
		nodes[orbiting].orbitees.push_back(&nodes[orbitee]);
	}

	for (std::pair<std::string, node> body : nodes) {
		node* orbited = body.second.orbiting;

		while (orbited != nullptr) {
			++orbits;
			orbited = orbited->orbiting;
		}
	}
}

int main() {
	std::string line, buffer;
	std::vector<std::string> raw_orbits;
	std::ifstream input("C:\\Advent-of-Code-2019\\Input VI");

	while (std::getline(input, line)) {
		raw_orbits.push_back(line);
	}

	process(raw_orbits);

	scan(&nodes["YOU"]);

	std::cout << "Part I: " << orbits << std::endl;

	std::cout << "Part II: " << steps - 2 << std::endl;
}