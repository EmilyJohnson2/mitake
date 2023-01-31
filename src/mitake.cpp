#include "mitake.h"
#include "picosha2.h"

std::vector<uint8_t> getHash(const std::vector<uint8_t>& data)
{
	std::vector<uint8_t> hash(picosha2::k_digest_size);
	picosha2::hash256(data, hash);
	return hash;
}