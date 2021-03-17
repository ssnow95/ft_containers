/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssnowbir <ssnowbir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 11:57:47 by ssnowbir          #+#    #+#             */
/*   Updated: 2021/03/17 20:39:40 by ssnowbir         ###   ########.fr       */
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
				// newArr = new 
				
				for(size_t i = 0; i < _last_cell_mem; i++)
				{
					newArr[i] = _arr[i];
				}
				_alloc.deallocate(_arr, _last_cell_mem);
				_arr = newArr;
				_finish = &_arr[_size_vector];
				_start = &_arr[0];
			}

			void change_val(pointer it, iterator position, const value_type& val)
			{
				T saveOld;
				T saveOld2;
				size_t i = 0;

				while(i <_size_vector)
				{
					if(it == position.getArr())
						break ;	
					i++;						
					it++;
				}
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
			// template <class InputIterator>
			// vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type());	
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
					std::cout <<  "arr[" << i << "] =" << _arr[i]<<std::endl;
				 }
				std::cout <<  "finish"<<*_finish<<std::endl;
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

			//************************************MODIFIERS*******************************//
			
// 		template <class InputIterator>
//   void assign (InputIterator first, InputIterator last);
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
				// std::cout<< "before: "<< *position<<std::endl;
				pointer it = _start;
				if(_size_vector < _last_cell_mem)
				{
					change_val(it, position, val);
				}
				else
				{
					reallocMem(_last_cell_mem * 2);
					_last_cell_mem = _last_cell_mem * 2;
					change_val(it, position, val);
				}
				// std::cout<< "after: "<< *position<<std::endl;
				return (position);
			}
    		void insert (iterator position, size_type n, const value_type& val)
			{
				pointer it = _start;
				if(_size_vector < _last_cell_mem)
					for(size_t i = 0; i < n; i++)
						change_val(it, position, val);
				else
				{
					reallocMem(_last_cell_mem * 2 + n);
					_last_cell_mem = _last_cell_mem * 2 + n;
					for(size_t i = 0; i < n; i++)
						change_val(it, position, val);
				}
			}	
			// template <class InputIterator>
    		// void insert (iterator position, InputIterator first, InputIterator last);

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

			// void swap (vector& x)
			// {
				
			// }

			reference operator[] (size_type n)
			{
				return (_arr[n]);
			}
			const_reference operator[] (size_type n) const
			{
				return (_arr[n]);
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
		
		
			
	};
};

#endif