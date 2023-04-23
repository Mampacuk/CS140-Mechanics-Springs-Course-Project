#ifndef SPRING_ARRAY_HPP
# define SPRING_ARRAY_HPP

# include "stdafx.hpp"
# include "spring.hpp"

namespace aua
{
	class spring_array
	{
		public:
			spring_array();
			~spring_array();
			spring_array(const spring_array &other);
			spring_array operator=(const spring_array &other);
			spring equivalent_spring(std::string spring_expr) const;
			template <typename SpringIterator>
			spring equivalent_spring(std::string spring_expr, SpringIterator first, SpringIterator last) const;
	};
}

#endif
