#include "converter.hpp"

namespace aua
{
	converter::converter() : _system(), _equivalent_spring() {}

	converter::~converter() {}

	converter::converter(const converter &other) : _system(other._system), _equivalent_spring(other._equivalent_spring) {}

	converter &converter::operator=(const converter &other)
	{
		this->_system = other._system;
		this->_equivalent_spring = other._equivalent_spring;
		return (*this);
	}

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

	double converter::approximate_value(size_t samples, double x0, double v0, double period) const
	{
		double omega_max = analyze_amplitudes(oscillate(samples, x0, v0, period), period);
		return (recover_value(omega_max));
	}

	double_vector converter::oscillate(size_t samples, double x0, double v0, double period) const
	{
		// std::cout << "equivalent spring with k = " << this->_equivalent_spring << std::endl;
		// std::cout << samples << " samples, period = " << period << ". oscillations are:" << std::endl;
		double_vector oscillations = this->_equivalent_spring.move(period, period / samples, x0, v0);
		// for (size_t i = 0; i < oscillations.size(); i++)
		// 	std::cout << oscillations[i] << ' ';
		// std::cout << std::endl;
		return (oscillations);
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
		j_max++; // to compensate for 0-indexing
		// std::cout << "j_max =" << j_max << std::endl;
		return (omega0 * j_max);
	}
} // namespace aua
