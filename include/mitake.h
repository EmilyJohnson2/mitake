#pragma once

#include <cstdint>
#include <vector>

constexpr uint32_t MAGIC   = 0x4B544D7F; // 0x7F M T K
constexpr uint32_t VERSION = 1;

struct Header
{
	uint32_t magic;
	uint32_t size;
	uint32_t tags;
	uint32_t verson;
	uint8_t  hash[32]; // SHA256
};

struct Point
{
	uint32_t tag;
	uint32_t x;
	uint32_t y;
};

std::vector<uint8_t> getHash(const std::vector<uint8_t>& data);