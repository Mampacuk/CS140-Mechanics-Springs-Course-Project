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
			std::cout << "generated a ball with position: " << GREEN BOLD << position << RESET GRAY << ", momentum: " << GREEN BOLD << momentum << RESET << std::endl;
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
		vector2d old_momentum = _momentum;
		#ifdef DEBUG_COLLISION_AND_ABSERR
			std::cout << GRAY;
			std::cout << "current position: " << LGREEN << _position << GRAY << ", current momentum: " << LGREEN << _momentum << RESET << " ";
			std::cout << RESET;
		#endif
		_position = (_table.is_vertical() ? vertical_intersection() : horizontal_intersection());
		_momentum.normalize();
		_reflections.push_back(_position);
		#ifdef DEBUG_COLLISION_AND_ABSERR
			std::cout << GRAY;
			std::cout << "new position: " << LGREEN << _position << GRAY << ", new momentum: " << LGREEN << _momentum << RESET << std::endl; 
			std::cout << RESET;
		#endif
		return (old_momentum);
	}

	vector2d ball::horizontal_intersection()
	{
		vector2d answer1;
		vector2d answer2;
		const double L = _table.get_length();

		if (_momentum.y() != 0)
			line_intersect_line(vector2d(0, _table.get_radius() * sgn(_momentum.y())), answer1);
		if (answer1.x() < 0 || (_momentum.y() == 0 && _momentum.x() < 0))
		{
			#ifdef DEBUG_COLLISION_AND_ABSERR
				std::cout << LRED;
				std::cout << "hit the left semi-circle ";
				std::cout << RESET;
			#endif
			line_intersect_circle(vector2d(0, 0), answer1, answer2);
			_momentum = vector2d((answer1.y() * answer1.y() - answer1.x() * answer1.x()) * _momentum.x() - 2 * answer1.x() * answer1.y() * _momentum.y(), -2 * answer1.x() * answer1.y() * _momentum.x() + (answer1.x() * answer1.x() - answer1.y() * answer1.y()) * _momentum.y());
		}
		else if (answer1.x() > L || (_momentum.y() == 0 && _momentum.x() > 0))
		{
			#ifdef DEBUG_COLLISION_AND_ABSERR
				std::cout << LRED;
				std::cout << "hit the right semi-circle ";
				std::cout << RESET;
			#endif
			line_intersect_circle(vector2d(L, 0), answer1, answer2);
			_momentum = vector2d((answer1.y() * answer1.y() - (answer1.x() - L) * (answer1.x() - L)) * _momentum.x() - 2 * (answer1.x() - L) * answer1.y() * _momentum.y(), -2 * (answer1.x() - L) * answer1.y() * _momentum.x() + ((answer1.x() - L) * (answer1.x() - L) - answer1.y() * answer1.y()) * _momentum.y());
		}
		else
		{
			#ifdef DEBUG_COLLISION_AND_ABSERR
				std::cout << LRED;
				std::cout << "hit the line ";
				std::cout << RESET;
			#endif
			_momentum = vector2d(_momentum.x(), -_momentum.y());
		}
		return (answer1);
	}

	vector2d ball::vertical_intersection()
	{
		double x, y;
		const double r = _table.get_radius();
		auto closure = [=](double x) { return objective(r, _position.x(), _position.y(), _momentum.x(), _momentum.y(), x); };
		if (_momentum.x() < 0)
		{
			x = bisection(closure, -r, _position.x());
			x = failsafe_bisection(closure, x, x, _position.x(), true);
		}
		else
		{
			x = bisection(closure, _position.x(), r);
			x = failsafe_bisection(closure, x, x, _position.x(), false);
		}
		y = _position.y() + (_momentum.y() / _momentum.x()) * (x - _position.x()) - (GRAVITY * (x - _position.x()) * (x - _position.x())) / (2 * _momentum.x() * _momentum.x());
		_momentum = vector2d((y * y - x * x) * _momentum.x() - 2 * x * y * _momentum.y(), -2 * x * y * _momentum.x() + (x * x - y * y) * _momentum.y());
		return (vector2d(x, y));
	}

	double ball::objective(double r, double x0, double y0, double px, double py, double x) const
	{
		double y = y0 + (py / px) * (x - x0) - (GRAVITY * (x - x0) * (x - x0)) / (2 * px * px);
		return (y * y + x * x - r * r);
	}

	double ball::failsafe_bisection(std::function<double(double)> f, double failsafe, double x, double bound, bool upper_bound) const
	{
		if (!std::isnan(failsafe))
		{
			if (upper_bound)
				return (failsafe_bisection(f, bisection(f, failsafe + std::numeric_limits<double>::epsilon(), bound), failsafe, bound, upper_bound));
			else
				return (failsafe_bisection(f, bisection(f, bound, failsafe - std::numeric_limits<double>::epsilon()), failsafe, bound, upper_bound));
		}
		return (x);
	}

	double ball::bisection(std::function<double(double)> f, double a, double b, double epsilon) const
	{
		double mid = (a + b) / 2;
		double mid_prev;

		if (f(a) * f(b) >= 0)
			return (std::nan(""));
		do
		{
			mid_prev = mid;
			if (f(a) * f(mid) < 0)
				b = mid;
			else
				a = mid;
			mid = (a + b) / 2;
		} while (std::abs(mid - mid_prev) > epsilon);
		return (mid);
	}

	void ball::line_intersect_circle(const vector2d &center, vector2d &answer1, vector2d &answer2) const
	{
		double prefactor = (center -_position) * _momentum;
		double square_root = std::sqrt(prefactor * prefactor - (_position * _position + center * center - _table.get_radius() * _table.get_radius() - 2 * _position * center));
		answer1 = _position + (prefactor + square_root) * _momentum;
		answer2 = _position + (prefactor - square_root) * _momentum;
	}

	void ball::line_intersect_line(const vector2d &base, vector2d &answer) const
	{
		answer = _position + (1 / _momentum.y()) * (base.y() - _position.y()) * _momentum;
	}

	std::ostream &operator<<(std::ostream &o, const ball &b)
	{
		o << "pos: " << b.get_position() << "; mom: " << b.get_momentum();
		return (o);
	}
} // namespace aua
