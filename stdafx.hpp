#ifndef STDAFX_HPP
# define STDAFX_HPP

# include <vector>
# include <cmath>
# include <string>
# include <stdexcept>
# include <iostream>

namespace aua
{
	class spring;

	typedef spring (spring::*spring_connection)(const spring&) const;

	typedef std::vector<double> double_vector;
	typedef std::vector<spring> spring_vector;
}

#endif
