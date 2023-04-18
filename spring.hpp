#ifndef SPRING_HPP
# define SPRING_HPP

# include <vector>

namespace aua
{
	typedef std::vector<double> double_vector;

	class spring
	{
		private:
			double	_k;
			void set_k(double k);
		public:
			spring();
			~spring();
			spring(double k);
			spring(const spring &other);
			spring &operator=(const spring &other);
			double get_k() const;
			double_vector move(double t, double dt, double x0, double v0);
			double_vector move(double t, double dt, double x0);
			double_vector move(double t0, double t1, double dt, double x0, double v0);
			double_vector move(double t0, double t1, double dt, double x0, double v0, double m);
	};
}

#endif