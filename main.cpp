// #include <iostream>
// #include <string>
// #include <deque>

// #include <stdlib.h>
// #include "map.hpp"

// #define TESTED_TYPE int
#define TESTED_NAMESPACE ft

// int		main(void)
// {
// 	// ft::map<int, int> m;
// 	// ft::pair<ft::map<int,int>::iterator, bool> insert_res = m.insert(ft::pair<int, int>(3,10));
// 	// std::cout << "Is inserted : " << insert_res.second << std::endl;
// 	// insert_res = m.insert(ft::pair<int, int>(69,1));
// 	// std::cout << "Is inserted : " << insert_res.second << std::endl;
// 	// insert_res = m.insert(ft::pair<int, int>(36,2));
// 	// std::cout << "Is inserted : " << insert_res.second << std::endl;
// 	// insert_res = m.insert(ft::pair<int, int>(90,3));
// 	// std::cout << "Is inserted : " << insert_res.second << std::endl;
// 	// insert_res = m.insert(ft::pair<int, int>(67,4));
// 	// std::cout << "Is inserted : " << insert_res.second << std::endl;
// 	// insert_res = m.insert(ft::pair<int, int>(42,5));
// 	// std::cout << "Is inserted : " << insert_res.second << std::endl;
// 	// insert_res = m.insert(ft::pair<int, int>(10,6));
// 	// std::cout << "Is inserted : " << insert_res.second << std::endl;
// 	// insert_res = m.insert(ft::pair<int, int>(67,7));
// 	// std::cout << "Is inserted : " << insert_res.second << std::endl;

// 	// m.__print_tree();
// 	// ft::map<int, int>::iterator it = m.begin();
// 	// ft::map<int, int>::iterator e_it = m.end();

// 	// for (;it != e_it; it++)
// 	// 	std::cout << "(key,val): (" <<  (*it).first << "," << (*it).second << ")" << std::endl;
// 	// std::cout << "size : " << m.size() << std::endl;
// 	// std::cout << "Backwards : " << std::endl;
// 	// it = m.begin();
// 	// for (;it != e_it;)
// 	// {
// 	// 	--e_it;
// 	// 	std::cout << "(key,val): (" <<  (*e_it).first << "," << (*e_it).second << ")" << std::endl;
// 	// }
// 	// std::cout << m.count(10);
// 	// std::cout << m.count(11) << std::endl;

// 	// it = m.find(11);
// 	// if (it != m.end())
// 	// 	std::cout << (*it).first << std::endl;
// 	return (0);
// }

#include "map.hpp"
#include "utility.hpp"
// #include <iostream>

// int		main(void)
// {
// 	ft::map<int, int> mp;
// 	ft::map<int, int>::iterator it;
// 	ft::map<int, int>::iterator e_it;
// 	ft::map<int, int>::iterator lb;
	
// 	for (int i = 1; i < 20; i += 2)
// 		mp[i] = i * 13;
// 	e_it = mp.end();
// 	for (it = mp.begin(); it != e_it; it++)
// 		std::cout << "(" << (*it).first << "," << (*it).second << ")" << std::endl;
// 	lb = mp.upper_bound(11);
// 	std::cout << (*lb).first << " " << (*lb).second  <<  std::endl;
// 	return (0);
// }

#include <list>

template <typename T>
class foo {
	public:
		typedef T	value_type;

		foo(void) : value(), _verbose(false) { };
		foo(value_type src, const bool verbose = false) : value(src), _verbose(verbose) { };
		foo(foo const &src, const bool verbose = false) : value(src.value), _verbose(verbose) { };
		~foo(void) { if (this->_verbose) std::cout << "~foo::foo()" << std::endl; };
		void m(void) { std::cout << "foo::m called [" << this->value << "]" << std::endl; };
		void m(void) const { std::cout << "foo::m const called [" << this->value << "]" << std::endl; };
		foo &operator=(value_type src) { this->value = src; return *this; };
		foo &operator=(foo const &src) {
			if (this->_verbose || src._verbose)
				std::cout << "foo::operator=(foo) CALLED" << std::endl;
			this->value = src.value;
			return *this;
		};
		value_type	getValue(void) const { return this->value; };
		void		switchVerbose(void) { this->_verbose = !(this->_verbose); };

		operator value_type(void) const {
			return value_type(this->value);
		}
	private:
		value_type	value;
		bool		_verbose;
};

template <typename T>
std::ostream	&operator<<(std::ostream &o, foo<T> const &bar) {
	o << bar.getValue();
	return o;
}
// --- End of class foo

template <typename T>
T	inc(T it, int n)
{
	while (n-- > 0)
		++it;
	return (it);
}

template <typename T>
T	dec(T it, int n)
{
	while (n-- > 0)
		--it;
	return (it);
}

static int iter = 0;

template <typename T>
std::string	printPair(const T &iterator, bool nl = true, std::ostream &o = std::cout)
{
	o << "key: " << iterator->first << " | value: " << iterator->second;
	if (nl)
		o << std::endl;
	return ("");
}




template <typename T_MAP>
void	printSize(T_MAP const &mp, bool print_content = 1)
{
	std::cout << "size: " << mp.size() << std::endl;
	std::cout << "max_size: " << mp.max_size() << std::endl;
	if (print_content)
	{
		typename T_MAP::const_iterator it = mp.begin(), ite = mp.end();
		std::cout << std::endl << "Content is:" << std::endl;
		for (; it != ite; ++it)
			std::cout << "- " << printPair(it, false) << std::endl;
	}
	std::cout << "###############################################" << std::endl;
}

#define T1 char
#define T2 foo<float>
typedef TESTED_NAMESPACE::map<T1, T2> _map;
typedef _map::const_iterator const_it;

static unsigned int i = 0;

void	ft_comp(const _map &mp, const const_it &it1, const const_it &it2)
{
	bool res[2];

	std::cout << "\t-- [" << ++i << "] --" << std::endl;
	res[0] = mp.key_comp()(it1->first, it2->first);
	res[1] = mp.value_comp()(*it1, *it2);
	std::cout << "with [" << it1->first << " and " << it2->first << "]: ";
	std::cout << "key_comp: " << res[0] << " | " << "value_comp: " << res[1] << std::endl;
}

int		main(void)
{
	_map	mp;

	ft::map<int, int> my_map;
	ft::map<int, int> my_map2;
	ft::map<int, int>::const_iterator c_it = my_map2.begin();
	ft::map<int, int>::iterator it = my_map.begin();


	mp['a'] = 2.3;
	mp['b'] = 1.4;
	mp['c'] = 0.3;
	mp['d'] = 4.2;
	printSize(mp);

	for (const_it it1 = mp.begin(); it1 != mp.end(); ++it1)
		for (const_it it2 = mp.begin(); it2 != mp.end(); ++it2)
			ft_comp(mp, it1, it2);

	printSize(mp);
	return (0);
}