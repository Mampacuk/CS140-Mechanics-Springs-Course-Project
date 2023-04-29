#ifndef CONVERTER_INT_HPP
# define CONVERTER_INT_HPP

# include "converter.hpp"
# include "converter_float.hpp"

namespace aua
{
	class converter_int : public converter
	{
		private:
			size_t _fixed_point;
		public:
			converter_int();
			virtual ~converter_int();
			converter_int(const converter_int&);
			converter_int &operator=(const converter_int&);
			void construct_system(const std::string &bits);
		protected:
			virtual void check_length(const std::string &bits) const;
			double recover_value(double omega_max) const;
	};
}

#endif
