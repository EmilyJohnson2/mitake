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
	/* �����ӡ65536��˵���û�����С��ˣ���֮���Ǵ���� */
	std::cout << *value;

	return 0;
}