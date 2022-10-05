#ifndef FT_VECTOR_HPP
# define FT_VECTOR_HPP

#include <memory> // std::allocator
#include <stdexcept> //std::out_of_range
#include "ft_algorithme.hpp" // ft::equal
#include "ft_iterator.hpp"
//#include "random_access_iterator.hpp"

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
			typedef typename ft::iterator_traits<iterator>::difference_type	difference_type; //c'est du c++11 ça non?
			typedef size_t													size_type;

			/* Constructors */
			explicit vector (const allocator_type& alloc = allocator_type());
			explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type());
			template <class InputIterator>
         	vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type());
			vector (const vector& x): _alloc(allocator_type());
			~vector();

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

			/* Capacity */
			size_type size() const;
			size_type max_size() const;
			void resize (size_type n, value_type val = value_type());
			size_type capacity() const;
			bool empty() const;
			void reserve (size_type n);

			/* Element access */
			reference at (size_type n);
			const_reference at (size_type n) const;
			reference front();
			const_reference front() const;
			reference back();
			const_reference back() const;
			value_type* data();
			const value_type* data() const;

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

			allocator_type get_allocator() const { return (this->_alloc)};

		private:
			pointer			_first;
			pointer			_last; //remplacer par _end pour plus de clarité
			pointer			_end_cap;
			allocator_type	_alloc;

			/* Some usefull private function */
			void		__destroy_from(pointer p);
			void		__push_n_back(size_type n, const value_type& val);
			void		__realloc_copy_and_delete(size_type n); ////to do
			size_type	__new_cap(size_type el_to_add); //// to do
			size_type	__space_remains();
			pointer		__memmove(pointer from_start, pointer from_end, pointer to_start);

	};
	/* --------------------------------------------------------------------------

		PRIVATE FUNCTIONS
		
	-------------------------------------------------------------------------- */

	template<class T, class Alloc>
	void vector<T,Alloc>::__destroy_from(pointer p)
	{
		pointer	new_last = this->_last;

		while (new_last != p)
			this->_alloc.destroy(--new_last);
		this->_last = new_last;
	}

	template<class T, class Alloc>
	void	vector<T,Alloc>::__push_n_back(size_type n, const value_type& val)
	{
		pointer	new_last;

		if (n > __space_remains())
			__realloc_copy_and_delete(__new_cap(n));
		new_last = this->_last;
		for (; n; n--)
			this->_alloc.construct(new_last++, val);
		this->_last = new_last;
	}

	template<class T, class Alloc>
	void	vector<T,Alloc>::__realloc_copy_and_delete(size_type n)
	{
		pointer	save_first = this->_first;
		pointer save_last = this->_last;
		pointer save_end_cap = this->_end_cap;

		this->_first = this->_alloc.allocate(n);
		this->_last = this->_first;
		this->_end_cap = this->_first + n;
		this->assign(save_first, save_last);
		
		//il faut destroy aussi les elements ici
		this->_alloc.deallocate(save_first, save_end_cap - save_first);
	}

	template<class T, class Alloc>
	typename vector<T,Alloc>::size_type
	vector<T,Alloc>::__new_cap(size_type el_to_add)
	{
		size_type	new_cap = capacity();
		size_type	current_size = size();

		while (new_cap < el_to_add + current_size)
			new_cap = new_cap * 2 + 1;
		return (new_cap);
	}

	template<class T, class Alloc>
	typename vector<T,Alloc>::size_type
	vector<T,Alloc>::__space_remains()
	{
		return (static_cast<size_type>(this->_end_cap - this->_last));
	}

	template<class T, class Alloc>
	typename vector<T,Alloc>::pointer
	vector<T,Alloc>::__memmove(pointer from_start, pointer from_end, pointer to_start)
	{
		pointer	new_last = to_start;

		if (from_start > to_start)
		{
			for (; from_start != from_end; from_start++)
			{
				_alloc.construct(to_start, *from_start);
				_alloc.destroy(from_start);
				to_start++;
			}
			new_last = to_start;
		}
		else if (from_start < to_start)
		{
			to_start += from_end - from_start;
			new_last = to_start;
			for (; from_start != from_end; from_end++)
			{
				_alloc.construct(to_start, *from_end);
				_alloc.destroy(from_end);
				to_start--;
			}
		}
		return (new_last);
	}

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
		this->_end_cap = this->_first + n;
		this->__push_n_back(n, val);
	}

	template<class T, class Alloc>
	template <class InputIterator>
    vector<T,Alloc>::vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type())
	:	_alloc(alloc)
	{
		size_type size = last - first;

		this->_first = this->_alloc.allocate(size);
		this->_last = this->_first;
		this->_end_cap = this->_first + size;
		this->assign(first, last);
	}

	template<class T, class Alloc>
	vector<T,Alloc>::vector (const vector& x)
	:	_alloc(allocator_type())
	{
		*this = x;
	}

	template<class T, class Alloc>
	vector<T,Alloc>::~vector()
	{
		clear();
		this->_alloc.deallocate(this->_first, this->capacity());
	}

	/* --------------------------------------------------------------------------

		MEMBER OPERATIONS
		
	-------------------------------------------------------------------------- */

	template<class T, class Alloc>
	vector<T,Alloc>& vector<T,Alloc>::operator= (const vector<T,Alloc>& x)
	{
		/* petit souvenir de ma naïveté */
		// const_iterator xstart = x.cbegin();
		// const_iterator xlast = x.cend();

		// this->_alloc = x.get_allocator();
		// if (size())
		// 	__destroy_from(this->_first);
		// this->_first = _alloc.allocate(x.size());
		// this->_last = this->_first;
		// for (; xstart != xlast; xstart++)
		// 	_alloc.construct(this->_last++, *xstart);
		// this->_end_cap = this->_last;
		this->assign(x.begin(), x.end());
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
	}

	template<class T, class Alloc>
	typename vector<T,Alloc>::const_iterator
	vector<T,Alloc>::begin() const
	{
		//using random_access_iterator class
		//return (iterator(this->_first));

		//using poitner as iterator
		return (this->_first);
	}

	template<class T, class Alloc>
	typename vector<T,Alloc>::iterator
	vector<T,Alloc>::end()
	{
		//using random_access_iterator class
		//return (iterator(this->_last));

		//using poitner as iterator
		return (this->_last);
	}

	template<class T, class Alloc>
	typename vector<T,Alloc>::const_iterator
	vector<T,Alloc>::end() const
	{
		//using random_access_iterator class
		//return (iterator(this->_last));

		//using poitner as iterator
		return (this->_last);
	}

	template<class T, class Alloc>
	typename vector<T,Alloc>::reverse_iterator
	vector<T,Alloc>::rbegin()
	{
		return (reverse_iterator(this->end()));
	}

	template<class T, class Alloc>
	typename vector<T,Alloc>::const_reverse_iterator
	vector<T,Alloc>::rbegin() const
	{
		return (const_reverse_iterator(this->end()));
	}

	template<class T, class Alloc>
	typename vector<T,Alloc>::reverse_iterator
	vector<T,Alloc>::rend()
	{
		return (reverse_iterator(this->begin()));
	}

	template<class T, class Alloc>
	typename vector<T,Alloc>::const_reverse_iterator
	vector<T,Alloc>::rend() const
	{
		return (const_reverse_iterator(this->begin()));
	}

	/* --------------------------------------------------------------------------

		CAPACITY

	-------------------------------------------------------------------------- */

	template<class T, class Alloc>
	typename vector<T,Alloc>::size_type
	vector<T,Alloc>::size() const
	{
		return (static_cast<size_type>(this->_last - this->_first));
	}

	template<class T, class Alloc>
	typename vector<T,Alloc>::size_type
	vector<T,Alloc>::max_size() const
	{
		return (this->_alloc.max_size());
	}

	template<class T, class Alloc>
	void	vector<T,Alloc>::resize(vector<T,Alloc>::size_type new_size, vector<T,Alloc>::value_type val = value_type())
	{
		size_type current_size = size();
		//if size under new_size, alloc::construct on pointer until new_size reached
		// else deastroy from the end until new_size reached
		if (new_size > current_size)
			__push_n_back(new_size - current_size, val);
		else
			__destroy_from(this->_first + new_size);
	}

	template<class T, class Alloc>
	typename vector<T,Alloc>::size_type
	vector<T,Alloc>::capacity() const
	{
		return (static_cast<size_type>(this->_end_cap - this->_first));
	}

	template<class T, class Alloc>
	bool vector<T,Alloc>::empty() const
	{
		return (size() == 0);
	}

	template<class T, class Alloc>
	void vector<T,Alloc>::reserve (size_type n)
	{
		if (n > capacity())
			__realloc_copy_and_delete(n - size());
	}

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
	}
	
	template<class T, class Alloc>
	typename vector<T,Alloc>::const_reference
	vector<T,Alloc>::at (size_type n) const
	{
		if (n > this::size())
			throw (std::out_of_range("vector"));
		return (this->_first[n]);
	}
	
	template<class T, class Alloc>
	typename vector<T,Alloc>::reference
	vector<T,Alloc>::front()
	{
		return (*(this->_first));
	}
	
	template<class T, class Alloc>
	typename vector<T,Alloc>::const_reference
	vector<T,Alloc>::front() const
	{
		return (*(this->_first));
	}
	
	template<class T, class Alloc>
	typename vector<T,Alloc>::reference
	vector<T,Alloc>::back()
	{
		return (*(this->_last));
	}
	
	template<class T, class Alloc>
	typename vector<T,Alloc>::const_reference
	vector<T,Alloc>::back() const
	{
		return (*(this->_last));
	}
	
	template<class T, class Alloc>
	typename vector<T,Alloc>::value_type*
	vector<T,Alloc>::data()
	{
		return (this->_first);
	}
	
	template<class T, class Alloc>
	const typename vector<T,Alloc>::value_type*
	vector<T,Alloc>::data() const
	{
		return (this->_first);
	}

	/* --------------------------------------------------------------------------

		MODIFIER

	-------------------------------------------------------------------------- */

	template<class T, class Alloc>
	template <class InputIterator>
	void vector<T,Alloc>::assign (InputIterator first, InputIterator last)
	{
		clear();
		for (; first != last; first++) //ici peut mieux faire en calculant au prealable si assez d'espace.
			this->push_back(*first);
	}
	
	template<class T, class Alloc>
	void vector<T,Alloc>::assign (size_type n, const value_type& val)
	{
		clear();
		this->__push_n_back(n, val);
		// for (; n > 0; n--)
		// 	this->push_back(val);
	}
	
	template<class T, class Alloc>
	void vector<T,Alloc>::push_back (const value_type& val)
	{
		this->__push_n_back(1, val);
		// if (this->_last == this->_end_cap)
		// 	this->reserve(capacity() * 2 + 1);
		// this->_alloc.construct(this->_last++, val);
	}
	
	template<class T, class Alloc>
	void vector<T,Alloc>::pop_back()
	{
		if (this->_last != this->_first) // if (! empty())
			this->_alloc.destroy(--(this->_last));
	}

	template<class T, class Alloc>
	typename vector<T,Alloc>::iterator
	vector<T,Alloc>::insert (iterator position, const value_type& val)
	{
		// reserve(size() + 1);
		// this->_last = __memmove(position, this->_last, position + 1);
		// _alloc.construct(position, val);
		insert(position, 1, val);
	}	
	
	template<class T, class Alloc>
	void vector<T,Alloc>::insert (iterator position, size_type n, const value_type& val)
	{
		reserve(size() + n);
		this->_last = __memmove(position, this->_last, position + n);
		for (; n; n--)
			_alloc.construct(position++, val);
	}
	
	template<class T, class Alloc>
	template <class InputIterator>
	void vector<T,Alloc>::insert (iterator position, InputIterator first, InputIterator last)
	{

	}
	
	template<class T, class Alloc>
	typename vector<T,Alloc>::iterator
	vector<T,Alloc>::erase (iterator position)
	{
		this->_alloc.destroy(position);
		this->_last = this->__memmove(position + 1, this->_last, position);
	}

	template<class T, class Alloc>
	typename vector<T,Alloc>::iterator
	vector<T,Alloc>::erase (iterator first, iterator last)
	{
		pointer save_first = first;

		if (last == this->_last)
			this->__destroy_from(first);
		else
		{
			for (; first != last; first++)
				this->_alloc.destroy(first);
			this->_last = this->__memmove(last, this->_last, save_first);
		}
	}
	
	template<class T, class Alloc>
	void vector<T,Alloc>::swap (vector& x)
	{
		swap(this->_alloc, x._alloc);
		swap(this->_first, x._first);
		swap(this->_last, x._last);
		swap(this->_end_cap, x._end_cap);
	}
	
	template<class T, class Alloc>
	void vector<T,Alloc>::clear()
	{
		this->__destroy_from(this->_first);
	}

	/* --------------------------------------------------------------------------

		NON MEMBER FUNCTIONS OVERLOAD

	-------------------------------------------------------------------------- */

	template <class T, class Alloc>
	bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		if (lhs.size() != rhs.size())
			return (false);
		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template <class T, class Alloc>
	bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		if (lhs.size() != rhs.size())
			return (true);
		return (! ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template <class T, class Alloc>
	bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template <class T, class Alloc>
	bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (! ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end()));
	}

	template <class T, class Alloc>
	bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end()));
	}

	template <class T, class Alloc>
	bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (! ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template <class T, class Alloc>
	void swap (vector<T,Alloc>& x, vector<T,Alloc>& y)
	{
		x.swap(y);
	}
}

#endif
