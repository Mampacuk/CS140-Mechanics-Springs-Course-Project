#ifndef SPRING_ARRAY_HPP
# define SPRING_ARRAY_HPP

# include "stdafx.hpp"
# include "spring.hpp"

namespace aua
{
	class spring_array
	{
		private:
			static spring build_spring(const std::string &spring_expr, spring_connection connect, size_t &i);
			static spring_connection choose_connection(const char bracket);
			static bool is_closing(const char opening, const char closing);
		public:
			spring_array();
			~spring_array();
			spring_array(const spring_array&);
			spring_array &operator=(const spring_array&);
			static spring equivalent_spring(const std::string &spring_expr);
		public:
			template <typename SpringIterator>
			static spring equivalent_spring(const std::string &spring_expr, SpringIterator first, SpringIterator last)
			{
				size_t i = 0;
				spring eff = build_spring(spring_expr, choose_connection(spring_expr[i]), i, first, last);
				if (i != spring_expr.size() || first != last)
					throw std::logic_error("Invalid Bracket/Brace Sequence Received.");
				return (eff);
			}
		private:
			template <typename SpringIterator>
			static spring build_spring(const std::string &spring_expr, spring_connection connect, size_t &i, SpringIterator &first, SpringIterator &last)
			{
				aua::spring spring;
				const size_t start = i;

				i++;
				if (i == spring_expr.size())
					throw std::logic_error("Invalid Bracket/Brace Sequence Received.");
				if (is_closing(spring_expr[start], spring_expr[i]))
				{
					if (first == last)
						throw std::logic_error("Invalid Bracket/Brace Sequence Received.");
					spring = *first++;
					i++;
					return (spring);
				}
				spring = build_spring(spring_expr, choose_connection(spring_expr[i]), i, first, last);
				while (!is_closing(spring_expr[start], spring_expr[i]))
				{
					aua::spring subspring = build_spring(spring_expr, choose_connection(spring_expr[i]), i, first, last);
					spring = (spring.*connect)(subspring);
				}
				i++;
				return (spring);
			}
	};

	std::ostream &operator<<(std::ostream &o, const spring &s);
} // namespace aua

#endif
