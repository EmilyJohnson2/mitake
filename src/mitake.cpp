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
	memcpy(&data[0], &header.magic, sizeof(Header::hash));
	memcpy(&data[4], &header.size, sizeof(Header::size));
	memcpy(&data[8], &header.tags, sizeof(Header::tags));
	memcpy(&data[12], &header.verson, sizeof(Header::verson));
	memcpy(&data[16], header.hash, sizeof(Header::hash));
}

void Mitake::writePoint(std::vector<uint8_t>& data, const Point& point)
{
	memcpy(&data, &point.tag, sizeof(Point::tag));
	memcpy(&data, &point.x, sizeof(Point::x));
	memcpy(&data, &point.y, sizeof(Point::y));
}

void Mitake::writePoints(std::vector<uint8_t>& data, const std::vector<Point>& points)
{
	for (uint32_t i = 0; i < points.size(); ++i) {
		memcpy(&data, &points[i].tag, sizeof(Point::tag));
		memcpy(&data, &points[i].x, sizeof(Point::x));
		memcpy(&data, &points[i].y, sizeof(Point::y));
	}
}

void Mitake::initHeader(Header& header, const std::vector<Point>& points, std::vector<uint8_t>& hash) 
{
	header.magic  = MAGIC;
	header.size   = static_cast<uint32_t>(points.size() * sizeof(Point) + sizeof(Header));
	header.tags   = static_cast<uint32_t>(points.size());
	header.verson = VERSION;
	*header.hash  = *reinterpret_cast<uint8_t*>(&hash);
}

bool Mitake::checkHeader(const std::vector<uint8_t>& data)
{

	return true;
}
