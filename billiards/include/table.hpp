#ifndef TABLE_HPP
# define TABLE_HPP

# include "stdafx.hpp"

namespace aua
{
	class table
	{
		private:
			double _radius;
			double _l;
			double _mom_lb;
			double _mom_ub;
		public:
			~table();
			table(const table &other);
			table(double radius = 1, double l = 0, double mom_lb = 1, double mom_ub = 1);
			table &operator=(const table &other);
			double get_radius() const;
			double get_l() const;
			double get_momentum_lb() const;
			double get_momentum_ub() const;
	};
} // namespace aua

#endif
