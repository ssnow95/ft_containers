/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssnowbir <ssnowbir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 16:54:57 by ssnowbir          #+#    #+#             */
/*   Updated: 2021/03/30 17:15:28 by ssnowbir         ###   ########.fr       */
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
const int TAIL(2);


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
			Node *_tail;
			
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
				_map->color = BLACK;
				_start = _map;
				_finish =_map;
				
				_tail->parent = _map;
				_map->right = _tail;
				
				_size_map++;
				return std::make_pair(iterator(this->_root), true);
			}
			void turnLeft(Node *node)
			{
				Node *tmp = node->right;
				if(node->left != nullptr)
				{
					node->parent->right = node->left;
				}
				if(node->parent->parent == nullptr)
				{
					_root = node;
				}
				else if(tmp->parent == tmp->parent->parent->left)
				{
					tmp->parent->parent->left = node;
				}
				else
				{
					tmp->parent->parent->right = node;
				}
				tmp->left = node;
				node->parent = tmp;
			}

			void turnRight(Node *node)
			{
				Node *tmp = node->parent;
				if(node->right != nullptr)
				{
					tmp->left = node->right;
				}
				if(tmp->parent == nullptr)
				{
					_root = node;
				}
				else if(tmp == tmp->parent->right)
				{
					tmp->parent->right = node;
				}
				else
				{
					tmp->parent->left = node;
				}
				node->right = tmp;
				tmp->parent = node;
			}
			void insertFix(Node *node)
			{
				Node *tmp;

				while(node->parent->color == RED) // пока родитель ноды красный мы в цикле
				{
					if(node->parent->parent->left == node->parent) // если родитель ноды является
					{                                              //  левым элементом бабушки
						tmp = node->parent;
						if(tmp->parent->right->color == RED)       //и правый элемент бабушки красный
						{
							tmp->parent->right->color = BLACK;     //делаем дочерние элементы бабушки(а значит и родителя черн)
							tmp->color = BLACK;
							tmp->parent->color = RED;
							node = node->parent->parent;           // переходит к ноде бабушки
						}
						else
						{
							if(node == node->parent->right)        // иначе если нода  правый ребенок
							{
								node = node->parent;               // переходим на родителя
								turnLeft(node);                    //и переварачиваем влево
							}
							node->parent->color = BLACK;           //делаем родителя черным
							node->parent->parent->color = RED;     // а бабушку красным
							turnRight(node->parent->parent);       //поворачиваем бабушку вправо
						}
					}
					else
					{
						if(node->parent->parent->right == node->parent)
						{
							tmp = node->parent;
							if(tmp->parent->left->color == RED)       //и левый элемент бабушки красный
							{
								tmp->parent->left->color = BLACK;     //делаем дочерние элементы бабушки(а значит и родителя черн)
								tmp->color = BLACK;
								tmp->parent->color = RED;
								node = node->parent->parent;           // переходит к ноде бабушки
							}
							else
							{
								if(node == node->parent->left)        // иначе если нода  левый ребенок
								{
									node = node->parent;              //переходим к родителю 
									turnRight(node);                 // поворачиваем вправо
								}
								node->parent->color = BLACK;           //делаем родителя черным
								node->parent->parent->color = RED;     // а бабушку красным
								turnLeft(node->parent->parent);       //поворачиваем бабушку влево	
							}
						}
					}
					if(node == _root)
						break ;
				}
				_root->color = BLACK;
			}
		public:
			//******************************* CONSTRUCTORS *********************************************//
			explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
			{

				_alloc = alloc;
				_key = comp;
				_start = nullptr;
				_root = nullptr;
				_size_map = 0;
				_tail = new Node();
				_tail->parent = nullptr;
				_tail->key_value.first = 0;
				_tail->key_value.second = 0;
				_tail->right = nullptr;
				_tail->left = nullptr;
				_tail->color = TAIL;
				_finish = nullptr;

			}
			//******************************* ITERATORS *********************************************//
			iterator begin()
			{
				if(_size_map == 0)
					return(_tail);
				return(iterator(_start));
			}
			// const_iterator begin() const
			// {
			// 	return(_start);
			// }
			iterator end()
			{
				if(_size_map == 0)
					return(_tail);
				return(iterator(_tail));
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
							if(src->right == _tail)
								break ;
								src = src->right;
						}
						for(;src->key_value.first > val.first && src->left; flag++)
							src = src->left;
						return (src);
					}
					else
					{
						for(;src->key_value.first > val.first && src->left; flag++)
							src = src->left;
						for(;src->key_value.first < val.first && src->right; flag++)
							src = src->right;
						return (src);
					}
					
				}
				return (src);
			}

			// Node *whereIsBrother(Node *parent)
			// {
			// 	Node *tmp = parent->parent;
				
			// 	int rightOrLeft = -1; // right = 0, left = 1;
			// 	std::cout << tmp->key_value.first<<", "<<  parent->key_value.first<<std::endl;
			// 	if(tmp->key_value.first < parent->key_value.first)
			// 		rightOrLeft = 0;
			// 	else
			// 		rightOrLeft = 1;
			// 	if(tmp->left != nullptr && rightOrLeft == 0)
			// 	{
			// 		std::cout << "left: "<< tmp->left->key_value.first<<std::endl;
			// 		return (tmp->left);
			// 	}
			// 	else if(tmp->right != nullptr && rightOrLeft == 1)
			// 	{
			// 		std::cout << "right: "<< tmp->right->key_value.first<<std::endl;
			// 		return (tmp->right);
			// 	}
			// 	return (nullptr);
			// }
			
			// void change_color(Node *k)
			// {

			// 	// int check  = -1;
			// 	// if(NewNode->parent->left != nullptr)
			// 	// 	check = 1;
			// 	// if(NewNode->parent->right != nullptr)
			// 	// 	check = 0;
			// 	// if((NewNode->parent->color == RED && (check == 0 && NewNode->parent->color == NewNode->parent->right->color)) || (check == 1 && NewNode->parent->color == NewNode->parent->left->color))
			// 	// {

			// 	// 	Node *brother = whereIsBrother(NewNode->parent);

					
			// 	// 	if(brother != nullptr && brother->color != BLACK)
			// 	// 	{
			// 	// 		std::cout << "brother-doughter: "<< brother->key_value.first<<std::endl;
			// 	// 		std::cout << "NewNode->color: "<< NewNode->parent->key_value.first<<std::endl;
			// 	// 		NewNode->parent->color = BLACK;
			// 	// 		brother->color = BLACK;
			// 	// 	}
			// 	// 	else if(NewNode->parent != BLACK  )
			// 	// 	{
			// 	// 			std::cout << "NewNode->color: "<< NewNode->parent->key_value.first<<std::endl;
			// 	// 		NewNode->parent->color = BLACK;
						
			// 	// 	}	 
			// 	// }
			// 	// if(NewNode->color == RED && NewNode->color == NewNode->parent->color)
			// 	// {
			// 	// 	Node *brother = whereIsBrother(NewNode);
			// 	// 	if(brother != nullptr && brother->color != BLACK)
			// 	// 	{
			// 	// 		std::cout << "brother-parent: "<< brother->key_value.first<<std::endl;
			// 	// 		std::cout << "NewNode->color: "<< NewNode->key_value.first<<std::endl;
			// 	// 		NewNode->color = BLACK;
			// 	// 		brother->color = BLACK;
			// 	// 	}
			// 	// 	else if(NewNode != BLACK )
			// 	// 	{
			// 	// 			std::cout << "NewNode->color: "<< NewNode->key_value.first<<std::endl;
			// 	// 		NewNode->color = BLACK;
			// 	// 	}
			// 	// }
			// }
	
			std::pair<iterator,bool> insert (const value_type& val)
			{
				std::cout << "Hi\n";
				if(_size_map == 0)
					makeFirstNode(val);
				else
				{
					
					Node *parentNewNode = whereNode(val);
					std::cout << "parent-->"<<  parentNewNode->key_value.first<<std::endl;
					if(parentNewNode->key_value.first != val.first)
					{
						Node *newMap = new Node;
						newMap->parent = parentNewNode;
						
						newMap->key_value = val;
						newMap->left = nullptr;
						newMap->right = nullptr;
						newMap->color = RED;
						_size_map++;
						if(val.first > parentNewNode->key_value.first)
						{
							if(parentNewNode->right == nullptr || parentNewNode->right == _tail)
							{
								parentNewNode->right = newMap;
								_tail->parent = newMap->right;
							}
							else
							{
								
								if(parentNewNode->right->key_value.first > newMap->key_value.first)
									newMap->right = parentNewNode->right;
								else
									newMap->right = parentNewNode->right;
							}
							
							if(newMap->key_value.first > _finish->key_value.first)
							{
								std::cout << newMap->key_value.first<<std::endl;
								newMap->right = _tail;
								_tail->parent = newMap;
								_finish = newMap;
							}
						}
						else
						{
							if(parentNewNode->left == nullptr)
								parentNewNode->left = newMap;
							else
							{
								if(parentNewNode->left->key_value.first > newMap->key_value.first)
									newMap->right = parentNewNode->left;
								else
									newMap->left = parentNewNode->left;
							}
							if(newMap->key_value.first < _start->key_value.first)
								_start = newMap;
						}
						std::cout << newMap->key_value.first<<"<--my, parent-->"<<  newMap->parent->key_value.first<<std::endl;
						insertFix(newMap);
					}
					else
						return std::make_pair(iterator(this->_root), true);

				}
				return std::make_pair(iterator(this->_root), true);
			}
			//******************************* OBSERVERS *********************************************//
			//******************************* OPERATIONS *********************************************//
			
	};
};
#endif