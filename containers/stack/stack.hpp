/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssnowbir <ssnowbir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 17:33:52 by ssnowbir          #+#    #+#             */
/*   Updated: 2021/03/23 14:19:53 by ssnowbir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP

# include <deque>
#include "../list/list.hpp"
#include "../list/list_iterator.hpp"



namespace ft
{
	template <class T, class Container = std::deque<T> >
	class stack
	{
		public:
			typedef T	value_type;
			typedef Container	container_type;
			typedef size_t	size_type;

		private:
			container_type	_mystack;
		public:
			explicit stack (const container_type& ctnr = container_type())
			{
				_mystack = ctnr;
			} 

			stack& operator= (const stack& x)
			{
				*this->_mystack = x._mystack;
				return (*this);
			}

			size_type size() const
			{
				return(_mystack.size());
			}
			
			bool empty() const
			{
				return(_mystack.empty());
			}

			value_type& top()
			{
				return (_mystack.back());
			}
			const value_type& top() const
			{
				return (_mystack.back());
			}

			void push (const value_type& val)
			{
				return (_mystack.push_back(val));
			}

			void pop()
			{
				return (_mystack.pop_back());
			}

			friend bool operator==(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
			{
				if(lhs._mystack == rhs._mystack)
					return (true);
				else
					return (false);
			}
			friend bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
			{
				if(lhs._mystack != rhs._mystack)
					return (true);
				else
					return (false);
			}
			friend bool operator<  (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
			{
				if(lhs._mystack < rhs._mystack)
					return (true);
				else
					return (false);
			}
			friend bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
			{
				if(lhs._mystack <= rhs._mystack)
					return (true);
				else
					return (false);
			}
			friend bool operator>  (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
			{
				if(lhs._mystack > rhs._mystack)
					return (true);
				else
					return (false);
			}
			friend bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
			{
				if(lhs._mystack >= rhs._mystack)
					return (true);
				else
					return (false);
			}
		};
};

#endif