/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssnowbir <ssnowbir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 10:16:36 by ssnowbir          #+#    #+#             */
/*   Updated: 2021/02/20 11:25:53 by ssnowbir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
namespace ft
{
  template < class T, class Alloc = std::allocator<T> >
  class list
  {
		private:
		typedef struct  						s_list
		{
			T 									*data;
			s_list 								*next;
			s_list 								*last;
			// s_list *head;
		}        								t_list;
		public:
		typedef  T  							value_type;
		typedef Alloc 							allocator_type;
		typedef size_t 							size_type;
		typedef allocator_type::reference 		reference;
		typedef allocator_type::const_reference const_reference;
		typedef allocator_type::pointer 		pointer;
		typedef allocator_type::const_pointer 	const_pointer;
		typedef ptrdiff_t 						difference_type;
		t_list                                  list;
		t_list									*list_pointer;
		// iterator
		// const_iterator
		// reverse_iterator
		// const_reverse_iterator
		public:
		// ******************Member functions*********************//
		explicit   								list (const allocator_type& alloc = allocator_type());
		explicit   								list (size_type n, const value_type& val = value_type(),
														const allocator_type& alloc = allocator_type());
		template <class InputIterator>
												list (InputIterator first, InputIterator last,
														const allocator_type& alloc = allocator_type());
												list (const list& x);
												~list();
		list&									operator= (const list& x);
		// ******************Iterators*********************//
		iterator								begin();
		const_iterator							begin() const;
		iterator								end();
		const_iterator							end() const;
		reverse_iterator						rbegin();
		const_reverse_iterator					rbegin() const;
		reverse_iterator						rend();
		const_reverse_iterator					rend() const;
		// ******************Capacity*********************//
		bool									empty() const;
		size_type								size() const;
		size_type 								max_size() const;
		// ******************Element access*********************//	
		reference 								front(); 
		const_reference							front() const;
		reference								back();
		const_reference							back() const;
		// ******************Element access*********************//
		template <class InputIterator>
		void 									assign (InputIterator first, InputIterator last);
		void									assign (size_type n, const value_type& val);
		void									push_front (const value_type& val);
		void									pop_front();
		void									push_back (const value_type& val);
		void									pop_back();
		iterator								insert (iterator position, const value_type& val);
		void									insert (iterator position, size_type n, const value_type& val);	
		template <class InputIterator>
		void									insert (iterator position, InputIterator first, InputIterator last);
		iterator								erase (iterator position);
		iterator								erase (iterator first, iterator last);
		void									swap (list& x);
		void									resize (size_type n, value_type val = value_type());
		void									clear();
	// ******************Operations*********************//
		void									splice (iterator position, list& x);	
		void									splice (iterator position, list& x, iterator i);
		void									splice (iterator position, list& x, iterator first, iterator last);	
		void									remove (const value_type& val);
		template <class Predicate>
		void									remove_if (Predicate pred);
		void									unique();
		template <class BinaryPredicate>
		void									unique (BinaryPredicate binary_pred);
		void									merge (list& x);
		template <class Compare>
		void									merge (list& x, Compare comp);
		void									sort();
		template <class Compare>
		void									sort (Compare comp);
		void									reverse();
		// ******************Observers*********************//
		allocator_type							get_allocator() const;
		// ******************Overlodes*********************//
		template <class T, class Alloc>
		bool									operator== (const list<T,Alloc>& lhs,
															const list<T,Alloc>& rhs);
		template <class T, class Alloc>
		bool									operator!= (const list<T,Alloc>& lhs,
															const list<T,Alloc>& rhs);
		template <class T, class Alloc>
		bool									operator<  (const list<T,Alloc>& lhs,
															const list<T,Alloc>& rhs);
		template <class T, class Alloc>
		bool									operator<= (const list<T,Alloc>& lhs,
															const list<T,Alloc>& rhs);
		template <class T, class Alloc>
		bool									operator>  (const list<T,Alloc>& lhs,
															const list<T,Alloc>& rhs);
		template <class T, class Alloc>
		bool									operator>= (const list<T,Alloc>& lhs,
															const list<T,Alloc>& rhs);
		template <class T, class Alloc>
		void									swap (list<T,Alloc>& x, list<T,Alloc>& y);
  };
  
};