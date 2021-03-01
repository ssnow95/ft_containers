#include "List.hpp"
#include <list>
#include <iterator>

int main()
{
	std::cout << "\x1b[36m--------------------LIST TEST------------------------\x1b[0m\n";
	ft::List<int>first((size_t)3, 10);
	std::list<int> mylist((size_t)3, 10);

	std::list<int>::iterator it = mylist.begin();
	std::list<int>::iterator it2 = mylist.end();


	ft::List<int>::iterator i = first.begin();
	ft::List<int>::iterator i2 = first.end();
	//TEST BEGIN()//
	std::cout <<"\x1b[4mbegin()\x1b[0m\n";
	std::cout <<"my: "<< *i<< "\t\t\t";
	std::cout <<"origin : "<< *it<< "\t\t\t";
	if(*i == *it)
		std::cout << "\x1b[32mOK\x1b[0m\n\n\n";
	else
		std::cout << "\x1b[31mWRONG\x1b[0m\n\n\n";


	//TEST END()//
	std::cout <<"\x1b[4mend()\x1b[0m\n";
	std::cout <<"my: "<< *i2<< "\t\t\t";
	std::cout <<"origin : "<< *it2<< "\t\t\t";
	if(*i2 == *it2)
		std::cout << "\x1b[32mOK\x1b[0m\n\n\n";
	else
		std::cout << "\x1b[31mWRONG\x1b[0m\n\n\n";



	//TEST POP_BACK()//
	mylist.pop_back();
	first.pop_back();
	it =  mylist.end();
	i = first.end();
	std::cout <<"\x1b[4mpop_back()\x1b[0m\n";
	std::cout <<"my: "<< *i<< "\t\t";
	std::cout <<"origin : "<< *it<< "\t\t\t\t";
	if(*i2 == *it2)
		std::cout << "\x1b[32mOK\x1b[0m\n\n\n";
	else
		std::cout << "\x1b[31mWRONG\x1b[0m\n\n\n";
	// std::list<int>::iterator it1 = mylist.begin();
	// std::list<int>::iterator it2 = mylist.end();
	// for(int i = 0; it1 < it2, it1++)
	// {
	// 	std::cout << i<< ", origin: "<< *it1<<"\n";
	// 	i++;
}


