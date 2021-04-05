/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssnowbir <ssnowbir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 16:54:57 by ssnowbir          #+#    #+#             */
/*   Updated: 2021/04/05 15:21:48 by ssnowbir         ###   ########.fr       */
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
			typedef ft::const_map_iterator<Key, T> const_iterator;
			typedef ft::reverse_map_iterator<Key, T> reverse_iterator;
			typedef ft::reverse_const_map_iterator<Key, T> const_reverse_iterator;
			typedef size_t size_type;

			class value_compare
			{
				friend class map;
				protected:
					Compare com;
					value_compare (Compare c) : com(c) {}

				public:
					typedef bool result;
					typedef value_type firstArg;
					typedef value_type secondArg;

					bool operator() (const value_type& lhs, const value_type& rhs) const
					{
						return com(lhs.first, rhs.first);
					}
			};
		
		private:
			Node *_map;
			Node *_root;
			Node *_start;
			Node *_finish;
			Node *_tail;
			Node *_begin;
			
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
				Node *y = node->right;
				node->right = y->left;
				if (y->left != nullptr)
					y->left->parent = node;
				y->parent = node->parent;
				if (node->parent == nullptr)
					_root = y;
				else if (node == node->parent->left)
					node->parent->left = y;
				else
					node->parent->right = y;
				y->left = node;
				node->parent = y;
			}

			void turnRight(Node *node)
			{
			 	Node *y = node->left;
				node->left = y->right;
				if (y->right != nullptr)
					y->right->parent = node;
				y->parent = node->parent;
				if (node->parent == nullptr)
					_root = y;
				else if (node == node->parent->right)
					node->parent->right = y;
				else
					node->parent->left = y;
				y->right = node;
				node->parent = y;
			}

			Node * minimum(Node * node)
			{
				if(!node)
					return(node->parent);
				while (node && node->left != nullptr)
					node = node->left;
				return node;
			}

			Node * maximum(Node * node)
			{
				while (node->right != nullptr && node->right != _tail)
					node = node->right;
				return node;
			}

			void	clear(Node *position)
			{
				if (!position)
					return ;
				clear(position->left);
				clear(position->right);
				delete position;
				_size_map--;
			}
			
			void insertFix(Node *node)
			{
				Node *tmp;

				while(node->parent->color == RED) // пока родитель ноды красный мы в цикле
				{
					if(node->parent->parent->left == node->parent) // если родитель ноды является
					{                                              //  левым элементом бабушки
						tmp = node->parent;
						if(tmp->parent->right &&tmp->parent->right->color == RED)       //и правый элемент бабушки красный
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
							if(tmp->parent->left && tmp->parent->left->color == RED)       //и левый элемент бабушки красный
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
			Node *whereNodeFromPosition(const value_type& val, iterator position)
			{
				int flag = 1;
				Node *src = position.getMap();
				while(flag)
				{
					flag = 0;
					if(src->key_value.first < val.first)
					{
						if(src == src->parent->right)
						{
							while(src->parent != _root && src == src->parent->right && src->parent != _tail)
								src = src->parent;
							if(src == src->parent->left)
								src = src->parent;	
						}
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
						if(src == src->parent->left)
						{
							while(src->parent != _root && src == src->parent->left)
								src = src->parent;
							if(src == src->parent->right)
								src = src->parent;
						}
						if(src == src->parent->right)
						{
							while(src->parent != _root && src == src->parent->right && src->key_value.first > val.first)
								src = src->parent;
							if(src == src->parent->left)
								src = src->parent;
						}
						
						for(;src->key_value.first > val.first && src->left; flag++)
							src = src->left;
						for(;src->key_value.first < val.first && src->right; flag++)
							src = src->right;
						return (src);
					}
					
				}
				return (src);
			}
		
			void rbTransplant(Node * nodeToBeDeleted, Node * node) 
			{
				if (nodeToBeDeleted->parent == nullptr)
					_root = node;
				else if (nodeToBeDeleted == nodeToBeDeleted->parent->left)
					nodeToBeDeleted->parent->left = node;
				else if (nodeToBeDeleted == nodeToBeDeleted->parent->right)
					nodeToBeDeleted->parent->right = node;
				if (node)
					node->parent = nodeToBeDeleted->parent;
			}
            void deleteFix(Node *x)
				{
					Node *s;
						
					if (x == nullptr)
						return;
						
					while (x && x != _root && x->color == BLACK)
					{
						if (x->parent && x == x->parent->left)		// если х - левый элемент
						{
							s = x->parent->right;
							if (s && s->color == RED)
							{
								s->color = BLACK;
								x->parent->color = RED;
								turnLeft(x->parent);
								s = x->parent->right;
							}

							if (s && s->left && s->right && s->left->color == BLACK && s->right->color == BLACK)
							{
								s->color = RED;
								x = x->parent;
							}
							else
							{
								if (s && s->right && s->right->color == BLACK)
								{
									s->left->color = BLACK;
									s->color = RED;
									turnRight(s);
									s = x->parent->right;
								}

								s->color = x->parent->color;
								x->parent->color = BLACK;
								s->right->color = BLACK;
								turnLeft(x->parent);
								x = _root;
							}
						}
						else									// если х - правый элемент
						{
							s = x->parent->left;
							if (s && s->color == RED)
							{
								s->color = BLACK;
								x->parent->color = RED;
								turnRight(x->parent);
								s = x->parent->left;
							}

							if (s && s->right && s->right->color == BLACK && s->right->color == BLACK)
							{
								s->color = RED;
								x = x->parent;
							}
							else
							{
								if (s && s->left && s->left->color == BLACK)
								{
									s->right->color = BLACK;
									s->color = RED;
									turnLeft(s);
									s = x->parent->left;
								}

								s->color = x->parent->color;
								x->parent->color = BLACK;
								s->left->color = BLACK;
								turnRight(x->parent);
								x = _root;
							}
						}
					}
					x->color = BLACK;				// _root->color = BLACK;
				}
		
			Node *  findNodaKey(const key_type& key)
			{
				Node * findNoda = nullptr;
				Node *begin = _root;

				while (begin != _tail && begin != nullptr)
				{
					if (begin->key_value.first == key)
					{
						findNoda = begin;
						break ;
					}
					else if (begin->key_value.first <= key)
						begin = begin->right;
					else
						begin = begin->left;
				}
				if (findNoda == nullptr || findNoda == _tail)
					return nullptr;
				return findNoda;
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
				_begin = new Node();
				_begin->parent = nullptr;
				_begin->key_value.first = 0;
				_begin->key_value.second = 0;
				_begin->right = nullptr;
				_begin->left = nullptr;
				_begin->color = TAIL;
				
				_tail->parent = nullptr;
				_tail->key_value.first = 0;
				_tail->key_value.second = 0;
				_tail->right = nullptr;
				_tail->left = nullptr;
				_tail->color = TAIL;
				_finish = nullptr;

			}
			
			template <class InputIterator>
  			map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type(),
			  												typename std::enable_if<!std::numeric_limits<InputIterator>::is_specialized>::type* = 0)
			{
				_alloc = alloc;
				_key = comp;
				_start = nullptr;
				_root = nullptr;
				_size_map = 0;
				_begin = new Node();
				_begin->parent = nullptr;
				_begin->key_value.first = 0;
				_begin->key_value.second = 0;
				_begin->right = nullptr;
				_begin->left = nullptr;
				_begin->color = TAIL;	
				
				_tail = new Node();
				_tail->parent = nullptr;
				_tail->key_value.first = 0;
				_tail->key_value.second = 0;
				_tail->right = nullptr;
				_tail->left = nullptr;
				_tail->color = TAIL;
				_finish = nullptr;
				insert(first, last);
			}
	
			map (const map& x)
			{
				_tail = new Node();
				_begin = new Node();
				_size_map = 0;
				*this = x;	
			}

			~map()
			{

				clear();
				delete _tail;
				delete _begin;
			}
			
			map&									operator=(const map& x)
			{
				if(_tail != nullptr || _begin != nullptr)
					this->clear();
				_start = nullptr;
				_root = nullptr;
				_size_map = 0;
				_begin->parent = nullptr;
				_begin->key_value.first = 0;
				_begin->key_value.second = 0;
				_begin->right = nullptr;
				_begin->left = nullptr;
				_begin->color = TAIL;	
				
				_tail->parent = nullptr;
				_tail->key_value.first = 0;
				_tail->key_value.second = 0;
				_tail->right = nullptr;
				_tail->left = nullptr;
				_tail->color = TAIL;
				_finish = nullptr;
				_size_map = 0;

				if(x._size_map > 0)
					insert(x.begin(), x.end());
				return *this;
			}
			//******************************* ITERATORS *********************************************//
			iterator begin()
			{
				if(_size_map == 0)
					return(_tail);
				return(iterator(_start));
			}
			
			const_iterator begin() const
			{
				if(_size_map == 0)
					return(_tail);
				return(const_iterator(_start));
			}
			
			iterator end()
			{
				if(_size_map == 0)
					return(_tail);
				return(iterator(_tail));
			}
			
			const_iterator end() const
			{
				if(_size_map == 0)
					return(_tail);
				return(const_iterator(_tail));
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
				_begin->parent = _start;
				if(_size_map == 0)
					return(_tail);
				return(reverse_iterator(_begin));
			}
			
			const_reverse_iterator rend() const
			{
				_begin->parent = _start;
				if(_size_map == 0)
					return(_tail);
				return(const_reverse_iterator(_begin));
			}
			//******************************* CAPACITY *********************************************//
			size_type size() const
			{
				return(_size_map);
			}

			bool empty() const
			{
				if(_size_map == 0)
					return (true);
				else
					return (false);
			}
			
			size_type max_size() const
			{
				return(std::numeric_limits<size_t>::max()/ sizeof(Node));
			}
			//******************************* ELEMENT ACCESS *********************************************//
			
			mapped_type& operator[] (const key_type& k)
			{
				iterator src = find(k);
				if(src.getMap() == _tail)
				{
					insert(std::make_pair(k, mapped_type()));
					src = find(k);
					return(src.getMap()->key_value.second);
				}
				else
				{
					return(src.getMap()->key_value.second);
				}
			}
			
			//******************************* NODIFIRES *********************************************//
			
	
			std::pair<iterator,bool> insert (const value_type& val)
			{
				if(_size_map == 0)
					makeFirstNode(val);
				else
				{
					
					Node *parentNewNode = whereNode(val);
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
								if(parentNewNode->left->key_value.first > newMap->key_value.first)
									newMap->right = parentNewNode->left;
								else
									newMap->left = parentNewNode->left;
							if(newMap->key_value.first < _start->key_value.first)
							{
								_start = newMap;
								_begin->parent = _start;
							}
						}
						insertFix(newMap);
						_tail->color = 2;
						return std::make_pair(iterator(newMap), true);
					}
					else
						return std::make_pair(iterator(parentNewNode), false);
				}
				return std::make_pair(iterator(_root), true);
			}
			

			iterator insert (iterator position, const value_type& val)
			{
				iterator isVal;
				if(_size_map == 0)
					makeFirstNode(val);
				if((isVal = find(val.first)) != _tail)
					return isVal;
				else
				{
					Node *parentNewNode = whereNodeFromPosition(val, position);
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
								parentNewNode->right = newMap;
							else
							{
								
								if(parentNewNode->right->key_value.first > newMap->key_value.first)
									newMap->right = parentNewNode->right;
								else
									newMap->right = parentNewNode->right;
							}
							
							if(newMap->key_value.first > _finish->key_value.first)
							{
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
							{
								_start = newMap;
								_begin->parent = _start;
							}
						}
						insertFix(newMap);
						_tail->color = 2;
						return iterator(newMap);
					}
					else
						return iterator(parentNewNode);
				}
				return iterator(_root);
			}
			template <class InputIterator>
  			void insert (InputIterator first, InputIterator last, typename std::enable_if<!std::numeric_limits<InputIterator>::is_specialized>::type* = 0)
			{
				while(first != last)
				{
					insert(first.getMap()->key_value);
					first++;
				}
			}
            
			void erase (iterator position)
                {
                    Node  *node;
                    Node  *y;
                    Node  *nodeToBeDeleted = position.getMap();
                    int    originalColor  = nodeToBeDeleted->color;

                    if (nodeToBeDeleted->left == nullptr)
                    {
                        node = nodeToBeDeleted->right;
                        rbTransplant(nodeToBeDeleted, node);
                        if (nodeToBeDeleted == _start)
                        {
							if(node)
                            	_start = minimum(node);
							else
								_start = nodeToBeDeleted->parent;
                        }
						if (nodeToBeDeleted == _finish)
                        {
							_finish = _tail->parent;
						}    
                    }
                    else if (nodeToBeDeleted->right == nullptr)
                    {
                        node = nodeToBeDeleted->left;
                        rbTransplant(nodeToBeDeleted, node);
                    }
                    else
                    {
                        y = minimum(nodeToBeDeleted->right);
                        originalColor = y->color;
                        node = y->right;

                        if (y->parent == nodeToBeDeleted)
                            node->parent = y;
                        else
                        {
                            rbTransplant(y, y->right);
                            y->right = nodeToBeDeleted->right;
                            y->right->parent = y;
                        }

                        rbTransplant(nodeToBeDeleted, y);
                        y->left = nodeToBeDeleted->left;
                        y->left->parent = y;
                        y->color = nodeToBeDeleted->color;
                    }
                    if (originalColor == BLACK)
                        deleteFix(node);
					_tail->color = TAIL;
					delete nodeToBeDeleted;
					_size_map--;
                }
	
                size_type erase (const key_type& key)
                {
                    Node * findNoda = nullptr;
                    findNoda = findNodaKey(key);
                    
                    if (findNoda == nullptr || findNoda == _tail)
                        return 0;
                    erase (iterator(findNoda));
                    return 1;
                }

                void erase (iterator first, iterator last)
				{
					while(first != last && first != _tail)
					{
						erase(first);
						first++;
					}
				}
                
                void swap (map& node)
				{
					map tmp;

					tmp = node;
					node = *this;
					*this = tmp;			
				}

                void clear()
                {
                    if (empty())
                        return;
                    _finish->right = nullptr;
                    this->clear(this->_root);
                    _map            = nullptr;
                    _start          = nullptr;
                    _finish         = nullptr;
                    _root           = nullptr;
                    _size_map       = 0;
                    _tail->parent   = nullptr;
                }

				
			//******************************* OBSERVERS *********************************************//
			
			key_compare key_comp () const
			{
				return(_key);
			}
			
			value_compare value_comp() const
			{
				return(value_compare(_key));
			}
			
			//******************************* OPERATIONS *********************************************//

			iterator find (const key_type& k)
			{
				int flag = 1;
				Node *src = _root;
				while(flag)
				{
					flag = 0;
					if(src && src->key_value.first < k)
					{
						for(;src->key_value.first < k && src->right; flag++)
						{
							if(src->right == _tail)
								break ;
								src = src->right;
						}
						for(;src->key_value.first > k && src->left; flag++)
							src = src->left;
						if(src->key_value.first == k)
							return (iterator(src));
						else
							return(end());
					}
					else
					{
						for(;src && src->key_value.first > k && src->left; flag++)
							src = src->left;
						for(;src && src->key_value.first < k && src->right; flag++)
							src = src->right;
						for(;src && src->key_value.first > k && src->left; flag++)
							src = src->left;
						if(src && src->key_value.first == k)
							return (iterator(src));
						else
							return(end());
					}
				}
				if(src && src->key_value.first == k)
					return (iterator(src));
				else
					return(end());
			}
			
			const_iterator find (const key_type& k) const
			{
								int flag = 1;
				Node *src = _root;
				while(flag)
				{
					flag = 0;
					if(src->key_value.first < k)
					{
						for(;src->key_value.first < k && src->right; flag++)
						{
							if(src->right == _tail)
								break ;
								src = src->right;
						}
						for(;src->key_value.first > k && src->left; flag++)
							src = src->left;
						if(src->key_value.first == k)
							return (const_iterator(src));
						else
							return(end());
					}
					else
					{
						for(;src->key_value.first > k && src->left; flag++)
							src = src->left;
						for(;src->key_value.first < k && src->right; flag++)
							src = src->right;
						if(src->key_value.first == k)
							return (const_iterator(src));
						else
							return(end());
					}
					
				}
				if(src->key_value.first == k)
					return (const_iterator(src));
				else
					return(end());
			}
			
			size_type count (const key_type & k) const
			{
				iterator src = find(k);
				if(src.getMap() == _tail)
					return(0);
				else
					return (1);
			}
	
			iterator lower_bound (const key_type& k)
			{
				iterator src = find(k);
				if(src.getMap() == _tail)
				{
					src = begin();
					while(src.getMap()->key_value.first < k)
						src++;
					return(src);
				}
				else
					return (src);
			}
			
			const_iterator lower_bound (const key_type& k) const
			{
				const_iterator src = find(k);
				if(src.getMap() == _tail)
				{
					src = begin();
					while(src.getMap()->key_value.first < k)
						src++;
					return(src);
				}
				else
					return (src);
			}

			iterator upper_bound (const key_type& k)
			{
				iterator src = find(k);
				if(src.getMap() == _tail)
				{
					src = begin();
					while(src.getMap()->key_value.first < k)
						src++;
					return(src);
				}
				else
				{
					src++;
					return (src);
				}
			}

			const_iterator upper_bound (const key_type& k) const
			{
				const_iterator src = find(k);
				if(src.getMap() == _tail)
				{
					src = begin();
					while(src.getMap()->key_value.first < k)
						src++;
					return(src);
				}
				else
				{
					src++;
					return (src);
				}
			}
			
			std::pair<const_iterator,const_iterator> equal_range (const key_type& k) const
			{
				const_iterator first = lower_bound(k);
				const_iterator second = upper_bound(k);
				return(std::pair<const_iterator, const_iterator>(first, second));
			}

			std::pair<iterator,iterator>             equal_range (const key_type& k)
			{
				iterator first = lower_bound(k);
				iterator second = upper_bound(k);
				return(std::pair<iterator, iterator>(first, second));
			}
	};
};
#endif