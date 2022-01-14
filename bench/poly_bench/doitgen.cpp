#include "../utility/rt.h"

int b0;
int b1;
int b2;

#define SUM_OFFSET 0
#define A_OFFSET b2
#define C4_OFFSET b2 + b0 * b1 * b2

void doitgen_trace(double* sum, double* A, double* C4) {

	int r, q, p, s;
    vector<int> idx;

	for (r = 0; r < b0; r++) {
		for (q = 0; q < b1; q++)  {
			for (p = 0; p < b2; p++)  {
                idx.clear(); idx.push_back(r); idx.push_back(q); idx.push_back(p);
				sum[p] = 0.0;
				rtTmpAccess(SUM_OFFSET + p, 0, 0, idx);
				for (s = 0; s < b2; s++) {
                    idx.clear(); idx.push_back(r); idx.push_back(q); idx.push_back(p); idx.push_back(s);
					sum[p] += A[r * b1 * b2 + q * b2 + s] * C4[s * b2 + p];
					rtTmpAccess(A_OFFSET + r * b1 * b2 + q * b2 + s, 1, 1, idx);
					rtTmpAccess(C4_OFFSET + s * b2 + p, 2, 2, idx);
					rtTmpAccess(SUM_OFFSET + p, 3, 0, idx);
					rtTmpAccess(SUM_OFFSET + p, 4, 0, idx);
				}
			}
			for (p = 0; p < b2; p++) {
                idx.clear(); idx.push_back(r); idx.push_back(q); idx.push_back(p);
				A[r * b1 * b2 + q * b2 + p] = sum[p];
				rtTmpAccess(SUM_OFFSET + p, 5, 0, idx);
				rtTmpAccess(A_OFFSET + r * b1 * b2 + q * b2 + p, 6, 1, idx);
			}
    	}
	}

}

int main(int argc, char* argv[]) {
	
    if (argc != 4) {
        cout << "This benchmark needs 3 loop bounds" << endl;
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
    b2 = stoi(argv[3]);
    
	double * sum = (double *) malloc(b2 * sizeof(double));
	double * A = (double *) malloc(b0 * b1 * b2 * sizeof(double));
	double * C4 = (double *) malloc(b2 * b2);
	
	doitgen_trace(sum, A, C4);

    dumpRIHistogram();
    
	return 0;
}


