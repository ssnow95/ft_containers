/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssnowbir <ssnowbir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 11:57:31 by ssnowbir          #+#    #+#             */
/*   Updated: 2021/04/05 15:31:47 by ssnowbir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef LIST_HPP
#define LIST_HPP

#include <iostream>
#include <memory>
#include <string>
#include <cstddef>
#include <limits>
#include <typeinfo>
#include <iterator>
#include "list_iterator.hpp"

namespace ft
{
  template < class T, class Alloc = std::allocator<T> >
  class list
  {
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
		allocator_type							_alloc;
		struct s_list<T>                        *_tail_lst;
		size_t									_list_size;

	public:
		typedef ft::iterator<T>					iterator;
		typedef ft::const_iterator<T>			const_iterator;
		typedef ft::reverse_iterator<T> 		reverse_iterator;
		typedef ft::const_reverse_iterator<T>	const_reverse_iterator;

		//--------------------constructors------------------------//
		explicit   								list (const allocator_type& alloc = allocator_type())
		{
			_alloc = alloc;
			_tail_lst = new struct s_list<T>;
			_tail_lst->prev = _tail_lst;
			_tail_lst->next = _tail_lst;
			_tail_lst->data = 0;
			_list_size = 0;

		}
		explicit   								list (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
		{
			_alloc = alloc;
			_tail_lst = new struct s_list<T>;
			_tail_lst->prev = _tail_lst;
			_tail_lst->next = _tail_lst;
			_tail_lst->data = 0;
			_list_size = 0;
			for(size_type i = 0; i < n; i++)
				push_back(val);
		}
		template <class InputIterator>			
												list (InputIterator first, InputIterator last,const allocator_type& alloc = allocator_type(),
														typename std::enable_if<!std::numeric_limits<InputIterator>::is_specialized>::type* = 0)
		{
			_alloc = alloc;
			_tail_lst = new struct s_list<T>;
			_tail_lst->prev = _tail_lst;
			_tail_lst->next = _tail_lst;
			_tail_lst->data = 0;
			_list_size = 0;
			for(; first != last; first++)
			{
				push_back(first.getList()->data);
			}
		}
												list (const list& x)
		{
			_tail_lst = new struct s_list<T>;
			_tail_lst->prev = _tail_lst;
			_tail_lst->next = _tail_lst;
			_tail_lst->data = 0;
			_list_size = 0;
			*this = x;
			return ;
		}
												~list()
		{

			clear();
			delete _tail_lst;
		}
		list&									operator=(const list& x)
		{
			clear();
			struct s_list<T>	*list_tmp = x._tail_lst->next;
			if(x._list_size > 0)
			{
				while(list_tmp != x._tail_lst)
				{
					push_back(list_tmp->data);
					list_tmp = list_tmp->next;
				}
			}
			return *this;
		}
		// ******************Iterators*********************//
		iterator								begin()
		{
			return (iterator(_tail_lst->next));
		}
		const_iterator							begin() const
		{
			return (const_iterator(_tail_lst->next));
		}
		iterator								end()
		{
			return (iterator(_tail_lst));
		}
		const_iterator							end() const
		{
			return (const_iterator(_tail_lst));
		}
		reverse_iterator						rbegin()
		{
			return (reverse_iterator(_tail_lst->prev));
		}
		const_reverse_iterator					rbegin() const
		{
			return (const_reverse_iterator(_tail_lst->prev));
		}
		reverse_iterator						rend()
		{
			return(reverse_iterator(_tail_lst));
		}
		const_reverse_iterator					rend() const
		{
			return(const_reverse_iterator(_tail_lst));
		}
		// ******************Capacity*********************//
		bool									empty() const
		{
			if(_list_size == 0)
				return (true);
			else
				return (false);
		}
		size_type								size() const
		{
			return(_list_size);
		}
		size_type 								max_size() const
		{
			return(std::numeric_limits<size_t>::max()/ sizeof(struct  s_list<T>));
		}
		// ******************Element access*********************//	
		reference 								front() //Возвращает ссылку на первый элемент(значение) в контейнере списка 
		{
			return (_tail_lst->next->data);
		}
		const_reference							front() const
		{
			return (_tail_lst->next->data);
		}
		reference								back()
		{
			return (_tail_lst->prev->data);
		}
		const_reference							back() const
		{
			return (_tail_lst->prev->data);
		}
// ******************Element access*********************//

		template <class InputIterator>
		void 									assign (InputIterator first, InputIterator last, typename std::enable_if<!std::numeric_limits<InputIterator>::is_specialized>::type* = 0)
		{
			clear();
			insert(begin(),first, last);
		}
		void									assign (size_type n, const value_type& val)
		{
			clear();
			for(size_type i = 0; i < n; i++)
				push_back(val);
		}
		void 									push_back(const T &val)
		{
			struct s_list<T>* tmp = new struct s_list<T>;          
			tmp->data = val;
			if(_list_size == 0)
			{
				_tail_lst->next  = tmp;
				_tail_lst->prev = tmp;
				tmp->next = _tail_lst;
				tmp->prev = _tail_lst;
				_list_size++;
				_tail_lst->data = _list_size;
			}
			else
			{
				tmp->prev = _tail_lst->prev;
				tmp->next = _tail_lst;
				_tail_lst->prev->next = tmp;
				_tail_lst->prev = tmp;
				_list_size++;
				_tail_lst->data = _list_size;
			}
		}
		void									pop_back()
		{
				struct s_list<T>* tmp = _tail_lst->prev;
				if(_list_size == 1)
				{
					_tail_lst->prev = _tail_lst;
					_tail_lst->next = _tail_lst;
					_list_size--;
					_tail_lst->data = _list_size;
					delete tmp;
				}
				else
				{
					_tail_lst->prev = _tail_lst->prev->prev; 
					_tail_lst->prev->next =_tail_lst;
					delete tmp;
					_list_size--;
					_tail_lst->data = _list_size;
				}
		}
		void									push_front (const value_type& val)
		{

			struct s_list<T>* tmp = new struct s_list<T>;          
			tmp->data = val;
			if(_list_size == 0)
			{
				_tail_lst->next  = tmp;
				_tail_lst->prev = tmp;
				tmp->next = _tail_lst;
				tmp->prev = _tail_lst;
				_list_size++;
				_tail_lst->data = _list_size;
			}
			else
			{
				tmp->prev = _tail_lst;
				tmp->next =_tail_lst->next;
				_tail_lst->next->prev = tmp;
				_tail_lst->next = tmp;
				_list_size++;
				_tail_lst->data = _list_size;
			}
		}
		void									pop_front ()
		{
			if(_list_size == 1)
			{
				struct s_list<T>* tmp =_tail_lst->next;
				_tail_lst->next = _tail_lst;
				_tail_lst->prev = _tail_lst;
				_list_size--;
				_tail_lst->data = _list_size;
				delete tmp;
			}
			else
			{
				struct s_list<T>* tmp =_tail_lst->next;
				_tail_lst->next = _tail_lst->next->next;
				_tail_lst->next->next->prev = _tail_lst;
				_list_size--;
				_tail_lst->data = _list_size;
				delete tmp;
			}
		}
		iterator								insert (iterator position, const value_type& val)
		{
			struct s_list<T>*newNoda = new struct s_list<T>;
			struct s_list<T>*tmp = position.getList();
			newNoda->data = val;
			newNoda->next = tmp;
			newNoda->prev = tmp->prev;
			tmp->prev->next = newNoda;
			tmp->prev = newNoda;
			_list_size++;
			_tail_lst->data = _list_size;
			return(position);
		}
		void									insert (iterator position, size_type n, const value_type& val)
		{
			for(size_type j = 0; j < n; j++)
			{
				insert(position, val);
			}
		}
		template <class InputIterator>
		void									insert (iterator position, InputIterator first, InputIterator last,
															typename std::enable_if<!std::numeric_limits<InputIterator>::is_specialized>::type* = 0)
		{	
			for(InputIterator it = first; it != last; it++)
				insert(position, *it);
		}
		iterator					erase (iterator position)
		{
			struct s_list<T>*tmp = position.getList();
			position++;
			tmp->prev->next = tmp->next;
			tmp->next->prev = tmp->prev;
			delete tmp;
			_list_size--;
			_tail_lst->data = _list_size;
			tmp = nullptr;
			return (position);
		}
		iterator								erase (iterator first, iterator last)
		{
			iterator tmp;
			while (first != last)
			{
				tmp = first;
				first++;
				erase(tmp);
			}
			return (first);
		}
		void									swap (list& x)
		{
			
			struct s_list<T>*tmp;
			size_t size;

			tmp = _tail_lst->next;
			tmp->prev->data = tmp->prev->data;
			size = _list_size;
			_tail_lst->next = x._tail_lst->next;
			_tail_lst->prev->data = x._tail_lst->prev->data;
			_list_size = x._list_size;
			x._tail_lst->next = tmp;
			x._tail_lst->prev->data = tmp->prev->data;
			x._list_size = size;
		}
		void									resize (size_type n, value_type val = value_type())
		{
			if(n > _list_size)
			{
				while(_list_size < n)
					push_back(val);
			}
			else
			{
				while(_list_size > n)
					pop_back();
			}
		}
		void									clear()
		{		
			while(_list_size > 0)
				pop_front();
		}
		// ******************Operations*********************//
		void 									splice (iterator position, list& x)
		{
			struct s_list<T>*tmpIter = position.getList();
			while(x._list_size)
			{
				struct s_list<T>* tmp = new struct s_list<T>;          
				tmp->data = x._tail_lst->prev->data;
				tmp->prev = tmpIter->prev;
				tmp->next = tmpIter;
				tmpIter->prev->next = tmp;
				tmpIter->prev = tmp;
				_list_size++;
				_tail_lst->data = _list_size;
				tmpIter = tmpIter->prev;
				x.pop_back();
			}
		}

		bool 									check(list& x, iterator i)
		{
			iterator src = x.begin();
			size_t j = 0;
			while(j < x._list_size)
			{
				if(src == i)
					return(true);
				src++;
				j++;
			}
			return(false);
		}
		void 								splice (iterator position, list& x, iterator i)
		{
			if (check(x, i) == false)
				return ;
			struct s_list<T> *tmpIter = position.getList();
			struct s_list<T> * tmp = new struct s_list<T>;
			size_t j = 0;
			iterator it = x.begin();
			tmp->data = i.getList()->data;
			tmp->prev = tmpIter->prev;
			tmp->next = tmpIter;
			tmpIter->prev->next = tmp;
			tmpIter->prev = tmp;
			tmpIter = tmpIter->prev;
			struct s_list<T>* iter = x._tail_lst->next;
			while(iter->data != tmp->data && j < x.size())
			{
				iter = iter->next;
				j++;
			}
			if(j != x.size())
			{
				_list_size++;
				_tail_lst->data = _list_size;
				iter->prev->next = iter->next;
				iter->next->prev = iter->prev;
				x._list_size--;
				delete iter;	
			}
		}
		void 								splice (iterator position, list& x, iterator first, iterator last)
		{
			while(first != last)
			{
				splice(position, x, first);
				first++;
			}
		}
		void 								remove (const value_type& val)
		{
			value_type src = _tail_lst->next->data;
			struct s_list<T>* tmp = _tail_lst->next;
			while(tmp != _tail_lst)
			{
				src = tmp->data;
				if(src == val)
					erase(iterator(tmp));
				tmp = tmp->next;
			}
			
		}

		template <class Predicate>
  		void 								remove_if (Predicate pred)
		{
			struct s_list<T>* tmp = _tail_lst->next;
			while(tmp != _tail_lst)
			{
				if(pred(tmp->data))
					erase(tmp);
				tmp = tmp->next;
			}
		}

		void 								sort()
		{
			iterator it = begin();
			iterator it2 = begin();
			iterator tmp;
			size_t j = 0;
			while(j < size())
			{
				it2 = begin();
				tmp = it2;
				it2++;
				while(it2 != end())
				{
					if(tmp > it2)
					{	
						insert(tmp, it2.getList()->data);
						erase(it2);
					}
					else
						tmp++;
					it2 = tmp;
					it2++;	
				}
				j++;
			}
		}
		
		template <class Compare>
  		void 							sort (Compare comp)
		{
			iterator it = begin();
			iterator it2 = begin();
			iterator tmp;
			size_t j = 0;
			while(j < size())
			{
				it2 = begin();
				tmp = it2;
				it2++;
				while(it2 != end())
				{
					if(comp(it2.getList()->data, tmp.getList()->data))
					{
						insert(tmp, it2.getList()->data);
						erase(it2);
					}
					else
						tmp++;
					it2 = tmp;
					it2++;	
				}
				j++;
			}
		}

		void 							unique()
		{
			iterator it = begin();
			iterator it2 = begin();
			size_t i = 0;
			size_t j = size();
			if(j == 0)
				return ;
			while(i < j - 1)
			{
				it = it2;
				it2++;
				if(*it == *it2)
					erase(it2);
				else
					it++;
				i++;
			}
		}

		template <class BinaryPredicate>
		void 							unique (BinaryPredicate binary_pred)
		{
			iterator it = begin();
			iterator it2 = begin();
			size_t i = 0;
			size_t j = size();
			if(j == 0)
				return ;
			while(i < j - 1)
			{
				it = it2;
				it2++;
				if(binary_pred(it.getList()->data, it2.getList()->data))
					erase(it2);
				else
					it++;
				i++;
			}
		}

		void 						merge (list& x)
		{

			if (&x == this)
			return ;

			iterator it = begin();
			iterator it2 = x.begin();

			while (it != end() && it2 != x.end())
			{
				while (it2 != x.end() && *it > *it2)
				{
					insert(it, it2.getList()->data);
					it2++;
				}
				it++;
			}
			if (it2 != x.end())
			this->splice(end(), x, it2, x.end());
			x.clear();

			
		}
		template <class Compare>
		void 						merge (list& x, Compare comp)
		{
						if (&x == this)
			return ;

			iterator it = begin();
			iterator it2 = x.begin();

			while (it != end() && it2 != x.end())
			{
				while (it2 != x.end() && comp(it2.getList()->data, it.getList()->data))
				{
					insert(it, it2.getList()->data);
					it2++;
				}
				it++;
			}
			if (it2 != x.end())
			this->splice(end(), x, it2, x.end());
			x.clear();
		}

		void 						reverse ()
		{

			size_t j = 0;
			iterator it = begin();
			iterator it2 = end();
			while(j < size())
			{
				it = begin();
				splice(it2, *this, it);
				it2--;
				j++;
			}
		}
};
		template <class T, class Alloc>
		bool 						operator== (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs)
		{
			const_iterator<T> it = lhs.begin();
			const_iterator<T> it2 = rhs.begin();
			if(lhs.size() == rhs.size())
			{
				while(it != lhs.end())
				{
					if(it.getList()->data != it2.getList()->data)
						return (false);
					it++;
					it2++;
				}
				return(true);
			}
			else
				return(false);
		}
		template <class T, class Alloc>
		bool 						operator!= (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs)
		{
			const_iterator<T> it = lhs.begin();
			const_iterator<T> it2 = rhs.begin();
			if(lhs.size() == rhs.size())
			{
				while(it != lhs.end())
				{
					if(it.getList()->data != it2.getList()->data)
						return (true);
					it++;
					it2++;
				}
				return(false);
			}
			else
				return(true);
		}
		template <class T, class Alloc>
		bool 						operator<  (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs)
		{
			if (lhs.size() == 0)
				return true;
			else if (rhs.size() == 0)
				return false;
			const_iterator<T> it = lhs.begin();
			const_iterator<T> it2 = rhs.begin();
			if(lhs.size() == rhs.size())
			{
				while(it != lhs.end())
				{
					if(it.getList()->data != it2.getList()->data)
						return (it.getList()->data < it2.getList()->data);
					it++;
					it2++;
				}
				return(false);
			}
			else
			{
				if(lhs.size() < rhs.size())
					return(true);
				else
				{
					it = lhs.begin();
					it2 = rhs.begin();
					while(it != lhs.end())
					{
						if(it.getList()->data != it2.getList()->data)
							return (it.getList()->data < it2.getList()->data);
						it++;
						it2++;
					}
				return(false);
				}
			}
		}
		template <class T, class Alloc>
		bool 									operator<= (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs)
		{
			if (lhs.size() == 0)
				return true;
			else if (rhs.size() == 0)
				return false;
			const_iterator<T> it = lhs.begin();
			const_iterator<T> it2 = rhs.begin();
			if(lhs.size() == rhs.size())
			{
				while(it != lhs.end())
				{
					if(it.getList()->data != it2.getList()->data)
						return (it.getList()->data <= it2.getList()->data);
					it++;
					it2++;
				}
				return(true);
			}
			else
			{
				if(lhs.size() <= rhs.size())
					return(true);
				else
				{
					it = lhs.begin();
					it2 = rhs.begin();
					while(it != lhs.end())
					{
						if(it.getList()->data != it2.getList()->data)
							return (it.getList()->data <= it2.getList()->data);
						it++;
						it2++;
					}
				return(false);
				}
			}
		}
		template <class T, class Alloc>
		bool 									operator>  (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs)
		{
			if (lhs.size() == 0)
				return false;
			else if (rhs.size() == 0)
				return true;
			const_iterator<T> it = lhs.begin();
			const_iterator<T> it2 = rhs.begin();
			if(lhs.size() >= rhs.size())
			{
				while(it != lhs.end())
				{
					if(it.getList()->data > it2.getList()->data)
						return (true);
					else
						return (false);
					it++;
					it2++;
				}
				return(false);
			}
			else
				return(false);
		}
		template <class T, class Alloc>
		bool 									operator>= (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs)
		{
			if (lhs.size() == 0)
				return false;
			else if (rhs.size() == 0)
				return true;
			const_iterator<T> it = lhs.begin();
			const_iterator<T> it2 = rhs.begin();
			if(lhs.size() >= rhs.size())
			{
				while(it != lhs.end())
				{
					if(it.getList()->data >= it2.getList()->data)
						return (true);
					else
						return (false);
					it++;
					it2++;
				}
				return(false);
			}
			else
				return(false);
		}
		template <class T, class Alloc>
		void swap(list<T, Alloc> &x, list <T, Alloc> &y)
		{
			x.swap(y);
		}	
};

#endif