#include "stdafx.hpp"
#include "ball.hpp"

int main(int argc, char **argv)
{
	size_t n;
	int signed_n;
	if (argc != 2)
	{
		std::cerr << "Usage: billiards <n>" << std::endl;
		return (EXIT_FAILURE);
	}
	std::stringstream ss(argv[1]);
	ss >> signed_n;
	if (ss.fail() || signed_n < 1)
	{
		std::cerr << "Invalid value for n." << std::endl;
		return (EXIT_FAILURE);
	}
	n = static_cast<size_t>(signed_n);
	aua::vector2d last_momentum;
	{
		aua::table table = aua::table();
		aua::ball ball = aua::ball::rand(table);
		std::cout << "ball: " << ball << std::endl;
		for (size_t i = 0; i < n; i++)
		{
			last_momentum = ball.bounce();
			// std::cout << "ball.reflections[" << i << "]: " << ball.get_reflections().back() << " with norm=|" << ball.get_reflections().back().norm() << "|" << std::endl;
		}
		aua::ball rball = aua::ball(ball.get_position(), -last_momentum, table);
		std::cout << "rball: " << rball << std::endl;
		for (size_t i = 0; i < n; i++)
		{
			rball.bounce();
			// std::cout << "rball.reflections[" << i << "]: " << rball.get_reflections().back() << " with norm=|" << rball.get_reflections().back().norm() << "|" << std::endl;
		}
		// for (size_t i = 0; i < n; i++)
		// {
		// 	std::cout << "ball.reflections[" << i << "]: " << ball.get_reflections()[i] << " with norm=|" << ball.get_reflections()[i].norm() << "|, rball.reflections[" << i << "]: " << rball.get_reflections()[i] << " with norm=|" << rball.get_reflections()[i].norm() << "|" << std::endl;
		// }
		size_t i;
		for (i = 0; i < n - 1; i++)
		{
			// std::cout << "abserr is " << (ball.get_reflections()[i] - rball.get_reflections()[n - 2 - i]).norm() << std::endl;
			// std::cout << "is it greater than " << DELTA << "? " << ((ball.get_reflections()[i] - rball.get_reflections()[n - 2 - i]).norm() > DELTA ? "YES" : "NO") << std::endl;
			if ((ball.get_reflections()[i] - rball.get_reflections()[n - 2 - i]).norm() > DELTA)
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
}
