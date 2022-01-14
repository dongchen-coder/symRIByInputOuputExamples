#include "../utility/rt.h"

int b0;

#define A_OFFSET 0

void lu_trace(double* A) {

	int i, j, k;
    vector<int> idx;

	for (i = 0; i < b0; i++) {
		for (j = 0; j <i; j++) {
			for (k = 0; k < j; k++) {
                idx.clear(); idx.push_back(i); idx.push_back(j); idx.push_back(k);
				A[i * b0 + j] -= A[i * b0 + k] * A[k * b0 + j];
				rtTmpAccess(A_OFFSET + i * b0 + k, 0, 0, idx);
				rtTmpAccess(A_OFFSET + k * b0 + j, 1, 0, idx);
				rtTmpAccess(A_OFFSET + i * b0 + j, 2, 0, idx);
				rtTmpAccess(A_OFFSET + i * b0 + j, 3, 0, idx);
			}
            idx.clear(); idx.push_back(i); idx.push_back(j);
			A[i * b0 + j] /= A[j * b0 + j];
			rtTmpAccess(A_OFFSET + j * b0 + j, 4, 0, idx);
			rtTmpAccess(A_OFFSET + i * b0 + j, 5, 0, idx);
			rtTmpAccess(A_OFFSET + i * b0 + j, 6, 0, idx);
		}
		for (j = i; j < b0; j++) {
			for (k = 0; k < i; k++) {
                idx.clear(); idx.push_back(i); idx.push_back(j); idx.push_back(k);
				A[i * b0 + j] -= A[i * b0 + k] * A[k * b0 + j];
				rtTmpAccess(A_OFFSET + i * b0 + k, 7, 0, idx);
				rtTmpAccess(A_OFFSET + k * b0 + j, 8, 0, idx);
				rtTmpAccess(A_OFFSET + i * b0 + j, 9, 0, idx);
				rtTmpAccess(A_OFFSET + i * b0 + j, 10, 0, idx);
			}
		}
	}
}

int main(int argc, char* argv[]) {

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
    
	double* A = (double *)malloc(b0 * b0 * sizeof(double));

	lu_trace(A);

    dumpRIHistogram();
    
    return 0;
}
