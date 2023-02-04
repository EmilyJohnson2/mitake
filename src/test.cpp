#include "mitake.h"

#include <iostream>

int main(int argc, char* argv[])
{
	Mitake mitake;
	Header header;
	Point  point {1, 255, 255};
	std::vector<uint8_t> data;
	std::vector<Point> points {8, point};
	std::vector<uint8_t> hash;

	mitake.getHash(hash);
	mitake.initHeader(header, points, hash);
	mitake.writeHeader(data, header);
	mitake.writePoints(data, points);

	if (mitake.checkHeader(data) == Ok) {
		std::cout << "true" << std::endl;
	}

	for (auto i : header.hash) {
		std::cout << i;
	}

	return 0;
}
