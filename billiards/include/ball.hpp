#ifndef BALL_HPP
# define BALL_HPP

# include "stdafx.hpp"
# include "table.hpp"

namespace aua
{
	class ball
	{
		private:
			vector2d _position;
			vector2d _momentum;
			table _table;
		public:
			ball();
			~ball();
			ball(vector2d position, vector2d momentum, table table);
			ball(const ball &other);
			ball &operator=(const ball &other);
			static ball rand(table table);
			const vector2d &get_position() const;
			const vector2d &get_momentum() const;
	};
} // namespace aua

std::ostream &operator<<(std::ostream &o, const aua::ball &b);

#endif
