#ifndef SPRING_HPP
# define SPRING_HPP

# include "stdafx.hpp"

namespace aua
{
	class spring
	{
		private:
			double	_k;	// stiffness coefficient
			void	set_k(double k);
			double	omega(double m) const;
			double	A(double t0, double x0, double v0, double m) const;
			double	B(double t0, double x0, double v0, double m) const;
		public:
			spring();
			~spring();
			explicit spring(double k);
			spring(const spring &other);
			spring &operator=(const spring &other);
			double			get_k() const;
			double_vector	move(double t, double dt, double x0, double v0) const;
			double_vector	move(double t, double dt, double x0) const;
			double_vector	move(double t0, double t1, double dt, double x0, double v0) const;
			double_vector	move(double t0, double t1, double dt, double x0, double v0, double m) const;
			spring			in_series(const spring &that) const;
			spring			in_parallel(const spring &that) const;
			spring			operator*(const spring &that) const;
			spring			operator+(const spring &that) const;
	};
}

#endif
