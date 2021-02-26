#ifndef LIST_HPP
#define LIST_HPP

#include <iostream>
#include <string>
#include <cstddef>
#include <limits>
#include "iterator_list.hpp"

namespace ft
{
  template < class T, class Alloc = std::allocator<T> >
  class List
  {
	  public:
	  	template<typename> friend class iterator;
		template<typename> friend class reverse_iterator;
		public:
		typedef  T  							value_type;
		typedef Alloc 							allocator_type;
		typedef size_t 							size_type;
		typedef value_type&						reference;
    	typedef const value_type&				const_reference;
    	typedef value_type*						pointer;
    	typedef const value_type*				const_pointer;
		typedef ptrdiff_t 						difference_type;
		
	private:
		
		struct s_list
		{
			T 									data;
			s_list 								*next;
			s_list 								*prev;
		};
		allocator_type							_alloc;
		struct s_list                           *_list;
		struct s_list                           *_lst_ptr;
		size_t									_list_size;
		// struct s_list									*ft_lstnew(value_type val);
		// void									ft_lstadd_back(struct s_list **lst, struct s_list *new_list);
	public:
		typedef ft::iterator<T>					iterator;
		typedef const ft::iterator<T>			const_iterator;
		typedef ft::reverse_iterator<T> 		reverse_iterator;
		typedef const ft::reverse_iterator<T>	const_reverse_iterator;

		//--------------------constructors------------------------//
		explicit   								List (const allocator_type& alloc = allocator_type());
		explicit   								List (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type());
		template <class InputIterator>			List (InputIterator first, InputIterator last,const allocator_type& alloc = allocator_type());
												List (const List& x);
												~List(){};
		List&									operator=(const List& x);



		iterator								begin();
		void 									push_back(const T &value);
		
		
  	};
	// template < class T, class Alloc>
	// struct s_list	*List::ft_lstnew(value_type val)
	// {
	// 	struct s_list *node = new struct s_list;
	// 	node->data = val;
	// 	node->next = nullptr;
	// 	node->prev = nullptr;
	// 	_lst_ptr =  nullptr;
	// 	_list_size = 0;
	// 	return (node);
	// }
	template < class T, class Alloc = std::allocator<T> >
	void ft::List<T>::push_back(const T &val)
	{
		struct s_list *tmp;

		_lst_ptr = _list;
		while (_list->next != 0)
		_list = _list->next;
		tmp = _list->prev;
		_list->prev = new struct s_list;
		_list->prev->next = _list;
		_list->prev->prev = tmp;
		_list->prev->data = val;
		tmp->next = _list->prev;
		_list = _lst_ptr;
		_list_size++;
	}
	template < class T, class Alloc = std::allocator<T> >
	explicit   									List<T>::List (const allocator_type& alloc = allocator_type())
	{
		_alloc = alloc;
		_list = ft_lstnew(0);
		_list_size = 0;
		_list_pointer = _list;
	}
	template < class T, class Alloc = std::allocator<T> >
	explicit   								List<T>::List (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
	{
		_alloc = alloc;
		_list_pointer = _list;
		for(_list_size = 0; _list_size < n; _list_size++)
		{
			push_back(val);
			// _list = _list->next;
		}
		_list = _list_pointer;
		for(_list_size = 0; _list_size < n; _list_size++)
		{
			std::cout <<_list_size<<_list->data<<"\n";

			_list = _list->next;
		}

	}
	template < class T, class Alloc>
	template < class T, class Alloc>
	template < class T, class Alloc>
	template < class T, class Alloc>
	template < class T, class Alloc>
	template < class T, class Alloc>
	template < class T, class Alloc>
	template < class T, class Alloc>
	template < class T, class Alloc>
	iterator									begin()
	{
		
		_list_pointer = _list;
		return(iterator(_list_pointer));
	}
};

#endif