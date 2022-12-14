#ifndef FT_STACK_HPP
# define FT_STACK_HPP

#include "vector.hpp"

namespace ft
{
	template <class T, class Container = vector<T> >
	class stack
	{
		public:
			typedef T										value_type;
			typedef Container								container_type;
			typedef typename container_type::size_type		size_type;

			/* Constructors */
			explicit stack (const container_type& ctnr = container_type());

			/* Member functions */
			bool empty() const;
			size_type size() const;
			value_type& top();
			const value_type& top() const;
			void push (const value_type& val);
			void pop();

		private:
			container_type	_C;
		public:
		/*
			Comparaison operator, using friend to acces the private container outside the class
			Operator == and operator < are sufficent to check all possible comparaison
		*/
		template <class _T, class _Container>
		friend bool operator== (const stack<_T,_Container>& lhs, const stack<_T,_Container>& rhs);
		template <class _T, class _Container>
		friend bool operator<  (const stack<_T,_Container>& lhs, const stack<_T,_Container>& rhs);

	};

	/* --------------------------------------------------------------------------

		CONSTRUCTOR
	
	-------------------------------------------------------------------------- */

	template<class T, class Container>
	stack<T,Container>::stack (const container_type& ctnr)
	:	_C(ctnr)
	{ }


	/* --------------------------------------------------------------------------

		MEMBER FUNCTIONS

	-------------------------------------------------------------------------- */

	template<class T, class Container>
	bool stack<T,Container>::empty() const
	{
		return (_C.empty());
	}

	template<class T, class Container>
	typename stack<T,Container>::size_type
	stack<T,Container>::size() const
	{
		return (_C.size());
	}

	template<class T, class Container>
	typename stack<T,Container>::value_type&
	stack<T,Container>::top()
	{
		return (_C.back());
	}

	template<class T, class Container>
	const typename stack<T,Container>::value_type&
	stack<T,Container>::top() const
	{
		return (_C.back());
	}

	template<class T, class Container>
	void stack<T,Container>::push (const value_type& val)
	{
		_C.push_back(val);
	}

	template<class T, class Container>
	void stack<T,Container>::pop()
	{
		_C.pop_back();
	}


	/* --------------------------------------------------------------------------

		NON MEMBER FUNCTIONS OVERLOAD

	-------------------------------------------------------------------------- */

	template <class T, class Container>
	bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (lhs._C == rhs._C);
	}
	
	template <class T, class Container>
	bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (!(lhs == rhs));
	}	
	
	template <class T, class Container>
	bool operator<  (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (lhs._C < rhs._C);
	}	
	
	template <class T, class Container>
	bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (!(rhs < lhs));
	}	
	
	template <class T, class Container>
	bool operator>  (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (rhs < lhs);
	}	
	
	template <class T, class Container>
	bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (!(lhs < rhs));
	}

}

#endif