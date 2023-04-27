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

	void spring::set_k(double k)
	{
		this->_k = k;
	}

	double spring::omega(double m) const
	{
		return (sqrt(get_k() / m));
	}

	double spring::A(double t0, double x0, double v0, double m) const
	{
		return (x0 * sin(omega(m) * t0) + (v0 * cos(omega(m) * t0)) / omega(m));
	}

	double spring::B(double t0, double x0, double v0, double m) const
	{
		return (x0 * cos(omega(m) * t0) - (v0 * sin(omega(m) * t0)) / omega(m));
	}

	double spring::get_k() const
	{
		return (this->_k);
	}

	double_vector spring::move(double t, double dt, double x0, double v0) const
	{
		return (move(0, t, dt, x0, v0, 1));
	}

	double_vector spring::move(double t, double dt, double x0) const
	{
		return (move(0, t, dt, x0, 0, 1));
	}

	double_vector spring::move(double t0, double t1, double dt, double x0, double v0) const
	{
		return (move(t0, t1, dt, x0, v0, 1));
	}

	double_vector spring::move(double t0, double t1, double dt, double x0, double v0, double m) const
	{
		double_vector coordinates;
		const double A = spring::A(t0, x0, v0, m);
		const double B = spring::B(t0, x0, v0, m);
		const double omega = spring::omega(m);
		for (double t = t0; t <= t1; t += dt)
		{
			const double tf = std::min(t, t1);
			coordinates.push_back(A * sin(omega * tf) + B * cos(omega * tf));
		}
		return (coordinates);
	}

	spring spring::in_series(const spring &that) const
	{
		return (spring(get_k() * that.get_k() / (get_k() + that.get_k())));
	}

	spring spring::in_parallel(const spring &that) const
	{
		return (spring(get_k() + that.get_k()));
	}

	spring spring::operator*(const spring &that) const
	{
		return (in_series(that));
	}

	spring spring::operator+(const spring &that) const
	{
		return (in_parallel(that));
	}

	std::ostream &operator<<(std::ostream &o, const spring &s)
	{
		o << s.get_k();
		return (o);
	}
} // namespace aua
