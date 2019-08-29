#include <iostream>
#include <stdio.h>

int xd() {
    printf("XDDXDXD");
}

int main() {
    int (*p)() = main;
    printf("main = %p\n", main);
}