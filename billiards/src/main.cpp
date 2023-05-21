#include "stdafx.hpp"
#include "ball.hpp"

int main(int argc, char **argv)
{
	double L = 0.0;
	size_t n;
	int signed_n;
	if (argc != 2 && argc != 3)
	{
		std::cerr << "usage: billiards <n> [<L>]" << std::endl;
		return (EXIT_FAILURE);
	}
	try
	{
		signed_n = std::stoi(argv[1]);
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
		return (EXIT_FAILURE);
	}
	if (signed_n < 1)
	{
		std::cerr << "invalid value for n" << std::endl;
		return (EXIT_FAILURE);
	}
	n = static_cast<size_t>(signed_n);
	if (argc == 3)
	{
		try
		{
			L = std::stod(argv[2]);
		}
		catch (const std::exception &e)
		{
			std::cerr << e.what() << std::endl;
			return (EXIT_FAILURE);
		}
		if (L < 0)
		{
			std::cerr << "invalid value for L" << std::endl;
			return (EXIT_FAILURE);
		}
	}
	aua::vector2d last_momentum;
	{
		std::cout << ">>>>>>>>>>>>>> TASK 1 <<<<<<<<<<<<<<" << std::endl;
		aua::table table = aua::table();
		aua::ball ball = aua::ball::rand(table);
		for (size_t i = 0; i < n; i++)
			last_momentum = ball.bounce();
		aua::ball rball = aua::ball(ball.get_position(), -last_momentum, table);
		for (size_t i = 0; i < n; i++)
			rball.bounce();
		size_t i;
		for (i = 0; i < n - 1; i++)
		{
			double abserr = (ball.get_reflections()[i] - rball.get_reflections()[n - 2 - i]).norm();
			#ifdef OUTPUT_COLLISION_AND_ABSERR
				std::cout << GRAY;
				std::cout << "for reflection " << (i + 1) << ", abserr() is " << abserr << ". ";
				std::cout << "is it greater than " << DELTA << "? " << (abserr > DELTA ? "YES" : "NO") << std::endl;
				std::cout << RESET;
			#endif
			if (abserr > DELTA)
				break ;
		}
		if (n > 1)
		{
			if (i == n - 1)
				std::cout << "Motion is reversible within absolute error of " << DELTA << "." << std::endl;
			else
				std::cout << "Motion is not reversible; paths deviated with error g. than or eq. to " << DELTA << " after " << i << " reflections." << std::endl;
		}
		else std::cout << "Can't reverse the path of only 1 reflection." << std::endl;
	}
	if (argc == 3)
	{
		std::cout << ">>>>>>>>>>>>>> TASK 3 <<<<<<<<<<<<<<" << std::endl;
		aua::table table = aua::table(1, L);
		aua::ball ball = aua::ball::rand(table);
		aua::double_list sample;
		for (size_t i = 0; i < n; i++)
		{
			ball.bounce();
			if (ball.get_reflections().back().x() >= 0 && ball.get_reflections().back().x() <= table.get_length())
				sample.push_back(ball.get_reflections().back().x() / table.get_length());
		}
		if (!sample.empty())
		{
			const size_t bin_count = static_cast<size_t>(std::sqrt(sample.size()));
			const double interval_length = 1.0 / bin_count;
			std::cout << sample.size() << " samples, bin count is " << bin_count << ", interval length is " << interval_length << std::endl;
			aua::double_list_vector bins(bin_count);
			for (aua::double_list::iterator it = sample.begin(); it != sample.end(); it++)
				bins[static_cast<size_t>(*it / interval_length)].push_back(*it);
			#ifdef DEBUG
				std::cout << GRAY;
				for (size_t i = 0; i < bins.size(); i++)
				{
					std::cout << "bin " << i << " of size " << bins[i].size() << " with content: [";
					for (aua::double_list::iterator it = bins[i].begin(); it != bins[i].end(); it++)
						std::cout << *it << ' ';
					std::cout << "\b]" << std::endl;
				}
				std::cout << RESET;
			#endif
			size_t bin_max = 0, bin_min = std::numeric_limits<size_t>::max();
			for (size_t i = 0; i < bins.size(); i++)
			{
				if (bins[i].size() > bin_max)
					bin_max = bins[i].size();
				if (bins[i].size() < bin_min)
					bin_min = bins[i].size();
			}
			std::cout << "maximum bin size: " << bin_max << ", minimum bin size: " << bin_min << std::endl;
			std::cout << "the difference between the largest bin and the smallest bin is " << std::abs(std::make_signed_t<size_t>(bin_max) - std::make_signed_t<size_t>(bin_min)) << std::endl;
			std::cout << "the ratio between the max bin and min bin is " << (double(bin_max) / bin_min) << std::endl;
		}
		else std::cout << "no samples generated hence no uniformity check can be performed" << std::endl;
	}
}
