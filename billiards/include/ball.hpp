#ifndef BALL_HPP
# define BALL_HPP

# include "stdafx.hpp"
# include "table.hpp"
# include "vector2d.hpp"

namespace aua
{
	class ball
	{
		private:
			vector2d 		_position;
			vector2d		_momentum;
			table			_table;
			vector2d_vector	_reflections;
		public:
			ball();
			~ball();
			ball(vector2d position, vector2d momentum, table table);
			ball(const ball &other);
			ball &operator=(const ball &other);
			static ball rand(table table);
			const vector2d &get_position() const;
			const vector2d &get_momentum() const;
			const vector2d_vector &get_reflections() const;
			void set_position(const vector2d &position);
			void set_momentum(const vector2d &momentum);
			vector2d bounce();
		private:
			vector2d horizontal_intersection();
			vector2d vertical_intersection();
			void line_intersect_circle(const vector2d &center, vector2d &answer1, vector2d &answer2) const;
			void line_intersect_line(const vector2d &base, vector2d &answer) const;
			void parabola_intersect_circle();
			double objective(double r, double x0, double y0, double v0x, double v0y, double x) const;
			double failsafe_bisection(std::function<double(double)> f, double failsafe, double x, double bound, bool upper_bound) const;
			double bisection(std::function<double(double)> f, double a, double b, double epsilon = std::numeric_limits<double>::epsilon()) const;
	};

	std::ostream &operator<<(std::ostream &o, const aua::ball &b);
} // namespace aua

#endif
