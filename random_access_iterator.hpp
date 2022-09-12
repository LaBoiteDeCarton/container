#ifndef RANDOM_ACCESS_ITERATOR_HPP
# define RANDOM_ACCESS_ITERATOR_HPP

#include <iterator>

struct random_access_iterator_tag {};

namespace ft
{
	template<class T>
	class random_access_iterator: public std::iterator<random_access_iterator_tag, T>
	{
		//typedef std::iterator<random_access_iterator_tag, T>::iterator_category iterator_category;
		//typedef std::iterator<random_access_iterator_tag, T>::pointer	pointer;
		//typedef T*	pointer;

		random_access_iterator(void) : _ptr(NULL) {}
		random_access_iterator(pointer ptr) : _ptr(ptr) {}
		random_access_iterator(const random_access_iterator& src): _ptr(src._ptr) {}

		random_access_iterator& operator=(const random_access_iterator& src)
		{
			this->_ptr = src._ptr;
			return (*this);
		}

		bool					operator==(const random_access_iterator& rhs) const
		{	return (this->_ptr == rhs._ptr);	}

		bool					operator!=(const random_access_iterator& rhs) const
		{	return (this->_ptr != rhs._ptr);	}

		value_type				operator*(void)
		{	return (*(this->_ptr));	}

		value_type				operator->(void)
		{	return (*this)	}

		private:
			pointer	_ptr;
	};	
}

#endif