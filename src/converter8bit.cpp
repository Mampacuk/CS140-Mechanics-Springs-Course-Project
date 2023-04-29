#include "converter8bit.hpp"

namespace aua
{
	converter8bit::converter8bit() : converter_int() {}

	converter8bit::~converter8bit() {}

	converter8bit::converter8bit(const converter8bit &other) : converter_int(other) {}

	converter8bit &converter8bit::operator=(const converter8bit &other)
	{
		converter_int::operator=(other);
		return (*this);
	}

	void converter8bit::check_length(const std::string &bits) const
	{
		if (bits.length() > 8)
			throw std::invalid_argument("Sequence of invalid length provided to a 8-bit converter.");
	}

	double converter8bit::recover_value(double omega_max) const
	{
		return (converter_int::recover_value(omega_max));
	}
} // namespace aua
