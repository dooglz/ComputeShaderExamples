#define DllExport __declspec( dllexport ) __stdcall
#include "CL/cl2.hpp"
#include <iostream>

extern "C"  void DllExport go_cl(cl::Platform& platform, cl::Device& device, size_t runs) {
	std::cout << "HELLO WORLD" << std::endl;
}
