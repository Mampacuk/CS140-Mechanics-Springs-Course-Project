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
		std::cout << "in spring::move()" << std::endl;
		std::cout << "t0 = " << t0 << ", t1 = " << t1 << ", dt = " << dt << ", x0 = " << x0 << ", v0 = " << v0 << ", m = " << m << std::endl;
		double_vector coordinates;
		const double omega = spring::omega(m);
		const double A = x0 * sin(omega * t0) + (v0 * cos(omega * t0)) / omega;
		const double B = x0 * cos(omega * t0) - (v0 * sin(omega * t0)) / omega;
		std::cout << "omega = " << omega << ", A = " << A << ", B = " << B << std::endl;
		for (double t = t0; t < t1; t += dt)
		{
			const double tf = std::min(t, t1);
			// std::cout << "in spring, t = " << tf << std::endl;
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

	spring &spring::operator*=(const spring &that)
	{
		return (*this = *this * that);
	}

	spring &spring::operator+=(const spring &that)
	{
		return (*this = *this + that);
	}

	std::ostream &operator<<(std::ostream &o, const spring &s)
	{
		o << s.get_k();
		return (o);
	}
} // namespace aua
