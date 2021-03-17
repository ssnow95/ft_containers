/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_iterator.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssnowbir <ssnowbir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 11:57:50 by ssnowbir          #+#    #+#             */
/*   Updated: 2021/03/15 18:58:22 by ssnowbir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_ITERATOR_HPP
#define VECTOR_ITERATOR_HPP

#include "vector.hpp"

namespace ft
{

	template<typename T>
	class vector_iterator
	{
		
		public:
			typedef T value_type;
			typedef T &reference;
			typedef T *pointer;
		protected:
			pointer arr;
			public:
													vector_iterator(){}
													vector_iterator(const vector_iterator &src){*this = src;}
													vector_iterator(pointer &src){arr = src;};

													vector_iterator(pointer *_arr){arr = _arr;}
			vector_iterator 						&operator=(const pointer &x) {if(arr != x){arr = x;}return arr;}
			virtual 								~vector_iterator() {}
			//-----------------------Overlodes-------------------------//
			bool 									operator==(const vector_iterator &x)
			{
				if(arr == x.arr)
					return true;
				else
					return false;
			}
			bool 									operator!=(const vector_iterator &x)
			{
				if(arr != x.arr)
					return true;
				else
					return false;			
			}
			value_type 										&operator*()
			{
				return *arr;
			}
			const value_type 								&operator*() const
			{
				return *arr;
			}
			pointer										operator->()
			{
				return &arr;
			}
			const pointer								operator->() const
			{
				return &arr;
			}
			vector_iterator							&operator++()
			{
				arr++;
				return (*this);
			}
			vector_iterator							operator++(int)
			{
				vector_iterator tmp(*this);
				operator++();
				return tmp;
			}
			vector_iterator							&operator--()
			{
				arr--;
				return (*this);
			}
			vector_iterator							operator--(int)
			{
				vector_iterator tmp(*this);
				operator--();
				return tmp;
			}
			bool operator>(const vector_iterator &x)
			{
				return (arr > x.arr);
			}

			bool operator<(const vector_iterator &x)
			{
				return (arr < x.arr);
			}

			pointer getArr()
			{
				return(arr);
			}
		};
		template <class T>
		class const_vector_iterator : public vector_iterator<T>
		{
		public:
			const_vector_iterator() {}

			const_vector_iterator(T *arr)
			{
				this->arr = arr;
			}

			const_vector_iterator(const const_vector_iterator &copy)
			{
				*this = copy;
			}

			const_vector_iterator &operator=(const const_vector_iterator &target)
			{
				this->arr = target.arr;
				return (*this);
			}

			~const_vector_iterator() {}

			const T &operator*()
			{
				return (*this->arr);
			}
		};

	template<typename T>
	class reverse_vector_iterator
	{
		
		public:
			typedef T value_type;
			typedef T &reference;
			typedef T *pointer;
		protected:
			pointer arr;
			public:
													reverse_vector_iterator(){}
													reverse_vector_iterator(const reverse_vector_iterator &src){*this = src;}
													reverse_vector_iterator(pointer &src){arr = src;};

													reverse_vector_iterator(pointer *_arr){arr = _arr;}
			reverse_vector_iterator 						&operator=(const pointer &x) {if(arr != x){arr = x;}return arr;}
			virtual 								~reverse_vector_iterator() {}
			//-----------------------Overlodes-------------------------//
			bool 									operator==(const reverse_vector_iterator &x)
			{
				if(arr == x.arr)
					return true;
				else
					return false;
			}
			bool 									operator!=(const reverse_vector_iterator &x)
			{
				if(arr != x.arr)
					return true;
				else
					return false;			
			}
			value_type 										&operator*()
			{
				return *arr;
			}
			const value_type 								&operator*() const
			{
				return *arr;
			}
			pointer										operator->()
			{
				return &arr;
			}
			const pointer								operator->() const
			{
				return &arr;
			}
			reverse_vector_iterator							&operator++()
			{
				arr--;
				return (*this);
			}
			reverse_vector_iterator							operator++(int)
			{
				reverse_vector_iterator tmp(*this);
				operator++();
				return tmp;
			}
			reverse_vector_iterator						&operator--()
			{
				arr++;
				return (*this);
			}
			reverse_vector_iterator						operator--(int)
			{
				reverse_vector_iterator tmp(*this);
				operator--();
				return tmp;
			}
			bool operator>(const reverse_vector_iterator &x)
			{
				return (arr > x.arr);
			}

			bool operator<(const reverse_vector_iterator &x)
			{
				return (arr < x.arr);
			}

			pointer getArr()
			{
				return(arr);
			}
		};
		template <class T>
		class const_reverse_vector_iterator : public reverse_vector_iterator<T>
		{
		public:
			const_reverse_vector_iterator() {}

			const_reverse_vector_iterator(T *arr)
			{
				this->arr = arr;
			}

			const_reverse_vector_iterator(const const_reverse_vector_iterator &copy)
			{
				*this = copy;
			}

			const_reverse_vector_iterator &operator=(const const_reverse_vector_iterator &target)
			{
				this->arr = target.arr;
				return (*this);
			}

			~const_reverse_vector_iterator() {}

			const T &operator*()
			{
				return (*this->arr);
			}
		};
}

#endif