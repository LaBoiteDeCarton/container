#ifdef FT
	#include "set.hpp"
	#include "utility.hpp"
	#define NAMESPACE ft
#else
	#include <set>
	#include <utility>
	#define NAMESPACE std
#endif
#include <list>
#include <iostream>

#define SET NAMESPACE::set<int>
#define SET2 NAMESPACE::set<int, std::greater<int> >

template <class F, class S>
std::ostream&	operator<<(std::ostream& o, const NAMESPACE::pair<F,S>& x)
{
	o << "(" << x.first << "," << x.second << ")";
	return (o);
}

template<class T, class Comp>
void	print_set(const NAMESPACE::set<T,Comp>& x)
{
	typedef NAMESPACE::set<T,Comp> P_SET;
	typename P_SET::const_iterator it = x.begin();
	typename P_SET::const_iterator ite = x.end();

	std::cout << "------ MAP ------" << std::endl;
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
		
		SET m;
		SET m1(ls.begin(), ls.end());
		SET m2(m1);
		SET2 m3(ls.begin(), ls.end());

		print_set(m);
		print_set(m1);
		print_set(m2);
		print_set(m3);

		m = m2;
		print_set(m);
		m2.clear();
		print_set(m2);
		m2.insert(42);
		m2.insert(42);
		m2.insert(8);
		m2.insert(1);
		m2.insert(90);
		m2.insert(76);
		m2.insert(66);
		m2.insert(45);
		m2.insert(45);
		m2.insert(34);
		m2.insert(77);
		m2.insert(90);
		m2.insert(99);
		m2.insert(8);
		m2.insert(6);
		m2.insert(4);
		m2.insert(4);
		m2.insert(3);
		m2.insert(5);
		print_set(m2);
		NAMESPACE::pair<SET::iterator, bool> ins_res;
		ins_res = m2.insert(32);
		if (ins_res.second)
			std::cout << "is inserted" << std::endl;
		else
			std::cout << "already exist" << std::endl;
		for (;ins_res.first != m2.end();ins_res.first++)
			std::cout << *ins_res.first;
		std::cout << std::endl;
		ins_res = m2.insert(32);
		if (ins_res.second)
			std::cout << "is inserted" << std::endl;
		else
			std::cout << "already exist" << std::endl;
		for (;ins_res.first != m2.end();ins_res.first++)
			std::cout << *ins_res.first;
		std::cout << std::endl;
		print_set(m2);
		m2.erase(m2.find(34));
		m2.erase(4);
		m2.erase(m2.find(66), m2.find(90));
		print_set(m2);
		m2.swap(m1);
		print_set(m1);
		print_set(m2);
		std::cout << m1.count(99) << m1.count(1) << m1.count(56) << std::endl;
	}
	system("leaks container | grep leaked | sed \"s/^[^ ]* //\" | sed \"s/^[^ ]* //\"");
	return (0);
}