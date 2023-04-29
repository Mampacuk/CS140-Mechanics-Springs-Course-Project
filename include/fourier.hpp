#ifndef FOURIER_HPP
# define FOURIER_HPP

# include "stdafx.hpp"

namespace aua
{
	class fourier
	{
		public:
			fourier();
			~fourier();
			fourier(const fourier&);
			fourier &operator=(const fourier&);
			static double_pair_vector transform(const double_vector &oscillations, double period);
	};
} // namespace aua

#endif
