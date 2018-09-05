#include <list>
#include <thread>
#include <iostream>
using namespace std;


list<int> filter(bool (*func) (int), list<int> l)
{
	int l_size = l.size();
	int l_half = l_size / 2;
	list<int> l_f;
	list<int> l_b;
	thread t_front([&] {
		int count = 0;
		list<int>::iterator p = l.begin();
		while (count < l_half) {
		  if(*p%17==0) l_f.push_back(*p);
		  p++;
		  count++;
		}
	});
	
	// use main_thread to process from back
	int count = l_half;
	list<int>::reverse_iterator p = l.rbegin();
	while (count < l_size) {
	  if(*p%17==0) l_b.push_front(*p);
	  p++;
	  count++;
	}

	t_front.join();
	l_f.splice(l_f.end(), l_b);
	return l_f;
}

/*
#include <list>
#include <thread>
using namespace std;

list<int> filter(bool (*func) (int), list<int> l)
{
	int l_size = l.size();
	int l_half = l_size / 2;

	thread t_front([&] {
		int count = 0;
		list<int>::iterator p = l.begin();
		while (count < l_half) {
			if(!func(*p)) p = l.erase(p);
			else p++;
			count++;
		}
	});

	thread t_back([&] {
		int count = l_half;
		list<int>::reverse_iterator p = l.rbegin();
		while (count < l_size) {
			if(!func(*p)) l.erase((++p).base());
			else p++;
			count++;
		}
	});

	t_front.join();
	t_back.join();

	return l;
}
*/

/*
#include<list>
using namespace std;
list<int> filter(bool (*func) (int), list<int> l) {
  for(auto it = l.begin(); it!=l.end();) {
    if(!func(*it))
      it = l.erase(it);
    else
      it++;
  }
  return l;
}
*/
