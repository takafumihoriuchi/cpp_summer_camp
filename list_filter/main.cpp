#include<iostream>
#include<list>
#include"clock.h"
using namespace std;

list<int> filter(bool (*func) (int), list<int> l);

bool f(int x) {
  return x%17==0;
}

int main(void) {
  int n;
  int x;
  list<int> l;
  cin >> n;
  for (int i=0; i<n; i++) {
    cin >> x;
    l.push_back(x);
  }

  start_counter();
  l = filter(f, l);
  print_counter();

  for(auto itr=l.begin(); itr!=l.end(); itr++) {
    cout<< *itr <<endl;
  }

  return 0;
}