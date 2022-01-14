#include "../utility/rt.h"

int b0;

#define A_OFFSET 0
#define B_OFFSET b0 * b0
#define Y_OFFSET b0 * b0 + b0
#define X_OFFSET b0 * b0 + b0 + b0

void ludcmp_trace(double* A, double* b, double* y, double* x) {

	int i, j, k;
	double w;
    vector<int> idx;

	for (i = 0; i < b0; i++) {
		for (j = 0; j <i; j++) {
            idx.clear(); idx.push_back(i); idx.push_back(j);
			w = A[i * b0 + j];
			rtTmpAccess(A_OFFSET + i * b0 + j, 0, 0, idx);
			for (k = 0; k < j; k++) {
                idx.clear(); idx.push_back(i); idx.push_back(j); idx.push_back(k);
				w -= A[i * b0 + k] * A[k * b0 + j];
				rtTmpAccess(A_OFFSET + i * b0 + k, 1, 0, idx);
				rtTmpAccess(A_OFFSET + k * b0 + j, 2, 0, idx);
			}
            
            idx.clear(); idx.push_back(i); idx.push_back(j);
			A[i * b0 + j] = w / A[j * b0 + j];
			rtTmpAccess(A_OFFSET + j * b0 + j, 3, 0, idx);
			rtTmpAccess(A_OFFSET + i * b0 + j, 4, 0, idx);
		}
		for (j = i; j < b0; j++) {
            idx.clear(); idx.push_back(i); idx.push_back(j);
			w = A[i * b0 + j];
			rtTmpAccess(A_OFFSET + i * b0 + j, 5, 0, idx);
			for (k = 0; k < i; k++) {
                idx.clear(); idx.push_back(i); idx.push_back(j); idx.push_back(k);
				w -= A[i * b0 + k] * A[k * b0 + j];
				rtTmpAccess(A_OFFSET + i * b0 + k, 6, 0, idx);
				rtTmpAccess(A_OFFSET + k * b0 + j, 7, 0, idx);
			}
            idx.clear(); idx.push_back(i); idx.push_back(j);
			A[i * b0 + j] = w;
			rtTmpAccess(A_OFFSET + i * b0 + j, 8, 0, idx);
		}
	}

	for (i = 0; i < b0; i++) {
        idx.clear(); idx.push_back(i);
		w = b[i];
		rtTmpAccess(B_OFFSET + i, 9, 1, idx);
		for (j = 0; j < i; j++) {
            idx.clear(); idx.push_back(i); idx.push_back(j);
			w -= A[i * b0 + j] * y[j];
			rtTmpAccess(A_OFFSET + i * b0 + j, 10, 0, idx);
			rtTmpAccess(Y_OFFSET + j, 11, 2, idx);
		}
        idx.clear(); idx.push_back(i);
		y[i] = w;
		rtTmpAccess(Y_OFFSET + i, 12, 2, idx);
	}
	for (i = b0-1; i >=0; i--) {
        idx.clear(); idx.push_back(i);
		w = y[i];
		rtTmpAccess(Y_OFFSET + i, 13, 2, idx);
		for (j = i+1; j < b0; j++) {
            idx.clear(); idx.push_back(i); idx.push_back(j);
			w -= A[i * b0 + j] * x[j];
			rtTmpAccess(A_OFFSET + i * b0 + j, 14, 0, idx);
			rtTmpAccess(X_OFFSET + j, 15, 3, idx);
		}
        idx.clear(); idx.push_back(i);
		x[i] = w / A[i * b0 + i];
		rtTmpAccess(A_OFFSET + i * b0 + i, 16, 0, idx);
		rtTmpAccess(X_OFFSET + i, 17, 3, idx);
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
    
	double* A = (double *)malloc(b0 * b0 *sizeof(double));
	double* b = (double *)malloc(b0 * sizeof(double));
	double* y = (double *)malloc(b0 * sizeof(double));
	double* x = (double *)malloc(b0 * sizeof(double));

	ludcmp_trace(A, b, y, x);

    dumpRIHistogram();
    
    return 0;
}
