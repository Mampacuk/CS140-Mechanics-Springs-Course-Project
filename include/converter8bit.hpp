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
			converter8bit(const converter8bit &other);
			converter8bit &operator=(const converter8bit &other);
		private:
			void check_length(const std::string &bits) const;
		private:
			double recover_value(double omega_max) const;
	};
}  // namespace aua

#endif
