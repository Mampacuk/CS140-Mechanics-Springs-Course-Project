#ifndef STDAFX_HPP
# define STDAFX_HPP

# include <utility>
# include <random>
# include <numbers>
# include <cmath>
# include <iostream>
# include <stdexcept>
# include <vector>
# include <list>
# include <sstream>
# include <limits>
# include <cstdlib>
# include <type_traits>

# define DELTA 0.01

# define DEBUG
// # define OUTPUT_COLLISION_AND_ABSERR

# define RESET		"\033[0m"
# define BOLD		"\033[1m"
# define BLACK		"\033[30m"
# define RED		"\033[31m"
# define GREEN		"\033[32m"
# define YELLOW		"\033[33m"
# define BLUE		"\033[34m"
# define MAGENTA	"\033[35m"
# define CYAN		"\033[36m"
# define LGRAY		"\033[37m"
# define GRAY		"\033[90m"
# define LRED		"\033[91m"
# define LGREEN		"\033[92m"

namespace aua
{
	class vector2d;

	typedef std::vector<vector2d> vector2d_vector;
	typedef std::list<double> double_list;
	typedef std::vector<double_list> double_list_vector;
	template <typename T> int sgn(T val)
	{
		return ((T(0) < val) - (val < T(0)));
	}
} // namespace aua

#endif
