#ifndef ITERATOR_LIST_HPP
#define ITERATOR_LIST_HPP

#include "List.hpp"

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
		private:
			struct s_list<T> *list;
		public:
			typedef T value_type;
			typedef T &reference;
			typedef T *pointer;
			public:
													iterator(){}
													iterator(const iterator &src){*this = src;}
													iterator(struct s_list<T> &src){list = src;};

													iterator(struct s_list<T> *_list){list = _list;}
			iterator 								&operator=(const struct s_list<T> &x) {if(list != x){list = x;}return list;}
													~iterator() {}
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
				if (this->list && this->list->next)
					this->list = this->list->next;
				return (*this);
			}
			iterator							operator++(int)
			{
				iterator tmp(*this);
				operator++();
				return tmp;
			}
			iterator							&operator--()
			{
				if (this->list && this->list->prev)
					this->list = this->list->prev;
				return (*this);
			}
			iterator							operator--(int)
			{
				iterator tmp(*this);
				operator--();
				return tmp;
			}
		};
		template<typename T>
		class reverse_iterator
		{
			private:
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
}

#endif