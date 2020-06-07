#pragma once

#ifdef DLL00FROMTEMPLATE_EXPORTS
#define API __declspec(dllexport)
#else
#define API __declspec(dllimport)
#endif

extern "C" {

	API int add(int a, int b);

}