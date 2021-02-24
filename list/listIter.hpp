#ifndef LISTITER_HPP
#define LISTITER_HPP

// #include "list.hpp"

// // namespace ft
// // {
// // 	template <class T>
// // 	struct Node
// // 	{
// // 		Node	*prev;
// // 		Node	*next;
// // 		T		*data;
// // 	};

// // 	template <class T>
// // 	class iterator_list
// // 	{
// // 	private:
// // 		T	operator++() const;
// // 		T	operator++() const;
// // 		T	operator--() const;
// // 		T	operator--() const;
// // 		T	&operator+=() const;
// // 		T	&operator-=() const;
// // 		bool	operator<() const;
// // 		bool	operator<=() const;
// // 		bool	operator>() const;
// // 		bool	operator>=() const;
// // 		T		&operator[]() const;

// // 	protected:
// // 		Node<T>	*newNode;
// // 	public:

// // 		iterator_list() {}

// // 		iterator_list(const iterator_list &copy)
// // 		{
// // 			*this = copy;
// // 		}

// // 		iterator_list &operator=(const iterator_list &target)
// // 		{
// // 			newNode = target.newNode;
// // 			return (*this);
// // 		}

// // 		~iterator_list() {}

// // 		iterator_list(Node<T> *list)
// // 		{
// // 			newNode = list;
// // 		}

// // 		iterator_list &operator++()
// // 		{
// // 			if ()
// // 				this->newNode = this->newNode->next;
// // 			return (*this);
// // 		}

// // 		iterator_list operator++(int)
// // 		{
// // 			iterator_list tmp(*this);
// // 			this->operator++();
// // 			return (tmp);
// // 		}

// // 		iterator_list &operator--()
// // 		{
// // 			if (newNode && newNode->prev)
// // 				newNode = newNode->prev;
// // 			return (*this);
// // 		}

// // 		iterator_list operator--(int)
// // 		{
// // 			iterator_list tmp(*this);
// // 			this->operator--();
// // 			return (tmp);
// // 		}

// //   		bool operator==(const iterator_list &c) const
// // 		{
// // 			return (newNode == c.newNode);
// // 		}

// //   		bool operator!=(const iterator_list &c) const
// // 		{
// // 			return (newNode != c.newNode);
// // 		}

// // 		T &operator*()
// // 		{
// // 			return (*newNode->data);
// // 		}

// // 		T *operator->()
// // 		{
// // 			return (newNode->data);
// // 		}

// // 		Node<T> *getNewNode()
// // 		{
// // 			return (newNode);
// // 		}
// // 	};

// // 	template <class T>
// // 	class reverse_iterator_list : public iterator_list<T>
// // 	{
// // 	public:
// // 		reverse_iterator_list() {}

// // 		reverse_iterator_list(Node<T> *copy)
// // 		{
// // 			this->newNode = copy;
// // 		}

// // 		reverse_iterator_list(const reverse_iterator_list &target)
// // 		{
// // 			*this = target;
// // 		}

// // 		~reverse_iterator_list() {}

// // 		reverse_iterator_list &operator=(const reverse_iterator_list &target)
// // 		{
// // 			this->newNode = target.newNode;
// // 			return (*this);
// // 		}

// // 		reverse_iterator_list &operator++()
// // 		{
// // 			if (this->newNode && this->newNode->prev)
// // 				this->newNode = this->newNode->prev;
// // 			return (*this);
// // 		}

// // 		reverse_iterator_list operator++(int)
// // 		{
// // 			reverse_iterator_list tmp(*this);
// // 			this->operator++();
// // 			return (tmp);
// // 		}

// // 		reverse_iterator_list &operator--()
// // 		{
// // 			if (this->newNode && this->newNode->next)
// // 				this->newNode = this->newNode->next;
// // 			return (*this);
// // 		}

// // 		reverse_iterator_list operator--(int)
// // 		{
// // 			reverse_iterator_list tmp(*this);
// // 			this->operator--();
// // 			return (tmp);
// // 		}
// // 	};


// namespace ft
// {
	
// 	template <class T>
// 	class iterator_list
// 	{

// 		t_list					*list;
// 		public:
// 		friend class list;
// 		typedef list<T>::t_list t_lst;
// 								iterator_list(){list = nullptr;}
// 								iterator_list(const iterator_list &x) { *this = x;}
// 		iterator_list 				&operator=(const t_lst &x) {if(list != x){list = x;}return list; }
// 		virtual 				~iterator_list() {}

// 		//-----------------------Overlodes-------------------------//
// 		bool 					operator==(const iterator_list &x)
// 		{
// 			if(list == x.list)
// 				return true;
// 			else
// 				return false;
// 		}
// 		bool 					operator!=(const iterator_list &x)
// 		{
// 			if(list != x.list)
// 				return true;
// 			else
// 				return false;			
// 		}
// 		T 						&operator*();
// 		{
// 			return list->data;
// 		}
// 		const T 				&operator*() const
// 		{
// 			return list->data;
// 		}
// 		T*						operator->()
// 		{
// 			return &list->data;
// 		}
// 		const T*				operator->() const
// 		{
// 			return &list->data;
// 		}
// 		iterator_list<T>				&operator++()
// 		{
// 			list = list->next;
// 			return list;
// 		}
// 		iterator_list<T>				&operator--()
// 		{
// 			list = list->prev;
// 			return list;
// 		}
// 	};

// 	template<typename T>
// 	class reverse_iterator_list
// 	{

// 		t_list					*list;
// 		public:
// 				friend class list;
// 				typedef list<T>::t_list t_lst;
// 								reverse_iterator_list(){list = nullptr;}
// 								reverse_iterator_list(const reverse_iterator_list &x) { *this = x;}
// 		reverse_iterator_list 		&operator=(const t_lst &x) {if(list != x){list = x;}return list; }
// 		virtual 				~reverse_iterator_list() {}

// 		//-----------------------Overlodes-------------------------//
// 		bool 					operator==(const reverse_iterator_list &x)
// 		{
// 			if(list == x.list)
// 				return true;
// 			else
// 				return false;
// 		}
// 		bool 					operator!=(const reverse_iterator_list &x)
// 		{
// 			if(list != x.list)
// 				return true;
// 			else
// 				return false;			
// 		}
// 		T 						&operator*();
// 		{
// 			return list->data;
// 		}
// 		const T 				&operator*() const
// 		{
// 			return list->data;
// 		}
// 		T*						operator->()
// 		{
// 			return &list->data;
// 		}
// 		const T*				operator->() const
// 		{
// 			return &list->data;
// 		}
// 		reverse_iterator_list<T>		&operator++()
// 		{
// 			list = list->prev;
// 			return list;
// 		}
// 		reverse_iterator_list<T>		&operator--()
// 		{
// 			list = list->next;
// 			return list;
// 		}
// 	};
// };
  	
	

#endif