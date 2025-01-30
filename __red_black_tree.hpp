#ifndef __RED_BLACK_TREE_HPP
#define __RED_BLACK_TREE_HPP

/*
			#Includes							//	used class or functions from inlcudes
*/
#include <memory>							 // std::allocator
#include "utility.hpp"						 // ft::pair
#include "algorithme.hpp"					 // ft::swap
#include "__tree_bidirectional_iterator.hpp" // ft::__tree_bidirectional_iter, ft::__tree_bidirectional_const_iter

#include <iostream>
namespace ft
{
	/* --------------------------------------------------------------------------

		BIDIRECTIONAL NODE

	-------------------------------------------------------------------------- */

	template <class T>
	class _node_rbt
	{
		typedef _node_rbt<T> *_NodePtr;

	public:
		_node_rbt();
		_node_rbt(const T &val);

		T content;
		bool is_red;
		_NodePtr father;
		_NodePtr left;
		_NodePtr right;

		static _NodePtr smallest(_NodePtr start)
		{
			while (start->left)
				start = start->left;
			return (start);
		}
		static _NodePtr biggest(_NodePtr start)
		{
			while (start->right)
				start = start->right;
			return (start);
		}
		static _NodePtr __uncle(_NodePtr node)
		{
			if (!node->father || !node->father->father) // au cas où
				return (NULL);
			if (node->father->father->left == node->father)
				return (node->father->father->right);
			return (node->father->father->left);
		}

		static bool __is_red(_NodePtr ptr)
		{
			if (!ptr)
				return (false);
			return (ptr->is_red);
		}

	private:
		_node_rbt(const _node_rbt &x);
		_node_rbt &operator=(const _node_rbt &x);
	};

	template <class T>
	_node_rbt<T>::_node_rbt()
		: is_red(true),
		  father(),
		  left(),
		  right()
	{
	}

	template <class T>
	_node_rbt<T>::_node_rbt(const T &val)
		: content(val),
		  is_red(true),
		  father(),
		  left(),
		  right()
	{
	}

	template <class T>
	_node_rbt<T>::_node_rbt(const _node_rbt &x)
	{
		(void)x;
	}

	template <class T>
	_node_rbt<T> &_node_rbt<T>::operator=(const _node_rbt<T> &x)
	{
		(void)x;
	}

	/* --------------------------------------------------------------------------

		BIDIRECTIONAL ORDERED TREE

	-------------------------------------------------------------------------- */

	template <class T, class ValComp, class Alloc = std::allocator<T>>
	class __rbt
	{
	public:
		typedef T value_type;
		typedef ValComp value_compare;
		typedef Alloc allocator_type;
		typedef size_t size_type;

	private:
		typedef _node_rbt<value_type> Node;
		typedef Node _EndNode;
		typedef typename allocator_type::template rebind<Node>::other _node_allocator_type;
		typedef typename _node_allocator_type::pointer _NodePtr;
		// typedef typename Node::_NodePtr								_NodePtr; est-ce que c'est pas mieux ça?
	public:
		typedef __tree_bidirectional_iter<value_type, Node> iterator;
		typedef __tree_bidirectional_const_iter<value_type, Node> const_iterator;

		/* Constructors */
		__rbt(const value_compare &val = value_compare(), const allocator_type &alloc = allocator_type());
		__rbt(const __rbt &x);
		__rbt &operator=(const __rbt &x);
		~__rbt();

		_node_allocator_type __node_alloc();
		allocator_type get_alloc() const { return (allocator_type()); }
		value_compare value_comp() const;

		/* Iterators */
		iterator begin();
		const_iterator begin() const;
		iterator end();
		const_iterator end() const;

		/* Capacity */
		size_type size() const;
		size_type max_size() const;

		/* Modifiers */
		pair<iterator, bool> insert(const value_type &val);
		iterator multi_insert(const value_type &val);
		// pair<const_iterator,bool>	insert(const value_type& val)
		void erase(const_iterator position);
		void clear();
		void swap(__rbt &x);

		/* Operations */
		template <class _KeyType>
		iterator find(const _KeyType &k);
		template <class _KeyType>
		const_iterator find(const _KeyType &k) const;
		template <class _KeyType>
		iterator find_first(const _KeyType &k);
		template <class _KeyType>
		const_iterator find_first(const _KeyType &k) const;
		template <class _KeyType>
		size_type count(const _KeyType &k) const;
		template <class _KeyType>
		iterator lower_bound(const _KeyType &k);
		template <class _KeyType>
		const_iterator lower_bound(const _KeyType &k) const;
		template <class _KeyType>
		iterator upper_bound(const _KeyType &k);
		template <class _KeyType>
		const_iterator upper_bound(const _KeyType &k) const;

	private:
		_NodePtr _begin;
		_EndNode _root;
		size_type _size;
		value_compare _value_comp;
		_node_allocator_type _node_alloc;

		_NodePtr __begin_node() const { return (this->_begin); };
		_NodePtr __end_node() const { return (this->_root.right); };
		void __destroy_all_from_node(_NodePtr node);
		template <class _KeyType>
		_NodePtr __first_after_key_included(const _KeyType &k) const;
		template <class _KeyType>
		_NodePtr __first_after_key(const _KeyType &k) const;
		_NodePtr &__find_leaf(_NodePtr &father, const value_type &val);

		/* Red Black Tree Algorithmes */
		void __rebalance_after_insert(_NodePtr node);
		void __rotate_tree_left(_NodePtr node);
		void __rotate_tree_right(_NodePtr node);
		// _NodePtr&				__transplant(_NodePtr x, _NodePtr y);
		// void					__make_node_disappear(_NodePtr node);
		void __rebalance_after_left_erase(_NodePtr father);
		void __rebalance_after_right_erase(_NodePtr father);

		/* print rbt to delete */
		// void	__print_rbt_i(int i, _NodePtr node)
		// {
		// 	if (node)
		// 	{
		// 		for (int j = 0; j < i; j++)
		// 			std::cout << "|";
		// 		std::cout << "*";
		// 		if (node->is_red == true)
		// 			std::cout << "R";
		// 		else
		// 			std::cout << "B";
		// 		std::cout << node->content;
		// 		std::cout << std::endl;
		// 		__print_rbt_i(i + 1, node->left);
		// 		__print_rbt_i(i + 1, node->right);
		// 	}
		// }
		// void	__print_rbt() {__print_rbt_i(0, _root.left);};
	};

	/* --------------------------------------------------------------------------

		CONSTRUCTORS

	-------------------------------------------------------------------------- */
	template <class T, class Compare, class Alloc>
	__rbt<T, Compare, Alloc>::__rbt(const value_compare &val, const allocator_type &alloc)
		: _root(),
		  _value_comp(val),
		  _node_alloc(alloc)
	{
		_root.left = NULL;
		_root.right = &_root;
		_root.father = NULL;
		_size = 0;
		_begin = _root.right;
	}

	template <class T, class Compare, class Alloc>
	__rbt<T, Compare, Alloc>::__rbt(const __rbt &x)
		: _root(),
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

	template <class T, class Compare, class Alloc>
	__rbt<T, Compare, Alloc> &__rbt<T, Compare, Alloc>::operator=(const __rbt<T, Compare, Alloc> &x)
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

	template <class T, class Compare, class Alloc>
	__rbt<T, Compare, Alloc>::~__rbt()
	{
		__destroy_all_from_node(_root.left);
	}

	/* --------------------------------------------------------------------------

		ITERATORS

	-------------------------------------------------------------------------- */

	template <class T, class Compare, class Alloc>
	typename __rbt<T, Compare, Alloc>::iterator
	__rbt<T, Compare, Alloc>::begin()
	{
		return (iterator(this->_begin));
	}

	template <class T, class Compare, class Alloc>
	typename __rbt<T, Compare, Alloc>::const_iterator
	__rbt<T, Compare, Alloc>::begin() const
	{
		return (const_iterator(this->_begin));
	}

	template <class T, class Compare, class Alloc>
	typename __rbt<T, Compare, Alloc>::iterator
	__rbt<T, Compare, Alloc>::end()
	{
		return (iterator(this->__end_node()));
	}

	template <class T, class Compare, class Alloc>
	typename __rbt<T, Compare, Alloc>::const_iterator
	__rbt<T, Compare, Alloc>::end() const
	{
		return (const_iterator(this->__end_node()));
	}

	/* --------------------------------------------------------------------------

		CAPACITY

	-------------------------------------------------------------------------- */

	template <class T, class Compare, class Alloc>
	typename __rbt<T, Compare, Alloc>::size_type
	__rbt<T, Compare, Alloc>::size() const
	{
		return (this->_size);
	}

	template <class T, class Compare, class Alloc>
	typename __rbt<T, Compare, Alloc>::size_type
	__rbt<T, Compare, Alloc>::max_size() const
	{
		return (_node_alloc.max_size());
	}

	/* --------------------------------------------------------------------------

		MODIFIERS

	-------------------------------------------------------------------------- */

	// prerequis, node->right existe
	template <class T, class Compare, class Alloc>
	void __rbt<T, Compare, Alloc>::__rotate_tree_left(_NodePtr node)
	{
		_NodePtr right_node = node->right;

		node->right = right_node->left;
		if (node->right)
			node->right->father = node;
		right_node->left = node;
		right_node->father = node->father;
		node->father = right_node;
		if (right_node->father->left == node)
			right_node->father->left = right_node;
		else
			right_node->father->right = right_node;
	}

	// prerequis, node->left existe
	template <class T, class Compare, class Alloc>
	void __rbt<T, Compare, Alloc>::__rotate_tree_right(_NodePtr node)
	{
		_NodePtr left_node = node->left;

		node->left = left_node->right;
		if (node->left)
			node->left->father = node;
		left_node->right = node;
		left_node->father = node->father;
		node->father = left_node;
		if (left_node->father->left == node)
			left_node->father->left = left_node;
		else
			left_node->father->right = left_node;
	}

	// node color is red
	template <class T, class Compare, class Alloc>
	void __rbt<T, Compare, Alloc>::__rebalance_after_insert(_NodePtr node)
	{
		_NodePtr uncle;

		while (node->father != __end_node() && node->father->is_red)
		{
			uncle = Node::__uncle(node);
			if (Node::__is_red(uncle))
			{
				node->father->is_red = false;
				uncle->is_red = false; // uncle existe pour sur
				node->father->father->is_red = true;
				node = node->father->father;
			}
			else if (node->father->left == node && node->father->father->right == node->father)
			{
				node = node->father;
				__rotate_tree_right(node);
			}
			else if (node->father->right == node && node->father->father->left == node->father) // triangle symetrique
			{
				node = node->father;
				__rotate_tree_left(node);
			}
			else if (node->father->left == node) // Cas 4, Oncle noir ligne
			{
				node->father->father->is_red = true;
				node->father->is_red = false;
				__rotate_tree_right(node->father->father);
			}
			else // Oncle noir ligne mais symetrique
			{
				node->father->father->is_red = true;
				node->father->is_red = false;
				__rotate_tree_left(node->father->father);
			}
		}
		this->_root.left->is_red = false;
	}

	template <class T, class Compare, class Alloc>
	pair<typename __rbt<T, Compare, Alloc>::iterator, bool>
	__rbt<T, Compare, Alloc>::insert(const value_type &val)
	{
		bool is_inserted = false;
		_NodePtr leaf_father;
		_NodePtr &leaf = __find_leaf(leaf_father, val);
		_NodePtr ret_ptr = leaf; // barbare

		if (leaf == NULL)
		{
			// leaf = __new_node(val); __add_node_to(leaf, leaf_father, val)
			leaf = _node_alloc.allocate(1);
			_node_alloc.construct(leaf, val);
			leaf->father = leaf_father;
			leaf->left = NULL; // déjà dans le constructeur?
			leaf->right = NULL;
			leaf->is_red = true;
			is_inserted = true;
			if (_begin->left)
				_begin = _begin->left;
			_size++;
			ret_ptr = leaf;
			__rebalance_after_insert(leaf);
		}
		return (pair<iterator, bool>(iterator(ret_ptr), is_inserted));
	}

	template <class T, class Compare, class Alloc>
	typename __rbt<T, Compare, Alloc>::iterator
	__rbt<T, Compare, Alloc>::multi_insert(const value_type &val)
	{
		_NodePtr leaf_father;
		_NodePtr &leaf = __find_leaf(leaf_father, val);
		_NodePtr ret_ptr = leaf; // barbare

		// leaf = __new_node(val); __add_node_to(leaf, leaf_father, val)
		leaf = _node_alloc.allocate(1);
		_node_alloc.construct(leaf, val);
		leaf->father = leaf_father;
		leaf->left = NULL; // déjà dans le constructeur?
		leaf->right = NULL;
		leaf->is_red = true;
		is_inserted = true;
		if (_begin->left)
			_begin = _begin->left;
		_size++;
		ret_ptr = leaf;
		__rebalance_after_insert(leaf);

		return (iterator(ret_ptr));
	}

	template <class T, class Compare, class Alloc>
	void __rbt<T, Compare, Alloc>::swap(__rbt<T, Compare, Alloc> &x)
	{
		ft::swap(this->_root.left, x._root.left);
		if (this->_root.left)
			this->_root.left->father = this->_root.right;
		if (x._root.left)
			x._root.left->father = x._root.right; // barbare
		ft::swap(this->_begin, x._begin);
		ft::swap(this->_size, x._size);
		ft::swap(this->_node_alloc, x._node_alloc);
		ft::swap(this->_value_comp, x._value_comp);
	}

	template <class T, class Compare, class Alloc>
	void __rbt<T, Compare, Alloc>::__destroy_all_from_node(_NodePtr node)
	{
		if (node != NULL)
		{
			__destroy_all_from_node(node->left);
			__destroy_all_from_node(node->right);
			_node_alloc.destroy(node);
			_node_alloc.deallocate(node, 1); // __destroy_one_node(_NodePtr node)
		}
	}

	template <class T, class Compare, class Alloc>
	void __rbt<T, Compare, Alloc>::clear()
	{
		__destroy_all_from_node(_root.left);
		_size = 0;
		_root.left = NULL;
		_begin = __end_node();
	}

	// template<class T, class Compare, class Alloc>
	// typename __rbt<T,Compare,Alloc>::_NodePtr&
	// __rbt<T,Compare,Alloc>::__transplant(_NodePtr x, _NodePtr y)
	// {
	// 	if (y)
	// 		y->father = x->father;
	// 	if (x->father->left == x)
	// 	{
	// 		x->father->left = y;
	// 		return (x->father->left);
	// 	}
	// 	x->father->right = y;
	// 	return (x->father->right);
	// }

	/* left node of father is black (may be NULL), balance correction needed on the left*/
	template <class T, class Compare, class Alloc>
	void __rbt<T, Compare, Alloc>::__rebalance_after_left_erase(_NodePtr father)
	{
		if (father->left && father->left->is_red)
		{
			father->left->is_red = false;
			return;
		}
		if (father == __end_node())
			return;
		if (father->right->is_red)
		{
			father->right->is_red = false;
			father->is_red = true;
			__rotate_tree_left(father);
			return (__rebalance_after_left_erase(father));
		}
		else if ((!father->right->left && !father->right->right) || (father->right->left && father->right->left->is_red == false && father->right->right && father->right->right->is_red == false))
		{
			father->right->is_red = true;
			if (father->father->left == father)
				return (__rebalance_after_left_erase(father->father));
			else
				return (__rebalance_after_right_erase(father->father));
		}
		else if (father->right->left && father->right->left->is_red)
		{
			father->right->left->is_red = false;
			father->right->is_red = true;
			__rotate_tree_right(father->right);
			return (__rebalance_after_left_erase(father));
		}
		else
		{
			father->right->is_red = father->is_red;
			father->is_red = false;
			father->right->right->is_red = false;
			return (__rotate_tree_left(father));
		}
	}

	/* right node of father is black (may be NULL), balance correction needed on the right */
	template <class T, class Compare, class Alloc>
	void __rbt<T, Compare, Alloc>::__rebalance_after_right_erase(_NodePtr father)
	{
		if (father->right && father->right->is_red)
		{
			father->right->is_red = false;
			return;
		}
		if (father->left->is_red)
		{
			father->left->is_red = false;
			father->is_red = true;
			__rotate_tree_right(father);
			return (__rebalance_after_right_erase(father));
		}
		else if ((!father->left->left && !father->left->right) || (father->left->left && father->left->left->is_red == false && father->left->right && father->left->right->is_red == false))
		{
			father->left->is_red = true;
			if (father->father->left == father)
				return (__rebalance_after_left_erase(father->father));
			else
				return (__rebalance_after_right_erase(father->father));
		}
		else if (father->left->right && father->left->right->is_red)
		{
			father->left->right->is_red = false;
			father->left->is_red = true;
			__rotate_tree_left(father->left);
			return (__rebalance_after_right_erase(father));
		}
		else
		{
			father->left->is_red = father->is_red;
			father->is_red = false;
			father->left->left->is_red = false;
			return (__rotate_tree_right(father));
		}
	}

	/* prerequis, position n'est pas end() */
	template <class T, class Compare, class Alloc>
	void __rbt<T, Compare, Alloc>::erase(const_iterator position)
	{
		const_iterator ptr(position++);
		_NodePtr next_ptr = position.node, del_ptr = ptr.node;
		_NodePtr father_save; // cas 3
		bool to_fix;

		if (del_ptr == __begin_node())
			this->_begin = next_ptr;
		if (del_ptr->left == NULL)
		{
			if (del_ptr->father->left == del_ptr)
				del_ptr->father->left = del_ptr->right;
			else if (del_ptr->father->right == del_ptr)
				del_ptr->father->right = del_ptr->right;
			if (del_ptr->right) // cas où les deux sont NULL on ne fait rien
				del_ptr->right->father = del_ptr->father;
			if (!del_ptr->is_red && del_ptr->father->left == del_ptr->right)
				__rebalance_after_left_erase(del_ptr->father);
			else if (!del_ptr->is_red)
				__rebalance_after_right_erase(del_ptr->father);
		}
		else if (del_ptr->right == NULL)
		{
			if (del_ptr->father->left == del_ptr)
				del_ptr->father->left = del_ptr->left;
			else if (del_ptr->father->right == del_ptr)
				del_ptr->father->right = del_ptr->left;
			del_ptr->left->father = del_ptr->father;
			if (!del_ptr->is_red && del_ptr->father->left == del_ptr->left)
				__rebalance_after_left_erase(del_ptr->father);
			else if (!del_ptr->is_red)
				__rebalance_after_right_erase(del_ptr->father);
		}
		else
		{
			to_fix = !next_ptr->is_red;
			if (next_ptr->father != del_ptr)
				father_save = next_ptr->father;
			else
				father_save = next_ptr;
			// On va remonter le noeud du ptr suivant a la place de celui a supprimer
			// On connecte le nouveau noeud avec la partie gauche de l'ancien
			next_ptr->left = del_ptr->left;
			next_ptr->left->father = next_ptr;
			// Il prend aussi ce qui est a droit du noeud a condition qu'il ne soit pas le noeud lui meme
			// dans le cas où c'est lui meme on a rien a faire
			if (del_ptr->right != next_ptr)
				next_ptr->right = del_ptr->right;
			// On détache le nouveau noeud de son environnement, le father du nouveau noeud pointe pluls vers lui mais vers NULL
			if (next_ptr->father->left == next_ptr)
				next_ptr->father->left = NULL;
			else if (next_ptr->father->right == next_ptr)
				next_ptr->father->right = NULL;
			// On redirige le noeud pere vers le noeud pere du noeud a supprimer
			next_ptr->father = del_ptr->father;
			// On redirige demande au pere du noeud de le rediriger vers lui
			if (del_ptr->father->left == del_ptr)
				del_ptr->father->left = next_ptr;
			else if (del_ptr->father->right == del_ptr)
				del_ptr->father->right = next_ptr;
			// enfin on redirigie les noeuds fils de droite si il existe vers lui meme via le father
			if (next_ptr->right)
				next_ptr->right->father = next_ptr;
			next_ptr->is_red = del_ptr->is_red;
			if (to_fix && father_save == next_ptr)
				__rebalance_after_right_erase(father_save);
			else if (to_fix)
				__rebalance_after_left_erase(father_save);
		}
		_node_alloc.destroy(del_ptr);
		_node_alloc.deallocate(del_ptr, 1);
		_size--;
	}

	/* --------------------------------------------------------------------------

		OPERATIONS

	-------------------------------------------------------------------------- */

	template <class T, class Compare, class Alloc>
	template <class _KeyType>
	typename __rbt<T, Compare, Alloc>::iterator
	__rbt<T, Compare, Alloc>::find(const _KeyType &k)
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

	template <class T, class Compare, class Alloc>
	template <class _KeyType>
	typename __rbt<T, Compare, Alloc>::const_iterator
	__rbt<T, Compare, Alloc>::find(const _KeyType &k) const
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

	template <class T, class Compare, class Alloc>
	template <class _KeyType>
	typename __rbt<T, Compare, Alloc>::iterator
	__rbt<T, Compare, Alloc>::find_first(const _KeyType &k)
	{
		_NodePtr node = _root.left;
		_NodePtr first_match = NULL;

		while (node != NULL)
		{
			if (_value_comp(node->content, k))
				node = node->right;
			else if (_value_comp(k, node->content))
				node = node->left;
			else
			{
				first_match = node;
				node = node->left;
				// plus rapide que d'utiliser iterator-- car on peux skip toute une partie de l'arbre
			}
		}
		return (first_match ? iterator(first_match) : end());
	}

	template <class T, class Compare, class Alloc>
	template <class _KeyType>
	typename __rbt<T, Compare, Alloc>::const_iterator
	__rbt<T, Compare, Alloc>::find_first(const _KeyType &k) const
	{
		_NodePtr node = _root.left;
		_NodePtr first_match = NULL;

		while (node != NULL)
		{
			if (_value_comp(node->content, k))
				node = node->right;
			else if (_value_comp(k, node->content))
				node = node->left;
			else
			{
				first_match = node;
				node = node->left;
			}
		}
		return (first_match ? const_iterator(first_match) : end());
	}

	template <class T, class Compare, class Alloc>
	template <class _KeyType>
	typename __rbt<T, Compare, Alloc>::size_type
	__rbt<T, Compare, Alloc>::count(const _KeyType &k) const
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

	template <class T, class Compare, class Alloc>
	template <class _KeyType>
	typename __rbt<T, Compare, Alloc>::iterator
	__rbt<T, Compare, Alloc>::lower_bound(const _KeyType &k)
	{
		return (iterator(__first_after_key_included(k)));
	}

	template <class T, class Compare, class Alloc>
	template <class _KeyType>
	typename __rbt<T, Compare, Alloc>::const_iterator
	__rbt<T, Compare, Alloc>::lower_bound(const _KeyType &k) const
	{
		return (const_iterator(__first_after_key_included(k)));
	}

	template <class T, class Compare, class Alloc>
	template <class _KeyType>
	typename __rbt<T, Compare, Alloc>::iterator
	__rbt<T, Compare, Alloc>::upper_bound(const _KeyType &k)
	{
		return (iterator(__first_after_key(k)));
	}

	template <class T, class Compare, class Alloc>
	template <class _KeyType>
	typename __rbt<T, Compare, Alloc>::const_iterator
	__rbt<T, Compare, Alloc>::upper_bound(const _KeyType &k) const
	{
		return (const_iterator(__first_after_key(k)));
	}

	template <class T, class Compare, class Alloc>
	template <class _KeyType>
	typename __rbt<T, Compare, Alloc>::_NodePtr
	__rbt<T, Compare, Alloc>::__first_after_key_included(const _KeyType &k) const
	{
		_NodePtr node = _root.left;
		_NodePtr found = __end_node();

		while (node != NULL)
		{
			if (!_value_comp(node->content, k))
			{
				found = node;
				node = node->left; // on continue a search car possiblement un plus petit que node content mais plus grand que k existe
			}
			else
				node = node->right;
		}
		return (found); // if non found end_node is returned as the result menaing nothing is bigger than k key
	}

	template <class T, class Compare, class Alloc>
	template <class _KeyType>
	typename __rbt<T, Compare, Alloc>::_NodePtr
	__rbt<T, Compare, Alloc>::__first_after_key(const _KeyType &k) const
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

	template <class T, class Compare, class Alloc>
	typename __rbt<T, Compare, Alloc>::value_compare
	__rbt<T, Compare, Alloc>::value_comp() const
	{
		return (_value_comp);
	}

	template <class T, class Compare, class Alloc>
	typename __rbt<T, Compare, Alloc>::_NodePtr &
	__rbt<T, Compare, Alloc>::__find_leaf(_NodePtr &father, const value_type &val)
	{
		_NodePtr node = _root.left; // static cast?

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
				if (node->father->left == node) // barbare
					return (node->father->left);
				else
					return (node->father->right);
			}
		}
	}
}

#endif