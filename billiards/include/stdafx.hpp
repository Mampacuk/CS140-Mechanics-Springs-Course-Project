#ifndef STDAFX_HPP
# define STDAFX_HPP

# include <utility>
# include <random>
# include <numbers>
# include <cmath>
# include <iostream>
# include <stdexcept>
# include <vector>
# include <sstream>

# define DELTA 0.01

namespace aua
{
	class vector2d;

	typedef std::vector<vector2d> vector2d_vector;

	template <typename T> int sgn(T val)
	{
		return ((T(0) < val) - (val < T(0)));
	}
} // namespace aua

#endif
