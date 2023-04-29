#include "converter_float.hpp"

namespace aua
{
	converter_float::converter_float() {}

	converter_float::~converter_float() {}

	converter_float::converter_float(const converter_float&) {}

	converter_float &converter_float::operator=(const converter_float&) { return (*this); }

	// fixed-point number notation is used.
	// a unique fixed point must be present in the string, separating integer
	// and fractional parts. for example,
	// iiiiiii.fffffff denotes a valid fixed-point bit sequence, where the value
	// is computed by the sum of set positive powers of 2 for integer part,
	// negative powers for the fractional part.
	void converter_float::construct_system(const std::string &bits)
	{
		std::string system = "[[";
		const size_t fixed_point = bits.find('.');
		if (fixed_point == std::string::npos || fixed_point != bits.rfind('.'))
			throw std::invalid_argument("Provided sequence is not a valid fixed-point number bit sequence.");
		for (size_t i = 0; i < fixed_point; i++)
		{
			const char bit = bits[i];
			if (bit != '0' && bit != '1')
				throw std::invalid_argument("Provided sequence is not a bit sequence.");
			if (bit - '0')
			{
				const size_t n = pow(2, fixed_point - 1 - i);
				system += "[";
				for (size_t j = 0; j < n; j++)
					system += "[]";
				system += "]";
			}
		}
		system += "][";
		for (size_t i = fixed_point + 1; i < bits.length(); i++)
		{
			const char bit = bits[i];
			if (bit != '0' && bit != '1')
				throw std::invalid_argument("Provided sequence is not a bit sequence.");
			if (bit - '0')
			{
				const size_t n = pow(2, i - fixed_point);
				system += "{";
				for (size_t j = 0; j < n; j++)
					system += "{}";
				system += "}";
			}
		}
		system += "]]";
		set_system(system);
		set_equivalent_spring(spring_array::equivalent_spring(get_system()));
	}

	double converter_float::recover_value(double omega_max) const
	{
		return (omega_max * omega_max);
	}
}
