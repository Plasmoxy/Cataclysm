#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define log(s, ...) printf(s, __VA_ARGS__)

char* multiply(const char* a, const char* b) {
	unsigned int la = strlen(a);
	unsigned int lb = strlen(b);

	unsigned int xmax = la + lb - 2; // max x index
	unsigned int rmin = 0;
	unsigned int rmax = 0;

	// alloc output with size for :
	// <reserved char for extra carry> <digits (xmax + 1)> <terminator>
	// -> 1 + xmax + 1 + 1
	char* output = malloc(((size_t)xmax + 3) * sizeof(char));
	output[xmax + 1] = 0;

	// size of carry is lb
	unsigned int* c = calloc(lb, sizeof(unsigned int));
	unsigned int sumc = 0; // carry for final sum

	log("xmax = %d\n", xmax);

	for (unsigned int x = 0; x <= xmax; x++) {
		if (x > la - 1) rmin++;

		unsigned int sumx = 0;

		log("x = %d, rmin = %d, rmax = %d\n", x, rmin, rmax);
		for (unsigned int r = rmin; r <= rmax; r++) {
			unsigned int fragment = (a[la - (x-r) - 1] - 48) * (b[lb - r - 1] - 48) + c[r];

			sumx += fragment % 10;
			c[r] = fragment / 10;

			log("    r = %d, frag = %d\n", r, fragment);
		}

		if (x < xmax - la + 1) rmax++;
		else rmax = lb - 1;

		char digit = (sumx + sumc) % 10 + 48;
		sumc = (sumx + sumc) / 10;

		output[xmax - x] = digit; // watch out for that one reserved carry output byte !

		log(">>>> sumx = %d, out digit = %c\n", sumx, digit);
	}

	log("final sum carry (sumc) = %d", sumc);
	if (sumc == 0) {
		// output++; // ignore the first char, is a memory leak XDXDXDXD
	}

	log("\n");

	free(c);
	return output;
}

int main() {
	
	const char* multiplyTest = multiply("3", "4");
	printf("multiplyTest len = %d\n", strlen(multiplyTest));
	printf("multiplyTest = %s\n", multiplyTest);

	printf("\n===============================\n");
	printf("12*34 = %s (408)\n", multiply("12", "34"));

	return 0;
}