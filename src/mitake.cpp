#include "mitake.h"

#include <sys/stat.h>

std::vector<uint8_t> getSHA256(std::vector<uint8_t>& data)
{
	std::vector<uint8_t> hash(picosha2::k_digest_size);
	picosha2::hash256(data, hash);
	return hash;
}

uint32_t getFileSize(const char* file)
{
	static struct stat info;
	stat(file, &info);
	return info.st_size;
}

MTKHeader InitHeader(std::vector<uint8_t>& hash, uint32_t sections)
{
	MTKHeader header;
	header.magic = MAGIC;
	memcpy(header.SHA256, &hash, 32);
	header.version = VERSION;
	header.sections = sections;
	return header;
}

MTKSection InitSection(uint32_t size, uint32_t fileNameLenth)
{
	MTKSection section { size, fileNameLenth };
	return section;
}

void MTKWriter::writeHeader(std::vector<uint8_t>& buf, MTKHeader& header)
{
	uint8_t* ptr = reinterpret_cast<uint8_t*>(&header);

	buf.insert(buf.begin(), ptr, ptr + sizeof(header));
}

void MTKWriter::writeSection(std::vector<uint8_t>& buf, MTKSection& section)
{
	uint8_t* ptr = reinterpret_cast<uint8_t*>(&section);
	buf.insert(buf.end(), ptr, ptr + sizeof(section));
}

void MTKWriter::writeData(std::vector<uint8_t>& buf, std::vector<uint8_t>& data)
{
	uint8_t* ptr = reinterpret_cast<uint8_t*>(&data);
	buf.insert(buf.end(), ptr, ptr + sizeof(data));
}
