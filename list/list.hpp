/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssnowbir <ssnowbir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 10:16:36 by ssnowbir          #+#    #+#             */
/*   Updated: 2021/02/24 18:06:10 by ssnowbir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <cstddef>
#include <limits>
// class iterator_list;
// class reverse_iterator_list;
// #include "listIter.hpp"
namespace ft
{
  template < class T, class Alloc = std::allocator<T> >
  class list
  {
	  public:
	  	friend class iterator;
		friend class reverse_iterator;
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
		typedef struct  						s_list
		{
			T 									data;
			s_list 								*next;
			s_list 								*prev;
		}        								t_list;
		t_list                                  *_list;
		size_t									_list_size;
		t_list									*_list_pointer;
		class iterator_list
		{

			t_list					*list;
			public:
									iterator_list(){list = nullptr;}
									iterator_list(const iterator_list &x) { *this = x;}
			iterator_list 				&operator=(const t_list &x) {if(list != x){list = x;}return list; }
			virtual 				~iterator_list() {}

			//-----------------------Overlodes-------------------------//
			bool 					operator==(const iterator_list &x)
			{
				if(list == x.list)
					return true;
				else
					return false;
			}
			bool 					operator!=(const iterator_list &x)
			{
				if(list != x.list)
					return true;
				else
					return false;			
			}
			T 						&operator*()
			{
				return list->data;
			}
			const T 				&operator*() const
			{
				return list->data;
			}
			T*						operator->()
			{
				return &list->data;
			}
			const T*				operator->() const
			{
				return &list->data;
			}
			iterator_list				&operator++()
			{
				list = list->next;
				return list;
			}
			iterator_list				&operator--()
			{
				list = list->prev;
				return list;
			}
		};
		class reverse_iterator_list
		{

			t_list					*list;
			public:
					// friend class list;
					// typedef list<T>::t_list t_list;
									reverse_iterator_list(){list = nullptr;}
									reverse_iterator_list(const reverse_iterator_list &x) { *this = x;}
			reverse_iterator_list 		&operator=(const t_list &x) {if(list != x){list = x;}return list; }
			virtual 				~reverse_iterator_list() {}

			//-----------------------Overlodes-------------------------//
			bool 					operator==(const reverse_iterator_list &x)
			{
				if(list == x.list)
					return true;
				else
					return false;
			}
			bool 					operator!=(const reverse_iterator_list &x)
			{
				if(list != x.list)
					return true;
				else
					return false;			
			}
			T 						&operator*()
			{
				return list->data;
			}
			const T 				&operator*() const
			{
				return list->data;
			}
			T*						operator->()
			{
				return &list->data;
			}
			const T*				operator->() const
			{
				return &list->data;
			}
			reverse_iterator_list		&operator++()
			{
				list = list->prev;
				return list;
			}
			reverse_iterator_list		&operator--()
			{
				list = list->next;
				return list;
			}
		};
		public:
		typedef iterator_list			iterator;
		typedef iterator_list			const_iterator;
		typedef reverse_iterator_list 	reverse_iterator;
		typedef reverse_iterator_list	const_reverse_iterator;
		// ******************Member functions*********************//

		t_list	*ft_lstnew(value_type val)
		{
			t_list *node = new t_list;
			node->data = val;
			node->next = nullptr;
			node->prev = nullptr;
			return (node);
		}
		void	ft_lstadd_back(t_list **lst, t_list *new_list)
		{
			if (!lst || !new_list)
				return ;
			if (!*lst)
				*lst = new_list;
			else
			{
				while ((*lst)->next)
					lst = &(*lst)->next;
				(*lst)->next = new_list;
			}
		}
		explicit   								list (const allocator_type& alloc = allocator_type())
		{
			_list = ft_lstnew(0);
			_list_size = 0;
			_list_pointer = _list;
		}
		explicit   								list (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
		{
			std::cout << "I'M HERE2\n";
			_list = ft_lstnew(0);
			_list_size = 0;
			_list_pointer = _list;
			for(size_type i = 0; i < n; i++)
			{
				t_list *new_list = ft_lstnew(val);
				ft_lstadd_back(&_list_pointer, new_list);
				_list = _list->next;
			}
		}
		template <class InputIterator>
												list (InputIterator first, InputIterator last,
														const allocator_type& alloc = allocator_type())
		{
			std::cout << "I'M HERE\n";
			_list = ft_lstnew(0);
			_list_size = 0;
			_list_pointer = _list;
			for(InputIterator i = first; i != last; i++)
			{
				t_list *new_list = ft_lstnew(i);
				ft_lstadd_back(&_list_pointer, new_list);
				std::cout << i<< ", data: "<< new_list->data<< "\n";
				_list = _list->next;
			}
		}
												list (const list& x){*this = x;};
												~list(){};
		list&									operator=(const list& x);
		// ******************Iterators*********************//
		// iterator								begin();
		// const_iterator							begin() const;
		// iterator								end();
		// const_iterator							end() const;
		// reverse_iterator						rbegin();
		// const_reverse_iterator					rbegin() const;
		// reverse_iterator						rend();
		// const_reverse_iterator					rend() const;
		// ******************Capacity*********************//
		// bool									empty() const;
		// size_type								size() const;
		// size_type 								max_size() const;
		// ******************Element access*********************//	
		// reference 								front(); 
		// const_reference							front() const;
		// reference								back();
		// const_reference							back() const;
		// ******************Element access*********************//
		// template <class InputIterator>
		// void 									assign (InputIterator first, InputIterator last);
		// void									assign (size_type n, const value_type& val);
		// void									push_front (const value_type& val);
		// void									pop_front();
		// void									push_back (const value_type& val);
		// void									pop_back();
		// iterator								insert (iterator position, const value_type& val);
		// void									insert (iterator position, size_type n, const value_type& val);	
		// template <class InputIterator>
		// void									insert (iterator position, InputIterator first, InputIterator last);
		// iterator					48doremi
					// erase (iterator position);
		// iterator								erase (iterator first, iterator last);
		// void									swap (list& x);
		// void									resize (size_type n, value_type val = value_type());
		// void									clear();
	// ******************Operations*********************//
		// void									splice (iterator position, list& x);	
		// void									splice (iterator position, list& x, iterator i);
		// void									splice (iterator position, list& x, iterator first, iterator last);	
		// void									remove (const value_type& val);
		// template <class Predicate>
		// void									remove_if (Predicate pred);
		// void									unique();
		// template <class BinaryPredicate>
		// void									unique (BinaryPredicate binary_pred);
		// void									merge (list& x);
		// template <class Compare>
		// void									merge (list& x, Compare comp);
		// void									sort();
		// template <class Compare>
		// void									sort (Compare comp);
		// void									reverse();
		// ******************Observers*********************//
		// allocator_type							get_allocator() const;
		// ******************Overlodes*********************//
		// template <class T, class Alloc>
		// bool									operator== (const list<T,Alloc>& lhs,
		// 													const list<T,Alloc>& rhs);
		// template <class T, class Alloc>
		// bool									operator!= (const list<T,Alloc>& lhs,
		// 													const list<T,Alloc>& rhs);
		// template <class T, class Alloc>
		// bool									operator<  (const list<T,Alloc>& lhs,
		// 													const list<T,Alloc>& rhs);
		// template <class T, class Alloc>
		// bool									operator<= (const list<T,Alloc>& lhs,
		// 													const list<T,Alloc>& rhs);
		// template <class T, class Alloc>
		// bool									operator>  (const list<T,Alloc>& lhs,
		// 													const list<T,Alloc>& rhs);
		// template <class T, class Alloc>
		// bool									operator>= (const list<T,Alloc>& lhs,
		// 													const list<T,Alloc>& rhs);
		// template <class T, class Alloc>
		// void									swap (list<T,Alloc>& x, list<T,Alloc>& y);
  };
};