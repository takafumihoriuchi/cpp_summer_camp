#include <vector>
#include <thread>

using namespace std;
typedef vector<vector<long long>> Matrix;


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


void product(Matrix& A, Matrix& B, Matrix& C)
{
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

}
