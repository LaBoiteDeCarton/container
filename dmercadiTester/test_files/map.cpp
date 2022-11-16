#ifdef FT
	#include "map.hpp"
	#include "utility.hpp"
	#define NAMESPACE ft
#else
	#include <map>
	#include <utility>
	#define NAMESPACE std
#endif
#include <list>
#include <iostream>

#define MAP NAMESPACE::map<int, int>
#define MAP2 NAMESPACE::map<int, int, std::greater<int> >

template <class F, class S>
std::ostream&	operator<<(std::ostream& o, const NAMESPACE::pair<F,S>& x)
{
	o << "(" << x.first << "," << x.second << ")";
	return (o);
}

template<class K, class T, class Comp>
void	print_map(const NAMESPACE::map<K,T,Comp>& x)
{
	typedef NAMESPACE::map<K,T,Comp> PMAP;
	typename PMAP::const_iterator it = x.begin();
	typename PMAP::const_iterator ite = x.end();

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
		std::list<NAMESPACE::pair<int,int> >	ls;
		for (int i = 0; i < 512; i++)
			ls.push_back(NAMESPACE::make_pair(i * i / (3.143567528 + 6397498/3247623), i));
		
		MAP m;
		MAP m1(ls.begin(), ls.end());
		MAP m2(m1);
		MAP2 m3(ls.begin(), ls.end());

		print_map(m);
		print_map(m1);
		print_map(m2);
		print_map(m3);

		m = m2;
		print_map(m);
		m2.clear();
		print_map(m2);
		m2[42] = 42;
		m2[42] = 41;
		m2[8] = 78;
		m2[1] = 3;
		m2[90] = 2;
		m2[76] = 1;
		m2[66] = 0;
		m2[45] = -38728;
		m2[45] = -376;
		m2[34] = 37;
		m2[77] = 23;
		m2[90] = 435;
		m2[99] = 434;
		m2[8] = 543;
		m2[6] = 645;
		m2[4] = 134;
		m2[4] = 1058;
		m2[3] = 842;
		m2[5] = 85;
		print_map(m2);
		NAMESPACE::pair<MAP::iterator, bool> ins_res;
		ins_res = m2.insert(NAMESPACE::make_pair(32,32));
		if (ins_res.second)
			std::cout << "is inserted" << std::endl;
		else
			std::cout << "already exist" << std::endl;
		for (;ins_res.first != m2.end();ins_res.first++)
			std::cout << *ins_res.first;
		std::cout << std::endl;
		ins_res = m2.insert(NAMESPACE::make_pair(32,32));
		if (ins_res.second)
			std::cout << "is inserted" << std::endl;
		else
			std::cout << "already exist" << std::endl;
		for (;ins_res.first != m2.end();ins_res.first++)
			std::cout << *ins_res.first;
		std::cout << std::endl;
		print_map(m2);
		m2.erase(m2.find(34));
		m2.erase(4);
		m2.erase(m2.find(66), m2.find(90));
		print_map(m2);
		m2.swap(m1);
		print_map(m1);
		print_map(m2);
		std::cout << m1.count(99) << m1.count(1) << m1.count(56) << std::endl;
	}
	system("leaks container | grep leaked | sed \"s/^[^ ]* //\" | sed \"s/^[^ ]* //\"");
	return (0);
}