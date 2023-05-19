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
		_position = other._position;
		_momentum = other._momentum;
		return (*this);
	}

	ball ball::rand(table table)
	{
		double theta;
		double r;
		vector2d position;
		vector2d momentum;
		std::uniform_real_distribution<double> unif(0.0, 1.0);
		std::random_device rd;
		std::default_random_engine generate(rd());

		theta = unif(generate) * 2 * std::numbers::pi;
		r = table.get_radius() * std::sqrt(unif(generate));

		position.set_x(r * std::cos(theta) + table.get_l() * unif(generate));
		position.set_y(r * std::sin(theta));

		theta = unif(generate) * 2 * std::numbers::pi;
		r = (table.get_momentum_ub() - table.get_momentum_lb()) * std::sqrt(unif(generate)) + table.get_momentum_lb();
		
		momentum.set_x(r * std::cos(theta));
		momentum.set_y(r * std::sin(theta));
		return (ball(position, momentum, table));
	}

	const vector2d &ball::get_position() const
	{
		return (_position);
	}

	const vector2d &ball::get_momentum() const
	{
		return (_momentum);
	}

	vector2d ball::bounce()
	{
		if (!_table.get_l())
		{
			double prefactor = -_position * _momentum;
			double square_root = std::sqrt(prefactor * prefactor - (_position * _position - _table.get_radius() * _table.get_radius()));
			double lambda_plus = prefactor + square_root;
			double lambda_minus = prefactor - square_root;

			vector2d x_plus = _position + lambda_plus * _momentum;
			vector2d x_minus = _position + lambda_minus * _momentum;
			std::cout << "x+:" << x_plus << ", x-:" << x_minus << std::endl;
		}
		return (_position);
	}

	std::ostream &operator<<(std::ostream &o, const ball &b)
	{
		o << "pos: " << b.get_position() << "; mom: " << b.get_momentum();
		return (o);
	}
} // namespace aua
