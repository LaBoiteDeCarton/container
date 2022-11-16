#ifdef FT
	#include "vector.hpp"
	#define NAMESPACE ft
#else
	#include <vector>
	#define NAMESPACE std
#endif
#include <list>
#include <iostream>

#define VECT NAMESPACE::vector<int>

void	print_vector(const VECT& x)
{
	VECT::const_iterator it = x.begin();
	VECT::const_iterator ite = x.end();

	std::cout << "------ VECTOR ------" << std::endl;
	std::cout << "Size : " << x.size() << std::endl;
	std::cout << "is empty ? : ";
	if (x.empty())
		std::cout << "yes" << std::endl;
	else
		std::cout << "no" << std::endl;
	std::cout << "content : " << std::endl;
	for(;it != ite ;it++)
		std::cout << *it << " ";
	std::cout << std::endl;
	std::cout << "------ ----- ------" << std::endl;
}

int main()
{
	{
		std::list<int>	ls;
		for (int i = 0; i < 512; i++)
			ls.push_back(i * i / (3.143567528 + 6397498/3247623));
		VECT	v;
		VECT	v2(ls.begin(), ls.end());
		VECT	v3(v2.begin() + 100, v2.end() - 100);
		const VECT	v4(v3);
		VECT	v5(123);
		VECT	v6(3,42);
		VECT	v7;

		v7 = v3;

		v3[33] = 98765;
		v4[10];

		print_vector(v);
		print_vector(v2);
		print_vector(v3);
		print_vector(v4);
		print_vector(v5);
		print_vector(v6);
		print_vector(v7);
		std::cout << v3.at(1) << std::endl;
		try {
			v3.at(10000) = 42;
		}
		catch (std::out_of_range &e) {
			std::cout << "Catch out_of_range exception!" << std::endl;
		}
		catch (std::exception &e) {
			std::cout << "Catch exception: " << e.what() << std::endl;
		}
		std::cout << "assign" << std::endl;
		v6.assign(13,3);
		print_vector(v6);

		std::cout << "push_back" << std::endl;
		v6.push_back(2);
		v6.push_back(2);
		v6.push_back(2);
		v6.push_back(2);
		v6.push_back(2);
		v6.push_back(2);
		v6.push_back(2);
		v6.push_back(2);
		v6.push_back(2);
		v6.push_back(2);
		v6.push_back(2);
		v6.push_back(2);
		v6.push_back(2);
		v6.push_back(2);
		print_vector(v6);

		std::cout << "pop_back" << std::endl;
		v6.pop_back();
		v6.pop_back();
		v6.pop_back();
		v6.pop_back();
		print_vector(v6);

		std::cout << "insert" << std::endl;
		v2.insert(v2.begin() + 50, 73);
		v2.insert(v2.begin() + 73, 50);
		print_vector(v2);
		v2.insert(v2.begin() + 73, 42, 42);
		print_vector(v2);

		std::cout << "swap" << std::endl;
		v3.swap(v2);
		print_vector(v2);
		print_vector(v3);

		std::cout << "erase" << std::endl;
		v3.erase(v3.begin() + 50);

		std::cout << "clear" << std::endl;
		v2.clear();
		print_vector(v2);

		std::cout << "erase with it" << std::endl;
		v3.erase(v3.begin(), v3.end());
		print_vector(v3);
	}
	system("leaks container | grep leaked | sed \"s/^[^ ]* //\" | sed \"s/^[^ ]* //\"");
	return (0);
}