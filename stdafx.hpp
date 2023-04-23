#ifndef STDAFX_HPP
# define STDAFX_HPP

# include <vector>
# include <cmath>
# include <string>
# include <stdexcept>

namespace aua
{
	class spring;

	typedef std::vector<double> double_vector;
	typedef spring (spring::*spring_connection)(const spring&) const;
}

#endif
