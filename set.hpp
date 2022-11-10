#ifndef SET_HPP
# define SET_HPP

/*
			#Includes					//	used class or functions from inlcudes
*/
#include <memory>						//	std::allocator
#include <functional>					//	std::less
#include "__binary_search_tree.hpp"		//	ft::__bst
#include "iterator.hpp"					//	ft::reverse_iterator

//To delete
// #include <set>
#include <map>

namespace ft
{
	template <class T, class Compare = std::less<T>,  class Alloc = std::allocator<T> >
	class set
	{
	public:
		typedef T														key_type;
		typedef T														value_type;
		typedef Compare													key_compare;
		typedef Compare													value_compare;
		typedef Alloc													allocator_type;
		typedef typename allocator_type::reference						reference;
		typedef typename allocator_type::const_reference				const_reference;
		typedef typename allocator_type::pointer						pointer;
		typedef typename allocator_type::const_pointer					const_pointer;
	private:
		/* Defininf the tree we are using. If you want to change the tree, change here the type definition */
		typedef __bst<value_type, value_compare, allocator_type>		ValBST;
	public:
		typedef typename ValBST::const_iterator							iterator;
		typedef typename ValBST::const_iterator							const_iterator;
		typedef ft::reverse_iterator<iterator>							reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>					const_reverse_iterator;
		typedef typename ft::iterator_traits<iterator>::difference_type	difference_type;
		typedef size_t													size_type;

		/* Contructors */
		explicit set (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type());
		template <class InputIterator>
		set (InputIterator first, InputIterator last,       const key_compare& comp = key_compare(),       const allocator_type& alloc = allocator_type());	
		set (const set& x);
		~set();

		set& operator= (const set& x);
		allocator_type get_allocator() const;

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
		bool empty() const;
		size_type size() const;
		size_type max_size() const;

		/* Modifiers */
		pair<iterator,bool> insert (const value_type& val);
		iterator insert (iterator hint, const value_type& val);
		template <class InputIterator>
		void insert (InputIterator first, InputIterator last);
		void erase (iterator position);
		size_type erase (const value_type& val);
    	void erase (iterator first, iterator last);
		void swap (set& x);
		void clear();

		/* Observers */
		key_compare key_comp() const;
		value_compare value_comp() const;

		/* Operators */
		iterator find (const value_type& val);
		const_iterator find (const value_type& val) const;
		size_type count (const value_type& val) const;
		iterator lower_bound (const value_type& val);
		const_iterator lower_bound( const value_type& val ) const;
		iterator upper_bound (const value_type& val);
		const_iterator upper_bound( const value_type& val ) const;
		pair<iterator,iterator> equal_range (const value_type& val);
		pair<const_iterator,const_iterator> equal_range( const value_type& val ) const;
	
	private:
		ValBST	_tree;

		template <class InputIterator>
		void	__insert_tag(InputIterator first, InputIterator last, ft::input_iterator_tag);
		template <class ForwardIterator>
		void	__insert_tag(ForwardIterator first, ForwardIterator last, ft::forward_iterator_tag);
		/* STD COMPATIBILITY std::*_iterator_tag */
		template <class InputIterator>
		void	__insert_tag(InputIterator first, InputIterator last, std::input_iterator_tag);
		template <class ForwardIterator>
		void	__insert_tag(ForwardIterator first, ForwardIterator last, std::forward_iterator_tag);
	};

	/* --------------------------------------------------------------------------

		PRIVATE FUNCTIONS
		
	-------------------------------------------------------------------------- */

	template <class T, class Comp, class Alloc>
	template <class InputIterator>
	void	set<T,Comp,Alloc>::__insert_tag(InputIterator first, InputIterator last, ft::input_iterator_tag)
	{
		for (; first != last;)
			insert(*first);
	}
	
	template <class T, class Comp, class Alloc>
	template <class ForwardIterator>
	void	set<T,Comp,Alloc>::__insert_tag(ForwardIterator first, ForwardIterator last, ft::forward_iterator_tag)
	{
		for (; first != last; first++)
			insert(*first);
	}
	
	template <class T, class Comp, class Alloc>
	template <class InputIterator>
	void	set<T,Comp,Alloc>::__insert_tag(InputIterator first, InputIterator last, std::input_iterator_tag)
	{
		for (; first != last;)
			insert(*first);
	}
	
	template <class T, class Comp, class Alloc>
	template <class ForwardIterator>
	void	set<T,Comp,Alloc>::__insert_tag(ForwardIterator first, ForwardIterator last, std::forward_iterator_tag)
	{
		for (; first != last; first++)
			insert(*first);
	}

	/* --------------------------------------------------------------------------

		CONCSTRUCTORS
		
	-------------------------------------------------------------------------- */

	template <class T, class Comp, class Alloc>
	set<T,Comp,Alloc>::set (const key_compare& comp, const allocator_type& alloc)
		:	_tree(comp, alloc)
	{ }

	template <class T, class Comp, class Alloc>
	template <class InputIterator>
	set<T,Comp,Alloc>::set (InputIterator first, InputIterator last, const key_compare& comp, const allocator_type& alloc)
		:	_tree(comp, alloc)
	{
		insert(first, last);
	}

	template <class T, class Comp, class Alloc>
	set<T,Comp,Alloc>::set (const set<T,Comp,Alloc>& x)
		:	_tree(x._tree)
	{ }

	template <class T, class Comp, class Alloc>
	set<T,Comp,Alloc>::~set()
	{ }

	template <class T, class Comp, class Alloc>
	set<T,Comp,Alloc>& set<T,Comp,Alloc>::operator= (const set<T,Comp,Alloc>& x)
	{
		_tree = x._tree;
		return (*this);
	}

	template <class T, class Comp, class Alloc>
	typename set<T,Comp,Alloc>::allocator_type
	set<T,Comp,Alloc>::get_allocator() const
	{
		return (_tree.get_alloc());
	}

	/* --------------------------------------------------------------------------

		ITERATORS
		
	-------------------------------------------------------------------------- */

	template <class T, class Comp, class Alloc>
	typename set<T,Comp,Alloc>::iterator
	set<T,Comp,Alloc>::begin()
	{
		return (_tree.begin());
	}

	template <class T, class Comp, class Alloc>
	typename set<T,Comp,Alloc>::const_iterator
	set<T,Comp,Alloc>::begin() const
	{
		return (_tree.begin());
	}

	template <class T, class Comp, class Alloc>
	typename set<T,Comp,Alloc>::iterator
	set<T,Comp,Alloc>::end()
	{
		return (_tree.end());
	}

	template <class T, class Comp, class Alloc>
	typename set<T,Comp,Alloc>::const_iterator
	set<T,Comp,Alloc>::end() const
	{
		return (_tree.end());
	}

	template <class T, class Comp, class Alloc>
	typename set<T,Comp,Alloc>::reverse_iterator
	set<T,Comp,Alloc>::rbegin()
	{
		return (reverse_iterator(this->end()));
	}

	template <class T, class Comp, class Alloc>
	typename set<T,Comp,Alloc>::const_reverse_iterator
	set<T,Comp,Alloc>::rbegin() const
	{
		return (const_reverse_iterator(this->end()));
	}

	template <class T, class Comp, class Alloc>
	typename set<T,Comp,Alloc>::reverse_iterator
	set<T,Comp,Alloc>::rend()
	{
		return (reverse_iterator(this->begin()));
	}

	template <class T, class Comp, class Alloc>
	typename set<T,Comp,Alloc>::const_reverse_iterator
	set<T,Comp,Alloc>::rend() const
	{
		return (const_reverse_iterator(this->begin()));
	}

	/* --------------------------------------------------------------------------

		CAPACITY
		
	-------------------------------------------------------------------------- */
	
	template <class T, class Comp, class Alloc>
	bool set<T,Comp,Alloc>::empty() const
	{
		return (size() == 0);
	}
	
	template <class T, class Comp, class Alloc>
	typename set<T,Comp,Alloc>::size_type
	set<T,Comp,Alloc>::size() const
	{
		return (this->_tree.size());
	}
	
	template <class T, class Comp, class Alloc>
	typename set<T,Comp,Alloc>::size_type
	set<T,Comp,Alloc>::max_size() const
	{
		return (_tree.max_size());
	}

	/* --------------------------------------------------------------------------

		MODIFIERS
		
	-------------------------------------------------------------------------- */


	template <class T, class Comp, class Alloc>
	pair<typename set<T,Comp,Alloc>::iterator,bool>
	set<T,Comp,Alloc>::insert (const value_type& val)
	{
		return (_tree.insert(val));
	}
	
	template <class T, class Comp, class Alloc>
	typename set<T,Comp,Alloc>::iterator
	set<T,Comp,Alloc>::insert (iterator hint, const value_type& val)
	{
		(void)hint;
		return (_tree.insert(val).first); //ignoring the hint
	}
	
	template <class T, class Comp, class Alloc>
	template <class _Iter>
	void set<T,Comp,Alloc>::insert (_Iter first, _Iter last)
	{
		__insert_tag(first, last, typename iterator_traits<_Iter>::iterator_category());
	}
	
	template <class T, class Comp, class Alloc>
	void set<T,Comp,Alloc>::erase (iterator position)
	{
		if (position != end())
			this->_tree.erase(position);
	}
	
	template <class T, class Comp, class Alloc>
	typename set<T,Comp,Alloc>::size_type
	set<T,Comp,Alloc>::erase (const key_type& k)
	{
		iterator position = find(k);

		if (position == end())
			return (0);
		erase(position);
		return (1);
	}
	
	template <class T, class Comp, class Alloc>
	void set<T,Comp,Alloc>::erase (iterator first, iterator last)
	{
		iterator next(first);

		for (;first != last; )
		{
			next++;
			erase(first);
			first = next;
		}
	}
	
	template <class T, class Comp, class Alloc>
	void set<T,Comp,Alloc>::swap (set<T,Comp,Alloc>& x)
	{
		this->_tree.swap(x._tree);
	}
	
	template <class T, class Comp, class Alloc>
	void set<T,Comp,Alloc>::clear()
	{
		_tree.clear();
	}

	/* --------------------------------------------------------------------------

		OBSERVERS
		
	-------------------------------------------------------------------------- */

	template <class T, class Comp, class Alloc>
	typename set<T,Comp,Alloc>::key_compare
	set<T,Comp,Alloc>::key_comp() const
	{
		return (this->_tree.value_comp());
	}

	template <class T, class Comp, class Alloc>
	typename set<T,Comp,Alloc>::value_compare
	set<T,Comp,Alloc>::value_comp() const
	{
		return (this->_tree.value_comp());
	}

	/* --------------------------------------------------------------------------

		OPERATIONS
		
	-------------------------------------------------------------------------- */


	template <class T, class Comp, class Alloc>
	typename set<T,Comp,Alloc>::iterator
	set<T,Comp,Alloc>::find (const value_type& k)
	{
		return (_tree.find(k));
	}

	template <class T, class Comp, class Alloc>
	typename set<T,Comp,Alloc>::const_iterator
	set<T,Comp,Alloc>::find (const value_type& k) const
	{
		return (_tree.find(k));
	}

	template <class T, class Comp, class Alloc>
	typename set<T,Comp,Alloc>::size_type
	set<T,Comp,Alloc>::count (const value_type& k) const
	{
		return (_tree.count(k));	
	}

	template <class T, class Comp, class Alloc>
	typename set<T,Comp,Alloc>::iterator
	set<T,Comp,Alloc>::lower_bound (const value_type& k)
	{
		return (_tree.lower_bound(k));
	}

	template <class T, class Comp, class Alloc>
	typename set<T,Comp,Alloc>::const_iterator
	set<T,Comp,Alloc>::lower_bound (const value_type& k) const
	{
		return (_tree.lower_bound(k));
	}

	template <class T, class Comp, class Alloc>
	typename set<T,Comp,Alloc>::iterator
	set<T,Comp,Alloc>::upper_bound (const value_type& k)
	{
		return (_tree.upper_bound(k));
	}

	template <class T, class Comp, class Alloc>
	typename set<T,Comp,Alloc>::const_iterator
	set<T,Comp,Alloc>::upper_bound (const value_type& k) const
	{
		return (_tree.upper_bound(k));
	}

	template <class T, class Comp, class Alloc>
	pair<typename set<T,Comp,Alloc>::const_iterator, typename set<T,Comp,Alloc>::const_iterator>	
	set<T,Comp,Alloc>::equal_range (const value_type& k) const
	{
		const_iterator lb = lower_bound(k);
		const_iterator ub(lb);

		if ((*lb) == k)
			ub++;
		return (make_pair(lb,ub));
	}

	template <class T, class Comp, class Alloc>
	pair<typename set<T,Comp,Alloc>::iterator,typename set<T,Comp,Alloc>::iterator>
	set<T,Comp,Alloc>::equal_range (const value_type& k)
	{
		iterator lb = lower_bound(k);
		iterator ub(lb);

		if ((*lb) == k)
			ub++;
		return (make_pair(lb,ub));
	}

	/* --------------------------------------------------------------------------

		NON MEMBER FUNCTIONS
		
	-------------------------------------------------------------------------- */

	template <class T, class Comp, class Alloc>
	bool operator== (const set<T,Comp,Alloc>& lhs, const set<T,Comp,Alloc>& rhs)
	{
		if (lhs.size() != rhs.size())
			return (false);
		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template <class T, class Comp, class Alloc>
	bool operator!= (const set<T,Comp,Alloc>& lhs, const set<T,Comp,Alloc>& rhs)
	{
		if (lhs.size() != rhs.size())
			return (true);
		return (! ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template <class T, class Comp, class Alloc>
	bool operator<  (const set<T,Comp,Alloc>& lhs, const set<T,Comp,Alloc>& rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template <class T, class Comp, class Alloc>
	bool operator<= (const set<T,Comp,Alloc>& lhs, const set<T,Comp,Alloc>& rhs)
	{
		return (! ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end()));
	}

	template <class T, class Comp, class Alloc>
	bool operator>  (const set<T,Comp,Alloc>& lhs, const set<T,Comp,Alloc>& rhs)
	{
		return (ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end()));
	}

	template <class T, class Comp, class Alloc>
	bool operator>= (const set<T,Comp,Alloc>& lhs, const set<T,Comp,Alloc>& rhs)
	{
		return (! ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template <class T, class Comp, class Alloc>
	void swap (set<T,Comp,Alloc>& x, set<T,Comp,Alloc>& y)
	{
		x.swap(y);
	}
}

#endif