#ifndef FT_TYPE_TRAITS_HPP
# define FT_TYPE_TRAITS_HPP

#include <type_traits>

namespace ft
{
	typedef std::integral_constant<bool,true> true_type;
	typedef std::integral_constant<bool,false> false_type;
	
	template <class T> struct is_integral : public false_type {};
	template <> struct is_integral<bool> : public true_type {};
	template <> struct is_integral<char> : public true_type {};
	template <> struct is_integral<char16_t> : public true_type {};
	template <> struct is_integral<char32_t> : public true_type {};
	template <> struct is_integral<wchar_t> : public true_type {};
	template <> struct is_integral<signed char> : public true_type {};
	template <> struct is_integral<short int> : public true_type {};
	template <> struct is_integral<int> : public true_type {};
	template <> struct is_integral<long int> : public true_type {};
	template <> struct is_integral<long long int> : public true_type {};
	template <> struct is_integral<unsigned char> : public true_type {};
	template <> struct is_integral<unsigned short int> : public true_type {};
	template <> struct is_integral<unsigned int> : public true_type {};
	template <> struct is_integral<unsigned long int> : public true_type {};
	template <> struct is_integral<unsigned long long int> : public true_type {};

	template <bool Cond, class T = void> struct enable_if;
	template <class T>
	struct enable_if<true, T> { typedef T type };

	//exemple de enable_if
	//imaginons qu'on veut une fonction generic qui calcul le modulo 3 d'un arg de type T mais seulement si c'est un integral type
	// template <class T>    : le type T inconnu donc c'est un template
	// typename enable_if<is_integral<T>::value, T>::type   : si le type T est un integral, is_integral value sera true, false sinon. Si false le enable_if ne compilera pas car pas de class existante avec false. Si true alors la classe existe alors on utilise ::type de cette class qui aura le meme type que T (deuxieme argument de enable_if, sachant qu'on peut mettre ce qu'on veut comme type, bool par exemple) comme étant le retour de la fonction
	// modulo_trois(T arg) { return (arg % 3) } 

	
}

#endif