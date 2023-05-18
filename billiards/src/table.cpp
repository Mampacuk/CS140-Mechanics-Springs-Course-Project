#include "table.hpp"

namespace aua
{
	table::~table() {}

	table::table(const table &other) : _radius(other._radius), _l(other._l) {}

	table::table(double radius, double l) : _radius(radius), _l(l) {}

	table &table::operator=(const table &other)
	{
		this->_radius = other._radius;
		this->_l = other._l;
		return (*this);
	}

	double table::get_radius() const
	{
		return (this->_radius);
	}

	double table::get_l() const
	{
		return (this->_l);
	}
} // namespace aua
