#include "fourier.hpp"

namespace aua
{
	fourier::fourier() {}

	fourier::~fourier() {}

	fourier::fourier(const fourier&) {}

	fourier &fourier::operator=(const fourier&) { return (*this); }

	// returns a double pair vector with coefficients:
	// pair.first = aj, pair.second = bj
	double_pair_vector fourier::transform(const double_vector &oscillations, double period)
	{
		const size_t samples = oscillations.size();
		const double dt = period / samples;
		const double omega0 = 2 * M_PI / period;
		double_pair_vector amplitudes;

		for (size_t j = 0; j < oscillations.size(); j++)
		{
			double dist;
			double t = 0;
			double aj = 0, bj = 0;
			for (size_t i = 0; i < oscillations.size(); i++, t += dt)
			{
				aj += oscillations[i] * cos(j * omega0 * i * t);
				bj += oscillations[i] * sin(j * omega0 * i * t);
			}
			aj = 2 * dt * aj / period;
			bj = 2 * dt * bj / period;
			amplitudes.push_back(double_pair(aj, bj));
		}
		return (amplitudes);
	}
} // namespace aua
