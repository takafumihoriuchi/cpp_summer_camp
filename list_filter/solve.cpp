#include <list>
#include <vector>
#include <thread>
#include <mutex>
using namespace std;

mutex mut;

list<int> filter(bool (*func) (int), list<int> l)
{
	int num_threads = 7;
	vector<thread> vecThreads(num_threads);
	for (int i=0; i<num_threads; i++) {
		list<int>::iterator p = l.begin();
		p += i;
		vecThreads[i] = thread([=, &l] {
			try {
				while (1) {
					if (*p%17!=0) {
						mut.lock();
						p = l.erase(p);
						mut.unlock();
					} else p++;
					if (p!=l.end()) break;
				}
			} catch (...) {
				// do nothing and terminate thread
			}
        });
	}
	for (int i=0; i<num_threads; i++) {
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