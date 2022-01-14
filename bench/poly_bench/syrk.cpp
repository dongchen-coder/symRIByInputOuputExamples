#include "../utility/rt.h"

int b0;
int b1;

#define A_OFFSET 0
#define C_OFFSET b0 * b1

void syrk_trace(double alpha, double beta, double* A, double* C)
{
    int i, j, k;
    vector<int> idx;
    
    /*  C := alpha*A*A' + beta*C */
    for (i = 0; i < b0; i++)
    {
        for (j = 0; j < b0; j++)
        {
            idx.clear(); idx.push_back(i); idx.push_back(j);
            C[i * b0 + j] = C[i * b0 + j] * beta;
			rtTmpAccess(C_OFFSET + i * b0 + j, 0, 0, idx);
			rtTmpAccess(C_OFFSET + i * b0 + j, 1, 0, idx);
        }
    }
    
    for (i = 0; i < b0; i++)
    {
        for (j = 0; j < b0; j++)
        {
            for (k = 0; k < b1; k++)
            {
                idx.clear(); idx.push_back(i); idx.push_back(j); idx.push_back(k);
                C[i * b0 + j] = C[i * b0 + j] + alpha * A[i * b1 + k] * A[j * b1 + k];
				rtTmpAccess(A_OFFSET + i * b1 + k, 2, 1, idx);
				rtTmpAccess(A_OFFSET + j * b1 + k, 3, 1, idx);
				rtTmpAccess(C_OFFSET + i * b0 + j, 4, 0, idx);
				rtTmpAccess(C_OFFSET + i * b0 + j, 5, 0, idx);
            }
        }
    }
    return;
}

int main(int argc, char const *argv[])
{
    
    if (argc != 3) {
        cout << "This benchmark needs 2 loop bounds" << endl;
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
    
    double* A = (double*)malloc( (b0*b1) * sizeof(double));
    double* C = (double*)malloc( (b0*b0) * sizeof(double));

    double alpha = 0.0;
    double beta = 1.5;

    syrk_trace(alpha, beta, A, C);

    dumpRIHistogram();
    
    return 0;
}
