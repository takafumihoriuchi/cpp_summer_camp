#include <iostream>
#include <list>
#include <vector>
#include <thread>
#include <mutex>
using namespace std;

int p_is_in_adrlist(list<list<int>::iterator> adr_list, list<int>::iterator p) {
	for (auto it = adr_list.begin(); it!=adr_list.end();) {
		if (*it == p) return 1;
		it++;
	}
	return 0;
}

void delete_p_from_adrlist(list<list<int>::iterator> &adr_list, list<int>::iterator p) {
	for (auto it = adr_list.begin(); it!=adr_list.end();) {
		if (*it == p) {
			it = adr_list.erase(it);
			return;
		}
		it++;
	}
}

list<int> filter(bool (*func) (int), list<int> l)
{
	mutex mut_init;
	mutex mut_1;
	mutex mut_2;

	list<list<int>::iterator> adr_list;
	const int num_thread = (l.size() < 8) ? l.size() : 7;
	vector<thread> vecThreads(num_thread);
	for (int i=0; i<num_thread; i++) {
		vecThreads[i] = thread([=, &l, &adr_list, &mut_init, &mut_1, &mut_2] {

			list<int>::iterator p;
			// set init pointer
			while (1) {
				mut_init.lock();
				p = l.begin();
				if (!p_is_in_adrlist(adr_list, p)) {
					adr_list.push_back(p);
					mut_init.unlock();
					break;
				}
			}

			while (1) {
				if (*p%17!=0) { // want to delete these elements
					mut_1.lock();
					delete_p_from_adrlist(adr_list, p);
					p = l.erase(p);
					mut_1.unlock();
					if (p == l.end()) return;
					// get next pointer
					while (1) {
						if (!p_is_in_adrlist(adr_list, p)) {
							adr_list.push_back(p);
							break;
						} else { // (p is in adr_list)
							p++;
							if (p == l.end()) return;
						}
					}
				} else { // keep these elements
					mut_2.lock();
					delete_p_from_adrlist(adr_list, p);
					p++;
					mut_2.unlock();
					if (p == l.end()) return;
					// get next pointer
					while (1) {
						if (!p_is_in_adrlist(adr_list, p)) {
							adr_list.push_back(p);
							break;
						} else { // (p is in adr_list)
							p++;
							if (p == l.end()) return;
						}
					}
				}
			}

		});
	}
	for (int i=0; i<num_thread; i++) {
		vecThreads[i].join();
	}
	return l;
}
