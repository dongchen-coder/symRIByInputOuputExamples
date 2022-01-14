#include "../utility/rt.h"

int b0;
int b1;

#define A_OFFSET 0
#define B_OFFSET b1 * b1
#define C_OFFSET b1 * b1 + b0 * b1

void syr2k_trace(double* A, double* B, double* C, double alpha, double beta) {

	int i, j, k;
    vector<int> idx;
    
	for (i = 0; i < b0; i++) {
		for (j = 0; j <= i; j++) {
            idx.clear(); idx.push_back(i); idx.push_back(j);
			C[i * b0 + j] *= beta;
			rtTmpAccess(C_OFFSET + i * b0 + j, 0, 0, idx);
			rtTmpAccess(C_OFFSET + i * b0 + j, 1, 0, idx);
		}
		for (k = 0; k < b1; k++) {
			for (j = 0; j <= i; j++) {
                idx.clear(); idx.push_back(i); idx.push_back(k); idx.push_back(j);
				C[i * b0 + j] += A[j * b1 + k]*alpha*B[i * b1 + k] + B[j * b1 + k]*alpha*A[i * b0 + k];
				rtTmpAccess(A_OFFSET + j * b1 + k, 2, 1, idx);
				rtTmpAccess(B_OFFSET + i * b1 + k, 3, 2, idx);
				rtTmpAccess(B_OFFSET + j * b1 + k, 4, 2, idx);
				rtTmpAccess(A_OFFSET + i * b0 + k, 5, 1, idx);
				rtTmpAccess(C_OFFSET + i * b0 + j, 6, 0, idx);
				rtTmpAccess(C_OFFSET + i * b0 + j, 7, 0, idx);
			}
		}
	}
}

int main(int argc, char* argv[]) {

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
    
	double* A = (double *)malloc(b1 * b1 * sizeof(double));
	double* B = (double *)malloc(b0 * b1 * sizeof(double));
	double* C = (double *)malloc(b0 * b0 * sizeof(double));
	double alpha = 0.2;
	double beta = 0.8;

	syr2k_trace(A, B, C, alpha, beta);

    dumpRIHistogram();
    
	return 0;
}
