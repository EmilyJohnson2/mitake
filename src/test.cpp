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

	char* h = reinterpret_cast<char*>(&header);

	FILE* fp = fopen("G:\\data.bin", "wb");
	fwrite(h, sizeof(header), 1, fp);
	fclose(fp);

	if (mtk.checkHeader(data)) {
		std::cout << "true" << std::endl;
	}

	return 0;
}
