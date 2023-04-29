#ifndef CONVERTER_HPP
# define CONVERTER_HPP

# include "spring.hpp"
# include "spring_array.hpp"
# include "fourier.hpp"

namespace aua
{
	class converter
	{
		private:
			std::string 	_system;
			spring			_equivalent_spring;
		protected:
			converter();
			virtual ~converter();
			converter(const converter&);
			void set_system(const std::string &system);
			void set_equivalent_spring(const spring &spring);
		public:
			converter &operator=(const converter&);
			virtual void construct_system(const std::string &bits) = 0;
			const std::string &get_system() const;
			const spring &get_equivalent_spring() const;
			double approximate_value(size_t samples, double x0 = 1, double v0 = 0, double period = 2 * M_PI) const;
		private:
			double_vector oscillate(size_t samples, double x0, double v0, double period) const;
			double analyze_amplitudes(const double_vector &oscillations, double period) const;
		protected:
			virtual double recover_value(double omega_max) const = 0;
	};
} // namespace aua

#endif
