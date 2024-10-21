#include "../utility/rt.h"

int b1;
int b0;

#define A_OFFSET 0
#define B_OFFSET b0 * b0

void jacobi_2d_trace(double* A, double* B) {

	int t, i, j;
    vector<int> idx;

	for (t = 0; t < b1; t++) {
		for (i = 1; i < b0 - 1; i++) {
			for (j = 1; j < b0 - 1; j++) {
                idx.clear(); idx.push_back(t); idx.push_back(i); idx.push_back(j);
				B[i * b0 + j] = 0.2 * (A[i * b0 + j] + A[i * b0 + j-1] + A[i * b0 + 1+j] + A[(1+i) * b0 + j] + A[(i-1) * b0 + j]);
				rtTmpAccess(A_OFFSET + i * b0 + j, 0, 0, idx);
				rtTmpAccess(A_OFFSET + i * b0 + j-1, 1, 0, idx);
				rtTmpAccess(A_OFFSET + i * b0 + 1+j, 2, 0, idx);
				rtTmpAccess(A_OFFSET + (1+i) * b0 + j, 3, 0, idx);
				rtTmpAccess(A_OFFSET + (i-1) * b0 + j, 4, 0, idx);
				rtTmpAccess(B_OFFSET + i * b0 + j, 5, 1, idx);
			}
		}
		for (i = 1; i < b0 - 1; i++) {
			for (j = 1; j < b0 - 1; j++) {
                idx.clear(); idx.push_back(t); idx.push_back(i); idx.push_back(j);
				A[i * b0 + j] = 0.2 * (B[i * b0 + j] + B[i * b0 + j-1] + B[i * b0 + 1+j] + B[(1+i) * b0 + j] + B[(i-1) * b0 + j]);
				rtTmpAccess(B_OFFSET + i * b0 + j, 6, 1, idx);
				rtTmpAccess(B_OFFSET + i * b0 + j-1, 7, 1, idx);
				rtTmpAccess(B_OFFSET + i * b0 + 1+j, 8, 1, idx);
				rtTmpAccess(B_OFFSET + (1+i) * b0 + j, 9, 1, idx);
				rtTmpAccess(B_OFFSET + (i-1) * b0 + j, 10, 1, idx);
				rtTmpAccess(A_OFFSET + i * b0 + j, 11, 0, idx);
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
    
	double* A = (double *)malloc(b0 * b0 * sizeof(double));
	double* B = (double *)malloc(b0 * b0 * sizeof(double));

	jacobi_2d_trace(A, B);

    dumpRIHistogram();
    
    return 0;
}
