/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssnowbir <ssnowbir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 16:54:57 by ssnowbir          #+#    #+#             */
/*   Updated: 2021/03/26 22:09:50 by ssnowbir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
#define MAP_HPP

#include <iostream>
#include <memory>
#include <string>
#include <cstddef>
#include <limits>
#include <typeinfo>
#include <iterator>
#include <utility>
#include "map_iterator.hpp"

const int BLACK(0);
const int RED(1);


namespace ft
{
	template < class Key,class T,class Compare = std::less<Key>, class Alloc =  std::allocator<std::pair<const Key,T> > > 
	class map
	{
		public:
			typedef Key										key_type;
			typedef T 										mapped_type;
			typedef std::pair<const key_type, mapped_type> 	value_type;
			typedef std::less<key_type> 					key_compare;
			typedef Alloc 									allocator_type;
			typedef T 										&reference;
			typedef const T 								&const_reference;
			typedef	T 										*pointer;
			typedef	const T 								*const_pointer;
			typedef struct s_map<Key,T> 					Node;
			typedef ft::map_iterator<Key, T> iterator;
			// typedef ft::const_map_iterator<Key, T> const_iterator;
			// typedef ft::reverse_map_iterator<Key, T> reverse_iterator;
			// typedef ft::const_reverse_map_iterator<Key, T> const_reverse_iterator;
			// typedef typename ft::MapIt<Key, T>::difference_type	difference_type;
			typedef size_t size_type;
		private:
			Node *_map;
			Node *_root;
			Node *_start;
			Node *_finish;
			
			key_compare 		_key;
			size_t 				_size_map;
			allocator_type		_alloc;

			std::pair<iterator,bool> makeFirstNode (const value_type& val)
			{
				_map = new Node;
				_root = _map;
				
				_map->parent = nullptr;
				_map->key_value = val;
				_map->left = nullptr;
				_map->right = nullptr;
				_map->color = BLACK;
				_start = _map;
				_finish =_map;
				_size_map++;
				return std::make_pair(iterator(this->_root), true);
			}
			// std::pair<iterator,bool> makeNewNode (const value_type& val, Node *parent)
			// {
			// 	_map = new Node;
				
			// 	_map->parent = parent;
			// 	_map->key_value = val;
			// 	_map->left = nullptr;
			// 	_map->right = nullptr;
			// 	_map->color = RED;
			// 	_size_map++;
			// 	return std::make_pair(iterator(this->_map), true);
			// }

			// void turnLeft(Node x)
			// {
				
			// }
		public:
			//******************************* CONSTRUCTORS *********************************************//
			explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
			{
				_alloc = alloc;
				_key = comp;
				_start = nullptr;
				_finish = nullptr;
				_root = nullptr;
				_size_map = 0;
			}
			//******************************* ITERATORS *********************************************//
			iterator begin()
			{
				return(iterator(_start));
			}
			// const_iterator begin() const
			// {
			// 	return(_start);
			// }
			iterator end()
			{
				return(iterator(_finish->right));
			}
			// const_iterator end() const
			// {
			// 	return(_finish);
			// }
			//******************************* CAPACITY *********************************************//
			size_type size() const
			{
				return(_size_map);
			}

			// bool empty() const
			// {
			// 	if(_size_map == 0)
			// 		return (true);
			// 	else
			// 		return (false);
			// }
			//******************************* ELEMENT ACCESS *********************************************//
			//******************************* NODIFIRES *********************************************//
			Node *whereNode(const value_type& val)
			{
				int flag = 1;
				Node *src = _root;
				while(flag)
				{
					flag = 0;
					if(src->key_value.first < val.first)
					{
						for(;src->key_value.first < val.first && src->right; flag++)
						{
							src = src->right;
						}
						for(;src->key_value.first > val.first && src->left; flag++)
						{
							src = src->left;
						}
					}
					else
					{
						for(;src->key_value.first > val.first && src->left; flag++)
						{
							src = src->left;
						}
						for(;src->key_value.first < val.first && src->right; flag++)
						{
							src = src->right;
						}
					}
					
				}
				return (src);
			}
			
			std::pair<iterator,bool> insert (const value_type& val)
			{
				if(_size_map == 0)
					makeFirstNode(val);
				else
				{
					Node *parentNewNode = whereNode(val);
					Node *newMap = new Node;
					newMap->parent = parentNewNode;
					newMap->key_value = val;
					newMap->left = nullptr;
					newMap->right = nullptr;
					newMap->color = RED;
					_size_map++;
					if(val.first > parentNewNode->key_value.first)
					{
						 parentNewNode->right = newMap;
						 
						 if(newMap->key_value.first > _finish->key_value.first)
						 	_finish = newMap;
					}
					else
					{
						 parentNewNode->left = newMap;
						 if(newMap->key_value.first < _start->key_value.first)
						 	_start = newMap;
					}
				}
				return std::make_pair(iterator(this->_root), true);
			}
			//******************************* OBSERVERS *********************************************//
			//******************************* OPERATIONS *********************************************//
			
	};
};
#endif