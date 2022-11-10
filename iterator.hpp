#ifndef FT_ITERATOR_HPP
# define FT_ITERATOR_HPP

#include <cstddef> //ptrdiff_t
#include "type_traits.hpp"
//#include <iterator>

namespace ft
{
	/* Defining iterator name tag */
	struct input_iterator_tag  {};
	struct output_iterator_tag {};
	struct forward_iterator_tag       : public input_iterator_tag         {};
	struct bidirectional_iterator_tag : public forward_iterator_tag       {};
	struct random_access_iterator_tag : public bidirectional_iterator_tag {};

	/* Defining iterators */
	template <class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>
  	struct iterator {
	public:
   		typedef T         value_type;
    	typedef Distance  difference_type;
    	typedef Pointer   pointer;
    	typedef Reference reference;
    	typedef Category  iterator_category;
	};

	/* Defining iterator_traits */
	template <class Iterator>
	class iterator_traits
	{
	public:
		typedef typename Iterator::difference_type difference_type;
		typedef typename Iterator::value_type value_type;
    	typedef typename Iterator::pointer pointer;
    	typedef typename Iterator::reference reference;
    	typedef typename Iterator::iterator_category iterator_category;
	};

	template <class T>
	class iterator_traits<T*>
	{
	public:
		typedef ptrdiff_t difference_type;
		typedef T value_type;
    	typedef T* pointer;
    	typedef T& reference;
    	typedef random_access_iterator_tag iterator_category;
	};

	template <class T>
	class iterator_traits<const T*>
	{
	public:
		typedef ptrdiff_t difference_type;
		typedef T value_type;
    	typedef const T* pointer;
    	typedef const T& reference;
    	typedef random_access_iterator_tag iterator_category;
	};

	/* Defining revers_iterator name tag */
	template <class Iterator>
	class reverse_iterator
	{
	public:
		typedef Iterator												iterator_type;
		typedef typename iterator_traits<Iterator>::iterator_category	iterator_category;
		typedef typename iterator_traits<Iterator>::value_type			value_type;
		typedef typename iterator_traits<Iterator>::difference_type		difference_type;
		typedef typename iterator_traits<Iterator>::pointer				pointer;
		typedef typename iterator_traits<Iterator>::reference			reference;

		reverse_iterator();
		explicit reverse_iterator (iterator_type it);
		template <class Iter>
		reverse_iterator (const reverse_iterator<Iter>& rev_it);
		
		iterator_type base() const;

		reference operator*() const;
		reverse_iterator operator+ (difference_type n) const;
		reverse_iterator& operator++();
		reverse_iterator  operator++(int);
		reverse_iterator& operator+= (difference_type n);
		reverse_iterator operator- (difference_type n) const;
		reverse_iterator& operator--();
		reverse_iterator  operator--(int);
		reverse_iterator& operator-= (difference_type n);
		pointer operator->() const;
		reference operator[] (difference_type n) const;

	private:
		iterator_type	_base;
	};

	template<class Iterator>
	reverse_iterator<Iterator>::reverse_iterator()
	:	_base()
	{ }
	
	template<class Iterator>
	reverse_iterator<Iterator>::reverse_iterator (iterator_type it)
	:	_base(it)
	{ }
	
	template<class Iterator>
	template<class Iter>
	reverse_iterator<Iterator>::reverse_iterator (const reverse_iterator<Iter>& rev_it)
	:	_base(rev_it.base())
	{ }
	
	template<class Iterator>
	typename reverse_iterator<Iterator>::iterator_type
	reverse_iterator<Iterator>::base() const
	{
		return (this->_base);
	}


	template<class Iterator>
	typename reverse_iterator<Iterator>::reference
	reverse_iterator<Iterator>::operator*() const
	{
		iterator_type temp(this->_base);
		--temp;
		return (*temp);
	}
	
	template<class Iterator>
	reverse_iterator<Iterator>
	reverse_iterator<Iterator>::operator+ (difference_type n) const
	{
		return (reverse_iterator<Iterator>(this->_base - n));
	}
	
	template<class Iterator>
	reverse_iterator<Iterator>&
	reverse_iterator<Iterator>::operator++()
	{
		this->_base--;
		return (*this);
	}
	
	template<class Iterator>
	reverse_iterator<Iterator> 
	reverse_iterator<Iterator>::operator++(int)
	{
		reverse_iterator<Iterator> temp(*this);
		++*this;
		return (temp);
	}
	
	template<class Iterator>
	reverse_iterator<Iterator>&
	reverse_iterator<Iterator>::operator+= (difference_type n)
	{
		this->_base -= n;
		return (*this);
	}
	
	template<class Iterator>
	reverse_iterator<Iterator>
	reverse_iterator<Iterator>::operator- (difference_type n) const
	{
		return (reverse_iterator<Iterator>(this->_base + n));
	}
	
	template<class Iterator>
	reverse_iterator<Iterator>&
	reverse_iterator<Iterator>::operator--()
	{
		this->_base++;
		return (*this);
	}
	
	template<class Iterator>
	reverse_iterator<Iterator> 
	reverse_iterator<Iterator>::operator--(int)
	{
		reverse_iterator<Iterator>	temp(*this);

		--*this;
		return (temp);
	}
	
	template<class Iterator>
	reverse_iterator<Iterator>&
	reverse_iterator<Iterator>::operator-= (difference_type n)
	{
		this->_base += n;
		return (*this);
	}
	
	template<class Iterator>
	typename reverse_iterator<Iterator>::pointer
	reverse_iterator<Iterator>::operator->() const
	{
		return (&(**this));
	}
	
	template<class Iterator>
	typename reverse_iterator<Iterator>::reference
	reverse_iterator<Iterator>::operator[] (difference_type n) const
	{
		return (*(*this + n));
	}

	/*
		Conflicting type, cplusplus.com mention only one Iterator in te template meaning the lhs and rhs got the same iteartor type.
		This is bad because we cannot compare const_reverse_iterator with reverse_iterator (and this is usefull for testing programm)

		In cplusplus.com the typename got two Iterators class.
		Not knowing which one is the good one (both saying is c++98), I choose to use the second one, because who can do more, can do less

	template <class Iterator>
	bool	operator== (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return (lhs.base() == rhs.base());
	}	

	template <class Iterator>
	bool	operator!= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return (lhs.base() != rhs.base());
	}

	template <class Iterator>
	bool	operator<  (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return (lhs.base() > rhs.base());
	}

	template <class Iterator>
	bool	operator<= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return (lhs.base() >= rhs.base());
	}

	template <class Iterator>
	bool	operator>  (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return (lhs.base() < rhs.base());
	}

	template <class Iterator>
	bool	operator>= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return (lhs.base() <= rhs.base());
	}
	
	template <class Iterator>
	reverse_iterator<Iterator> operator+ (typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& rev_it)
	{
		return (rev_it + n);
		return (reverse_iterator<Iterator>(rev_it.base() - n));
	}

	template <class Iterator>
	typename reverse_iterator<Iterator>::difference_type operator- (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return (rhs.base() - lhs.base());
	}	
	*/

	template <class Iterator1, class Iterator2>
	bool	operator== (const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
	{
		return (lhs.base() == rhs.base());
	}	

	template <class Iterator1, class Iterator2>
	bool	operator!= (const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
	{
		return (lhs.base() != rhs.base());
	}

	template <class Iterator1, class Iterator2>
	bool	operator<  (const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
	{
		return (lhs.base() > rhs.base());
	}

	template <class Iterator1, class Iterator2>
	bool	operator<= (const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
	{
		return (lhs.base() >= rhs.base());
	}

	template <class Iterator1, class Iterator2>
	bool	operator>  (const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
	{
		return (lhs.base() < rhs.base());
	}

	template <class Iterator1, class Iterator2>
	bool	operator>= (const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
	{
		return (lhs.base() <= rhs.base());
	}

	template <class Iterator>
	reverse_iterator<Iterator> operator+ (typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& rev_it)
	{
		return (rev_it + n);
		return (reverse_iterator<Iterator>(rev_it.base() - n));
	}

	template <class Iterator1, class Iterator2>
	typename reverse_iterator<Iterator1>::difference_type operator- (const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
	{
		return (rhs.base() - lhs.base());
	}	
	
	/*
		function distance for an input iterator type (Complexity O(n))
	 */
	template<class Iterator>
	typename iterator_traits<Iterator>::difference_type
	__distance (Iterator first, Iterator last, input_iterator_tag)
	{
		typename iterator_traits<Iterator>::difference_type dist(0);

		for (; first != last; first++, dist++)
			;
		return (dist);
	}

	/*
		function distance for an random access iterator type (Complexity O(1))
	 */
	template<class Iterator>
	typename iterator_traits<Iterator>::difference_type
	__distance (Iterator first, Iterator last, random_access_iterator_tag)
	{
		return (static_cast<typename iterator_traits<Iterator>::difference_type>(last - first));
	}

	/* function distance pour calculer les nombre d'element compris entre first and last
		Input iterator est invalidé apres l'utilisation de distance
	 */
	template<class Iterator>
	typename iterator_traits<Iterator>::difference_type
	distance (Iterator first, Iterator last)
	{
		return (__distance(first, last, typename iterator_traits<Iterator>::iterator_category()));
	}

	// template <class __it_category> struct __is_input_iterator_tag : public false_type {};
	// template<> struct __is_input_iterator_tag<input_iterator_tag> : public true_type {};


	// template <class __it_category> struct __is_forward_iterator_tag : public false_type {};
	// template<> struct __is_forward_iterator_tag<forward_iterator_tag> : public true_type {};
	// template<> struct __is_forward_iterator_tag<bidirectional_iterator_tag> : public true_type {};
	// template<> struct __is_forward_iterator_tag<random_access_iterator_tag> : public true_type {};

	// template <class Iterator>
	// struct __is_input_iterator : public false_type {};
	
	// template <class Iterator
	// 		, enable_if<__is_input_iterator_tag<typename iterator_traits<Iterator>::iterator_category>::type>
	// 					,Iterator>
	// struct __is_input_iterator : public true_type {};
}

#endif
