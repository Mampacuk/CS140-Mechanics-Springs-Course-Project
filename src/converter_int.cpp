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

	// little-endian convention is used
	void converter_int::construct_system(const std::string &bits)
	{
		check_length(bits);
		std::string float_bits;
		const size_t padding = bits.find_first_not_of('0');			// erase trailing zeros
		float_bits = bits.substr(padding);							// find where to pad
		float_bits.insert(0, 4 - (float_bits.length() % 4), '0');	// pad for bits to be multiple of 4
		this->_fixed_point = float_bits.length() / 2;
		float_bits.insert(float_bits.begin() + this->_fixed_point, '.');
		converter_float fixed;
		fixed.construct_system(float_bits);
		set_system(fixed.get_system());
		set_equivalent_spring(fixed.get_equivalent_spring());
	}

	void converter_int::check_length(const std::string &bits) const
	{
		if (bits.length() > sizeof(int) * 8)
			throw std::invalid_argument("Sequence of invalid length provided to a 32-bit converter.");
	}

	double converter_int::recover_value(double omega_max) const
	{
		return (omega_max * omega_max * pow(2, this->_fixed_point));
	}
} // namespace aua
