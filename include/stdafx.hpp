#ifndef STDAFX_HPP
# define STDAFX_HPP

# define _USE_MATH_DEFINES

# include <vector>
# include <cmath>
# include <string>
# include <stdexcept>
# include <iostream>
# include <utility>

namespace aua
{
	class spring;

	typedef spring (spring::*spring_connection)(const spring&) const;

	typedef std::pair<double, double> double_pair;

	typedef std::vector<double> double_vector;
	typedef std::vector<double_pair> double_pair_vector;
	typedef std::vector<spring> spring_vector;
} // namespace aua

#endif
