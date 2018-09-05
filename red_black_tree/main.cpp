#include<functional>
#include<iostream>
#include<vector>
#include "clock.h"
// #include"rbtree.cpp"

using namespace std;

function<void()> insert_vec(vector<int>&);
void tree_print();

int main(void) {
  int n;
  int x;
  // rbtree<int> t;
  vector<int> v;
  cin>>n;
  for(int i=0; i<n; i++) {
    cin>>x;
    v.push_back(x);
  }
  start_counter();
  function<void()> print = insert_vec(v);
  print_counter();
  // tree_print();
  print();
}
