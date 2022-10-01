#ifndef FT_VECTOR_HPP
# define FT_VECTOR_HPP

#include "random_access_iterator.hpp"
#include <vector>
namespace ft
{
	template<class T, class Alloc = std::allocator<T> >
	class vector
	{
		public:
			typedef T														value_type;
			typedef Alloc													allocator_type;
			typedef typename allocator_type::reference						reference;
			typedef typename allocator_type::const_reference				const_reference;
			typedef typename allocator_type::pointer						pointer;
			typedef typename allocator_type::const_pointer					const_pointer;
			//typedef typename ft::random_access_iterator<T>				iterator;
			//typedef typename ft::random_access_iterator<const T>			const_iterator;
			typedef typename pointer										iterator;
			typedef typename const_pointer									const_iterator;
			typedef typename ft::reverse_iterator<iterator>					reverse_iterator;
			typedef typename ft::reverse_iterator<const_iterator>			const_reverse_iterator;
			typedef typename ft::iterator_traits<iterator>::difference_type	difference_type;
			typedef size_t													size_type;

			explicit vector (const allocator_type& alloc = allocator_type());	
			explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
			{
				allocator_type
			};
			template <class InputIterator>
         	vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type());
			vector (const vector& x);

			vector& operator= (const vector& x);

			iterator begin() { return (this->_first) };
			const_iterator begin() const { return (this->_begin) };
			iterator end() { return (this->_last) };
			const_iterator end() const { return (this->_last) };
			reverse_iterator rbegin();
			const_reverse_iterator rbegin() const;
			reverse_iterator rend();
			const_reverse_iterator rend() const;
			const_iterator cbegin() const noexcept;
			const_iterator cend() const noexcept;
			const_reverse_iterator crbegin() const noexcept;
			const_reverse_iterator crend() const noexcept;

			size_type size() const { return (static_cast<size_type>(this->_last - this->_first)) };
			size_type max_size() const { return (allocator_type().max_size()) };
			void resize (size_type n, value_type val = value_type());
			size_type capacity() const; { return (static_cast<size_type>(this->_end_cap - this->_first)) }
			bool empty() const;
			void reserve (size_type n);
			void shrink_to_fit();

			reference operator[] (size_type n);
			const_reference operator[] (size_type n) const;
			reference at (size_type n);
			const_reference at (size_type n) const;
			reference front();
			const_reference front() const;
			reference back();
			const_reference back() const;
			value_type* data() noexcept;
			const value_type* data() const noexcept;

			template <class InputIterator>
			void assign (InputIterator first, InputIterator last);	
			void assign (size_type n, const value_type& val);
			void push_back (const value_type& val);
			void pop_back();
			iterator insert (iterator position, const value_type& val);	
    		void insert (iterator position, size_type n, const value_type& val);
			template <class InputIterator>
			void insert (iterator position, InputIterator first, InputIterator last);
			iterator erase (iterator position);
			iterator erase (iterator first, iterator last);
			void swap (vector& x);
			void clear();
			template <class... Args>
			iterator emplace (const_iterator position, Args&&... args);
			template <class... Args>
			void emplace_back (Args&&... args);

			allocator_type get_allocator() const;

		private:
			pointer	_first;
			pointer	_last;
			pointer _end_cap;
	};

	template<class T, class Alloc>
	void	vector<T,Alloc>::resize(vector<T,Alloc>::size_type new_size, vector<T,Alloc>::value_type val = value_type())
	{
		size_type current_size = size();
		
	};

	template <class T, class Alloc>  bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
	template <class T, class Alloc>  bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
	template <class T, class Alloc>  bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
	template <class T, class Alloc>  bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
	template <class T, class Alloc>  bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
	template <class T, class Alloc>  bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
	template <class T, class Alloc>  void swap (vector<T,Alloc>& x, vector<T,Alloc>& y);
}

#endif
