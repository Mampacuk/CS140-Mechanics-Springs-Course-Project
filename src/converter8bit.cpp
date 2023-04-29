#include "converter8bit.hpp"

namespace aua
{
	converter8bit::converter8bit() {}

	converter8bit::~converter8bit() {}

	converter8bit::converter8bit(const converter8bit&) {}

	converter8bit &converter8bit::operator=(const converter8bit&) { return (*this); }

	void converter8bit::check_length(const std::string &bits) const
	{
		if (bits.length() > sizeof(int8_t))
			throw std::invalid_argument("Sequence of invalid length provided to a 8-bit converter.");
	}
} // namespace aua
