/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_iterator.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssnowbir <ssnowbir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 11:57:40 by ssnowbir          #+#    #+#             */
/*   Updated: 2021/04/03 17:54:53 by ssnowbir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_ITERATOR_HPP
#define  LIST_ITERATOR_HPP

#include "list.hpp"

namespace ft
{

	template<typename T>
	struct  						s_list
	{
		T 									data;
		s_list 								*next;
		s_list 								*prev;
	};
	template<typename T>
	class iterator
	{
		protected:
			struct s_list<T> *list;
		public:
			typedef T value_type;
			typedef T &reference;
			typedef T *pointer;
			typedef std::ptrdiff_t difference_type;
			public:
													iterator(){}
													iterator(const iterator &src){*this = src;}
													iterator(struct s_list<T> &src){list = src;};

													iterator(struct s_list<T> *_list){list = _list;}
			iterator 								&operator=(const struct s_list<T> &x) {if(list != x){list = x;}return list;}
			virtual 								~iterator() {}
			//-----------------------Overlodes-------------------------//
			bool 									operator==(const iterator &x)
			{
				if(list == x.list)
					return true;
				else
					return false;
			}
			bool 									operator!=(const iterator &x)
			{
				if(list != x.list)
					return true;
				else
					return false;			
			}
			value_type 										&operator*()
			{
				return this->list->data;
			}
			const value_type 								&operator*() const
			{
				return this->list->data;
			}
			pointer										operator->()
			{
				return &list->data;
			}
			const pointer								operator->() const
			{
				return &list->data;
			}
			iterator							&operator++()
			{
				if (list && list->next)
					list = list->next;
				return (*this);
			}
			iterator							operator++(int)
			{
				iterator tmp(*this);
				operator++();
				return tmp;
			}

			difference_type						operator-(iterator const &other)
			{
				return (this->list - other.list);
			}
			
			iterator							&operator--()
			{
				if (list && list->prev)
					list = list->prev;
				return (*this);
			}
			iterator							operator--(int)
			{
				iterator tmp(*this);
				operator--();
				return tmp;
			}
			bool operator>(const iterator &x)
			{
				return (list->data > x.list->data);
			}

			bool operator<(const iterator &x)
			{
				return (list->data < x.list->data);
			}

			struct s_list<T> *getList()
			{
				return(list);
			}
		};
		template <class T>
		class const_iterator : public iterator<T>
		{
		public:
			const_iterator() {}

			const_iterator(struct s_list<T> *list)
			{
				this->list = list;
			}

			const_iterator(const const_iterator &copy)
			{
				*this = copy;
			}

			const_iterator &operator=(const const_iterator &target)
			{
				this->list = target.list;
				return (*this);
			}

			~const_iterator() {}

			const T &operator*()
			{
				return (this->list->data);
			}
		};

		template<typename T>
		class reverse_iterator
		{
			protected:
			struct s_list<T> 						*list;
			public:
			typedef T 								value_type;
			typedef T 								&reference;
			typedef T 								*pointer;


													reverse_iterator(){}
													reverse_iterator(const reverse_iterator &src){*this = src;}
													reverse_iterator(struct s_list<T> &src){list = src;};

													reverse_iterator(struct s_list<T> *_list){list = _list;}
			reverse_iterator						&operator=(const struct s_list<T> &x) {if(list != x){list = x;}return list;}
													~reverse_iterator() {}
				//-----------------------Overlodes-------------------------//
			bool 									operator==(const reverse_iterator &x)
			{
				if(list == x.list)
					return true;
				else
					return false;
			}
			bool 									operator!=(const reverse_iterator &x)
			{
				if(list != x.list)
					return true;
				else
					return false;			
			}
			value_type 										&operator*()
			{
				return this->list->data;
			}
			const value_type 								&operator*() const
			{
				return this->list->data;
			}
			pointer										operator->()
			{
				return &list->data;
			}
			const pointer								operator->() const
			{
				return &list->data;
			}
			reverse_iterator							&operator++()
			{
				if (this->list && this->list->next)
					this->list = this->list->next;
				return (*this);
			}
			reverse_iterator							operator++(int)
			{
				reverse_iterator tmp(*this);
				operator++();
				return tmp;
			}
			reverse_iterator							&operator--()
			{
				if (this->list && this->list->prev)
					this->list = this->list->prev;
				return (*this);
			}
			reverse_iterator							operator--(int)
			{
				reverse_iterator tmp(*this);
				operator--();
				return tmp;
			}
		};
		template <class T>
		class const_reverse_iterator: public reverse_iterator<T>
		{
		public:
			const_reverse_iterator() {}

			const_reverse_iterator(struct s_list<T> *list)
			{
				this->list = list;
			}

			const_reverse_iterator(const const_reverse_iterator &copy)
			{
				*this = copy;
			}

			const_reverse_iterator &operator=(const const_reverse_iterator &target)
			{
				this->list = target.list;
				return (*this);
			}

			~const_reverse_iterator() {}

			const T &operator*()
			{
				return (this->list->data);
			}
		};
}

#endif