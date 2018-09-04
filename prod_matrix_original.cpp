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

/*
#include <iostream>
#include <vector>
#include <thread>
#include "clock.h"
using namespace std;

#define init_matrix(row, col) Matrix(row, vector<long long>(col, 0))

typedef vector<vector<long long>> Matrix;

void input_matrix(Matrix &mat) {
	int row, col;
	cin >> row >> col;
	mat = init_matrix(row, col);
	for (int r = 0; r < row; r++) {
		for (int c = 0; c < col; c++) {
			cin >> mat[r][c];
		}
	}
}

void print_matrix(Matrix &mat) {
	for (unsigned int row = 0; row < mat.front().size(); row++) {
		for (unsigned int col = 0; col < mat.size(); col++) {
			cout << mat[row][col] << " ";
		}
		cout << endl;
	}
}

void partial_calc(Matrix A, Matrix B, Matrix &C, int row, int col)
{
	int sum = 0;
	int k;
	for (k=0; k<B.size(); k++) {
		sum += A[row][k] * B[k][col];
	}
	C[row][col] = sum;
	return;
}

int main()
{
	Matrix A, B, C;
	input_matrix(A);
	input_matrix(B);

	if (A.size() != B.front().size()) {
		cerr << "Error: Product is undefined." << endl;
		return 1;
	}

	C = init_matrix(A.size(), B.front().size());

	start_counter();
	// === BEGIN ===
	int thread_n = A.size() * B.front().size();

	cout << "A.size(): " << A.size() << endl;
	cout << "A.front().size(): " << A.front().size() << endl;
	print_matrix(A);
	cout << "B.size(): " << B.size() << endl;
	cout << "B.front().size(): " << B.front().size() << endl;
	print_matrix(B);
	
	vector<thread> vecThreads(thread_n);
	int row, col;
	for (row=0; row<A.size(); row++) {
		for (col=0; col<B.front().size(); col++) {
			int idx = row*2+col;
			vecThreads[idx] = thread([=, &C] {
				partial_calc(A, B, C, row, col);
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
*/