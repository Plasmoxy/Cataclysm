#include <stdio.h>
#include <iostream>
#include <string>

using namespace std;

__global__ void hello() {
	printf("XD\n");
}

__global__ void xd() {

}

int main() {
	
	hello <<<1, 1000>>> ();
	cudaDeviceSynchronize();

	return 0;
}