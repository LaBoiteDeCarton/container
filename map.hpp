#ifndef FT_MAP_HPP
# define FT_MAP_HPP

/*
			#Includes					//	used class or functions from inlcudes
*/
#include <memory>						//	std::allocator
#include <functional>					//	std::less && std::binary_function
#include "utility.hpp"					//	ft::pair
#include "algorithme.hpp"				//	ft::equal ft::swap
#include "iterator.hpp"					//	ft::iterator, ft::iterator_traits, ft::bidirectional_iterator_tag, ft::reverse_iterator
#include "__binary_search_tree.hpp"		//	ft::__bst

namespace ft
{
	template < class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<pair<const Key,T> > >
	class map
	{
		public:
			typedef Key														key_type;
			typedef T														mapped_type;
			typedef pair<const Key,T>										value_type;
			typedef Compare													key_compare;
			typedef Alloc													allocator_type;
			typedef typename allocator_type::reference						reference;
			typedef typename allocator_type::const_reference				const_reference;
			typedef typename allocator_type::pointer						pointer;
			typedef typename allocator_type::const_pointer					const_pointer;
			
			class value_compare : public std::binary_function<value_type, value_type, bool>
			{
				friend class map;
			protected:
				key_compare	comp;
				value_compare(Compare c): comp(c) {};
			public:
				bool	operator() (const value_type& lhs, const value_type& rhs) const{
					return (comp(lhs.first, rhs.first));
				};
				bool	operator() (const key_type& k, const value_type& rhs) const{
					return (comp(k, rhs.first));
				};
				bool	operator() (const value_type& lhs, const key_type& k) const{
					return (comp(lhs.first, k));
				};
			};

		private:
			/* Defininf the tree we are using. If you want to change the tree, change here the type definition */
			typedef __bst<value_type, value_compare, allocator_type>		KeyValBST;
		public:
			typedef typename KeyValBST::iterator							iterator;
			typedef typename KeyValBST::const_iterator						const_iterator;
			typedef ft::reverse_iterator<iterator>							reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>					const_reverse_iterator;
			typedef typename ft::iterator_traits<iterator>::difference_type	difference_type;
			typedef size_t													size_type;

			/* Contructors */
			explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type());	
			template <class InputIterator>
			map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type());	
			map (const map& x);
			~map();

			map& operator= (const map& x);
			allocator_type get_allocator() const;

			/* Iterators */
			const_iterator begin() const;
			iterator begin();
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

			/* Element access */
			mapped_type& operator[] (const key_type& k);
			mapped_type& at (const key_type& k);
			const mapped_type& at (const key_type& k) const;

			/* Modifiers */
			pair<iterator,bool> insert (const value_type& val);
			iterator insert (iterator hint, const value_type& val);	
			template <class InputIterator>
			void insert (InputIterator first, InputIterator last);
			void erase (iterator position);
			size_type erase (const key_type& k);
			void erase (iterator first, iterator last);
			void swap (map& x);
			void clear();

			/* Observers */
			key_compare key_comp() const;
			value_compare value_comp() const;

			/* Operations */
			iterator find (const key_type& k);
			const_iterator find (const key_type& k) const;
			size_type count (const key_type& k) const;
			iterator lower_bound (const key_type& k);
			const_iterator lower_bound (const key_type& k) const;
			iterator upper_bound (const key_type& k);
			const_iterator upper_bound (const key_type& k) const;
			pair<const_iterator,const_iterator>	equal_range (const key_type& k) const;
			pair<iterator,iterator>	equal_range (const key_type& k);

		private:
			KeyValBST		_tree;

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

	template < class Key, class T, class Comp, class Alloc>
	template <class InputIterator>
	void	map<Key,T,Comp,Alloc>::__insert_tag(InputIterator first, InputIterator last, ft::input_iterator_tag)
	{
		for (; first != last;)
			insert(*first);
	}
	
	template < class Key, class T, class Comp, class Alloc>
	template <class ForwardIterator>
	void	map<Key,T,Comp,Alloc>::__insert_tag(ForwardIterator first, ForwardIterator last, ft::forward_iterator_tag)
	{
		for (; first != last; first++)
			insert(*first);
	}
	
	template < class Key, class T, class Comp, class Alloc>
	template <class InputIterator>
	void	map<Key,T,Comp,Alloc>::__insert_tag(InputIterator first, InputIterator last, std::input_iterator_tag)
	{
		for (; first != last;)
			insert(*first);
	}
	
	template < class Key, class T, class Comp, class Alloc>
	template <class ForwardIterator>
	void	map<Key,T,Comp,Alloc>::__insert_tag(ForwardIterator first, ForwardIterator last, std::forward_iterator_tag)
	{
		for (; first != last; first++)
			insert(*first);
	}

	/* --------------------------------------------------------------------------

		CONSTRUCTORS
		
	-------------------------------------------------------------------------- */
	template < class Key, class T, class Comp, class Alloc>
	map<Key,T,Comp,Alloc>::map (const key_compare& comp, const allocator_type& alloc)
		:	_tree(comp, alloc)
	{ }

	template < class Key, class T, class Comp, class Alloc>
	template <class InputIterator>
	map<Key,T,Comp,Alloc>::map (InputIterator first, InputIterator last, const key_compare& comp, const allocator_type& alloc)
		:	_tree(comp, alloc)
	{
		insert(first, last);
	}

	template < class Key, class T, class Comp, class Alloc>
	map<Key,T,Comp,Alloc>::map (const map<Key,T,Comp,Alloc>& x)
		:	_tree(x._tree)
	{ }

	template < class Key, class T, class Comp, class Alloc>
	map<Key,T,Comp,Alloc>::~map()
	{ }

	template < class Key, class T, class Comp, class Alloc>
	map<Key,T,Comp,Alloc>& map<Key,T,Comp,Alloc>::operator= (const map<Key,T,Comp,Alloc>& x)
	{
		_tree = x._tree;
		return (*this);
	}

	template < class Key, class T, class Comp, class Alloc>
	typename map<Key,T,Comp,Alloc>::allocator_type
	map<Key,T,Comp,Alloc>::get_allocator() const
	{
		return (_tree.get_alloc());
	}

	/* --------------------------------------------------------------------------

		ITERATORS
		
	-------------------------------------------------------------------------- */

	template < class Key, class T, class Comp, class Alloc>
	typename map<Key,T,Comp,Alloc>::iterator
	map<Key,T,Comp,Alloc>::begin()
	{
		return (_tree.begin());
	}

	template < class Key, class T, class Comp, class Alloc>
	typename map<Key,T,Comp,Alloc>::const_iterator
	map<Key,T,Comp,Alloc>::begin() const
	{
		return (_tree.begin());
	}

	template < class Key, class T, class Comp, class Alloc>
	typename map<Key,T,Comp,Alloc>::iterator
	map<Key,T,Comp,Alloc>::end()
	{
		return (_tree.end());
	}

	template < class Key, class T, class Comp, class Alloc>
	typename map<Key,T,Comp,Alloc>::const_iterator
	map<Key,T,Comp,Alloc>::end() const
	{
		return (_tree.end());
	}

	template < class Key, class T, class Comp, class Alloc>
	typename map<Key,T,Comp,Alloc>::reverse_iterator
	map<Key,T,Comp,Alloc>::rbegin()
	{
		return (reverse_iterator(this->end()));
	}

	template < class Key, class T, class Comp, class Alloc>
	typename map<Key,T,Comp,Alloc>::const_reverse_iterator
	map<Key,T,Comp,Alloc>::rbegin() const
	{
		return (const_reverse_iterator(this->end()));
	}

	template < class Key, class T, class Comp, class Alloc>
	typename map<Key,T,Comp,Alloc>::reverse_iterator
	map<Key,T,Comp,Alloc>::rend()
	{
		return (reverse_iterator(this->begin()));
	}

	template < class Key, class T, class Comp, class Alloc>
	typename map<Key,T,Comp,Alloc>::const_reverse_iterator
	map<Key,T,Comp,Alloc>::rend() const
	{
		return (const_reverse_iterator(this->begin()));
	}

	/* --------------------------------------------------------------------------

		CAPACITY
		
	-------------------------------------------------------------------------- */
	
	template < class Key, class T, class Comp, class Alloc>
	bool map<Key,T,Comp,Alloc>::empty() const
	{
		return (size() == 0);
	}
	
	template < class Key, class T, class Comp, class Alloc>
	typename map<Key,T,Comp,Alloc>::size_type
	map<Key,T,Comp,Alloc>::size() const
	{
		return (this->_tree.size());
	}
	
	template < class Key, class T, class Comp, class Alloc>
	typename map<Key,T,Comp,Alloc>::size_type
	map<Key,T,Comp,Alloc>::max_size() const
	{
		return (_tree.max_size());
	}
	
	/* --------------------------------------------------------------------------

		ELEMENT ACCESS
		
	-------------------------------------------------------------------------- */

	template < class Key, class T, class Comp, class Alloc>
	typename map<Key,T,Comp,Alloc>::mapped_type&
	map<Key,T,Comp,Alloc>::operator[] (const key_type& k)
	{
		iterator	el = insert(ft::make_pair(k,mapped_type())).first;

		return ((*el).second);
	}

	template < class Key, class T, class Comp, class Alloc>
	typename map<Key,T,Comp,Alloc>::mapped_type&
	map<Key,T,Comp,Alloc>::at (const key_type& k)
	{
		iterator it = find(k);

		if (it == end())
			throw (std::out_of_range("map"));
		return ((*it).second); //get mapped type ainsi value_type peut etre n'importe quoi -> la flemme
	}

	template < class Key, class T, class Comp, class Alloc>
	const typename map<Key,T,Comp,Alloc>::mapped_type&
	map<Key,T,Comp,Alloc>::at (const key_type& k) const
	{
		const_iterator it = find(k);

		if (it == end())
			throw (std::out_of_range("map"));
		return ((*it).second);
	}

	/* --------------------------------------------------------------------------

		MODIFIERS
		
	-------------------------------------------------------------------------- */


	template < class Key, class T, class Comp, class Alloc>
	pair<typename map<Key,T,Comp,Alloc>::iterator,bool>
	map<Key,T,Comp,Alloc>::insert (const value_type& val)
	{
		return (_tree.insert(val));
	}
	
	template < class Key, class T, class Comp, class Alloc>
	typename map<Key,T,Comp,Alloc>::iterator
	map<Key,T,Comp,Alloc>::insert (iterator hint, const value_type& val)
	{
		(void)hint;
		return (_tree.insert(val).first); //ignoring the hint
	}
	
	template < class Key, class T, class Comp, class Alloc>
	template <class _Iter>
	void map<Key,T,Comp,Alloc>::insert (_Iter first, _Iter last)
	{
		__insert_tag(first, last, typename iterator_traits<_Iter>::iterator_category());
	}
	
	template < class Key, class T, class Comp, class Alloc>
	void map<Key,T,Comp,Alloc>::erase (iterator position)
	{
		if (position != end())
			this->_tree.erase(position);
	}
	
	template < class Key, class T, class Comp, class Alloc>
	typename map<Key,T,Comp,Alloc>::size_type
	map<Key,T,Comp,Alloc>::erase (const key_type& k)
	{
		iterator position = find(k);

		if (position == end())
			return (0);
		erase(position);
		return (1);
	}
	
	template < class Key, class T, class Comp, class Alloc>
	void map<Key,T,Comp,Alloc>::erase (iterator first, iterator last)
	{
		iterator next(first);

		for (;first != last; )
		{
			next++;
			erase(first);
			first = next;
		}
	}
	
	template < class Key, class T, class Comp, class Alloc>
	void map<Key,T,Comp,Alloc>::swap (map<Key,T,Comp,Alloc>& x)
	{
		this->_tree.swap(x._tree);
	}
	
	template < class Key, class T, class Comp, class Alloc>
	void map<Key,T,Comp,Alloc>::clear()
	{
		_tree.clear();
	}

	/* --------------------------------------------------------------------------

		OBSERVERS
		
	-------------------------------------------------------------------------- */

	template < class Key, class T, class Comp, class Alloc>
	typename map<Key,T,Comp,Alloc>::key_compare
	map<Key,T,Comp,Alloc>::key_comp() const
	{
		return (this->_tree.value_comp().comp);
	}

	template < class Key, class T, class Comp, class Alloc>
	typename map<Key,T,Comp,Alloc>::value_compare
	map<Key,T,Comp,Alloc>::value_comp() const
	{
		return (this->_tree.value_comp());
	}

	/* --------------------------------------------------------------------------

		OPERATIONS
		
	-------------------------------------------------------------------------- */


	template < class Key, class T, class Comp, class Alloc>
	typename map<Key,T,Comp,Alloc>::iterator
	map<Key,T,Comp,Alloc>::find (const key_type& k)
	{
		return (_tree.find(k));
	}

	template < class Key, class T, class Comp, class Alloc>
	typename map<Key,T,Comp,Alloc>::const_iterator
	map<Key,T,Comp,Alloc>::find (const key_type& k) const
	{
		return (_tree.find(k));
	}

	template < class Key, class T, class Comp, class Alloc>
	typename map<Key,T,Comp,Alloc>::size_type
	map<Key,T,Comp,Alloc>::count (const key_type& k) const
	{
		return (_tree.count(k));	
	}

	template < class Key, class T, class Comp, class Alloc>
	typename map<Key,T,Comp,Alloc>::iterator
	map<Key,T,Comp,Alloc>::lower_bound (const key_type& k)
	{
		return (_tree.lower_bound(k));
	}

	template < class Key, class T, class Comp, class Alloc>
	typename map<Key,T,Comp,Alloc>::const_iterator
	map<Key,T,Comp,Alloc>::lower_bound (const key_type& k) const
	{
		return (_tree.lower_bound(k));
	}

	template < class Key, class T, class Comp, class Alloc>
	typename map<Key,T,Comp,Alloc>::iterator
	map<Key,T,Comp,Alloc>::upper_bound (const key_type& k)
	{
		return (_tree.upper_bound(k));
	}

	template < class Key, class T, class Comp, class Alloc>
	typename map<Key,T,Comp,Alloc>::const_iterator
	map<Key,T,Comp,Alloc>::upper_bound (const key_type& k) const
	{
		return (_tree.upper_bound(k));
	}

	template < class Key, class T, class Comp, class Alloc>
	pair<typename map<Key,T,Comp,Alloc>::const_iterator, typename map<Key,T,Comp,Alloc>::const_iterator>	
	map<Key,T,Comp,Alloc>::equal_range (const key_type& k) const
	{
		const_iterator lb = lower_bound(k);
		const_iterator ub(lb);

		if ((*lb).first == k)
			ub++;
		return (make_pair(lb,ub));
		//return (make_pair(lower_bound(k), upper_bound(k))); // ce return si multiple, si unique autant faire appel a bound qu'une seule fois
	}

	template < class Key, class T, class Comp, class Alloc>
	pair<typename map<Key,T,Comp,Alloc>::iterator,typename map<Key,T,Comp,Alloc>::iterator>
	map<Key,T,Comp,Alloc>::equal_range (const key_type& k)
	{
		iterator lb = lower_bound(k);
		iterator ub(lb);

		if ((*lb).first == k)
			ub++;
		return (make_pair(lb,ub));
		// return (make_pair(lower_bound(k), upper_bound(k)));
	}

	/* --------------------------------------------------------------------------

		NON MEMBER FUNCTIONS
		
	-------------------------------------------------------------------------- */

	template < class Key, class T, class Comp, class Alloc>
	bool operator== (const map<Key,T,Comp,Alloc>& lhs, const map<Key,T,Comp,Alloc>& rhs)
	{
		if (lhs.size() != rhs.size())
			return (false);
		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template < class Key, class T, class Comp, class Alloc>
	bool operator!= (const map<Key,T,Comp,Alloc>& lhs, const map<Key,T,Comp,Alloc>& rhs)
	{
		if (lhs.size() != rhs.size())
			return (true);
		return (! ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template < class Key, class T, class Comp, class Alloc>
	bool operator<  (const map<Key,T,Comp,Alloc>& lhs, const map<Key,T,Comp,Alloc>& rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template < class Key, class T, class Comp, class Alloc>
	bool operator<= (const map<Key,T,Comp,Alloc>& lhs, const map<Key,T,Comp,Alloc>& rhs)
	{
		return (! ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end()));
	}

	template < class Key, class T, class Comp, class Alloc>
	bool operator>  (const map<Key,T,Comp,Alloc>& lhs, const map<Key,T,Comp,Alloc>& rhs)
	{
		return (ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end()));
	}

	template < class Key, class T, class Comp, class Alloc>
	bool operator>= (const map<Key,T,Comp,Alloc>& lhs, const map<Key,T,Comp,Alloc>& rhs)
	{
		return (! ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template < class Key, class T, class Comp, class Alloc>
	void swap (map<Key,T,Comp,Alloc>& x, map<Key,T,Comp,Alloc>& y)
	{
		x.swap(y);
	}

}

# endif