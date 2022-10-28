#ifndef FT_UTILITY_HPP
# define FT_UTILITY_HPP

namespace ft
{
	template <class T1, class T2>
	struct pair
	{
		typedef T1	first_type;
		typedef T2	second_type;

		/* Constructors */
		pair() {};
		template<class U, class V>
		pair (const pair<U,V>& pr) : first(pr.first), second(pr.second) {};
		pair (const first_type& a, const second_type& b): first(a), second(b) {};

		pair& operator= (const pair& pr)
		{
			this->first = pr.first;
			this->second = pr.second;
			return (*this);
		};
		
		first_type	first;
		second_type	second;
	};

	/* Relational operators */
	template <class T1, class T2>
	bool operator== (const pair<T1,T2> lhs, const pair<T1,T2> rhs)
	{
		return (lhs.first == rhs.first && lhs.second == rhs.second);
	}
	template <class T1, class T2>
	bool operator<= (const pair<T1,T2> lhs, const pair<T1,T2> rhs)
	{
		return (lhs.first <= rhs.first
			|| (lhs.first > rhs.first && lhs.second <= rhs.second));
	}
	template <class T1, class T2>
	bool operator< (const pair<T1,T2> lhs, const pair<T1,T2> rhs)
	{
		return (lhs.first < rhs.first
			|| (lhs.first >= rhs.first && lhs.second < rhs.second));
	}
	template <class T1, class T2>
	bool operator>= (const pair<T1,T2> lhs, const pair<T1,T2> rhs)
	{
		return (lhs.first >= rhs.first
			|| (lhs.first < rhs.first && lhs.second >= rhs.second));
	}
	template <class T1, class T2>
	bool operator> (const pair<T1,T2> lhs, const pair<T1,T2> rhs)
	{
		return (lhs.first > rhs.first
			|| (lhs.first <= rhs.first && lhs.second > rhs.second));
	}
	template <class T1, class T2>
	bool operator!= (const pair<T1,T2> lhs, const pair<T1,T2> rhs)
	{
		return (lhs.first != rhs.first && lhs.second != rhs.second);
	}

	template< class T1, class T2 >
	pair<T1, T2> make_pair( T1 fst, T2 snd )
	{
		return (pair<T1,T2>(fst, snd))
	}

	// C++11
	/* swap pair */
	// template <class T1, class T2>
	// void swap (pair<T1,T2>& x, pair<T1,T2>& y)
	// {
	// 	x.swap(y);
	// };

	// je garde __pair_geter en souvenir car c'est cool comme façon de faire
	// template <size_t I> class __pair_geter;

	// template <>
	// class __pair_geter<0>
	// {
	// 	template <class T1, class T2>
	// 	T1& get(pair<T1, T2> &pr) { return (pr.first); };

	// 	template <class T1, class T2>
	// 	const T1& get(const pair<T1, T2> &pr) { return (pr.first); };
	// };

	// template <>
	// class __pair_geter<1>
	// {
	// 	template <class T1, class T2>
	// 	T1& get(pair<T1, T2> &pr) { return (pr.second); };

	// 	template <class T1, class T2>
	// 	const T1& get(const pair<T1, T2> &pr) { return (pr.second); };
	// };

	// template <size_t I, class T1, class T2>
	// typename std::tuple_element< I, pair<T1,T2> >::type&
	// get (pair<T1,T2>& pr)
	// {
	// 	__pair_geter<I>.get(pr);
	// };

	// template <size_t I, class T1, class T2>
	// typename std::tuple_element< I, pair<T1,T2> >::type&&
	// get (pair<T1,T2>&& pr)
	// {
	// 	__pair_geter<I>.get(pr);
	// };

	// template <size_t I, class T1, class T2>
	// const typename std::tuple_element< I, pair<T1,T2> >::type&
	// get (const pair<T1,T2>& pr)
	// {
	// 	__pair_geter<I>.get(pr);
	// };
};

#endif