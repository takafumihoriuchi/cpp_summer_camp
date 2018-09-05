#include <vector>
#include <thread>

using namespace std;
typedef vector<vector<long long>> Matrix;

void product(Matrix& A, Matrix& B, Matrix& C)
{
    int n_row = A.front().size();
    int n_col = B.size();


    thread t1 = thread([=, &C] {

        for (int y=0; y<n_row/2; y++) {
            for (int x=0; x<n_col; x++) {
                int sum = 0;
                int num_elem = A.size();
                for (int k=0; k<num_elem; k++)
                    sum += A[k][y] * B[x][k];
                C[x][y] = sum;
            }
        }

    });

    thread t2 = thread([=, &C] {

        for (int y=n_row/2; y<n_row; y++) {
            for (int x=0; x<n_col; x++) {
                int sum = 0;
                int num_elem = A.size();
                for (int k=0; k<num_elem; k++)
                    sum += A[k][y] * B[x][k];
                C[x][y] = sum;
            }
        }

    });

    t1.join();
    t2.join();

}

/*
void product(Matrix& A, Matrix& B, Matrix& C)
{
	int n_row = A.front().size();
    int n_col = B.size();
	vector<thread> vecThreads_row(n_row);
    vector<thread> vecThreads_col(n_col);

	for (int y=0; y<n_row; y++) {
        vecThreads_row[y] = thread([=, &C] {
            
            
            for (int x=0; x<n_col; x++) {
                vecThreads_col[x] = thread([=, &C] {
                    int sum = 0;
                    int num_elem = A.size();
                    for (int k=0; k<num_elem; k++)
                        sum += A[k][y] * B[x][k];
                    C[x][y] = sum;
                });
            }
            for (int i=0; i<n_col; i++) {
                vecThreads_col[i].join();
            }


        });
	}

	for (int i=0; i<n_row; i++) {
		vecThreads_row[i].join();
	}

}
*/