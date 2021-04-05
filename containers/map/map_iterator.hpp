/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_iterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssnowbir <ssnowbir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 17:00:21 by ssnowbir          #+#    #+#             */
/*   Updated: 2021/04/05 15:29:56 by ssnowbir         ###   ########.fr       */
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
			bool 									operator==(const map_iterator &x)
			{
				if(_map == x._map)
					return(true);
				return(false);
			}
			bool 									operator!=(const map_iterator &x)
			{
				if(_map != x._map)
					return(true);
				return(false);
			}
			value_type 								&operator*()
			{
				return (_map->key_value);
			}
			const value_type 						&operator*() const
			{
				return (_map->key_value);	
			}	
			pointer									operator->()
			{
				return (&(this->_map->key_value));	
			}
			const pointer							operator->() const
			{
				return (&_map->key_value);	
			}
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
				else if(_map->right == nullptr && _map->parent && _map->key_value.first > _map->parent->key_value.first)
				{
					tmp = _map;
					struct s_map<Key,T> *tmp2 = _map->parent;
					while(tmp2 && tmp2->key_value.first < tmp->key_value.first)
					{
						tmp2 = tmp2->parent;
					}
					tmp = tmp2;
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
				else if(_map->color == 2)
					return("\x1b[33m");
				else
				    return ("\x1b[31m");	
			}
			
			map_iterator       &operator--()
			{
				struct s_map<Key,T> *it = _map;
				
				if (it->color == 2) 
				{
					it = it->parent;
				}
				else if (it->left)
				{
					it = it->left;
					while (it->right)
						it = it->right;
				}
				else if (it->left == nullptr && it->parent && it->key_value.first > it->parent->key_value.first) 
				{
					it = it->parent;
				}
				else if (it->left == nullptr && it->parent && it->parent->parent) 
				{
					while (it->parent && it->key_value.first < it->parent->key_value.first)
						it = it->parent;
					it = it->parent;
				}
				else if (it->left == nullptr)
				it = it->left;
				this->_map = it;
				return (*this);
			}

			map_iterator							operator--(int)
			{
				map_iterator tmp(*this);
				operator--();
				return tmp;
			}
			bool 									operator>(const map_iterator &x)
			{
				return (this->_map > x._map);
			}
			bool 									operator<(const map_iterator &x)
			{
				return (this->_map < x._map);
			}
			struct s_map<Key,T>	*getMap()
			{
				return (this->_map);
			}
	};
		template <class Key, class T>
		class const_map_iterator : public map_iterator<Key, T>
		{
		public:
			const_map_iterator() {}

			const_map_iterator(struct s_map<Key, T> *_map)
			{
				this->_map = _map;
			}

			const_map_iterator(const const_map_iterator &copy)
			{
				*this = copy;
			}

			const_map_iterator &operator=(const const_map_iterator &target)
			{
				this->_map = target._map;
				return (*this);
			}

			~const_map_iterator() {}

			const std::pair<Key,T> &operator*()
			{
				return (this->_map->key_value);
			}
	};



	template <class Key, class T>
	class reverse_map_iterator
	{
		public:
			typedef std::pair<Key,T> value_type;
			typedef std::pair<Key,T> &reference;
			typedef std::pair<Key,T> *pointer;
			typedef std::ptrdiff_t difference_type;
		protected:
			struct s_map<Key,T> *_map;
		public:
													reverse_map_iterator(){}
													reverse_map_iterator(const reverse_map_iterator &src){*this = src;}
													reverse_map_iterator(struct s_map<Key,T> &src){_map = src;};

													reverse_map_iterator(struct s_map<Key,T> *_list){_map = _list;}
			reverse_map_iterator 							&operator=(const struct s_map<Key,T> &x) {if(_map != x){_map = x;}return _map;}
			virtual 								~reverse_map_iterator() {}
			//-----------------------Overlodes-------------------------//
			bool 									operator==(const reverse_map_iterator &x)
			{
				if(_map == x._map)
					return(true);
				return(false);
			}
			bool 									operator!=(const reverse_map_iterator &x)
			{
				if(_map != x._map)
					return(true);
				return(false);
			}
			value_type 								&operator*()
			{
				return (_map->key_value);
			}
			const value_type 						&operator*() const
			{
				return (_map->key_value);	
			}	
			pointer									operator->()
			{
				return (&(this->_map->key_value));	
			}
			const pointer							operator->() const
			{
				return (&_map->key_value);	
			}
			reverse_map_iterator					&operator--()
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
				else if(_map->right == nullptr && _map->parent && _map->key_value.first > _map->parent->key_value.first)
				{
					tmp = _map;
					struct s_map<Key,T> *tmp2 = _map->parent;
					while(tmp2 && tmp2->key_value.first < tmp->key_value.first)
					{
						tmp2 = tmp2->parent;
					}
					tmp = tmp2;
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
			reverse_map_iterator					operator--(int)
			{
				reverse_map_iterator tmp(*this);
				operator--();
				return tmp;
			}
			std::string 							getColor()
			{
				if(_map->color == 0)
					return ("\x1b[34m");
				else if(_map->color == 2)
					return("\x1b[33m");
				else
				    return ("\x1b[31m");	
			}
			
			reverse_map_iterator      			 &operator++()
			{
				struct s_map<Key,T> *it = _map;
				
				if (it->color == 2) 
				{
				it = it->parent;
				}
				else if (it->left)
				{
				it = it->left;
				while (it->right)
					it = it->right;
				}
				else if (it->left == nullptr && it->parent && it->key_value.first > it->parent->key_value.first)
				{
				it = it->parent;
				}
				else if (it->left == nullptr && it->parent && it->parent->parent)
				{
				while (it->parent && it->key_value.first < it->parent->key_value.first)
				it = it->parent;
				it = it->parent;
				}
				else if (it->left == nullptr) 
				it = it->left;
				this->_map = it;
				return (*this);
			}

			reverse_map_iterator					operator++(int)
			{
				reverse_map_iterator tmp(*this);
				operator++();
				return tmp;
			}
			bool 									operator>(const reverse_map_iterator &x)
			{
				return (this->_map > x._map);
			}
			bool 									operator<(const reverse_map_iterator &x)
			{
				return (this->_map < x._map);
			}
			struct s_map<Key,T>	*getMap()
			{
				return (this->_map);
			}
		};
		template <class Key, class T>
		class reverse_const_map_iterator : public reverse_map_iterator<Key, T>
		{
		public:
			reverse_const_map_iterator() {}

			reverse_const_map_iterator(struct s_map<Key, T> *_map)
			{
				this->_map = _map;
			}

			reverse_const_map_iterator(const reverse_const_map_iterator &copy)
			{
				*this = copy;
			}

			reverse_const_map_iterator &operator=(const reverse_const_map_iterator &target)
			{
				this->_map = target._map;
				return (*this);
			}

			~reverse_const_map_iterator() {}

			const std::pair<Key,T> &operator*()
			{
				return (this->_map->key_value);
			}
		};
};
#endif