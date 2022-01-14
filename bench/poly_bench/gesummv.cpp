#include "../utility/rt.h"

int b0;

#define A_OFFSET 0
#define B_OFFSET b0 * b0
#define TMP_OFFSET b0 * b0 + b0 * b0
#define X_OFFSET b0 * b0 + b0 * b0 + b0
#define Y_OFFSET b0 * b0 + b0 * b0 + b0 + b0

void gesummv_trace(double alpha, double beta, double* A, double* B, double* tmp, double* x, double* y)
{
	int i, j;    
    vector<int> idx;
    
	for (i = 0; i < b0; i++)
    {
        idx.clear(); idx.push_back(i);
        tmp[i] = 0;
        y[i] = 0;

		rtTmpAccess(TMP_OFFSET + i, 0, 0, idx);
		rtTmpAccess(Y_OFFSET + i, 1, 1, idx);
	
        for (j = 0; j < b0; j++)
        {
            idx.clear(); idx.push_back(i); idx.push_back(j);
            tmp[i] = A[i * b0 + j] * x[j] + tmp[i];
            y[i] = B[i * b0 + j] * x[j] + y[i];
        	rtTmpAccess(A_OFFSET + i * b0 + j, 2, 2, idx);
			rtTmpAccess(X_OFFSET + j, 3, 3, idx);
			rtTmpAccess(TMP_OFFSET + i, 4, 0, idx);
			rtTmpAccess(TMP_OFFSET + i, 5, 0, idx);
			rtTmpAccess(B_OFFSET + i * b0 + j, 6, 4, idx);
            rtTmpAccess(X_OFFSET + j, 7, 3, idx);
            rtTmpAccess(Y_OFFSET + i, 8, 1, idx);
            rtTmpAccess(Y_OFFSET + i, 9, 1, idx);
		}

        idx.clear(); idx.push_back(i);
        y[i] = alpha * tmp[i] + beta * y[i];
        
		rtTmpAccess(TMP_OFFSET + i, 10, 0, idx);
		rtTmpAccess(Y_OFFSET + i, 11, 1, idx);
		rtTmpAccess(Y_OFFSET + i, 12, 1, idx);
    }

	return;
}

int main(int argc, char const *argv[])
{
    if (argc != 2) {
        cout << "This benchmark needs 1 loop bounds" << endl;
        return 0;
    }
    for (int i = 1; i < argc; i++) {
        if (!isdigit(argv[i][0])) {
            cout << "arguments must be integer" << endl;
            return 0;
        }
    }
    
    b0 = stoi(argv[1]);
    
    double* A = (double*)malloc( (b0*b0) * sizeof(double));
    double* x = (double*)malloc( b0 * sizeof(double));
    double* tmp = (double*)malloc( b0 * sizeof(double));
    double* B = (double*)malloc( (b0*b0) * sizeof(double));
    double* y = (double*)malloc( b0 * sizeof(double));

    for (int i = 0; i < b0; ++i)
    {
        x[i] = i % 256;
    }

    for (int i = 0; i < b0*b0; ++i)
    {
        A[i] = i / 10;
        B[i] = i / 25;
    }

    double alpha = 1.0;
    double beta = 1.5;

    gesummv_trace(alpha, beta, A, B, tmp, x, y);
  
    dumpRIHistogram();
    
    return 0;
}
