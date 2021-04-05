/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_iterator.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssnowbir <ssnowbir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 11:57:50 by ssnowbir          #+#    #+#             */
/*   Updated: 2021/04/05 19:40:47 by ssnowbir         ###   ########.fr       */
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
			typedef std::ptrdiff_t difference_type;
		protected:
			pointer arr;
			public:
													vector_iterator(){}
													vector_iterator(const vector_iterator &src){*this = src;}
													vector_iterator(reference src){*arr = src;};

													vector_iterator(pointer _arr){arr = _arr;}
			vector_iterator 						&operator=(const pointer &x)
			{
				arr = x;
				return (*this);
			}
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

			difference_type						operator-(vector_iterator const &other)
			{
				return (this->arr - other.arr);
			}

			difference_type						operator+(vector_iterator const &other)
			{
				return (this->arr - other.arr);
			}

			void operator += (difference_type n)
			{
				arr += n;
			};

			void operator -= (difference_type n)
			{
				arr -= n;
			};

			// vector_iterator operator + (difference_type n)
			// {
			// 	vector_iterator ptr;

			// 	ptr.arr = arr + n;
			// 	return (ptr);
			// };
			
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

			value_type &operator[](const size_t &x)
			{
				return *(arr + x); 
			}
  			const value_type &operator[](const size_t &x) const
			{ 
				return *(arr + x); 
			}

			vector_iterator operator+(const size_t &x)
			{
				return (this->arr + x);
			}
  			vector_iterator operator-(const size_t &x)
			{
				return (this->arr - x);
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
			typedef std::ptrdiff_t difference_type;
		protected:
			pointer arr;
			public:
													reverse_vector_iterator(){}
													reverse_vector_iterator(const reverse_vector_iterator &src){*this = src;}
													reverse_vector_iterator(pointer src){arr = src;};

			reverse_vector_iterator 						&operator=(const T &x) {if(arr != x){arr = x;}return *this;}
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

			difference_type						operator-(reverse_vector_iterator const &other)
			{
				return (this->arr - other.arr);
			}

			difference_type						operator+(reverse_vector_iterator const &other)
			{
				return (this->arr + other.arr);
			}

			reverse_vector_iterator operator+(const size_t &x)
			{
				return (this->arr + x);
			}
  			reverse_vector_iterator operator-(const size_t &x)
			{
				return (this->arr - x);
			}

			T &operator[](const size_t &target)
			{
				return *(arr + target); 
			}
  			const T &operator[](const size_t &target) const
			{ 
				return *(arr + target); 
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