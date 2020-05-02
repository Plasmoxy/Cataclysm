
#include "fmt.h"
#include <fmt/printf.h>

extern "C" void prontln(char* str) {
	fmt::printf(str);
}