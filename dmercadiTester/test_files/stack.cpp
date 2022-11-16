#ifdef FT
	#include "stack.hpp"
	#define NAMESPACE ft
#else
	#include <stack>
	#define NAMESPACE std
#endif
#include <list>
#include <iostream>

#define STACK NAMESPACE::stack<int>
#define STACK2 NAMESPACE::stack<int,std::list<int> >

template <class stack_type>
void	print_stack(const stack_type& x)
{
	std::cout << "------ STACK ------" << std::endl;
	std::cout << "Size : " << x.size() << std::endl;
	std::cout << "is empty ? : ";
	if (x.empty())
		std::cout << "yes" << std::endl;
	else
		std::cout << "no" << std::endl;
	if (!x.empty())
		std::cout << "top : " << x.top() <<  std::endl;
	std::cout << "------ ----- ------" << std::endl;
}

int main()
{
	{
		std::list<int> ls;
		for (int i = 0; i < 100; i++)
			ls.push_back(i * i / (3.143567528 + 6397498/3247623));
		STACK s1;
		STACK2 s2(ls);
		STACK s3;

		for (int i = 0; i < 100; i++)
			s1.push(i * i / (3.143567528 + 6397498/3247623));
		for (int i = 50; i < 123; i++)
			s3.push(i * i / (3.143567528 + 6397498/3247623));
		print_stack(s1);
		print_stack(s2);
		print_stack(s3);
		for (int i = 0; i < 20; i++)
			s1.pop();
		while (!s3.empty())
			s3.pop();
		print_stack(s1);
		print_stack(s2);
		print_stack(s3);
	}
	system("leaks container | grep leaked | sed \"s/^[^ ]* //\" | sed \"s/^[^ ]* //\"");
	return (0);
}