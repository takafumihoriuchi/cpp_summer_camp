#include <list>
#include <vector>
#include <thread>
#include <algorithm>
#include <mutex>
using namespace std;

mutex mut;
mutex mut_addel;

#define NUM_THREADS 7

list<int> filter(bool (*func) (int), list<int> l)
{
	vector<thread> vecThreads(NUM_THREADS);
	vector<list<int>::iterator> vecAddress;
	// vector<> vecInitp(NUM_THREADS);

	for (int i=0; i<NUM_THREADS; i++) {
		list<int>::iterator init_p = l.begin();
		for (int j=0; j<i; j++) init_p++; // p += i;
		vecAddress.push_back(init_p);
	}
	for (int i=0; i<NUM_THREADS; i++) {
		
		vecThreads[i] = thread([=, &l, &vecAddress] {
			list<int>::iterator p = init_p;
			list<int>::iterator p_tmp;

			while (1) {
				p_tmp = p;
				if (*p%17!=0) {
					l.erase(p);
					for (int j=0; j<i+1; j++) p_tmp++; // p_tmp += i; // p_tmp++;
					while (find(vecAddress.begin(), vecAddress.end(), p_tmp) != vecAddress.end()) {
						// when containing // wait
					}
					mut_addel.lock();
						vecAddress.erase(remove(vecAddress.begin(), vecAddress.end(), p), vecAddress.end());
					mut_addel.unlock();
					mut.lock();
						for (int j=0; j<i+1; j++) p++; // p += i; // p++; // when not containing
						vecAddress.push_back(p);
					mut.unlock();
				} else {
					for (int j=0; j<i+1; j++) p_tmp++; // p_tmp += i; // p_tmp++;
					while (find(vecAddress.begin(), vecAddress.end(), p_tmp) != vecAddress.end()) {
						// when containing // wait
					}
					mut_addel.lock();
						vecAddress.erase(remove(vecAddress.begin(), vecAddress.end(), p), vecAddress.end());
					mut_addel.unlock();
					mut.lock();
						for (int j=0; j<i+1; j++) p++; // p += i; // p++; // when not containing
						vecAddress.push_back(p);
					mut.unlock();
				}
				if (p == l.end()) break;
			}
        });

	}
	for (int i=0; i<NUM_THREADS; i++) {
		vecThreads[i].join();
	}

	return l;
}

/*
#include <list>
#include <thread>
using namespace std;

list<int> filter(bool (*func) (int), list<int> l)
{
	thread t17([&] {
		for(auto it = l.begin(); it!=l.end(); ) {
			if(*it == 17) it = l.erase(it);
			else it++;
		}
	});

	thread t34([&] {
		for(auto it = l.begin(); it!=l.end(); ) {
			if(*it == 34) it = l.erase(it);
			else it++;
		}
	});

	thread t51([&] {
		for(auto it = l.begin(); it!=l.end(); ) {
			if(*it == 51) it = l.erase(it);
			else it++;
		}
	});

	thread t68([&] {
		for(auto it = l.begin(); it!=l.end(); ) {
			if(*it == 68) it = l.erase(it);
			else it++;
		}
	});

	thread t85([&] {
		for(auto it = l.begin(); it!=l.end(); ) {
			if(*it == 85) it = l.erase(it);
			else it++;
		}
	});

	thread t102([&] {
		for(auto it = l.begin(); it!=l.end(); ) {
			if(*it == 102) it = l.erase(it);
			else it++;
		}
	});

	thread t119([&] {
		for(auto it = l.begin(); it!=l.end(); ) {
			if(*it == 119) it = l.erase(it);
			else it++;
		}
	});

	for(auto it = l.begin(); it!=l.end();) {
		if(!func(*it)) it = l.erase(it);
		else it++;
	}

	t17.join();
	t34.join();
	t51.join();
	t68.join();
	t85.join();
	t102.join();
	t119.join();

	return l;
}
*/