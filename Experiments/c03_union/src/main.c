#include <stdio.h>

typedef union {
	int value;
	unsigned char bytes[8];
} IntByte;

int main() {
	
	printf("union struct size = %d\n", sizeof(IntByte));

	IntByte t = {256};
	for (int i = sizeof(t.bytes) - 1; i >= 0; i--) {
		printf("%02X ", t.bytes[i]);
	}
	printf("\n");

	printf("value int = %d", t.value);

	return 0;
}