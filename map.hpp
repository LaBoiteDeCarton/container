#ifndef FT_MAP_HPP
# define FT_MAP_HPP

#include <memory> // std::allocator
#include <functional> // std::less  and std::binary_function
#include "ft_utility.hpp" // ft::pair

#include "iterator.hpp" // ft::iterator ft::iterator_traits ft::bidirectional_iterator_tag

//#include <map>

namespace ft
{
	/* --------------------------------------------------------------------------

		ITERATOR FOR IDIRECTIONAL ORDERED TREE
		
	-------------------------------------------------------------------------- */


	template<class T>
	class __tree_bidirectional_iter: public iterator<bidirectional_iterator_tag, T>
	{
	public:
		__tree_bidirectional_iter();
		__tree_bidirectional_iter(const __tree_bidirectional_iter& x);

		__tree_bidirectional_iter& operator=(const __tree_bidirectional_iter& x);
		
		T& operator*();
		T& operator->();
		__tree_bidirectional_iter& operator++();
		__tree_bidirectional_iter& operator++(int);
		__tree_bidirectional_iter& operator--();
		__tree_bidirectional_iter& operator--(int);

	private:
		//NodeType	*node;
	};

	template<class T>
	T& __tree_bidirectional_iter<T>::operator*()
	{

	}

	template<class T>
	bool operator== (const __tree_bidirectional_iter<T>& lhs, const __tree_bidirectional_iter<T>& rhs)
	{
		
	}

	template<class T>
	bool operator!= (const __tree_bidirectional_iter<T>& lhs, const __tree_bidirectional_iter<T>& rhs)
	{
		
	}	


	/* --------------------------------------------------------------------------

		BIDIRECTIONAL ORDERED TREE (+ NODE)
		
	-------------------------------------------------------------------------- */

	template<class T>
	class	_node_bst
	{
		_node_bst();
		_node_bst(const T& val);

		_node_bst& operator=(const _node_bst& x);

		// _node_bst_add_left();
		// _node_bst_add_right();
	public:
		const T		node;
		_node_bst	*father; //needed for iterator++ -- etc
		_node_bst	*left;
		_node_bst	*right;
	private:
	};

	template<class T, class Comp, class Alloc = std::allocator<T> >
	class __bst
	{
		public:
			typedef T			value_type;
			typedef Comp		key_compare;
			typedef Alloc		allocator_type;
			typedef size_t		size_type;

			__bst();
			~__bst();
			
			size_type	size() { return (this->_size); }; 

		private:
			typedef _node_bst<T>	Node;

			__bst(value_type& val);
			__bst(__bst& x);
			__bst& operator=(__bst& x);

			Node		*_root;
			size_type	_size;
	};

	template < class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<pair<const Key,T> > >
	class map
	{
		public:
			typedef Key											key_type;
			typedef T											mapped_type;
			typedef pair<const Key,T>							value_type;
			typedef Compare										key_compare;
			typedef Alloc										allocator_type;
			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;
			typedef __tree_bidirectional_iter<value_type>		iterator;
			typedef __tree_bidirectional_iter<const value_type>	const_iterator;
			typedef ft::reverse_iterator<iterator>				reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;
			typedef typename ft::iterator_traits<iterator>::difference_type	difference_type; //c'est du c++11 ça non?
			typedef size_t													size_type;


			class value_compare : public std::binary_function<value_type, value_type, bool>
			{
				friend class map;
			protected:
				Compare	comp;
				value_compare(Compare c): comp(c) {};
			public:
				bool	operator() (const value_type& lhs, const value_type& rhs) const{
					return (comp(lhs.first, rhs.first));
				};
			};

			/* Contructors */
			explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type());	
			template <class InputIterator>
			map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type());	
			map (const map& x);
			~map();

			map& operator= (const map& x);
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
			typedef __bst<value_type, key_compare, allocator_type>	KeyValBST;
			
			KeyValBST		_tree;

	};

	/* --------------------------------------------------------------------------

		CONSTRUCTORS
		
	-------------------------------------------------------------------------- */
	template < class Key, class T, class Comp, class Alloc>
	map<Key,T,Comp,Alloc>::map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
	{

	}

	template < class Key, class T, class Comp, class Alloc>
	template <class InputIterator>
	map<Key,T,Comp,Alloc>::map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
	{

	}

	template < class Key, class T, class Comp, class Alloc>
	map<Key,T,Comp,Alloc>::map (const map& x)
	{

	}

	template < class Key, class T, class Comp, class Alloc>
	map<Key,T,Comp,Alloc>::~map()
	{

	}

	template < class Key, class T, class Comp, class Alloc>
	map<Key,T,Comp,Alloc>& map<Key,T,Comp,Alloc>::operator= (const map<Key,T,Comp,Alloc>& x)
	{

	}

	template < class Key, class T, class Comp, class Alloc>
	typename map<Key,T,Comp,Alloc>::allocator_type
	map<Key,T,Comp,Alloc>::get_allocator() const
	{

	}

	/* --------------------------------------------------------------------------

		ITERATORS
		
	-------------------------------------------------------------------------- */

	template < class Key, class T, class Comp, class Alloc>
	typename map<Key,T,Comp,Alloc>::iterator
	map<Key,T,Comp,Alloc>::begin()
	{
		
	}

	template < class Key, class T, class Comp, class Alloc>
	typename map<Key,T,Comp,Alloc>::const_iterator
	map<Key,T,Comp,Alloc>::begin() const
	{
		
	}

	template < class Key, class T, class Comp, class Alloc>
	typename map<Key,T,Comp,Alloc>::iterator
	map<Key,T,Comp,Alloc>::end()
	{
		
	}

	template < class Key, class T, class Comp, class Alloc>
	typename map<Key,T,Comp,Alloc>::const_iterator
	map<Key,T,Comp,Alloc>::end() const
	{
		
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
		allocator_type().maxsize();
	}
	
	/* --------------------------------------------------------------------------

		ELEMENT ACCESS
		
	-------------------------------------------------------------------------- */

	template < class Key, class T, class Comp, class Alloc>
	typename map<Key,T,Comp,Alloc>::mapped_type&
	map<Key,T,Comp,Alloc>::operator[] (const key_type& k)
	{

	}

	template < class Key, class T, class Comp, class Alloc>
	typename map<Key,T,Comp,Alloc>::mapped_type&
	map<Key,T,Comp,Alloc>::at (const key_type& k)
	{

	}

	template < class Key, class T, class Comp, class Alloc>
	const typename map<Key,T,Comp,Alloc>::mapped_type&
	map<Key,T,Comp,Alloc>::at (const key_type& k) const
	{

	}

	/* --------------------------------------------------------------------------

		MODIFIERS
		
	-------------------------------------------------------------------------- */


	template < class Key, class T, class Comp, class Alloc>
	pair<typename map<Key,T,Comp,Alloc>::iterator,bool>
	map<Key,T,Comp,Alloc>::insert (const value_type& val)
	{

	}
	
	template < class Key, class T, class Comp, class Alloc>
	map<Key,T,Comp,Alloc>::iterator
	map<Key,T,Comp,Alloc>::insert (iterator hint, const value_type& val)
	{

	}
	
	template < class Key, class T, class Comp, class Alloc>
	template <class InputIterator>
	void map<Key,T,Comp,Alloc>::insert (InputIterator first, InputIterator last)
	{

	}
	
	template < class Key, class T, class Comp, class Alloc>
	void map<Key,T,Comp,Alloc>::erase (iterator position)
	{

	}
	
	template < class Key, class T, class Comp, class Alloc>
	typename map<Key,T,Comp,Alloc>::size_type
	map<Key,T,Comp,Alloc>::erase (const key_type& k)
	{

	}
	
	template < class Key, class T, class Comp, class Alloc>
	void map<Key,T,Comp,Alloc>::erase (iterator first, iterator last)
	{

	}
	
	template < class Key, class T, class Comp, class Alloc>
	void map<Key,T,Comp,Alloc>::swap (map& x)
	{

	}
	
	template < class Key, class T, class Comp, class Alloc>
	void map<Key,T,Comp,Alloc>::clear()
	{

	}

	/* --------------------------------------------------------------------------

		OBSERVERS
		
	-------------------------------------------------------------------------- */

	template < class Key, class T, class Comp, class Alloc>
	typename map<Key,T,Comp,Alloc>::key_compare
	map<Key,T,Comp,Alloc>::key_comp() const
	{
		
	}

	template < class Key, class T, class Comp, class Alloc>
	typename map<Key,T,Comp,Alloc>::value_compare
	map<Key,T,Comp,Alloc>::value_comp() const
	{
		
	}

	/* --------------------------------------------------------------------------

		OPERATIONS
		
	-------------------------------------------------------------------------- */


	template < class Key, class T, class Comp, class Alloc>
	typename map<Key,T,Comp,Alloc>::iterator
	map<Key,T,Comp,Alloc>::find (const key_type& k)
	{

	}

	template < class Key, class T, class Comp, class Alloc>
	typename map<Key,T,Comp,Alloc>::const_iterator
	map<Key,T,Comp,Alloc>::find (const key_type& k) const
	{

	}

	template < class Key, class T, class Comp, class Alloc>
	typename map<Key,T,Comp,Alloc>::size_type
	map<Key,T,Comp,Alloc>::count (const key_type& k) const
	{

	}

	template < class Key, class T, class Comp, class Alloc>
	typename map<Key,T,Comp,Alloc>::iterator
	map<Key,T,Comp,Alloc>::lower_bound (const key_type& k)
	{

	}

	template < class Key, class T, class Comp, class Alloc>
	typename map<Key,T,Comp,Alloc>::const_iterator
	map<Key,T,Comp,Alloc>::lower_bound (const key_type& k) const
	{

	}

	template < class Key, class T, class Comp, class Alloc>
	typename map<Key,T,Comp,Alloc>::iterator
	map<Key,T,Comp,Alloc>::upper_bound (const key_type& k)
	{

	}

	template < class Key, class T, class Comp, class Alloc>
	typename map<Key,T,Comp,Alloc>::const_iterator
	map<Key,T,Comp,Alloc>::upper_bound (const key_type& k) const
	{

	}

	template < class Key, class T, class Comp, class Alloc>
	pair<typename map<Key,T,Comp,Alloc>::const_iterator, typename map<Key,T,Comp,Alloc>::const_iterator>	
	map<Key,T,Comp,Alloc>::equal_range (const key_type& k) const
	{

	}

	template < class Key, class T, class Comp, class Alloc>
	pair<typename map<Key,T,Comp,Alloc>::iterator,typename map<Key,T,Comp,Alloc>::iterator>
	map<Key,T,Comp,Alloc>::equal_range (const key_type& k)
	{

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