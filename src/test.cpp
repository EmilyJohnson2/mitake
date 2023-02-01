#include "mitake.h"

#include <iostream>

int main(int argc, char* argv[])
{
	MITAKE mtk;
	Header header;
	Point p { 17341, 2233, 2414 };
	std::vector<uint8_t> data;
	std::vector<Point> points { 32, p };

	mtk.writePoints(data, points);
	std::vector<uint8_t> hash = mtk.getHash(data);
	mtk.initHeader(header, points, hash);

	std::cout << header.hash;

	return 0;
}