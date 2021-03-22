/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssnowbir <ssnowbir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 11:57:47 by ssnowbir          #+#    #+#             */
/*   Updated: 2021/03/22 15:00:55 by ssnowbir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <memory>
#include <string>
#include <cstddef>
#include <limits>
#include <typeinfo>
#include <stdexcept>
#include <iterator>
#include "vector_iterator.hpp"

namespace ft
{
	
	template < class T, class Alloc = std::allocator<T> >
	class vector
	{
		public:
			typedef  T  									value_type;
			typedef Alloc 									allocator_type;
			typedef size_t 									size_type;
			typedef value_type&								reference;
			typedef const value_type&						const_reference;
			typedef value_type*								pointer;
			typedef const value_type*						const_pointer;
			typedef ptrdiff_t 								difference_type;
			typedef ft::vector_iterator<T>					iterator;
			typedef ft::const_vector_iterator<T>			const_iterator;
			typedef ft::reverse_vector_iterator<T> 			reverse_iterator;
			typedef ft::const_reverse_vector_iterator<T>	const_reverse_iterator;
		private:
			allocator_type									_alloc;
			value_type										*_start;
			value_type										*_finish;
			value_type										*_arr;
			size_type										_size_vector;
			size_type										_last_cell_mem;
			
			void reallocMem(size_t sum)
			{
				value_type	*newArr;

				newArr = _alloc.allocate(sum);
				for(size_t i = 0; i < _size_vector; i++)
					newArr[i] = _arr[i];
				_alloc.deallocate(_arr, _last_cell_mem);
				_arr = newArr;
				_finish = &_arr[_size_vector];
				_start = _arr;
			}
			void change_val(size_t i, const value_type& val)
			{
				T saveOld;
				T saveOld2;
				saveOld = _arr[i];
				_alloc.destroy(&_arr[i]);
				_arr[i] = val;
				_size_vector++;
				while(++i <_size_vector - 1)
				{
					saveOld2 = _arr[i];
					_alloc.destroy(&_arr[i]);
					_arr[i] = saveOld;
					saveOld = saveOld2;
				}
				_alloc.destroy(&_arr[i]);
				_arr[i] = saveOld;
				_finish++;
			}
			iterator insertValInputIt (const value_type& val, size_t i)
			{
					size_t tmp;
					iterator it = begin();
										
					T saveVal;
					T saveVal2;
					if (_size_vector + 1 > _last_cell_mem)
					{
						reallocMem((_last_cell_mem + 1) * 2);
						_last_cell_mem = (_last_cell_mem + 1) * 2;
					}
					saveVal = _arr[i];
					_arr[i] = val;
					tmp = i;
					i++;
					_size_vector++;
					while(i < _size_vector)
					{
						saveVal2 = _arr[i];
						_arr[i] = saveVal;
						saveVal = saveVal2;
						i++;
					}
					_finish = &_arr[i];
					return (iterator(&(_arr[tmp])));
			}
		public:
			//************************************MEMBER FUNCTION*******************************//
			explicit vector (const allocator_type& alloc = allocator_type())
			{
				_alloc = alloc;
				_size_vector = 0;
				_arr = _alloc.allocate(2);
				_start = _arr;
				_finish = &_arr[0];
				_last_cell_mem = 2;
			}
			explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
			{
				_alloc = alloc;
				_size_vector = 0;
				_arr = _alloc.allocate(n);
				_start = _arr;
				_finish = _arr;
				for(size_type i = 0; i < n; i++)
				{
					_alloc.construct(_finish, val);
					_size_vector++;
					_finish++;
				}
				_last_cell_mem = _size_vector;
			}
			~vector()
			{
				if (_last_cell_mem > 0)
				{                   //ХЗ решить если раскоментить падает swap
					_alloc.deallocate(_arr, _last_cell_mem);
					std::cout << "DELETE: _last_cell_mem:"<< _last_cell_mem<<std::endl;
				}
				_last_cell_mem = 0;
				_size_vector = 0;
			}
			template <class InputIterator>
			vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(),
										typename std::enable_if<!std::numeric_limits<InputIterator>::is_specialized>::type* = 0)
			{
				_alloc = alloc;
				_size_vector = 0;
				_arr = _alloc.allocate(2);
				_start = _arr;
				_finish = _arr;
				assign(first, last);
			}	
			vector (const vector& x)
			{
				_alloc = x._alloc;
				_size_vector = 0;
				_start = _arr;
				_finish = _arr;
				_last_cell_mem = 0;
				*this = x;
				return ;
			}

			 vector& operator= (const vector& x)
			 {
				 clear();
				 _alloc = x._alloc;
				 _size_vector = x._size_vector;
				 _last_cell_mem = x._last_cell_mem;
				 _arr = _alloc.allocate(x._last_cell_mem);
				 _start = x._start;
				_finish = x._start;
				//  x._arr = x._start;
				size_type i = 0;
				std::cout <<  x._last_cell_mem<<std::endl;
				 for(; i < x._last_cell_mem ; i++)
				 {
					_arr[i] = *_finish;
					_finish++;
				 }
				 return (*this);
			 }
			//************************************ITERATORS*******************************//

			iterator begin()
			{
				return(iterator(_start));
			}
			const_iterator begin() const
			{
				return(const_iterator(_start));
			}

			iterator end()
			{
				return (iterator(_finish));
			}
			const_iterator end() const
			{
				return (const_iterator(_finish));
			}

			reverse_iterator rbegin()
			{
				return(reverse_iterator(_finish));
			}
			const_reverse_iterator rbegin() const
			{
				return(const_reverse_iterator(_finish));
			}

			reverse_iterator rend()
			{
				return(reverse_iterator(_start));
			}
			const_reverse_iterator rend() const
			{
				return(const_reverse_iterator(_start));
			}

			//************************************CAPACITY*******************************//

			size_type size() const
			{
				return(_size_vector);
			}
			
			size_type max_size() const
			{
				return(_alloc.max_size());
			}

			void resize (size_type n, value_type val = value_type())
			{
				if( n < _size_vector)
				{
					size_t i = 0;
					pointer tmp = _start;
					while(i < n)
					{
						i++;
						tmp++;
					}
					_finish = &_arr[i];
					_size_vector = n;
					while(i < _size_vector)
					{
						_alloc.destroy(tmp);
						tmp++;
						i++;
					}
				}
				else
				{
					reallocMem((_size_vector + n) * 2);
					_last_cell_mem = (_size_vector + n) * 2;
					size_t i = 0;
					pointer tmp = _start;
					while(i < _size_vector)
					{
						tmp++;
						i++;
					}
					while(i < n)
					{
						_arr[i] = val;
						i++;
						tmp++;
						_finish++;
					}
					_size_vector = n;
				}
			}
			
			size_type capacity () const
			{
				return(_last_cell_mem);
			}

			bool empty () const
			{
				if(_size_vector == 0)
				{std::cout <<  "i'm here2"<<std::endl;
					return (true);
				}
				else
					return (false);
			}

			void reserve (size_type n)
			{
				if(n > _last_cell_mem)
				{
					reallocMem(n);
					_last_cell_mem = n;
				}
			}

			//************************************ELEMENT ACCESS*******************************//

			reference operator[] (size_type n)
			{
				return (_arr[n]);
			}
			const_reference operator[] (size_type n) const
			{
				return (_arr[n]);
			}

			reference at (size_type n)
			{
				if(n < 0 && n > _size_vector)
				{
					throw std::out_of_range("");
				}
				else
					return (_arr[n]);	
				
			}
			const_reference at (size_type n) const
			{
				if(n < 0 && n > _size_vector)
				{
					throw std::out_of_range("");
				}
				else
					return (_arr[n]);	
			}

			reference front()
			{
				return(*_start);
			}
			const_reference front() const
			{
				return(*_start);
			}

			reference back()
			{
				return(*--_finish);
			}
			const_reference back() const
			{
				return(*--_finish);
			}

			//************************************MODIFIERS*******************************//
			
			template <class InputIterator>
  			void assign (InputIterator first, InputIterator last, typename std::enable_if<!std::numeric_limits<InputIterator>::is_specialized>::type* = 0)
			{
				clear();
				insert(begin(), first, last);
			}
			void assign (size_type n, const value_type& val)
			{
				clear();
				_size_vector = 0;
				_arr = _alloc.allocate(2);
				_start = _arr;
				_finish = &_arr[0];
				_last_cell_mem = 2; 
				for(size_t i = 0; i < n; i++)
				{
					push_back(val);
				}
			}
			
			void push_back (const value_type& val)
			{
				if(_size_vector < _last_cell_mem)
				{ 
					_alloc.construct(&_arr[_size_vector], val);
					_size_vector++;
					_finish++;
				}
				else
				{
					reallocMem(_last_cell_mem * 2);
					_last_cell_mem = _last_cell_mem * 2;
					_alloc.construct(&_arr[_size_vector], val);
					_size_vector++;
					_finish++;
				}
				 
			}

			void pop_back()
			{
				if(_size_vector > 0)
				{
					_finish--;
					_alloc.destroy(&_arr[_size_vector]);
					_size_vector--;
				}
			}
			iterator insert (iterator position, const value_type& val)
			{

					size_type i = 0;
					size_t tmp;
					iterator it = begin();
										
					T saveVal;
					T saveVal2;
					if (_size_vector + 1 > _last_cell_mem)
					{
						reallocMem((_last_cell_mem + 1) * 2);
						_last_cell_mem = (_last_cell_mem + 1) * 2;
					}
					while (i < _size_vector)
					{
						if (position == it)
							break;
						++it;
						i++;
					}	
					saveVal = _arr[i];
					_arr[i] = val;
					tmp = i;
					i++;
					_size_vector++;
					while(i < _size_vector)
					{
						saveVal2 = _arr[i];
						_arr[i] = saveVal;
						saveVal = saveVal2;
						i++;
					}
					_finish = &_arr[i];
					return (iterator(&(_arr[tmp])));
			}
			
			void insert (iterator position, size_type n, const value_type& val)
			{
				if(_size_vector < _last_cell_mem)
					for(size_t i = 0; i < n; i++)
					{
						position = insert(position, val);
					}
				else
				{
					reallocMem(_last_cell_mem * 2 + n);
					_last_cell_mem = _last_cell_mem * 2 + n;
					for(size_t i = 0; i < n; i++)
					{
						position = insert(position, val);
					}
				}
			}	
			
			template <class InputIterator>
    		void insert (iterator position, InputIterator first, InputIterator last, typename std::enable_if<!std::numeric_limits<InputIterator>::is_specialized>::type* = 0)
			{
				 size_t sum = 1;
				InputIterator iter = first;
				iterator it = begin();
				int i = 0;
				while(iter != last)
				{
					iter++;
					sum++;
				}
				while(it != position)
				{
					it++;
					i++;
				} 
				if(_size_vector + sum < _last_cell_mem)
					 while(first != last)
					{
					 insertValInputIt(*first.getArr(), i++);
						++first;
					}
				else
				{
					reallocMem(_last_cell_mem * 2 + sum);
					_last_cell_mem = _last_cell_mem * 2 + sum;
					while(first != last)
					{
						insertValInputIt(*first.getArr(), i++);
						++first;
					}
				}
			}

			iterator erase (iterator position)
			{
				T src;
				T newVal;
				pointer arr = _start;
				size_t i = 0;
				
				for(; i < size(); i++)
				{
					if(arr == position.getArr())
							break ;
					arr++;
				}
				if(i == size() - 1)
				{
					_alloc.destroy(&_arr[i]);
					_size_vector--;
					_finish = &_arr[i];
					position--;
				}
				else
				{
					for(; arr != _finish; arr++ && i++)
					{
						src = _arr[i];
						if(i != size() - 1)
							newVal = _arr[i + 1];
						else
							newVal = _arr[i];
						_alloc.destroy(&_arr[i]);
						if(i !=  _size_vector)
							_arr[i] = newVal;
					}
					if(_size_vector != 0)
						_size_vector--;
				}
				if(_size_vector == 0)
					return(iterator(_start));	
				return(position);
			}
			
			iterator erase (iterator first, iterator last)
			{
				while(first != last)
				{
					erase(first);
					last--;
					_finish--;
				}
				return (first);
			}

			void swap (vector& x)
			{
				// std::cout<<  _size_vector<<std::endl;
				size_t size_vector = _size_vector;
				size_t last_cell_mem = _last_cell_mem;
				T *arr = _arr;
				// T *start = _arr;
				// T *finish = &_arr[_size_vector];

				_size_vector = x._size_vector;
				_last_cell_mem = x._last_cell_mem;
				_arr = x._arr;
				_start = &_arr[0];
				_finish = &_arr[_size_vector];

				x._size_vector = size_vector;
				x._last_cell_mem = last_cell_mem;
				x._arr = arr;
				x._start =&x._arr[0];
				std::cout << *x._start<<", "<<  x._arr[0]<<std::endl;
				x._finish = &x._arr[_size_vector];	
			}

			void clear ()
			{
				if(_size_vector == 0)
					return ;
				else
				{
					_alloc.deallocate(_start, _last_cell_mem);
					_size_vector = 0;
					_last_cell_mem = 0;
				}
				_size_vector = 0;
				_arr = _alloc.allocate(2);
				_start = _arr;
				_finish = &_arr[0];
				_last_cell_mem = 2;
				
			}
			//************************************ALLOCATOR*******************************//
			allocator_type get_allocator () const
			{
				return(_alloc);
			}

			//************************************OVERLOADES*******************************//

			
			
	};
	template <class T, class Alloc>
	bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		const_vector_iterator<T> it = lhs.begin();
		const_vector_iterator<T> it2 = rhs.begin();
		if(lhs.size() == rhs.size())
		{
			while(it != lhs.end())
			{
				if(*it.getArr() != *it2.getArr())
				{std::cout << "here"<<*it.getArr()<< "!="<< *it2.getArr()<<std::endl;
					return (false);
				}
				it++;
				it2++;
			}
			return(true);
		}
		else
			return(false);
	}
	
	template <class T, class Alloc>
		bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
		{
			const_vector_iterator<T> it = lhs.begin();
			const_vector_iterator<T> it2 = rhs.begin();
			if(lhs.size() == rhs.size())
			{
				while(it != lhs.end())
				{
					if(*it.getArr() != *it2.getArr())
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
		bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
		{
			const_vector_iterator<T> it = lhs.begin();
			const_vector_iterator<T> it2 = rhs.begin();
			if(lhs.size() == rhs.size())
			{
				while(it != lhs.end())
				{
					if(*it.getArr() != *it2.getArr())
						return (*it.getArr() < *it2.getArr());
					it++;
					it2++;
				}
				return(false);
			}
			else
				return(lhs.size() < rhs.size());
		}

	template <class T, class Alloc>
	bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		const_vector_iterator<T> it = lhs.begin();
		const_vector_iterator<T> it2 = rhs.begin();
		if(lhs.size() > rhs.size())
		{
			while(it != lhs.end())
			{
				if(*it.getArr() > *it2.getArr())
					return (*it.getArr() > *it2.getArr());
				it++;
				it2++;
			}
			return(false);
		}
		else
			return(lhs.size() <= rhs.size());
	}
	
template <class T, class Alloc>
	bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		const_vector_iterator<T> it = lhs.begin();
		const_vector_iterator<T> it2 = rhs.begin();
		if(lhs.size() <= rhs.size())
		{
			while(it != lhs.end())
			{
				if(*it.getArr() > *it2.getArr())
					return (true);
				it++;
				it2++;
			}
			return(true);
		}
		else
			return(true);
	}
	
template <class T, class Alloc>
	bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		const_vector_iterator<T> it = lhs.begin();
		const_vector_iterator<T> it2 = rhs.begin();
		if(lhs.size() < rhs.size())
		{
			while(it != lhs.end())
			{
				if(*it.getArr() < *it2.getArr())
					return (*it.getArr() < *it2.getArr());
				it++;
				it2++;
			}
			return(false);
		}
		else
			return(lhs.size() >= rhs.size());
	}
};


#endif