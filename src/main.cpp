#include "mitake.h"

#include <iostream>
#include <cstdint>

struct Union
{
	uint16_t a;
	uint16_t b;
};

int main(int argc, char* argv[])
{
	Union u { 0, 1 };
	uint32_t* value = reinterpret_cast<uint32_t*>(&u);
	/* 如果打印65536则说明该机器是小序端，反之则是大序端 */
	std::cout << *value;

	return 0;
}