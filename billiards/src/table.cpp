#include "table.hpp"

namespace aua
{
	table::~table() {}

	table::table(const table &other) : _radius(other._radius), _length(other._length), _mom_lb(other._mom_lb), _mom_ub(other._mom_ub), _vertical(other._vertical) {}

	table::table(double radius, double length, double mom_lb, double mom_ub) : _radius(radius), _length(length), _mom_lb(mom_lb), _mom_ub(mom_ub), _vertical(false)
	{
		if (_mom_lb > _mom_ub || radius <= 0 || length < 0 || mom_lb < 0 || mom_ub < 0)
			throw std::logic_error("invalid arguments to a billiard table");
	}

	table &table::operator=(const table &other)
	{
		_radius = other._radius;
		_length = other._length;
		_mom_lb = other._mom_lb;
		_mom_ub = other._mom_ub;
		return (*this);
	}

	double table::get_radius() const
	{
		return (_radius);
	}

	double table::get_length() const
	{
		return (_length);
	}

	double table::get_momentum_lb() const
	{
		return (_mom_lb);
	}

	double table::get_momentum_ub() const
	{
		return (_mom_ub);
	}

	bool table::is_vertical() const
	{
		return (_vertical);
	}

	void table::rotate_axis()
	{
		if (_length)
			std::logic_error("can't rotate a non-circular billiard table");
		_vertical = !_vertical;
	}
} // namespace aua
