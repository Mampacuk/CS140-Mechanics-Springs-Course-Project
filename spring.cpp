#include "spring.hpp"

namespace aua
{
	spring::spring() : _k(1) {}

	spring::~spring() {}

	spring::spring(double k) : _k(k) {}

	spring::spring(const spring &other) : _k(other._k) {}

	spring &spring::operator=(const spring &other)
	{
		this->_k = other._k;
		return (*this);
	}

	double spring::get_k() const
	{
		return (this->_k);
	}

	void spring::set_k(double k)
	{
		this->_k = k;
	}

	double_vector spring::move(double t, double dt, double x0, double v0)
	{
		double_vector coordinates;
		//...
		return (coordinates);
	}

	double_vector spring::move(double t, double dt, double x0)
	{
		double_vector coordinates;
		//...
		return (coordinates);
	}

	double_vector spring::move(double t0, double t1, double dt, double x0, double v0)
	{
		double_vector coordinates;
		//...
		return (coordinates);
	}

	double_vector spring::move(double t0, double t1, double dt, double x0, double v0, double m)
	{
		double_vector coordinates;
		//...
		return (coordinates);
	}
}
