#include "../utility/rt.h"

int b0;

#define X_OFFSET 0
#define B_OFFSET b0
#define L_OFFSET b0 + b0

void trisolv_trace(double* x, double* b, double* L) {

	int i, j;
    vector<int> idx;

	for (i = 0; i < b0; i++) {
        idx.clear(); idx.push_back(i);
		x[i] = b[i];
        rtTmpAccess(B_OFFSET + i, 0, 1, idx);
		rtTmpAccess(X_OFFSET + i, 1, 0, idx);
        
		for (j = 0; j <i; j++) {
            idx.clear(); idx.push_back(i); idx.push_back(j);
			x[i] -= L[i * b0 + j] * x[j];
			rtTmpAccess(L_OFFSET + i * b0 + j, 2, 2, idx);
			rtTmpAccess(X_OFFSET + j, 3, 0, idx);
			rtTmpAccess(X_OFFSET + i, 4, 0, idx);
			rtTmpAccess(X_OFFSET + i, 5, 0, idx);
		}
        idx.clear(); idx.push_back(i);
		x[i] = x[i] / L[i * b0 + i];
		rtTmpAccess(X_OFFSET + i, 6, 0, idx);
		rtTmpAccess(L_OFFSET + i * b0 + i, 7, 2, idx);
		rtTmpAccess(X_OFFSET + i, 8, 0, idx);
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
    
	double* x = (double *)malloc(b0 * sizeof(double));
	double* b = (double *)malloc(b0 * sizeof(double));
	double* L = (double *)malloc(b0 * b0 * sizeof(double));

	trisolv_trace(x, b, L);

    dumpRIHistogram();
    
    return 0;
}

