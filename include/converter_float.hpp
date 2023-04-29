#ifndef CONVERTER_FLOAT_HPP
# define CONVERTER_FLOAT_HPP

# include "converter.hpp"

namespace aua
{
	class converter_float : public converter
	{
		public:
			converter_float();
			~converter_float();
			converter_float(const converter_float&);
			converter_float &operator=(const converter_float&);
			void construct_system(const std::string &bits);
			double max_amplitude_to_decimal(double omega_max) const;
		private:
			double recover_value(double omega_max) const;
	};
}

#endif
