#include "table.hpp"

namespace aua
{
	table::~table() {}

	table::table(const table &other) : _radius(other._radius), _l(other._l), _mom_lb(other._mom_lb), _mom_ub(other._mom_ub) {}

	table::table(double radius, double l, double mom_lb, double mom_ub) : _radius(radius), _l(l), _mom_lb(mom_lb), _mom_ub(mom_ub)
	{
		if (_mom_lb > _mom_ub || radius <= 0 || l < 0 || mom_lb < 0 || mom_ub < 0)
			throw std::logic_error("Invalid arguments to a billiard table.");
	}

	table &table::operator=(const table &other)
	{
		_radius = other._radius;
		_l = other._l;
		_mom_lb = other._mom_lb;
		_mom_ub = other._mom_ub;
		return (*this);
	}

	double table::get_radius() const
	{
		return (_radius);
	}

	double table::get_l() const
	{
		return (_l);
	}

	double table::get_momentum_lb() const
	{
		return (_mom_lb);
	}

	double table::get_momentum_ub() const
	{
		return (_mom_ub);
	}
} // namespace aua
