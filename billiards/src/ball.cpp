#include "stdafx.hpp"
#include "ball.hpp"

namespace aua
{
	ball::ball() : _position(), _momentum(), _table() {}

	ball::~ball() {}

	ball::ball(vector2d position, vector2d momentum, table table) : _position(position), _momentum(momentum), _table(table) {}

	ball::ball(const ball &other) : _position(other._position), _momentum(other._momentum) {}

	ball &ball::operator=(const ball &other)
	{
		this->_position = other._position;
		this->_momentum = other._momentum;
		return (*this);
	}

	ball ball::rand(table table)
	{
		std::uniform_real_distribution<double> unif(-table.get_radius(), table.get_radius());
		std::uniform_real_distribution<double> sunif(-1.0, 1.0);
		std::random_device rd;
		std::default_random_engine sample(rd());
		vector2d position;
		vector2d momentum(sunif(sample), sunif(sample));
		const double magnitude = std::sqrt(momentum.first * momentum.first + momentum.second * momentum.second);

		momentum.first /= magnitude;
		momentum.second /= magnitude;
		do
		{
			position = vector2d(unif(sample), unif(sample));
		} while (position.first * position.first + position.second * position.second >= 1);
		return (ball(position, momentum, table));
	}

	const vector2d &ball::get_position() const
	{
		return (this->_position);
	}

	const vector2d &ball::get_momentum() const
	{
		return (this->_momentum);
	}
} // namespace aua

std::ostream &operator<<(std::ostream &o, const aua::ball &b)
{
	o << "pos: [" << b.get_position().first << ", " << b.get_position().second << "]; mom: [" << b.get_momentum().first << ", " << b.get_momentum().second << "]";
	return (o);
}
