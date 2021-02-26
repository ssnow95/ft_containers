#ifndef ITERATOR_LIST_HPP
#define ITERATOR_LIST_HPP

#include "List.hpp"

namespace ft
{
	template<typename T>
	class iterator
	{
		template<typename> friend class List;
		protected:
			typedef struct  						s_list
			{
				T 									data;
				s_list 								*next;
				s_list 								*prev;
			}										t_list;

			t_list *list;
		public:
			public:
													iterator(){list = nullptr;}
													iterator(const iterator &x) { *this = x;}
			iterator 								&operator=(const t_list &x) {if(list != x){list = x;}return list; }
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
			T 										&operator*()
			{
				return list->data;
			}
			const T 								&operator*() const
			{
				return list->data;
			}
			T*										operator->()
			{
				return &list->data;
			}
			const T*								operator->() const
			{
				return &list->data;
			}
			iterator							&operator++()
			{
				list = list->next;
				return list;
			}
			iterator							&operator--()
			{
				list = list->prev;
				return list;
			}
		};
		template<typename T>
		class reverse_iterator
		{
			template<typename> friend class List;
			protected:
				typedef struct  						s_list
				{
					T 									data;
					s_list 								*next;
					s_list 								*prev;
				}										t_list;

				t_list *list;
			public:
				public:
														reverse_iterator(){list = nullptr;}
														reverse_iterator(const reverse_iterator &x) { *this = x;}
				reverse_iterator 								&operator=(const t_list &x) {if(list != x){list = x;}return list; }
				virtual 								~reverse_iterator() {}
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
				T 										&operator*()
				{
					return list->data;
				}
				const T 								&operator*() const
				{
					return list->data;
				}
				T*										operator->()
				{
					return &list->data;
				}
				const T*								operator->() const
				{
					return &list->data;
				}
				reverse_iterator		&operator++()
				{
					list = list->prev;
					return list;
				}
				reverse_iterator		&operator--()
				{
					list = list->next;
					return list;
				}
		};
	}

#endif