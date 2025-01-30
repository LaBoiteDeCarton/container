#ifndef DEQUE_HPP
#define DEQUE_HPP

#include "iterator.hpp" // ft::bidirectional_iterator_tag

#include <memory> // std::allocator

namespace ft
{
    template <class T>
    class __deque_iter;

    template <class T>
    class __deque_const_iter //: public ft::iterator<ft::bidirectional_iterator_tag, T>
    {
    public:
        typedef T value_type;
        typedef ptrdiff_t difference_type;
        typedef T *pointer;
        typedef T &reference;
        typedef bidirectional_iterator_tag iterator_category;
    };

    template <class T, class Alloc = std::allocator<T>>
    class deque
    {
        typedef T value_type;
        typedef Alloc allocator_type;
        typedef allocator_type::reference reference;
        typedef typename allocator_type::const_reference const_reference;
        typedef typename allocator_type::pointer pointer;
        typedef typename allocator_type::const_pointer const_pointer;
    };
}

#endif
