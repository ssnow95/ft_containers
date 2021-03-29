/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_iterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssnowbir <ssnowbir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 17:00:21 by ssnowbir          #+#    #+#             */
/*   Updated: 2021/03/26 21:46:02 by ssnowbir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_ITERATOR_HPP
#define  MAP_ITERATOR_HPP

#include "map.hpp"

namespace ft
{
	template <class Key, class T>
	struct 					s_map
	{
		struct s_map 		*parent;
		struct s_map 		*left;
		struct s_map 		*right;
		std::pair<Key,T> 	key_value;
		int					color;
	};

	template <class Key, class T>
	class map_iterator
	{
		public:
			typedef std::pair<Key,T> value_type;
			typedef std::pair<Key,T> &reference;
			typedef std::pair<Key,T> *pointer;
			typedef std::ptrdiff_t difference_type;
		protected:
			struct s_map<Key,T> *_map;
		public:
													map_iterator(){}
													map_iterator(const map_iterator &src){*this = src;}
													map_iterator(struct s_map<Key,T> &src){_map = src;};

													map_iterator(struct s_map<Key,T> *_list){_map = _list;}
			map_iterator 							&operator=(const struct s_map<Key,T> &x) {if(_map != x){_map = x;}return _map;}
			virtual 								~map_iterator() {}
			//-----------------------Overlodes-------------------------//
			// bool 									operator==(const map_iterator &x)
			// {
			// 	if(_map == x._map)
			// 		return(true);
			// 	return(false);
			// }
			bool 									operator!=(const map_iterator &x)
			{
				if(_map != x._map)
					return(true);
				return(false);
			}
			// value_type 								&operator*()
			// {
			// 	return (_map->key_value);
			// }
			// const value_type 						&operator*() const
			// {
			// 	return (_map->key_value);	
			// }	
			pointer									operator->()
			{
				return (&(this->_map->key_value));	
			}
			// const pointer							operator->() const
			// {
			// 	return (&_map->key_value);	
			// }
			map_iterator							&operator++()
			{
				if (!_map)
					return (*this);
				struct s_map<Key,T> *tmp = _map;
				if(_map->right)
				{
					tmp = _map->right;
					while(tmp->left)
						tmp = tmp->left;
				}
				else if(_map->right == nullptr && _map->parent && _map->key_value.first < _map->parent->key_value.first)
				{
					tmp = _map;
					tmp = tmp->parent;
				}
				else if (_map->right == nullptr)
				{
					tmp = _map->right;
				}
				_map = tmp;
				return (*this);				
			}
			map_iterator							operator++(int)
			{
				map_iterator tmp(*this);
				operator++();
				return tmp;
			}
			std::string getColor()
			{
				if(_map->color == 0)
					return ("\x1b[34m");
				else
				    return ("\x1b[31m");	
			}
			
			// map_iterator							&operator--()
			// {
			// 	struct s_map<Key,T> tmp;
			// 	if(_map)
			// 	{
			// 		if(_map->left)
			// 		{
			// 			tmp = _map->left;
			// 			while(tmp->right)
			// 				tmp = tmp->right;
			// 		}
			// 		else
			// 		{
			// 			if(_map->parent)
			// 				tmp = _map->parent;	
			// 		}
			// 		_map = tmp;
			// 		return (*this);
			// 	}
			// 	else
			// 		return ;
			// }
			// map_iterator							operator--(int)
			// {
			// 	map_iterator tmp(*this);
			// 	operator--();
			// 	return tmp;
			// }
			// difference_type							operator+(map_iterator const &other)
			// {
			// 	map_iterator ptr;

			// 	ptr._map= map + n;
			// 	return (ptr);
			// }
			// difference_type						operator-(map_iterator const &other)
			// {
			// 	return (this->_map - other._map);
			// }
			// bool 									operator>(const map_iterator &x)
			// {
			// 	return (this->_map > x._map);
			// }
			// bool 									operator<(const map_iterator &x)
			// {
			// 	return (this->_map < x._map);
			// }
			// struct s_map<Key,T>							*getMap()
			// {
			// 	return (this->_map);
			// }
	};
};
#endif