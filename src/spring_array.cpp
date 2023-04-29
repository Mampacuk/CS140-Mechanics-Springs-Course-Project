# include "spring_array.hpp"

namespace aua
{
	spring_array::spring_array() {}

	spring_array::~spring_array() {}

	spring_array::spring_array(const spring_array&) {}

	spring_array &spring_array::operator=(const spring_array&) { return (*this); }

	spring spring_array::equivalent_spring(const std::string &spring_expr)
	{
		size_t i = 0;
		if (spring_expr.empty())
			throw std::length_error("Empty Spring Expression Received.");
		spring eff = build_spring(spring_expr, choose_connection(spring_expr[i]), i);
		if (i != spring_expr.size())
			throw std::invalid_argument("Invalid Bracket/Brace Sequence Received.");
		return (eff);
	}

	spring spring_array::build_spring(const std::string &spring_expr, spring_connection connect, size_t &i)
	{
		aua::spring spring;
		const size_t start = i;

		i++;
		if (i == spring_expr.size())
			throw std::invalid_argument("Invalid Bracket/Brace Sequence Received.");
		if (is_closing(spring_expr[start], spring_expr[i]))
		{
			i++;
			return (spring);
		}
		spring = build_spring(spring_expr, choose_connection(spring_expr[i]), i);
		while (!is_closing(spring_expr[start], spring_expr[i]))
		{
			aua::spring subspring = build_spring(spring_expr, choose_connection(spring_expr[i]), i);
			spring = (spring.*connect)(subspring);
		}
		i++;
		return (spring);
	}

	spring_connection spring_array::choose_connection(const char bracket)
	{
		if (bracket == '{' || bracket == '}')
			return (spring::in_series);
		else if (bracket == '[' || bracket == ']')
			return (spring::in_parallel);
		throw std::invalid_argument("Invalid Bracket/Brace Received.");
	}

	bool spring_array::is_closing(const char opening, const char closing)
	{
		if (closing != '}' && closing != ']' && closing != '[' && closing != '{')
			throw std::invalid_argument("Invalid Closing Bracket/Brace Encountered.");
		if (opening == '{')
			return (closing == '}');
		else if (opening == '[')
			return (closing == ']');
		throw std::invalid_argument("Invalid Opening Bracket/Brace Encountred.");
	}
} // namespace aua
