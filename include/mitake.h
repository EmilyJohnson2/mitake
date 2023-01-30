#pragma once

#include "picosha2.h"

#include <vector>
#include <cstdint>
#include <memory>

static constexpr float VERSION = 1.0;
static constexpr uint32_t MAGIC = 0x4B544D7F;

struct MTKHeader
{
	uint32_t magic;
	std::vector<uint8_t> SHA256[32];
	float version;
	uint32_t sections;
};

struct MTKSection
{
	uint32_t size;
	uint32_t fileNameLenth;
};

class MTKWriter
{
public:
	void writeHeader(std::vector<uint8_t>& buf, MTKHeader& header);
	void writeSection(std::vector<uint8_t>& buf, MTKSection& section);
	void writeData(std::vector<uint8_t>& buf, std::vector<uint8_t>& data);
};

class MTKReader
{
public:
	 MTKHeader readHeader(std::vector<uint8_t>& data);
	 MTKSection readSection();
	 std::vector<uint8_t>& readData();
};

extern std::vector<uint8_t> getSHA256(std::vector<uint8_t>& data);
extern uint32_t getFileSize(const char* file);
extern MTKHeader InitHeader(std::vector<uint8_t>& hash, uint32_t sections);
extern MTKSection InitSection(uint32_t size, uint32_t fileNameLenth);