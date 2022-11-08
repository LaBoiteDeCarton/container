#include <iostream>
#include <vector>

#define NAMESPACE std
#define TYPE int

using namespace NAMESPACE;

template <class T>
void	printcap(vector<T> const &vect)
{
	std::cout << "vect.capacity() = " << vect.capacity() << std::endl;
}

int main ()
{
	vector<TYPE> vect1;
	vector<TYPE> vect2(13);
	vector<TYPE> vect3(vect2);
	vector<TYPE> vect4(3, 1);

	std::cout << "###### printing Capacity ######" << std::endl;
	for (int i = 0; i < 100; i++)
	{
		std::cout << i << " ";
		printcap(vect2);
		vect2.push_back(1);
	}
	for (int i = 0; i < 50; i++)
	{
		std::cout << i << " ";
		printcap(vect2);
		vect2.pop_back();
	}
	return (0);
}