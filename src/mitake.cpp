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

#include "mitake.h"
#include "picosha2.h"

std::vector<uint8_t> Mitake::getHash(const std::vector<uint8_t>& data)
{
	std::vector<uint8_t> hash(picosha2::k_digest_size);
	picosha2::hash256(data, hash);
	return hash;
}

void Mitake::writeHeader(std::vector<uint8_t>& buffer, const Header& header)
{
	buffer.resize(sizeof(Header));
	memcpy(&buffer[0], &header, sizeof(Header));
}

void Mitake::writePoint(std::vector<uint8_t>& buffer, const Point& point)
{
	std::vector<uint8_t> pointData(sizeof(Point));
	memcpy(&pointData[0], &point, sizeof(Point));
	buffer.insert(buffer.end(), pointData.begin(), pointData.end());
}

void Mitake::writePoints(std::vector<uint8_t>& buffer, const std::vector<Point>& points)
{
	for (const auto& point : points)
	{
		writePoint(buffer, point);
	}
}

void Mitake::initHeader(Header& header, const std::vector<Point>& points, std::vector<uint8_t>& hash)
{
	header.magic = MAGIC;
	header.size = sizeof(Header) + points.size() * sizeof(Point);
	header.tags = points.size();
	header.verison = VERSION;

	std::vector<uint8_t> buffer;
	writeHeader(buffer, header);
	writePoints(buffer, points);
	hash = getHash(buffer);
	memcpy(header.hash, hash.data(), hash.size());
}

CheckErrors Mitake::checkHeader(const std::vector<uint8_t>& data)
{
	Header headerBuffer;

	memcpy(&headerBuffer, data.data(), sizeof(Header));
	if (headerBuffer.magic != MAGIC)
		return IllegalMagic;
	if (headerBuffer.size != data.size())
		return IllegalSize;
	if (headerBuffer.tags != (data.size() - sizeof(Header)) / sizeof(Point))
		return IllegalTags;
	if (headerBuffer.verison != VERSION)
		return IllegalVerison;

	std::vector<uint8_t> buffer(data.begin() + sizeof(Header), data.end());
	std::vector<uint8_t> hash = getHash(buffer);
	uint8_t hashBuffer[sizeof(Header::hash)];

	memcpy(hashBuffer, &hash, sizeof(Header::hash));
	for (auto i = 0; i < sizeof(Header::hash); ++i) {
		if (headerBuffer.hash[i] != hashBuffer[i])
			return IllegalHash;
	}

	return Ok;
}
