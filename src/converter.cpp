#include "converter.hpp"

namespace aua
{
	converter::converter() {}

	converter::~converter() {}

	converter::converter(const converter&) {}

	converter &converter::operator=(const converter&) {}

	void converter::set_system(const std::string &system)
	{
		this->_system = system;
	}

	void converter::set_equivalent_spring(const spring &spring)
	{
		this->_equivalent_spring = spring;
	}

	const std::string &converter::get_system() const
	{
		return (this->_system);
	}

	const spring &converter::get_equivalent_spring() const
	{
		return (this->_equivalent_spring);
	}

	double converter::approximate_value(size_t samples, double period) const
	{
		double omega_max = analyze_amplitudes(oscillate(samples, period), period);
		return (recover_value(omega_max));
	}

	double_vector converter::oscillate(size_t samples, double period) const
	{
		return (this->_equivalent_spring.move(period, period / samples, 0)); // x0 = 0
	}

	double converter::analyze_amplitudes(const double_vector &oscillations, double period) const
	{
		size_t j_max = 0;
		double dist_max = 0;
		const double omega0 = 2 * M_PI / period;
		double_pair_vector amplitudes = fourier::transform(oscillations, period);
		for (size_t j = 0; j < amplitudes.size(); j++)
		{
			const double aj = amplitudes[j].first;
			const double bj = amplitudes[j].second;
			double dist = sqrt(aj * aj + bj * bj);
			if (dist > dist_max)
			{
				dist_max = dist;
				j_max = j;
			}
		}
		return (omega0 * j_max);
	}
}
