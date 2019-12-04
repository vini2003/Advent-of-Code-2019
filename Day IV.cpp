#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <charconv>
#include <array>

int main() {
	int pS = 108457, pF = 562041, partI = 0, partII = 0;
	char pV = 0, pP = 0;
	bool hasPair = 0, hasDecrease = 0;

	std::string buffer;
	std::vector<std::string> pairs;
	std::array<char, 6> str;

	for (int num = pS; num <= pF; ++num) {
		buffer.clear();
		pairs.clear();

		hasPair = false;
		hasDecrease = false;

		std::to_chars(str.data(), str.data() + str.size(), num);

		pV = NULL;
		for (int k = 0; k < str.size(); ++k) {
			if (str[k] < pV) {
				hasDecrease = true;
			}
			pV = str[k];
		}

		if (!hasDecrease) {
			pP = NULL;
			for (int pos = 0; pos <= str.size(); ++pos) {
				if (pP == str[pos] && pos < str.size()) {
					buffer += str[pos];
				} else {
					if (buffer.size() > 1) {
						pairs.push_back(buffer);
					}
					buffer.clear();
					pP = str[pos];
					buffer += str[pos];
				}
			}

			hasPair = pairs.size() > 0;

			if (hasPair) {
				++partI;
			}

			if (hasPair) {
				for (std::string pair : pairs) {
					if (pair.size() == 2) {
						++partII;
						break;
					}
				}
			}
		}
	}
	std::cout << "Part I: " << partI << std::endl;

	std::cout << "Part II: " << partII << std::endl;
}