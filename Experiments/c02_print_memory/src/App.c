#include <stdio.h>

void print_bytes(void *ptr, int size) {
    unsigned char *p = ptr;
    int i;
    for (i=0; i<size; i++) {
        printf("%02hhx ", p[i]);
        if ((i+1)%8 == 0) printf("\n");
    }
    printf("\n");
}

int main(void) {
    int a[] = {1633209, 232948, 239423};
    print_bytes(a, 12);

    char* p = (char*)a + 2;
    printf("%d\n", *p);
    return 0;
}