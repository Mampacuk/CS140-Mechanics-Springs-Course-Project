#include "stdafx.hpp"
#include "converter_float.hpp"

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

		converter.construct_system("11.0");
		std::cout << converter.get_equivalent_spring() << std::endl;
	}
}
