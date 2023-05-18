#ifndef TABLE_HPP
# define TABLE_HPP

namespace aua
{
	class table
	{
		private:
			double _radius;
			double _l;
		public:
			~table();
			table(const table &other);
			table(double radius = 1, double l = 0);
			table &operator=(const table &other);
			double get_radius() const;
			double get_l() const;
	};
} // namespace aua


#endif
