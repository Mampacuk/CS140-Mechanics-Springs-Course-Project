#ifndef CONVERTER8BIT_HPP
# define CONVERTER8BIT_HPP

# include "converter_int.hpp"

namespace aua
{
	class converter8bit : public converter_int
	{
		public:
			converter8bit();
			~converter8bit();
			converter8bit(const converter8bit&);
			converter8bit &operator=(const converter8bit&);
			spring bits_to_spring(const std::string &bits) const;
			double max_amplitude_to_decimal(double omega_max) const;
		private:
			void check_length(const std::string &bits) const;
	};
}  // namespace aua

	// spring converter8bit::bits_to_spring(const std::string &bits) const
	// {
	// 	spring k_eff(0);
	// 	if (bits.length() > sizeof(int8_t))
	// 		throw std::invalid_argument("Sequence of invalid length provided to a 8-bit converter.");
	// 	for (size_t i = 0; i < bits.length(); i++)
	// 	{
	// 		const char bit = bits[i];
	// 		if (bit != '0' && bit != '1')
	// 			throw std::invalid_argument("Provided sequence is not a bit sequence.");
	// 		k_eff += spring((bit - '0') * pow(2, i));
	// 	}
	// 	return (k_eff);
	// }

#endif
