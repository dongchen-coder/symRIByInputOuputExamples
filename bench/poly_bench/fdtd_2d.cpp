#include "../utility/rt.h"

int b0;
int b1;
int b2;

#define FICT_OFFSET 0
#define EY_OFFSET b0
#define EX_OFFSET b0 + b1 * b2
#define HZ_OFFSET b0 + b1 * b2 + b1 * b2


void fdtd_2d_trace(double* _fict_, double* ey, double* ex, double* hz) {

	int t, i, j;
    vector<int> idx;
    
	for(t = 0; t < b0; t++) {
		for (j = 0; j < b2; j++) {
            idx.clear(); idx.push_back(i); idx.push_back(j);
			ey[0 * b2 + j] = _fict_[t];
			rtTmpAccess(FICT_OFFSET + t, 0, 0, idx);
			rtTmpAccess(EY_OFFSET + 0 * b2 + j, 1, 1, idx);
		}

		for (i = 1; i < b1; i++)
			for (j = 0; j < b2; j++) {
                idx.clear(); idx.push_back(i); idx.push_back(j);
				ey[i * b2 + j] = ey[i * b2 + j] - 0.5 * (hz[i * b2 + j] - hz[(i-1) * b2 + j]);
				rtTmpAccess(EY_OFFSET + i * b2 + j, 2, 1, idx);
				rtTmpAccess(HZ_OFFSET + i * b2 + j, 3, 2, idx);
				rtTmpAccess(HZ_OFFSET + (i-1) * b2 + j, 4, 2, idx);
				rtTmpAccess(EY_OFFSET + i * b2 + j, 5, 1, idx);
			}

		for (i = 0; i < b1; i++)
			for (j = 1; j < b2; j++) {
                idx.clear(); idx.push_back(i); idx.push_back(j);
				ex[i * b2 + j] = ex[i * b2 + j] - 0.5 * (hz[i * b2 + j]-hz[i * b2 + j - 1]);
				rtTmpAccess(EX_OFFSET + i * b2 + j, 6, 3, idx);
				rtTmpAccess(HZ_OFFSET + i * b2 + j, 7, 2, idx);
				rtTmpAccess(HZ_OFFSET + i * b2 + j - 1, 8, 2, idx);
				rtTmpAccess(EX_OFFSET + i * b2 + j, 9, 3, idx);
			}

		for (i = 0; i < b1 - 1; i++)
			for (j = 0; j < b2 - 1; j++) {
                idx.clear(); idx.push_back(i); idx.push_back(j);
				hz[i * b2 + j] = hz[i * b2 + j] - 0.7 * (ex[i * b2 + j + 1] - ex[i * b2 + j] + ey[(i+1) * b2 + j] - ey[i * b2 + j]);
    			rtTmpAccess(HZ_OFFSET + i * b2 + j, 10, 2, idx);
				rtTmpAccess(EX_OFFSET + i * b2 + j + 1, 11, 3, idx);
				rtTmpAccess(EX_OFFSET + i * b2 + j, 12, 3, idx);
				rtTmpAccess(EY_OFFSET + (i+1) * b2 + j, 13, 1, idx);
				rtTmpAccess(EY_OFFSET + i * b2 + j, 14, 1, idx);
				rtTmpAccess(HZ_OFFSET + i * b2 + j, 15, 2, idx);
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
    
	double* _fict_ = (double *)malloc(b0 * sizeof(double));
	double* ey = (double *)malloc(b1 * b2 * sizeof(double));
	double* ex = (double *)malloc(b1 * b2 * sizeof(double));
	double* hz = (double *)malloc(b1 * b2 * sizeof(double));

	fdtd_2d_trace(_fict_, ey, ex, hz);

    dumpRIHistogram();
    
	return 0;
}
