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
