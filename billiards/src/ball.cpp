#include "stdafx.hpp"
#include "ball.hpp"

namespace aua
{
	ball::ball() : _position(), _momentum(), _table(), _reflections() {}

	ball::~ball() {}

	ball::ball(vector2d position, vector2d momentum, table table) : _position(position), _momentum(momentum), _table(table), _reflections() {}

	ball::ball(const ball &other) : _position(other._position), _momentum(other._momentum), _reflections() {}

	ball &ball::operator=(const ball &other)
	{
		_position = other._position;
		_momentum = other._momentum;
		_table = other._table;
		_reflections.clear();
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

		position.set_x(r * std::cos(theta) + table.get_length() * unif(generate));
		position.set_y(r * std::sin(theta));

		theta = unif(generate) * 2 * std::numbers::pi;
		r = (table.get_momentum_ub() - table.get_momentum_lb()) * std::sqrt(unif(generate)) + table.get_momentum_lb();
		
		momentum.set_x(r * std::cos(theta));
		momentum.set_y(r * std::sin(theta));
		#ifdef DEBUG
			std::cout << GRAY;
			std::cout << "generated a ball with position: " << GREEN << position << GRAY << ", momentum: " << GREEN << momentum << RESET << std::endl;
			std::cout << RESET;
		#endif
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

	const vector2d_vector &ball::get_reflections() const
	{
		return (_reflections);
	}

	void ball::set_position(const vector2d &position)
	{
		this->_position = position;
	}

	void ball::set_momentum(const vector2d &momentum)
	{
		this->_momentum = momentum;
	}

	vector2d ball::bounce()
	{
		vector2d answer1;
		vector2d answer2;
		const double L = _table.get_length();
		vector2d old_momentum = _momentum;
		#ifdef OUTPUT_COLLISION_AND_ABSERR
			std::cout << GRAY;
			std::cout << "current position: " << LGREEN << _position << GRAY << ", current momentum: " << LGREEN << _momentum << RESET << " ";
			std::cout << RESET;
		#endif
		if (_momentum.y() != 0)
			intersect_line(vector2d(0, _table.get_radius() * sgn(_momentum.y())), answer1);
		if (answer1.x() < 0 || (_momentum.y() == 0 && _momentum.x() < 0))
		{
			#ifdef OUTPUT_COLLISION_AND_ABSERR
				std::cout << LRED;
				std::cout << "hit the left semi-circle ";
				std::cout << RESET;
			#endif
			intersect_circle(vector2d(0, 0), answer1, answer2);
			_momentum = vector2d((answer1.y() * answer1.y() - answer1.x() * answer1.x()) * _momentum.x() - 2 * answer1.x() * answer1.y() * _momentum.y(),
							-2 * answer1.x() * answer1.y() * _momentum.x() + (answer1.x() * answer1.x() - answer1.y() * answer1.y()) * _momentum.y());
		}
		else if (answer1.x() > L || (_momentum.y() == 0 && _momentum.x() > 0))
		{
			#ifdef OUTPUT_COLLISION_AND_ABSERR
				std::cout << LRED;
				std::cout << "hit the right semi-circle ";
				std::cout << RESET;
			#endif
			intersect_circle(vector2d(L, 0), answer1, answer2);
			_momentum = vector2d((answer1.y() * answer1.y() - (answer1.x() - L) * (answer1.x() - L)) * _momentum.x() - 2 * (answer1.x() - L) * answer1.y() * _momentum.y(),
							-2 * (answer1.x() - L) * answer1.y() * _momentum.x() + ((answer1.x() - L) * (answer1.x() - L) - answer1.y() * answer1.y()) * _momentum.y());
		}
		else
		{
			#ifdef OUTPUT_COLLISION_AND_ABSERR
				std::cout << LRED;
				std::cout << "hit the line ";
				std::cout << RESET;
			#endif
			_momentum = vector2d(_momentum.x(), -_momentum.y());
		}
		_momentum.normalize();
		_position = answer1;
		_reflections.push_back(_position);
		#ifdef OUTPUT_COLLISION_AND_ABSERR
			std::cout << GRAY;
			std::cout << "new position: " << LGREEN << _position << GRAY << ", new momentum: " << LGREEN << _momentum << RESET << std::endl; 
			std::cout << RESET;
		#endif
		return (old_momentum);
	}

	void ball::intersect_circle(const vector2d &center, vector2d &answer1, vector2d &answer2)
	{
		double prefactor = (center -_position) * _momentum;
		double square_root = std::sqrt(prefactor * prefactor - (_position * _position + center * center - _table.get_radius() * _table.get_radius() - 2 * _position * center));
		answer1 = _position + (prefactor + square_root) * _momentum;
		answer2 = _position + (prefactor - square_root) * _momentum;
	}

	void ball::intersect_line(const vector2d &base, vector2d &answer)
	{
		answer = _position + (1 / _momentum.y()) * (base.y() - _position.y()) * _momentum;
	}

	std::ostream &operator<<(std::ostream &o, const ball &b)
	{
		o << "pos: " << b.get_position() << "; mom: " << b.get_momentum();
		return (o);
	}
} // namespace aua
