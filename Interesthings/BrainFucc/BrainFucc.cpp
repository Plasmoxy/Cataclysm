/*

BrainFucc by Plasmoxy (2020)
Including dev tools.

> = increases memory pointer, or moves the pointer to the right 1 block.
< = decreases memory pointer, or moves the pointer to the left 1 block.
+ = increases value stored at the block pointed to by the memory pointer
- = decreases value stored at the block pointed to by the memory pointer
[ = like c while(cur_block_value != 0) loop.
] = if block currently pointed to's value is not zero, jump back to [
, = like c getchar(). input 1 character.
. = like c putchar(). print 1 character to the console

*/

#include <iostream>
#include <fmt/printf.h>
#include <fstream>
#include <string>

unsigned char block[30000] = { 0 };

void displayBlockRange(unsigned int p, unsigned int from, unsigned int to) {
	fmt::print("{} [", from);
	for (; from <= to; from++) {
		if (from == p) std::cout << "(";
		std::cout << (int)block[from];
		if (from == p) std::cout << ")";
		if (from != to) std::cout << " ";
	}
	fmt::print("] {}\n", to);
}

int main(int argc, char** argv)
{
	if (argc <= 1) {
		fmt::print("You must specify brainfuk source as argument");
		return 1;
	}

	std::ifstream sourcef(argv[1]);
	if (!sourcef.is_open()) {
		fmt::print("Failed to open file: {}", argv[1]);
		return 1;
	}

	auto source = std::string(
		std::istreambuf_iterator<char>(sourcef), 
		std::istreambuf_iterator<char>()
	);
	auto len = source.length();

	// Actual BF implementation :

	unsigned int i = 0; // instruction pointer
	unsigned int p = 0; // block pointer
	unsigned int loops[255] = {0}; // 255 nested loops
	unsigned char loopi = 0; // current loop idx, 0 = no loop

	while (i < source.length()) {

		switch (source[i]) {
		case '#':
			displayBlockRange(p, 0, 10);
			break;
		case '>': p++; break;
		case '<': p--; break;
		case '+': block[p]++; break;
		case '-': block[p]--; break;

		case '[':
			loopi++;
			loops[loopi] = i;
			break;

		case ']':
			if (block[p] != 0) {
				i = loops[loopi];
			}
			else {
				loopi--;
			}
			break;

		case ',':
			int input;
			std::cout << "<- ";
			std::cin >> input;
			std::cin.clear();
			std::cin.ignore();
			block[p] = (char)input;
			break;

		case '.':
			std::cout << "-> " << (int)block[p] << std::endl;
			// std::cout << block[p];
			break;
		default:
			break;
		}

		i++;
	}

	return 0;
}
