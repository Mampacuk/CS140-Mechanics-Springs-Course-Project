#include "vector2d.hpp"

namespace aua
{
	vector2d::vector2d() : _x(0.0), _y(0.0) {}

	vector2d::~vector2d() {}

	vector2d::vector2d(double x, double y) : _x(x), _y(y) {}

	vector2d::vector2d(const vector2d &other) : _x(other._x), _y(other._y) {}

	vector2d &vector2d::operator=(const vector2d &other)
	{
		_x = other._x;
		_y = other._y;
		return (*this);
	}

	double vector2d::x() const
	{
		return (_x);
	}

	double vector2d::y() const
	{
		return (_y);
	}

	void vector2d::set_x(double x)
	{
		_x = x;
	}

	void vector2d::set_y(double y)
	{
		_y = y;
	}

	double vector2d::norm() const
	{
		return (std::sqrt(_x * _x + _y * _y));
	}

	void vector2d::normalize()
	{
		double magnitude = norm();
		_x /= magnitude;
		_y /= magnitude;
	}

	double vector2d::operator*(const vector2d &other) const
	{
		return (_x * other._x + _y * other._y);
	}

	vector2d vector2d::operator*(double scalar) const
	{
		return (vector2d(scalar * _x, scalar * _y));
	}

	vector2d vector2d::operator-() const
	{
		return (vector2d(-_x, -_y));
	}

	vector2d vector2d::operator-(const vector2d &other) const
	{
		return (vector2d(_x - other._x, _y - other._y));
	}

	vector2d vector2d::operator+(const vector2d &other) const
	{
		return (vector2d(_x + other._x, _y + other._y));
	}

	vector2d operator*(double scalar, const vector2d &vector)
	{
		return (vector * scalar);
	}

	std::ostream &operator<<(std::ostream &o, const vector2d &v)
	{
		o << "(" << v.x() << ", " << v.y() << ")";
		return (o);
	}
} // namespace aua
