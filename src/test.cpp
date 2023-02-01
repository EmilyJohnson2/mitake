#include "mitake.h"

#include <iostream>

int main(int argc, char* argv[])
{
	MITAKE mtk;
	Header header;
	Point p { 171, 2203, 114 };
	std::vector<uint8_t> data;
	std::vector<Point> points { 32, p };

	mtk.writePoints(data, points);
	std::vector<uint8_t> hash = mtk.getHash(data);
	mtk.initHeader(header, points, hash);

	std::cout << sizeof(header.hash) << std::endl;
	for (auto i = 0; i < hash.size(); ++i) {
		std::cout << hash[i];
	}

	return 0;
}
