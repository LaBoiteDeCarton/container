#ifndef FT_VECTOR_HPP
# define FT_VECTOR_HPP

//#include "random_access_iterator.hpp"
//#include <vector>
#include <memory> // std::allocator
#include <stdexcept> //std::out_of_range
#include "ft_algorithme.hpp" // ft::equal
#include "ft_iterator.hpp"

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
			typedef pointer													iterator;
			typedef const_pointer											const_iterator;
			typedef typename ft::reverse_iterator<iterator>					reverse_iterator;
			typedef typename ft::reverse_iterator<const_iterator>			const_reverse_iterator;
			typedef typename ft::iterator_traits<iterator>::difference_type	difference_type;
			typedef size_t													size_type;

			/* Constructors */
			explicit vector (const allocator_type& alloc = allocator_type());
			explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type());
			template <class InputIterator>
         	vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type());
			vector (const vector& x): _alloc(allocator_type());

			/* Member Operators */
			vector& operator= (const vector& x);
			reference operator[] (size_type n);
			const_reference operator[] (size_type n) const;

			/* Iterators */
			iterator begin();
			const_iterator begin() const;
			iterator end();
			const_iterator end() const;
			reverse_iterator rbegin();
			const_reverse_iterator rbegin() const;
			reverse_iterator rend();
			const_reverse_iterator rend() const;
			// C++11 const_iterator cbegin() const noexcept;
			// C++11 const_iterator cend() const noexcept;
			// C++11 const_reverse_iterator crbegin() const noexcept;
			// C++11 const_reverse_iterator crend() const noexcept;

			/* Capacity */
			size_type size() const;
			size_type max_size() const;
			void resize (size_type n, value_type val = value_type()); /****/
			size_type capacity() const;
			bool empty() const;
			void reserve (size_type n); /****/
			// c++11void shrink_to_fit();

			/* Element access */
			reference at (size_type n);
			const_reference at (size_type n) const;
			reference front();
			const_reference front() const;
			reference back();
			const_reference back() const;
			value_type* data() noexcept;
			const value_type* data() const noexcept;

			/* Modifier */
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
			//template <class... Args>
			//iterator emplace (const_iterator position, Args&&... args);
			//template <class... Args>
			//void emplace_back (Args&&... args);

			allocator_type get_allocator() const { return (this->_alloc)};

		private:
			//size_type		_size;
			pointer			_first;
			pointer			_last;
			pointer			_end_cap;
			allocator_type	_alloc;
	};

	/* --------------------------------------------------------------------------

		CONSTRUCTORS
		
	-------------------------------------------------------------------------- */

	template<class T, class Alloc>
	vector<T,Alloc>::vector (const allocator_type& alloc = allocator_type())
	:	_alloc(alloc),
		_first(NULL),
		_last(NULL),
		_end_cap(NULL)
	{ }

	template<class T, class Alloc>
	vector<T,Alloc>::vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
	:	_alloc(alloc)
	{
		this->_first = _alloc.allocate(n);
		this->_last = this->_first;
		while (n--)
			_alloc.construct((this->_last)++, val);
		this->_end_cap = this->_last;
	}

	template<class T, class Alloc>
	template <class InputIterator>
    vector<T,Alloc>::vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type())
	:	_alloc(alloc)
	{
		this->_first = _alloc.allocate(last - first);
		this->_last = this->_first;
		for (; first != last; first++)
			_alloc.construct((this->_last)++, *first);
		this->_end_cap = this->_last;
	}

	template<class T, class Alloc>
	vector<T,Alloc>::vector (const vector& x)
	:	_alloc(allocator_type())
	{
		*this = x;
	}

	/* --------------------------------------------------------------------------

		MEMBER OPERATIONS
		
	-------------------------------------------------------------------------- */

	template<class T, class Alloc>
	vector<T,Alloc>& vector<T,Alloc>::operator= (const vector<T,Alloc>& x)
	{
		const_iterator xstart = x.cbegin();
		const_iterator xlast = x.cend();

		this->_alloc = x.get_allocator();
		if (size())
			__destroy_all();
		this->_first = _alloc.allocate(x.size());
		this->_last = this->_first;
		for (; xstart != xlast; xstart++)
			_alloc.construct(this->_last++, *xstart);
		this->_end_cap = this->_last;
		return (*this);
	}

	template<class T, class Alloc>
	typename vector<T,Alloc>::reference
	vector<T,Alloc>::operator[] (size_type n)
	{
		return (this->_first[n]);
	}

	template<class T, class Alloc>
	typename vector<T,Alloc>::const_reference
	vector<T,Alloc>::operator[] (size_type n) const
	{
		return (this->_first[n]);
	}

	/* --------------------------------------------------------------------------

		ITERATORS
		
	-------------------------------------------------------------------------- */

	template<class T, class Alloc>
	typename vector<T,Alloc>::iterator
	vector<T,Alloc>::begin()
	{
		//using random_access_iterator class
		//return (iterator(this->_first));

		//using poitner as iterator
		return (this->_first);
	};

	template<class T, class Alloc>
	typename vector<T,Alloc>::const_iterator
	vector<T,Alloc>::begin() const
	{
		//using random_access_iterator class
		//return (iterator(this->_first));

		//using poitner as iterator
		return (this->_first)
	};

	template<class T, class Alloc>
	typename vector<T,Alloc>::iterator
	vector<T,Alloc>::end()
	{
		//using random_access_iterator class
		//return (iterator(this->_last));

		//using poitner as iterator
		return (this->_last)
	};

	template<class T, class Alloc>
	typename vector<T,Alloc>::const_iterator
	vector<T,Alloc>::end() const
	{
		//using random_access_iterator class
		//return (iterator(this->_last));

		//using poitner as iterator
		return (this->_last)
	};

	template<class T, class Alloc>
	typename vector<T,Alloc>::reverse_iterator
	vector<T,Alloc>::rbegin()
	{
		return (reverse_iterator(this->end()));
	};

	template<class T, class Alloc>
	typename vector<T,Alloc>::const_reverse_iterator
	vector<T,Alloc>::rbegin() const
	{
		return (const_reverse_iterator(this->end()));
	};

	template<class T, class Alloc>
	typename vector<T,Alloc>::reverse_iterator
	vector<T,Alloc>::rend()
	{
		return (reverse_iterator(this->begin()));
	};

	template<class T, class Alloc>
	typename vector<T,Alloc>::const_reverse_iterator
	vector<T,Alloc>::rend() const
	{
		return (const_reverse_iterator(this->begin()));
	};

	/* --------------------------------------------------------------------------

		CAPACITY

	-------------------------------------------------------------------------- */

	template<class T, class Alloc>
	typename vector<T,Alloc>::size_type
	vector<T,Alloc>::size() const
	{
		return (static_cast<size_type>(this->_last - this->_first))
	};

	template<class T, class Alloc>
	typename vector<T,Alloc>::size_type
	vector<T,Alloc>::max_size() const
	{
		return (_alloc.max_size())
	};

	template<class T, class Alloc>
	void	vector<T,Alloc>::resize(vector<T,Alloc>::size_type new_size, vector<T,Alloc>::value_type val = value_type())
	{
		size_type current_size = size();
		//if size under new_size, alloc::construct on pointer until new_size reached
		// else deastroy from the end until new_size reached
	};

	template<class T, class Alloc>
	typename vector<T,Alloc>::size_type
	vector<T,Alloc>::capacity() const
	{
		return (static_cast<size_type>(this->_end_cap - this->_first))
	};

	template<class T, class Alloc>
	bool vector<T,Alloc>::empty() const
	{
		return (size() == 0);
	};

	template<class T, class Alloc>
	void vector<T,Alloc>::reserve (size_type n)
	{

	};

	/* --------------------------------------------------------------------------

		ELEMENT ACCESS

	-------------------------------------------------------------------------- */

	template<class T, class Alloc>
	typename vector<T,Alloc>::reference
	vector<T,Alloc>::at (size_type n)
	{
		if (n > this::size())
			throw (std::out_of_range("vector"));
		return (this->_first[n]);
	};
	
	template<class T, class Alloc>
	typename vector<T,Alloc>::const_reference
	vector<T,Alloc>::at (size_type n) const
	{
		if (n > this::size())
			throw (std::out_of_range("vector"));
		return (this->_first[n]);
	};
	
	template<class T, class Alloc>
	typename vector<T,Alloc>::reference
	vector<T,Alloc>::front()
	{
		return (*(this->_first));
	};
	
	template<class T, class Alloc>
	typename vector<T,Alloc>::const_reference
	vector<T,Alloc>::front() const
	{
		return (*(this->_first));
	};
	
	template<class T, class Alloc>
	typename vector<T,Alloc>::reference
	vector<T,Alloc>::back()
	{
		return (*(this->_last));
	};
	
	template<class T, class Alloc>
	typename vector<T,Alloc>::const_reference
	vector<T,Alloc>::back() const
	{
		return (*(this->_last));
	};
	
	template<class T, class Alloc>
	typename vector<T,Alloc>::value_type*
	vector<T,Alloc>::data()
	{
		return (this->_first);
	};
	
	template<class T, class Alloc>
	const typename vector<T,Alloc>::value_type*
	vector<T,Alloc>::data() const
	{
		return (this->_first);
	};

	/* --------------------------------------------------------------------------

		MODIFIER

	-------------------------------------------------------------------------- */

	template<class T, class Alloc>
	template <class InputIterator>
	void vector<T,Alloc>::assign (InputIterator first, InputIterator last)
	{
		clear();
		for (; first != last; first++)
			this->push_back(*first); //il est possible de mieux faire
	};
	
	template<class T, class Alloc>
	void vector<T,Alloc>::assign (size_type n, const value_type& val)
	{
		clear();
		for (; n > 0; n--)
			this->push_back(val); //il est possible de mieux faire
	};
	
	template<class T, class Alloc>
	void vector<T,Alloc>::push_back (const value_type& val)
	{

	};
	
	template<class T, class Alloc>
	void vector<T,Alloc>::pop_back()
	{
		this->_alloc.destroy(--(this->_last));
	};

	template<class T, class Alloc>
	typename vector<T,Alloc>::iterator
	vector<T,Alloc>::insert (iterator position, const value_type& val)
	{

	};	
	
	template<class T, class Alloc>
	void vector<T,Alloc>::insert (iterator position, size_type n, const value_type& val)
	{

	};
	
	template<class T, class Alloc>
	template <class InputIterator>
	void vector<T,Alloc>::insert (iterator position, InputIterator first, InputIterator last)
	{

	};
	
	template<class T, class Alloc>
	typename vector<T,Alloc>::iterator
	vector<T,Alloc>::erase (iterator position)
	{

	};

	template<class T, class Alloc>
	typename vector<T,Alloc>::iterator
	vector<T,Alloc>::erase (iterator first, iterator last)
	{

	};
	
	template<class T, class Alloc>
	void vector<T,Alloc>::swap (vector& x)
	{

	};
	
	template<class T, class Alloc>
	void vector<T,Alloc>::clear()
	{

	};

	/* --------------------------------------------------------------------------

		NON MEMBER FUNCTIONS OVERLOAD

	-------------------------------------------------------------------------- */

	template <class T, class Alloc>
	bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		if (lhs.size() != rhs.size())
			return (false);
		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	};

	template <class T, class Alloc>
	bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		if (lhs.size() != rhs.size())
			return (true);
		return (! ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	};

	template <class T, class Alloc>
	bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	};

	template <class T, class Alloc>
	bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (! ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end()));
	};

	template <class T, class Alloc>
	bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end()));
	};

	template <class T, class Alloc>
	bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (! ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	};

	template <class T, class Alloc>
	void swap (vector<T,Alloc>& x, vector<T,Alloc>& y)
	{
		x.swap(y);
	};
}

#endif
