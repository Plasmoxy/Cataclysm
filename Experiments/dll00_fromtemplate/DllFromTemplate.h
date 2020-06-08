#pragma once
#include "pch.h"

extern "C" {
	
	API int add(int a, int b);
	API const char* emitStringPtr();
	API const char* emitReusedStringObjPtr();
	API const char* emitStringAutoMarshal();
	API void tryOpenCv();

}