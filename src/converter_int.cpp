#include "converter_int.hpp"

namespace aua
{
	converter_int::converter_int() : converter() {}

	converter_int::~converter_int() {}

	converter_int::converter_int(const converter_int &other) : converter(other) {}

	converter_int &converter_int::operator=(const converter_int &other)
	{
		converter::operator=(other);
		return (*this);
	}

	void converter_int::construct_system(const std::string &bits)
	{
		check_length(bits);
		//...
	}

	void converter_int::check_length(const std::string &bits) const
	{
		if (bits.length() > sizeof(int))
			throw std::invalid_argument("Sequence of invalid length provided to a 32-bit converter.");
	}
} // namespace aua
