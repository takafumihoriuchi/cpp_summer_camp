#include <vector>
#include <thread>

using namespace std;
typedef vector<vector<long long>> Matrix;

void product(Matrix& A, Matrix& B, Matrix& C)
{
    int n_row = A.front().size();
    int n_col = B.size();

    int num_threads = 8;
    int rows_per_thread = n_row / num_threads;

    vector<thread> vecThreads(num_threads-1);
    for (int i=0; i<(num_threads-1); i++) {
        vecThreads[i] = thread([=, &C] {
            int begin_row = rows_per_thread * i;
            int end_row = rows_per_thread * (i+1);
            for (int y=begin_row; y<end_row; y++) {
                for (int x=0; x<n_col; x++) {
                    int sum = 0;
                    int num_elem = A.size();
                    for (int k=0; k<num_elem; k++)
                        sum += A[k][y] * B[x][k];
                    C[x][y] = sum;
                }
            }
        });
    }

    // process the last batch of rows with main_thread
    int i = num_threads - 1;
    int begin_row = rows_per_thread * i;
    int end_row = n_row;
    for (int y=begin_row; y<end_row; y++) {
        for (int x=0; x<n_col; x++) {
            int sum = 0;
            int num_elem = A.size();
            for (int k=0; k<num_elem; k++)
                sum += A[k][y] * B[x][k];
            C[x][y] = sum;
        }
    }

    for (int i=0; i<(num_threads-1); i++) {
        vecThreads[i].join();
    }

    return;
}
