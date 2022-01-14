#include "../utility/rt.h"

int b1;
int b0;

#define A_OFFSET 0
#define B_OFFSET b1 * b1
#define C_OFFSET b1 * b1 + b1 * b0

void symm_trace(double* A, double* B, double* C, double alpha, double beta) {
	
	int i, j, k;	
	double temp2;
    vector<int> idx;

	for (i = 0; i < b1; i++) {
		for (j = 0; j < b0; j++ ) {
			temp2 = 0;
			for (k = 0; k < i; k++) {
                idx.clear(); idx.push_back(i); idx.push_back(j); idx.push_back(k);
				C[k * b0 + j] += alpha*B[i * b0 + j] * A[i * b1 + k];
				temp2 += B[k * b0 + j] * A[i * b1 + k];
                rtTmpAccess(B_OFFSET + i * b0 + j, 0, 1, idx);
                rtTmpAccess(A_OFFSET + i * b1 + k, 1, 2, idx);
                rtTmpAccess(C_OFFSET + k * b0 + j, 2, 0, idx);
                rtTmpAccess(C_OFFSET + k * b0 + j, 3, 0, idx);
                rtTmpAccess(B_OFFSET + k * b0 + j, 4, 1, idx);
                rtTmpAccess(A_OFFSET + i * b1 + k, 5, 2, idx);
			}
            idx.clear(); idx.push_back(i); idx.push_back(j);
            
			C[i * b0 + j] = beta * C[i * b0 + j] + alpha*B[i * b0 + j] * A[i * b1 + i] + alpha * temp2;
            rtTmpAccess(C_OFFSET + i * b0 + j, 6, 0, idx);
            rtTmpAccess(B_OFFSET + i * b0 + j, 7, 1, idx);
            rtTmpAccess(A_OFFSET + i * b1 + i, 8, 2, idx);
            rtTmpAccess(C_OFFSET + i * b0 + j, 9, 0, idx);
		}
	}
	return;
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
	double* B = (double *)malloc(b1 * b0 * sizeof(double));
	double* C = (double *)malloc(b1 * b0 * sizeof(double));
	double alpha = 0.2;
	double beta = 0.8;

	symm_trace(A, B, C, alpha, beta);

    dumpRIHistogram();
    
	return 0;
}
