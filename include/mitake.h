/*
	Copyright 2023 Somnium Chase

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

	   http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#pragma once

#include <cstdint>
#include <vector>

constexpr uint32_t MAGIC   = 0x4B544D7F; // 0x7F M T K
constexpr uint32_t VERSION = 1;

enum CheckErrors
{
	IllegalMagic,
	IllegalSize,
	IllegalTags,
	IllegalVerison,
	IllegalHash,
	Ok
};

struct Header
{
	uint32_t magic;
	uint32_t size;
	uint32_t tags;
	uint32_t verison;
	uint8_t  hash[32]; // SHA256
};

struct Point
{
	uint32_t tag;
	uint32_t x;
	uint32_t y;
};

class Mitake
{
	public:
		void writeHeader(std::vector<uint8_t>& buffer, const Header& header);
		void writePoint(std::vector<uint8_t>& buffer, const Point& point);
		void writePoints(std::vector<uint8_t>& data, const std::vector<Point>& points);
		std::vector<uint8_t> getHash(const std::vector<uint8_t>& data);
		void initHeader(Header& header, const std::vector<Point>& points, std::vector<uint8_t>& hash);
		CheckErrors checkHeader(const std::vector<uint8_t>& data);
};