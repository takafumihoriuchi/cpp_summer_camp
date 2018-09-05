#include <iostream>
#include <thread>
#include <vector>
#include <algorithm>
#include "clock.h"

using namespace std;
void print_vec(vector<int> &a) {
  for(auto i = a.begin(); i!=a.end(); i++) {
    cout<< *i << " ";
  }
  cout<<endl;  
}

void quicksort_(vector<int> &a, int l, int r) {
  if (l < r) {
    int p = a[(l+r)/2];
    int i = l-1, j = r+1;
    while (1) {
      // thread t([&]{while (a[++i] < p);});
      // thread s([&]{while (a[--j] > p);});
      while (a[++i] < p);
      while (a[--j] > p);
      // t.join();
      // s.join();
      if (i >= j) break;
      swap(a[i], a[j]);
    }
    // thread t1(quicksort, ref(a), l, i-1);
    // thread t2(quicksort, ref(a), j+1, r);
    // t1.join();
    // t2.join();
    quicksort_(a, l, i-1);
    quicksort_(a, j+1, r);
  }
}
void quicksort(vector<int> &a) {
  int len = a.size()-1;

  thread t1(quicksort_, ref(a), 0, len/4);
  thread t2(quicksort_, ref(a), len/4+1, (len*2)/4);
  thread t3(quicksort_, ref(a), (len*2)/4+1, (len*3)/4);
  thread t4(quicksort_, ref(a), (len*3)/4+1, len);
  t1.join();
  t2.join();
  t3.join();
  t4.join();
  inplace_merge(a.begin(), a.begin()+len/4+1, a.begin()+len/2+1);
  inplace_merge(a.begin()+len/2+1, a.begin()+(len*3)/4+1, a.end());
  inplace_merge(a.begin(), a.begin()+len/2+1, a.end());
}
