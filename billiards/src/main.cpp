#include "stdafx.hpp"
#include "ball.hpp"

int main()
{
	aua::ball b = aua::ball::rand(aua::table());
	std::cout << "b currently:" << b << std::endl;
	b.bounce();
}
