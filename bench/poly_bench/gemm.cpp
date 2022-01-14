#include "../utility/rt.h"

int b0;
int b1;
int b2;

#define A_OFFSET 0
#define B_OFFSET b0 * b2
#define C_OFFSET b0 * b2 + b2 * b1

void gemm_trace(double alpha, double beta, double* A, double* B, double* C) {
    int i,j,k;
    vector<int> idx;
    
    for (i = 0; i < b0; i++)
    {
        for (j = 0; j < b1; j++)
        {
            idx.clear(); idx.push_back(i); idx.push_back(j);
            C[i * b1 + j] *= beta;
			rtTmpAccess(C_OFFSET + i * b1 + j, 0, 0, idx);
			rtTmpAccess(C_OFFSET + i * b1 + j, 1, 0, idx);

            for (k = 0; k < b2; k++)
            {
                idx.clear(); idx.push_back(i); idx.push_back(j); idx.push_back(k);
                C[i * b1 + j] += alpha * A[i * b2 + k] * B[k * b1 + j];
                rtTmpAccess(A_OFFSET + i * b2 + k, 2, 1, idx);
                rtTmpAccess(B_OFFSET + k * b1 + j, 3, 2, idx);
				rtTmpAccess(C_OFFSET + i * b1 + j, 4, 0, idx);
				rtTmpAccess(C_OFFSET + i * b1 + j, 5, 0, idx);
            }
        }
    }
    return;
}

int main(int argc, char* argv[]) {
    
    if (argc != 4) {
        cout << "This benchmark needs 3 loop bounds" << endl;
        return 0;
    }
    for (int i = 1; i < argc; i++) {
        if (!isdigit(argv[i][0])) {
            cout << "arguments must be integer" << endl;
            return 0;
        }
    }
    
    b0 = stoi(argv[1]);
    b1 = stoi(argv[2]);
    b2 = stoi(argv[3]);
    
    double* A = (double*)malloc(b0 * b2 * sizeof(double));
    double* B = (double*)malloc(b2 * b1 * sizeof(double));
    double* C = (double*)malloc(b0 * b1 * sizeof(double));

    for (int i = 0; i < b0*b2; ++i)
    {
        A[i] = i % 256;
    }

    for (int i = 0; i < b2 * b1; ++i)
    {
        B[i] = i % 48;
    }

    double alpha = 1.0;
    double beta = 1.5;

    gemm_trace(alpha, beta, A, B, C);

    dumpRIHistogram();
    
    return 0;
}
