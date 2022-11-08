#ifndef __BINARY_SEARCH_TREE_HPP
# define __BINARY_SEARCH_TREE_HPP
#include <memory> // std::allocator
#include "utility.hpp" // ft::pair
#include "algorithme.hpp" // ft::swap

//To delete
#include <iostream>

namespace ft
{
	/* --------------------------------------------------------------------------

		ITERATOR FOR IDIRECTIONAL ORDERED TREE
		
	-------------------------------------------------------------------------- */

	template<class T, class NodeType> class	__tree_bidirectional_const_iter;

	template<class T, class NodeType> //l'iterator peut aller avec nimporte quel arbre tant qu'il respect la bidirectionalité et l'ordre
	class __tree_bidirectional_iter: public iterator<bidirectional_iterator_tag, T>
	{
	private:
		typedef NodeType				Node;
		template<class,class> friend class __tree_bidirectional_const_iter;
	public:
		__tree_bidirectional_iter(); //create nullptr
		__tree_bidirectional_iter(Node *node);
		__tree_bidirectional_iter(const __tree_bidirectional_iter<T,NodeType>& x);
		~__tree_bidirectional_iter();
		
		__tree_bidirectional_iter& operator=(const __tree_bidirectional_iter& x);
		
		T&	operator*() const;
		T	*operator->() const;

		__tree_bidirectional_iter& operator++();
		__tree_bidirectional_iter operator++(int);
		__tree_bidirectional_iter& operator--();
		__tree_bidirectional_iter operator--(int);

		template<class _T, class _NodeType>
		friend bool operator== (const __tree_bidirectional_iter<_T,_NodeType>& lhs, const __tree_bidirectional_iter<_T,_NodeType>& rhs);
		template<class _T, class _NodeType>
		friend bool operator== (const __tree_bidirectional_iter<_T,_NodeType>& lhs, const __tree_bidirectional_const_iter<_T,_NodeType>& rhs);
	public:
		Node							*node;
	};

	template<class T, class NodeType>
	__tree_bidirectional_iter<T,NodeType>::__tree_bidirectional_iter()
		:	node()
	{ }

	template<class T, class NodeType>
	__tree_bidirectional_iter<T,NodeType>::__tree_bidirectional_iter(Node *x)
		:	node(x)
	{ }
	
	template<class T, class NodeType>
	__tree_bidirectional_iter<T,NodeType>::__tree_bidirectional_iter(const __tree_bidirectional_iter<T,NodeType>& x)
		:	node(x.node)
	{ }

	// template<class T, class NodeType>
	// __tree_bidirectional_iter<T,NodeType>::__tree_bidirectional_iter(const __tree_bidirectional_iter<const T,NodeType>& x)
	// 	:	node(x.node)
	// { }

	// template<class T, class NodeType>
	// __tree_bidirectional_iter<T,NodeType>::__tree_bidirectional_iter(const __tree_bidirectional_const_iter<T,NodeType>& x)
	// 	:	node(x.node)
	// { }

	template<class T, class NodeType>
	__tree_bidirectional_iter<T,NodeType>::~__tree_bidirectional_iter()
	{ }

	template<class T, class NodeType>
	__tree_bidirectional_iter<T,NodeType>& __tree_bidirectional_iter<T, NodeType>::operator++()
	{
		if (this->node->right)
			node = NodeType::smallest(node->right);
		else
		{
			while (node->father && node->father->left != node) //node->father null n'arrive jamais // ah bon?
				node = node->father;
			node = node->father;
		}
		return (*this);
	}

	template<class T, class NodeType>
	__tree_bidirectional_iter<T,NodeType> __tree_bidirectional_iter<T, NodeType>::operator++(int)
	{
		__tree_bidirectional_iter tmp(*this);
		++(*this);
		return (tmp);
	}

	template<class T, class NodeType>
	__tree_bidirectional_iter<T,NodeType>& __tree_bidirectional_iter<T, NodeType>::operator--()
	{
		if (this->node->left)
			node = NodeType::biggest(node->left);
		else
		{
			while (node->father && node->father->right != node) //node->father null n'arrive jamais
				node = node->father;
			node = node->father;
		}
		return (*this);
	}

	template<class T, class NodeType>
	__tree_bidirectional_iter<T,NodeType> __tree_bidirectional_iter<T, NodeType>::operator--(int)
	{
		__tree_bidirectional_iter tmp(*this);
		++(*this);
		return (tmp);
	}

	template<class T, class NodeType>
	T& __tree_bidirectional_iter<T, NodeType>::operator*() const
	{
		return (node->content);
	}

	// template<class T, class NodeType>
	// const T& __tree_bidirectional_iter<T, NodeType>::operator*() const
	// {
	// 	return (node->content);
	// }

	template<class T, class NodeType>
	T	*__tree_bidirectional_iter<T, NodeType>::operator->() const
	{
		return (&(node->content));
	}

	// template<class T, class NodeType>
	// const T	*__tree_bidirectional_iter<T, NodeType>::operator->() const
	// {
	// 	return (&(node->content));
	// }

	template<class T, class NodeType>
	__tree_bidirectional_iter<T,NodeType>& __tree_bidirectional_iter<T, NodeType>::operator=(const __tree_bidirectional_iter<T, NodeType>& x)
	{
		this->node = x.node;
		return (*this);
	}

	template<class T, class NodeType>
	bool operator== (const __tree_bidirectional_iter<T, NodeType>& lhs, const __tree_bidirectional_iter<T, NodeType>& rhs)
	{
		return (lhs.node == rhs.node);
	}

	template<class T, class NodeType>
	bool operator!= (const __tree_bidirectional_iter<T, NodeType>& lhs, const __tree_bidirectional_iter<T, NodeType>& rhs)
	{
		return (!(lhs == rhs));
	}

	/* --------------------------------------------------------------------------

		CONST ITERATOR FOR IDIRECTIONAL ORDERED TREE
		
	-------------------------------------------------------------------------- */


	template<class T, class NodeType> //l'iterator peut aller avec nimporte quel arbre tant qu'il respect la bidirectionalité et l'ordre
	class __tree_bidirectional_const_iter: public iterator<bidirectional_iterator_tag, T>
	{
	private:
		typedef NodeType								Node;
		//typedef Node*					NodePtr;
	public:
		__tree_bidirectional_const_iter(); //create nullptr
		__tree_bidirectional_const_iter(Node *node);
		__tree_bidirectional_const_iter(const __tree_bidirectional_const_iter& x);
		__tree_bidirectional_const_iter(__tree_bidirectional_iter<T,NodeType> x);
		~__tree_bidirectional_const_iter();
		
		__tree_bidirectional_const_iter& operator=(const __tree_bidirectional_const_iter& x);
		
		const T&	operator*() const;
		const T		*operator->() const;

		__tree_bidirectional_const_iter& operator++();
		__tree_bidirectional_const_iter operator++(int);
		__tree_bidirectional_const_iter& operator--();
		__tree_bidirectional_const_iter operator--(int);

		template<class _T, class _NodeType>
		friend bool operator== (const __tree_bidirectional_const_iter<_T,_NodeType>& lhs, const __tree_bidirectional_const_iter<_T,_NodeType>& rhs);
		template<class _T, class _NodeType>
		friend bool operator== (const __tree_bidirectional_const_iter<_T,_NodeType>& lhs, const __tree_bidirectional_iter<_T,_NodeType>& rhs);
	private:
		template <class,class> friend class __tree_bidirectional_iter;
		Node							*node;
	};

	template<class T, class NodeType>
	__tree_bidirectional_const_iter<T,NodeType>::__tree_bidirectional_const_iter()
		:	node()
	{ }

	template<class T, class NodeType>
	__tree_bidirectional_const_iter<T,NodeType>::__tree_bidirectional_const_iter(Node *x)
		:	node(x)
	{ }
	
	template<class T, class NodeType>
	__tree_bidirectional_const_iter<T,NodeType>::__tree_bidirectional_const_iter(const __tree_bidirectional_const_iter<T,NodeType>& x)
		:	node(x.node)
	{ }

	template<class T, class NodeType>
	__tree_bidirectional_const_iter<T,NodeType>::__tree_bidirectional_const_iter(__tree_bidirectional_iter<T,NodeType> x)
		:	node(x.node)
	{ }

	template<class T, class NodeType>
	__tree_bidirectional_const_iter<T,NodeType>::~__tree_bidirectional_const_iter()
	{ }

	template<class T, class NodeType>
	__tree_bidirectional_const_iter<T,NodeType>& __tree_bidirectional_const_iter<T, NodeType>::operator++()
	{
		if (this->node->right)
			node = NodeType::smallest(node->right);
		else
		{
			while (node->father && node->father->left != node) //node->father null n'arrive jamais // ah bon?
				node = node->father;
			node = node->father;
		}
		return (*this);
	}

	template<class T, class NodeType>
	__tree_bidirectional_const_iter<T,NodeType> __tree_bidirectional_const_iter<T, NodeType>::operator++(int)
	{
		__tree_bidirectional_const_iter tmp(*this);
		++(*this);
		return (tmp);
	}

	template<class T, class NodeType>
	__tree_bidirectional_const_iter<T,NodeType>& __tree_bidirectional_const_iter<T, NodeType>::operator--()
	{
		if (this->node->left)
			node = NodeType::biggest(node->left);
		else
		{
			while (node->father && node->father->right != node) //node->father null n'arrive jamais
				node = node->father;
			node = node->father;
		}
		return (*this);
	}

	template<class T, class NodeType>
	__tree_bidirectional_const_iter<T,NodeType> __tree_bidirectional_const_iter<T, NodeType>::operator--(int)
	{
		__tree_bidirectional_const_iter tmp(*this);
		++(*this);
		return (tmp);
	}

	template<class T, class NodeType>
	const T& __tree_bidirectional_const_iter<T, NodeType>::operator*() const
	{
		return (node->content);
	}

	template<class T, class NodeType>
	const T	*__tree_bidirectional_const_iter<T, NodeType>::operator->() const
	{
		return (&(node->content));
	}

	template<class T, class NodeType>
	__tree_bidirectional_const_iter<T,NodeType>& __tree_bidirectional_const_iter<T, NodeType>::operator=(const __tree_bidirectional_const_iter<T, NodeType>& x)
	{
		this->node = x.node;
		return (*this);
	}

	template<class T, class NodeType>
	bool operator== (const __tree_bidirectional_const_iter<T, NodeType>& lhs, const __tree_bidirectional_const_iter<T, NodeType>& rhs)
	{
		return (lhs.node == rhs.node);
	}

	template<class T, class NodeType>
	bool operator== (const __tree_bidirectional_const_iter<T, NodeType>& lhs, const __tree_bidirectional_iter<T, NodeType>& rhs)
	{
		return (lhs.node == rhs.node);
	}

	template<class T, class NodeType>
	bool operator== (const __tree_bidirectional_iter<T, NodeType>& lhs, const __tree_bidirectional_const_iter<T, NodeType>& rhs)
	{
		return (lhs.node == rhs.node);
	}

	template<class T, class NodeType>
	bool operator!= (const __tree_bidirectional_const_iter<T, NodeType>& lhs, const __tree_bidirectional_const_iter<T, NodeType>& rhs)
	{
		return (!(lhs == rhs));
	}	

	template<class T, class NodeType>
	bool operator!= (const __tree_bidirectional_const_iter<T, NodeType>& lhs, const __tree_bidirectional_iter<T, NodeType>& rhs)
	{
		return (!(lhs == rhs));
	}

	template<class T, class NodeType>
	bool operator!= (const __tree_bidirectional_iter<T, NodeType>& lhs, const __tree_bidirectional_const_iter<T, NodeType>& rhs)
	{
		return (!(lhs == rhs));
	}	

	/* --------------------------------------------------------------------------

		BIDIRECTIONAL ORDERED TREE (+ NODE)
		
	-------------------------------------------------------------------------- */

	template<class T>
	class	_node_bst
	{
		typedef _node_bst<T>*	_NodePtr;
	public:
		_node_bst();
		_node_bst(const T& val);

		_node_bst& operator=(const _node_bst& x);

		// _node_bst_add_left();
		// _node_bst_add_right();
		T			content;
		bool		is_red;
		_NodePtr	father;
		_NodePtr	left;
		_NodePtr	right;

		static _NodePtr	smallest(_NodePtr start)
		{
			while (start->left)
				start = start->left;
			return (start);
		}
		static _NodePtr	biggest(_NodePtr start)
		{
			while (start->right)
				start = start->right;
			return (start);
		}
	private:
	};

	template<class T>
	_node_bst<T>::_node_bst()
		:	father(),
			left(),
			right()
	{ }

	template<class T>
	_node_bst<T>::_node_bst(const T& val)
		:	content(val),
			father(),
			left(),
			right()
	{ }

	template<class T>
	_node_bst<T>& _node_bst<T>::operator=(const _node_bst<T>& x)
	{
		content = x.content;
		father = x.father;
		left = x.left;
		right = x.right;
	}

	template<class T, class ValComp, class Alloc = std::allocator<T> >
	class __bst
	{
		public:
			typedef T									value_type;
			typedef ValComp								value_compare;
			typedef Alloc								allocator_type;
			typedef size_t								size_type;
			typedef typename T::first_type				key_type; //ne va pas marcher avec SET faut etre plus Smart
		private:
			typedef _node_bst<value_type>	Node;
			typedef Node			_EndNode;
			typedef typename allocator_type::template rebind<Node>::other	_node_allocator_type;
			typedef typename _node_allocator_type::pointer					_NodePtr;
			//typedef typename Node::_NodePtr								_NodePtr; est-ce que c'est pas mieux ça?
		public: 
			typedef __tree_bidirectional_iter<value_type, Node>				iterator;
			typedef __tree_bidirectional_const_iter<value_type, Node>		const_iterator;

			/* Constructors */
			__bst(const value_compare& val = value_compare(), const allocator_type& alloc = allocator_type());
			__bst(const __bst& x);
			__bst& operator=(const __bst& x);
			~__bst();

			
			_node_allocator_type	__node_alloc();

			iterator			begin();
			const_iterator		begin() const;
			iterator			end();
			const_iterator		end() const;
			size_type			size() const;
			pair<iterator,bool>	insert(const value_type& val);
			// template <class _Iter>
			// void				insert(_Iter first, _Iter last);
			iterator			find(const key_type& k);
			const_iterator		find(const key_type& k) const;
			size_type			count(const key_type& k) const;
			allocator_type		get_alloc() const {return (allocator_type());}
			size_type			max_size() const {return (_node_alloc.max_size());}
			void				clear();
			iterator 			lower_bound (const key_type& k);
			const_iterator		lower_bound (const key_type& k) const;
			iterator			upper_bound (const key_type& k);
			const_iterator		upper_bound (const key_type& k) const;
			value_compare		value_comp() const;
		
		private:
			_NodePtr			__begin_node() const { return (this->_begin); };
			_NodePtr			__end_node() const { return (this->_root.right); };

			void				__destroy_all_from_node(_NodePtr node);
			_NodePtr			__first_after_key_included(const key_type& k) const;
			_NodePtr			__first_after_key(const key_type& k) const;

			// template <class _Iter>
			// void				__insert_range(_Iter first, _Iter last);
			// template <class _Iter>
			// void				__insert_range(_Iter first, _Iter last, ft::input_iterator_tag);
			// template <class _Iter>
			// void				__insert_range(_Iter first, _Iter last, ft::forward_iterator_tag);
			// template <class _Iter>
			// void				__insert_range(_Iter first, _Iter last, std::input_iterator_tag);
			// template <class _Iter>
			// void				__insert_range(_Iter first, _Iter last, std::forward_iterator_tag);

			void			swap(__bst& x);

		private:
			_NodePtr				_begin;
			_EndNode				_root; //right is end, so it itself, left is the first node. If nothing, is itself so as begin == end. Father is always nullptr
									//for the iterator, -- check if end(), meaning if father exist then proceed to do the same as usual
			size_type				_size;
			value_compare			_value_comp;
			_node_allocator_type	_node_alloc;

			_NodePtr&				__find_leaf(_NodePtr& father, const value_type& val);

			//TODELET
		public:
			void					__print() const { __print_nodedtree(0,_root.left);}
		private:
			void					__print_nodedtree(int i, _NodePtr ptr) const
			{
				if (!ptr)
					return ;
				for (int j = 0; j < i; j++)
					std::cout << "| ";
				std::cout << "-";
				std::cout << "(key,val): ("<<  ptr->content.first << "," << ptr->content.second << ")" << std::endl;
				__print_nodedtree(i + 1, ptr->left);
				__print_nodedtree(i + 1, ptr->right);
			}
	};

	/* --------------------------------------------------------------------------

		CONSTRUCTORS
		
	-------------------------------------------------------------------------- */
	template<class T, class Compare, class Alloc>
	__bst<T,Compare,Alloc>::__bst(const value_compare& val, const allocator_type& alloc)
		:	_root(),
			_value_comp(val),
			_node_alloc(alloc)
	{
		_root.left = NULL;
		_root.right = &_root;
		_root.father = NULL;
		_size = 0;
		_begin = _root.right;
	}

	template<class T, class Compare, class Alloc>
	__bst<T,Compare,Alloc>::__bst(const __bst& x)
		:	_root(),
			_value_comp(x._value_comp),
			_node_alloc(x._node_alloc)
	{
		_root.left = NULL;
		_root.right = &_root;
		_root.father = NULL;
		_size = 0;
		_begin = _root.right;
		*this = x;
	}

	template<class T, class Compare, class Alloc>
	__bst<T,Compare,Alloc>& __bst<T,Compare,Alloc>::operator=(const __bst<T,Compare,Alloc>& x)
	{
		this->_node_alloc = x._node_alloc;
		this->_value_comp = x._value_comp;
		this->clear();
		const_iterator c_it = x.begin();
		const_iterator c_end = x.end();

		for (; c_it != c_end; c_it++)
			insert(*c_it);
		return (*this);
	}

	template<class T, class Compare, class Alloc>
	__bst<T,Compare,Alloc>::~__bst()
	{ }

	/* --------------------------------------------------------------------------

		ITERATORS
		
	-------------------------------------------------------------------------- */
	
	template<class T, class Compare, class Alloc>
	typename __bst<T,Compare,Alloc>::iterator
	__bst<T,Compare,Alloc>::begin()
	{
		return (iterator(this->_begin));
	}

	template<class T, class Compare, class Alloc>
	typename __bst<T,Compare,Alloc>::const_iterator
	__bst<T,Compare,Alloc>::begin() const
	{
		return (const_iterator(this->_begin));
	}

	template<class T, class Compare, class Alloc>
	typename __bst<T,Compare,Alloc>::iterator
	__bst<T,Compare,Alloc>::end()
	{
		return (iterator(this->__end_node()));
	}

	template<class T, class Compare, class Alloc>
	typename __bst<T,Compare,Alloc>::const_iterator
	__bst<T,Compare,Alloc>::end() const
	{
		return (const_iterator(this->__end_node()));
	}

	/* --------------------------------------------------------------------------

		CAPACITY
		
	-------------------------------------------------------------------------- */

	template<class T, class Compare, class Alloc>
	typename __bst<T,Compare,Alloc>::size_type
	__bst<T,Compare,Alloc>::size() const 
	{
		return (this->_size);
	}

	/* --------------------------------------------------------------------------

		MODIFIERS
		
	-------------------------------------------------------------------------- */

	template<class T, class Compare, class Alloc>
	pair<typename __bst<T,Compare,Alloc>::iterator,bool>
	__bst<T,Compare,Alloc>::insert(const value_type& val)
	{
		bool		is_inserted = false;
		_NodePtr	leaf_father;
		_NodePtr&	leaf = __find_leaf(leaf_father, val);

		if (leaf == NULL)
		{
			//leaf = __new_node(val); __add_node_to(leaf, leaf_father, val)
			leaf = _node_alloc.allocate(1);
			_node_alloc.construct(leaf, val);
			leaf->father = leaf_father;
			leaf->left = NULL; //déjà dans le constructeur?
			leaf->right = NULL;
			is_inserted = true;
			if (_begin->left)
				_begin = _begin->left;
			_size++;
		}
		return (pair<iterator,bool>(iterator(leaf),is_inserted));
	}

	template<class T, class Compare, class Alloc>
	void __bst<T,Compare,Alloc>::swap(__bst<T,Compare,Alloc>& x)
	{
		swap(this->_begin, x._begin);
		swap(this->_size, x._size);
		swap(this->_root, x._root);
		swap(this->_node_alloc, x._node_alloc);
		swap(this->_value_comp, x._value_comp);
	}

	template<class T, class Compare, class Alloc>
	void __bst<T,Compare,Alloc>::__destroy_all_from_node(_NodePtr node)
	{
		if (node != NULL)
		{
			__destroy_all_from_node(node->left);
			__destroy_all_from_node(node->right);
			_node_alloc.destroy(node);
			_node_alloc.deallocate(node, 1);
		}
	}

	template<class T, class Compare, class Alloc>
	void __bst<T,Compare,Alloc>::clear()
	{
		__destroy_all_from_node(_root.left);
		_size = 0;
		_root.left = NULL;
		_begin = __end_node();
	}

	/* --------------------------------------------------------------------------

		OPERATIONS
		
	-------------------------------------------------------------------------- */

	template<class T, class Compare, class Alloc>
	typename __bst<T,Compare,Alloc>::iterator
	__bst<T,Compare,Alloc>::find (const key_type& k)
	{
		_NodePtr node = _root.left;

		while (node != NULL)
		{
			if (_value_comp(node->content, k))
				node = node->right;
			else if (_value_comp(k, node->content))
				node = node->left;
			else
				return (iterator(node));
		}
		return (end());
	}

	template<class T, class Compare, class Alloc>
	typename __bst<T,Compare,Alloc>::const_iterator
	__bst<T,Compare,Alloc>::find (const key_type& k) const
	{
		_NodePtr node = _root.left;

		while (node != NULL)
		{
			if (_value_comp(node->content, k))
				node = node->right;
			else if (_value_comp(k, node->content))
				node = node->left;
			else
				return (const_iterator(node));
		}
		return (end());
	}

	template<class T, class Compare, class Alloc>
	typename __bst<T,Compare,Alloc>::size_type
	__bst<T,Compare,Alloc>::count(const key_type& k) const
	{
		_NodePtr node = _root.left;

		while (node != NULL)
		{
			if (_value_comp(node->content, k))
				node = node->right;
			else if (_value_comp(k, node->content))
				node = node->left;
			else
				return (1);
		}
		return (0);
	}

	template<class T, class Compare, class Alloc>
	typename __bst<T,Compare,Alloc>::iterator
	__bst<T,Compare,Alloc>::lower_bound (const key_type& k)
	{
		return (iterator(__first_after_key_included(k)));
	}

	template<class T, class Compare, class Alloc>
	typename __bst<T,Compare,Alloc>::const_iterator
	__bst<T,Compare,Alloc>::lower_bound (const key_type& k) const
	{
		return (const_iterator(__first_after_key_included(k)));
	}

	template<class T, class Compare, class Alloc>
	typename __bst<T,Compare,Alloc>::iterator
	__bst<T,Compare,Alloc>::upper_bound (const key_type& k)
	{
		return (iterator(__first_after_key(k)));
	}

	template<class T, class Compare, class Alloc>
	typename __bst<T,Compare,Alloc>::const_iterator
	__bst<T,Compare,Alloc>::upper_bound (const key_type& k) const
	{
		return (const_iterator(__first_after_key(k)));
	}

	template<class T, class Compare, class Alloc>
	typename __bst<T,Compare,Alloc>::_NodePtr
	__bst<T,Compare,Alloc>::__first_after_key_included(const key_type& k) const
	{
		_NodePtr node = _root.left;
		_NodePtr found = __end_node();

		while (node != NULL)
		{
			if (!_value_comp(node->content, k))
			{
				found = node;
				node = node->left; //on continue a search car possiblement un plus petit que node content mais plus grand que k existe
			}
			else
				node = node->right;
		}
		return (found); // if non found end_node is returned as the result menaing nothing is bigger than k key
	}

	template<class T, class Compare, class Alloc>
	typename __bst<T,Compare,Alloc>::_NodePtr
	__bst<T,Compare,Alloc>::__first_after_key(const key_type& k) const
	{
		_NodePtr node = _root.left;
		_NodePtr found = __end_node();

		while (node != NULL)
		{
			if (_value_comp(k, node->content))
			{
				found = node;
				node = node->left;
			}
			else
				node = node->right;
		}
		return (found); // if non found end_node is returned as the result menaing nothing is bigger than k key
	}


	
	template<class T, class Compare, class Alloc>
	typename __bst<T,Compare,Alloc>::value_compare
	__bst<T,Compare,Alloc>::value_comp() const
	{
		return (_value_comp);
	}

	template<class T, class Compare, class Alloc>
	typename __bst<T,Compare,Alloc>::_NodePtr&
	__bst<T,Compare,Alloc>::__find_leaf(_NodePtr& father, const value_type& val)
	{
		_NodePtr	node = _root.left; //static cast?

		if (node == NULL)
		{
			father = _root.right;
			return (_root.left);
		}
		while (1)
		{
			if (_value_comp(val, node->content))
			{
				if (node->left == NULL)
				{
					father = node;
					return (node->left);
				}
				node = node->left;
			}
			else if (_value_comp(node->content, val))
			{
				if (node->right == NULL)
				{
					father = node;
					return (node->right);
				}
				node = node->right;
			}
			else
			{
				if (node->father->left == node) //barbare
					return (node->father->left);
				else
					return (node->father->right);
			}
		}
	}

	/* --------------------------------------------------------------------------

		NON MEMBER FUNCTIONS
		
	-------------------------------------------------------------------------- */

	template<class T, class Compare, class Alloc>
	void swap (__bst<T,Compare,Alloc>& x, __bst<T,Compare,Alloc>& y)
	{
		x.swap(y);
	}
}

#endif