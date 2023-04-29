#include "stdafx.hpp"
#include "converter_float.hpp"
#include "converter_int.hpp"
#include "converter8bit.hpp"

int main()
{
	{
		aua::spring test = aua::spring_array::equivalent_spring("[[[]{}]{[][]}]");
		//														   1+1 +  1*1 = 2 + 0.5 = 2.5
		std::cout << "the spring's k is " << test << " (must be 2.5)" << std::endl;
	}

	{
		aua::spring_vector springs;

		springs.push_back(aua::spring(3));
		springs.push_back(aua::spring(5));
		springs.push_back(aua::spring(6));
		springs.push_back(aua::spring(1));

		aua::spring test = aua::spring_array::equivalent_spring("[[[]{}]{[][]}]", springs.begin(), springs.end());
		//														   3+5 + 6*1 = 8 + 6/7 = 8 + 0.85714 = 8.85714
		std::cout << "the spring's k is " << test << " (must be 8.85714)" << std::endl;
	}

	{
		aua::converter_float converter;

		converter.construct_system("111.");
		std::cout << converter.get_system() << std::endl;
		std::cout << converter.get_equivalent_spring() << std::endl;

		std::cout << "approximation for \"111.0\": " << converter.approximate_value(5) << std::endl;
	}

	{
		aua::converter_int converter;

		converter.construct_system("00010001");
		std::cout << converter.get_system() << std::endl;
		std::cout << converter.get_equivalent_spring() << std::endl;

		std::cout << "approximation for \"00010001\": " << converter.approximate_value(4) << std::endl;
	}

	{
		aua::converter_int converter;

		converter.construct_system("10001");
		std::cout << converter.get_system() << std::endl;
		std::cout << converter.get_equivalent_spring() << std::endl;

		std::cout << "approximation for \"00010001\": " << converter.approximate_value(4) << std::endl;
	}

	{
		aua::converter8bit converter;

		converter.construct_system("10001");
		std::cout << converter.get_system() << std::endl;
		std::cout << converter.get_equivalent_spring() << std::endl;

		std::cout << "approximation for \"00010001\": " << converter.approximate_value(4) << std::endl;
	}

	{
		aua::converter8bit converter;

		converter.construct_system("10001");
		std::cout << converter.get_system() << std::endl;
		std::cout << converter.get_equivalent_spring() << std::endl;

		std::cout << "approximation for \"00010001\": " << converter.approximate_value(4) << std::endl;
	}
}
