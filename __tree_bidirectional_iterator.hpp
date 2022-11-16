#ifndef __TREE_BIDIRECTIONAL_ITERATOR_HPP
# define __TREE_BIDIRECTIONAL_ITERATOR_HPP

#include "iterator.hpp"

namespace ft
{
	/* --------------------------------------------------------------------------

		ITERATOR FOR DIRECTIONAL ORDERED TREE
		
	-------------------------------------------------------------------------- */

	template<class T, class NodeType> class	__tree_bidirectional_const_iter;

	template<class T, class NodeType>
	class __tree_bidirectional_iter//: public ft::iterator<ft::bidirectional_iterator_tag, T>
	{
	private:
		typedef NodeType					Node;
		template<class,class> friend class __tree_bidirectional_const_iter;
	public:
		typedef	T							value_type;
    	typedef ptrdiff_t  					difference_type;
		typedef T*							pointer;
		typedef T&							reference;
		typedef bidirectional_iterator_tag	iterator_category;

		__tree_bidirectional_iter();
		__tree_bidirectional_iter(Node *node);
		__tree_bidirectional_iter(const __tree_bidirectional_iter<T,NodeType>& x);
		~__tree_bidirectional_iter();
		
		__tree_bidirectional_iter& operator=(const __tree_bidirectional_iter& x);
		
		reference	operator*() const;
		pointer		operator->() const;

		__tree_bidirectional_iter& operator++();
		__tree_bidirectional_iter operator++(int);
		__tree_bidirectional_iter& operator--();
		__tree_bidirectional_iter operator--(int);

		template<class _T, class _NodeType>
		friend bool operator== (const __tree_bidirectional_iter<_T,_NodeType>& lhs, const __tree_bidirectional_iter<_T,_NodeType>& rhs);
		template<class _T, class _NodeType>
		friend bool operator== (const __tree_bidirectional_iter<_T,_NodeType>& lhs, const __tree_bidirectional_const_iter<_T,_NodeType>& rhs);
		template<class _T, class _NodeType>
		friend bool operator== (const __tree_bidirectional_const_iter<_T, _NodeType>& lhs, const __tree_bidirectional_iter<_T, _NodeType>& rhs);
	private:
		Node							*node;
		template <class, class, class> friend class __rbt;
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
			while (node->father && node->father->left != node)
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
			while (node->father && node->father->right != node)
				node = node->father;
			node = node->father;
		}
		return (*this);
	}

	template<class T, class NodeType>
	__tree_bidirectional_iter<T,NodeType> __tree_bidirectional_iter<T, NodeType>::operator--(int)
	{
		__tree_bidirectional_iter tmp(*this);
		--(*this);
		return (tmp);
	}

	template<class T, class NodeType>
	typename __tree_bidirectional_iter<T, NodeType>::reference
	__tree_bidirectional_iter<T, NodeType>::operator*() const
	{
		return (node->content);
	}

	template<class T, class NodeType>
	typename __tree_bidirectional_iter<T, NodeType>::pointer
	__tree_bidirectional_iter<T, NodeType>::operator->() const
	{
		return (&(node->content));
	}

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

		CONST ITERATOR FOR DIRECTIONAL ORDERED TREE
		
	-------------------------------------------------------------------------- */


	template<class T, class NodeType>
	class __tree_bidirectional_const_iter//: public iterator<bidirectional_iterator_tag, const T>
	{
	private:
		typedef NodeType								Node;
	public:
		typedef	T							value_type;
    	typedef ptrdiff_t  					difference_type;
		typedef const T*					pointer;
		typedef const T&					reference;
		typedef bidirectional_iterator_tag	iterator_category;

		__tree_bidirectional_const_iter();
		__tree_bidirectional_const_iter(Node *node);
		__tree_bidirectional_const_iter(const __tree_bidirectional_const_iter& x);
		__tree_bidirectional_const_iter(__tree_bidirectional_iter<T,NodeType> x);
		~__tree_bidirectional_const_iter();
		
		__tree_bidirectional_const_iter& operator=(const __tree_bidirectional_const_iter& x);
		
		reference	operator*() const;
		pointer		operator->() const;

		__tree_bidirectional_const_iter& operator++();
		__tree_bidirectional_const_iter operator++(int);
		__tree_bidirectional_const_iter& operator--();
		__tree_bidirectional_const_iter operator--(int);

		template<class _T, class _NodeType>
		friend bool operator== (const __tree_bidirectional_const_iter<_T,_NodeType>& lhs, const __tree_bidirectional_const_iter<_T,_NodeType>& rhs);
		template<class _T, class _NodeType>
		friend bool operator== (const __tree_bidirectional_const_iter<_T,_NodeType>& lhs, const __tree_bidirectional_iter<_T,_NodeType>& rhs);
		template<class _T, class _NodeType>
		friend bool operator== (const __tree_bidirectional_const_iter<_T, _NodeType>& lhs, const __tree_bidirectional_iter<_T, _NodeType>& rhs);
	private:
		Node							*node;
		template <class,class> friend class __tree_bidirectional_iter;
		template <class, class, class> friend class __rbt;
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
			while (node->father && node->father->left != node)
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
			while (node->father && node->father->right != node)
				node = node->father;
			node = node->father;
		}
		return (*this);
	}

	template<class T, class NodeType>
	__tree_bidirectional_const_iter<T,NodeType> __tree_bidirectional_const_iter<T, NodeType>::operator--(int)
	{
		__tree_bidirectional_const_iter tmp(*this);
		--(*this);
		return (tmp);
	}

	template<class T, class NodeType>
	typename __tree_bidirectional_const_iter<T, NodeType>::reference
	__tree_bidirectional_const_iter<T, NodeType>::operator*() const
	{
		return (node->content);
	}

	template<class T, class NodeType>
	typename __tree_bidirectional_const_iter<T, NodeType>::pointer
	__tree_bidirectional_const_iter<T, NodeType>::operator->() const
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
}

#endif