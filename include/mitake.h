#pragma once

#include <cstdint>

constexpr uint32_t MAGIC = 0x4B544D7F; // 0x7F M T K

struct Header
{
	uint32_t magic;
	uint32_t size;
	uint8_t  hash[32]; // SHA256
};