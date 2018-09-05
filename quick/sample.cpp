#include <vector>
#include "clock.h"

using namespace std;

void quicksort(vector<int> &a, int l, int r) {
  if (l < r) {
    int p = a[(l+r)/2];
    int i = l-1, j = r+1;
    while (1) {
      while (a[++i] < p);
      while (a[--j] > p);
      if (i >= j) break;
      swap(a[i], a[j]);
    }
    quicksort(a, l, i-1);
    quicksort(a, j+1, r);
  }
}
void quicksort(vector<int> &a) {
  quicksort(a, 0, a.size()-1);
}
