#include "mitake.h"

#include <iostream>

int main(int argc, char* argv[])
{
	Mitake mtk;
	Header header;
	Point p(44, 44, 44);
	std::vector<uint8_t> data;
	std::vector<Point> points(4, p);

	std::vector<uint8_t> hash = mtk.getHash(data);
	mtk.initHeader(header, points, hash);
	mtk.writeHeader(data, header);

	if (mtk.checkHeader(data)) {
		std::cout << "true" << std::endl;
	}

	return 0;
}
