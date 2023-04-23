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
			spring_array(const spring_array &other);
			spring_array operator=(const spring_array &other);
			static spring equivalent_spring(const std::string &spring_expr);
			template <typename SpringIterator>
			static spring equivalent_spring(const std::string &spring_expr, SpringIterator first, SpringIterator last);
	};
}

#endif
