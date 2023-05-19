#ifndef VECTOR2D_HPP
# define VECTOR2D_HPP

# include "stdafx.hpp"

namespace aua
{
	class vector2d
	{
		private:
			double _x;
			double _y;
		public:
			vector2d();
			~vector2d();
			vector2d(double x, double y);
			vector2d(const vector2d &other);
			vector2d &operator=(const vector2d &other);
			double get_x() const;
			double get_y() const;
			void set_x(double x);
			void set_y(double y);
			double magnitude() const;
			double operator*(const vector2d &other) const;
			vector2d operator*(double scalar) const;
			vector2d operator-() const;
			vector2d operator-(const vector2d &other) const;
			vector2d operator+(const vector2d &other) const;
	};

	vector2d operator*(double scalar, const vector2d &vector);
	std::ostream &operator<<(std::ostream &o, const aua::vector2d &v);
} // namespace aua


#endif
