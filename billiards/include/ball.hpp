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
			void intersect_circle(const vector2d &center, vector2d &answer1, vector2d &answer2);
			void intersect_line(const vector2d &base, vector2d &answer);
	};

	std::ostream &operator<<(std::ostream &o, const aua::ball &b);
} // namespace aua

#endif
