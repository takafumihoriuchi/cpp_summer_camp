#include <iostream>
#include <vector>
#include <thread>
#include "clock.h"
using namespace std;

#define init_matrix(w,h) Matrix(w,vector<long long>(h,0))

typedef vector<vector<long long>> Matrix;

void input_matrix(Matrix& m){
  int w,h;
  cin >> w >> h;
  m = init_matrix(w,h);
  for (int y=0; y<h; y++){
    for (int x=0; x<w; x++){
      cin >> m[x][y];
    }
  }
}

void print_matrix(Matrix& m){
  for (unsigned int y=0; y<m.front().size(); y++){
    for (unsigned int x=0; x<m.size(); x++){
      cout << m[x][y] << " ";
    }
    cout << endl;
  }
}

void partial_calc(Matrix A, Matrix B, Matrix &C, int y, int x)
{
  int sum = 0;
  int k;
  for (k=0; k<A.size(); k++) {
    sum += A[k][y] * B[x][k];
  }
  C[x][y] = sum;
  return;
}

int main(){
  Matrix A,B,C;
  input_matrix(A);
  input_matrix(B);

  if (A.size() != B.front().size()){
    cerr << "Error: Product is undefined." << endl;
    return 1;
  }

  C = init_matrix(B.size(), A.front().size());

  start_counter();
  // === BEGIN ===
  /*
  // for checking
  cout << "A:\n";
  print_matrix(A);
  cout << "------\n";
  cout << "B:\n";
  print_matrix(B);
  cout << "------\n";
  */

  int thread_n = B.size() * A.front().size();
  vector<thread> vecThreads(thread_n);

  for (int y=0; y<A.front().size(); y++){
    for (int x=0; x<B.size(); x++){   
      int idx = y*B.size()+x;
      vecThreads[idx] = thread([=, &C] {
        partial_calc(A, B, C, y, x);
      });
    }
  }
  for (int i=0; i<thread_n; i++) {
    vecThreads[i].join();
  }
  
  // === END ===
  print_counter();

  print_matrix(C);

  return 0;
}

/*

1 2    1 4 2
3 4    5 3 6
5 6

1+10  4+6 2+12

つまり、思っていたものと、row, col の順序が逆

*/