#include "../utility/rt.h"
#include <math.h>

int b0;
int b1;

#define A_OFFSET 0
#define R_OFFSET b1 * b0
#define Q_OFFSET b1 * b0 + b1 * b1

void gramschmidt_trace(double* A, double* R, double* Q) {

	int k, i, j;
	double nrm;
    vector<int> idx;

	for (k = 0; k < b1; k++) {
		nrm = 0.0;
		for (i = 0; i < b0; i++) {
            idx.clear(); idx.push_back(k); idx.push_back(i);
			nrm += A[i * b1 + k] * A[i * b1 + k];
			rtTmpAccess(A_OFFSET + i * b1 + k, 0, 0, idx);
			rtTmpAccess(A_OFFSET + i * b1 + k, 1, 0, idx);
		}
        idx.clear(); idx.push_back(k);
		R[k * b1 + k] = sqrt(nrm);
		rtTmpAccess(R_OFFSET + k * b1 + k, 2, 1, idx);
		for (i = 0; i < b0; i++) {
            idx.clear(); idx.push_back(k); idx.push_back(i);
			Q[i * b1 + k] = A[i * b1 + k] / R[k * b1 + k];
			rtTmpAccess(A_OFFSET + i * b1 + k, 3, 0, idx);
			rtTmpAccess(R_OFFSET + k * b1 + k, 4, 1, idx);
			rtTmpAccess(Q_OFFSET + i * b1 + k, 5, 2, idx);
		}
		for (j = k + 1; j < b1; j++) {
            idx.clear(); idx.push_back(k); idx.push_back(j);
			R[k * b1 + j] = 0.0;
			rtTmpAccess(R_OFFSET + k * b1 + j, 6, 1, idx);
			for (i = 0; i < b0; i++) {
                idx.clear(); idx.push_back(k); idx.push_back(j); idx.push_back(i);
				R[k * b1 + j] += Q[i * b1 + k] * A[i * b1 + j];
				rtTmpAccess(Q_OFFSET + i * b1 + k, 7, 2, idx);
				rtTmpAccess(A_OFFSET + i * b1 + j, 8, 0, idx);
				rtTmpAccess(R_OFFSET + k * b1 + j, 9, 1, idx);
                rtTmpAccess(R_OFFSET + k * b1 + j, 10, 1, idx);
			}
			for (i = 0; i < b0; i++) {
                idx.clear(); idx.push_back(k); idx.push_back(j); idx.push_back(i);
        		A[i * b1 + j] = A[i * b1 + j] - Q[i * b1 + k] * R[k * b1 + j];
				rtTmpAccess(A_OFFSET + i * b1 + j, 11, 0, idx);
				rtTmpAccess(Q_OFFSET + i * b1 + k, 12, 2, idx);
				rtTmpAccess(R_OFFSET + k * b1 + j, 13, 1, idx);
				rtTmpAccess(A_OFFSET + i * b1 + j, 14, 0, idx);
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
    
	double * A = (double *)malloc(b1 * b0 * sizeof(double));
	double * R = (double *)malloc(b1 * b1 * sizeof(double));
	double * Q = (double *)malloc(b0 * b1 * sizeof(double));

	gramschmidt_trace(A, R, Q);

    dumpRIHistogram();
    
	return 0;
}
