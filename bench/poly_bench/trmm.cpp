#include "../utility/rt.h"

int b0;
int b1;

#define A_OFFSET 0
#define B_OFFSET b0 * b0

void trmm_trace(double* A, double* B, double alpha) {

	int i, j, k;
    vector<int> idx;

	for (i = 0; i < b0; i++) {
		for (j = 0; j < b1; j++) {
			for (k = i+1; k < b0; k++) {
                idx.clear(); idx.push_back(i); idx.push_back(j); idx.push_back(k);
				B[i * b1 + j] += A[k * b0 + i] * B[k * b1 + j];
				rtTmpAccess(A_OFFSET + k * b0 + i, 0, 0, idx);
				rtTmpAccess(B_OFFSET + k * b1 + j, 1, 1, idx);
				rtTmpAccess(B_OFFSET + i * b1 + j, 2, 1, idx);
				rtTmpAccess(B_OFFSET + i * b1 + j, 3, 1, idx);
			}
            idx.clear(); idx.push_back(i); idx.push_back(j);
			B[i * b1 + j] = alpha * B[i * b1 + j];
     		rtTmpAccess(B_OFFSET + i * b1 + j, 4, 1, idx);
			rtTmpAccess(B_OFFSET + i * b1 + j, 5, 1, idx);
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
    
	double* A = (double *)malloc(b0 * b0 * sizeof(double));
	double* B = (double *)malloc(b0 * b1 * sizeof(double));
	double alpha = 0.2;

	trmm_trace(A, B, alpha);
 
    dumpRIHistogram();
    
    return 0;
}
