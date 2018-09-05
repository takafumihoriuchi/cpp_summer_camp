#include <iostream>
#include <thread>
#include <vector>
#include <algorithm>
#include "clock.h"

using namespace std;

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
  thread t1(quicksort_, ref(a), 0, (a.size()-1)/2);
  thread t2(quicksort_, ref(a), (a.size()-1)/2+1, a.size()-1);
  t1.join();
  t2.join();
  inplace_merge(a.begin(), a.begin()+(a.size()-1)/2+1, a.end());
}
