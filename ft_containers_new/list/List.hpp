#ifndef LIST_HPP
#define LIST_HPP

#include <iostream>
# include <memory>
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
		struct s_list<T>                        *_list;
		struct s_list<T>                        *_head_lst;
		struct s_list<T>                        *_tail_lst;
		size_t									_list_size;
	public:
		typedef ft::iterator<T>					iterator;
		typedef const ft::iterator<T>			const_iterator;
		typedef ft::reverse_iterator<T> 		reverse_iterator;
		typedef const ft::reverse_iterator<T>	const_reverse_iterator;

		//--------------------constructors------------------------//
		explicit   								List (const allocator_type& alloc = allocator_type())
		{
			_alloc = alloc;
			_list = new struct s_list<T>;
			_list->next = nullptr;
			_list->prev = nullptr;

			_head_lst =  nullptr;
			_tail_lst = nullptr;
			_list_size = 0;
		}
		explicit   								List (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
		{
			_alloc = alloc;
			for(_list_size = 0; _list_size < n; _list_size++)
				push_back(val);
			_list = _head_lst;
			int i = 0;
			while(_list)
			{
				std::cout <<i<< ", data: "<<_list->data<<"\n";
				i++;
				_list = _list->next;
			}
			_list = _head_lst;//delete
		}
		template <class InputIterator>			List (InputIterator first, InputIterator last,const allocator_type& alloc = allocator_type())
		{
			_alloc = alloc;
			while(first != last)
			{
				push_back(first);
				_list_size++;
				first++;
			}
			_list = _head_lst;
			int i = 0;
			while(_list)
			{
				std::cout <<i<< ", data: "<<_list->data<<"\n";
				i++;
				_list = _list->next;
			}	
			_list = _head_lst;//delete
		}
												List (const List& x){*this = x;}
												~List(){};
		List&									operator=(const List& x);
		// ******************Iterators*********************//
		iterator								begin()
		{
			return (iterator(_list));
		}
		const_iterator							begin() const
		{
			return (iterator(_list));
		}
		iterator								end()
		{
			return (iterator(_tail_lst));
		}
		const_iterator							end() const
		{
			return (iterator(_tail_lst));
		}
		// reverse_iterator						rbegin()
		// {
		// 	return (reverse_iterator());
		// }
		// const_reverse_iterator					rbegin() const
		// {
		// 	rreturn (reverse_iterator(_tail_lst));
		// }
		// reverse_iterator						rend()
		// {
		// 	_list_pointer = _list;
		// 	return(reverse_iterator(_list_pointer));
		// }
		// const_reverse_iterator					rend() const
		// {
		// 	_list_pointer = _list;
		// 	return(const_reverse_iterator(_list_pointer));
		// }
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
			return(std::numeric_limits<size_t>::max());
		}
		// ******************Element access*********************//	
		reference 								front() //Возвращает ссылку на первый элемент(значение) в контейнере списка 
		{
			return (_head_lst->data);
		}
		const_reference							front() const
		{
			return (_head_lst->data);
		}
		reference								back()
		{
			return (_tail_lst->data);
		}
		const_reference							back() const
		{
			return (_tail_lst->data);
		}
// ******************Element access*********************//
		template <class InputIterator>
		void 									assign (InputIterator first, InputIterator last)
		{
			// clear();
			if (first != last)
			{
				while (first != last)
				{
					push_back(*first);
					++first;
				}
			}
		}
		void									assign (size_type n, const value_type& val)
		{
			size_type i = 0;
			while(i < n)
			{
				push_back(val);
				i++;
			}
		}
		void 									push_back(const T &val)
		{
			struct s_list<T>* tmp = new struct s_list<T>;             //Выделение памяти под новый элемент структуры
			tmp->next = nullptr;                   //Указываем, что изначально по следующему адресу пусто
			tmp->data = val;                         //Записываем значение в структуру
			
			if (_head_lst != nullptr)                    //Если список не пуст
			{
				tmp->prev = _tail_lst;               //Указываем адрес на предыдущий элемент в соотв. поле
				_tail_lst->next = tmp;               //Указываем адрес следующего за хвостом элемента
				_tail_lst = tmp;                     //Меняем адрес хвоста
			}
			else //Если список пустой
			{
				tmp->prev = nullptr;               //Предыдущий элемент указывает в пустоту
				_head_lst = _tail_lst = tmp;              //Голова=Хвост=тот элемент, что сейчас добавили
			}
		}
		void									pop_back()
		{
			if(_list_size == 1)
				clear();
			else
			{
				_tail_lst = _tail_lst->prev;
				while(_list)
				{
					if(_list->next == nullptr)
					{
						_list->prev->next = nullptr;
						delete _list;
						_list = nullptr;
						_list_size--;
						break ;
					}
					else
						_list = _list->next;
				}
			}
			_list = _head_lst;
			int r = 0;
			while(_list)
			{
				std::cout <<r<< ", data: "<<_list->data<<"\n";
				r++;
				_list = _list->next;
			}
			_list = _head_lst;//delete

		}
		void push_front (const value_type& val)
		{
			struct s_list<T>* tmp = new struct s_list<T>;             //Выделение памяти под новый элемент структуры
			tmp->next = nullptr;                   //Указываем, что изначально по следующему адресу пусто
			tmp->data = val; 
			if(_head_lst == nullptr)
			{
				tmp->prev = nullptr;               //Предыдущий элемент указывает в пустоту
				_head_lst = _tail_lst = tmp;              //Голова=Хвост=тот элемент, что сейчас добавили
			}
			else
			{
				tmp->next = _list;
				_head_lst = _list = tmp;
			}
			_list = _head_lst;
			int r = 0;
			while(_list)
			{
				std::cout <<r<< "-----, data: "<<_list->data<<"\n";
				r++;
				_list = _list->next;
			}
			_list = _head_lst;//delete
		}
		// iterator								insert (iterator position, const value_type& val);
		// void									insert (iterator position, size_type n, const value_type& val);	
		// template <class InputIterator>
		// void									insert (iterator position, InputIterator first, InputIterator last);
		// iterator					
					// erase (iterator position);
		// iterator								erase (iterator first, iterator last);
		// void									swap (list& x);
		// void									resize (size_type n, value_type val = value_type())
		// {
			
		// }
		void									clear()
		{
			struct s_list<T>  *ptr = _list;
			while(_list)
			{
				ptr = _list;
				_list = _list->next;
				delete ptr;
				ptr = nullptr;
			}
			_list_size = 0;
		}
  	};
};

#endif