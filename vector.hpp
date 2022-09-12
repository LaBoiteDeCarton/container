#ifndef VECTOR_HPP
# define VECTOR_HPP

#include "random_access_iterator.hpp"

namespace ft
{
	template<class T, class Alloc = std::allocator<T>>
	class vector
	{
		public:
			typedef T											value_type;
			typedef Alloc										allocator_type;
			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;
			typedef ft::random_access_iterator<T>				iterator;
			//typedef const_iterator;
			//typedef reverse_iterator;	
			//typedef const_reverse_iterator;
			//typedef difference_type;
			//typedef size_type;
			explicit vector (const allocator_type& alloc = allocator_type());	
			explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type());
			template <class InputIterator>
         	vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type());
			vector (const vector& x);	
			}
}

#endif
