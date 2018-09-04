#include <iostream>
#include <vector>
#include "clock.h"
#define init_matrix(w,h) Matrix(w,vector<long long>(h,0))

using namespace std;
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

int main(){
  Matrix A,B,C;
  input_matrix(A);
  input_matrix(B);

  if (A.size() != B.front().size()){
    cerr << "Error: Product is undefined." << endl;
    return 1;
  }

  C = init_matrix(B.size(),A.front().size());

  start_counter();
  // === BEGIN ===
  for (int x=0; x<B.size(); x++){
    for (int y=0; y<A.front().size(); y++){
      int sum=0;
      for (int k=0; k<A.size(); k++){
        sum += A[k][y]*B[x][k];
      }
      C[x][y] = sum;
    }
  }
  // === END ===
  print_counter();

  print_matrix(C);

  return 0;
}
