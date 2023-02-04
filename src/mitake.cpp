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

void Mitake::writeHeader(std::vector<uint8_t>& data, const Header& header)
{
	memcpy(data.data(), &header.magic, sizeof(Header::magic));
	memcpy(data.data(), &header.size, sizeof(Header::size));
	memcpy(data.data(), &header.tags, sizeof(Header::tags));
	memcpy(data.data(), &header.verison, sizeof(Header::verison));
	memcpy(data.data(), header.hash, sizeof(Header::hash));
}

void Mitake::writePoint(std::vector<uint8_t>& data, const Point& point)
{
	memcpy(data.data(), &point.tag, sizeof(Point::tag));
	memcpy(data.data(), &point.x, sizeof(Point::x));
	memcpy(data.data(), &point.y, sizeof(Point::y));
}

void Mitake::writePoints(std::vector<uint8_t>& data, const std::vector<Point>& points)
{
	for (uint32_t i = 0; i < points.size(); ++i) {
		memcpy(data.data(), &points[i].tag, sizeof(Point::tag));
		memcpy(data.data(), &points[i].x, sizeof(Point::x));
		memcpy(data.data(), &points[i].y, sizeof(Point::y));
	}
}

void Mitake::initHeader(Header& header, const std::vector<Point>& points, std::vector<uint8_t>& hash) 
{
	header.magic   = MAGIC;
	header.size    = static_cast<uint32_t>(points.size() * sizeof(Point) + sizeof(Header));
	header.tags    = static_cast<uint32_t>(points.size());
	header.verison = VERSION;
	*header.hash   = *reinterpret_cast<uint8_t*>(&hash);
}

CheckErrors Mitake::checkHeader(const std::vector<uint8_t>& data)
{
	Header hBuf;
	Point  pBuf;

	memcpy(&hBuf, data.data(), sizeof(Header));
	if (hBuf.magic != MAGIC) return IllegalMagic;


	return Ok;
}
