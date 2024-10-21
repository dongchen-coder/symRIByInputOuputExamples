#include "../utility/rt.h"

int b1;
int b0;

#define A_OFFSET 0

void seidel_2d_trace(double* A) {

	int t, i, j;
    vector<int> idx;

	for (t = 0; t <= b1 - 1; t++)
		for (i = 1; i<= b0 - 2; i++)
			for (j = 1; j <= b0 - 2; j++) {
                idx.clear(); idx.push_back(t); idx.push_back(i); idx.push_back(j);
				A[i * b0 + j] = (A[(i-1) * b0 + j-1] + A[(i-1) * b0 + j] + A[(i-1) * b0 + j+1] + A[i * b0 + j-1] + A[i * b0 + j] + A[i * b0 + j+1] + A[(i+1) * b0 + j-1] + A[(i+1) * b0 + j] + A[(i+1) * b0 + j+1]) / 9.0;
				rtTmpAccess(A_OFFSET + (i-1) * b0 + j-1, 0, 0, idx);
				rtTmpAccess(A_OFFSET + (i-1) * b0 + j, 1, 0, idx);
				rtTmpAccess(A_OFFSET + (i-1) * b0 + j+1, 2, 0, idx);
				rtTmpAccess(A_OFFSET + i * b0 + j-1, 3, 0, idx);
				rtTmpAccess(A_OFFSET + i * b0 + j, 4, 0, idx);
				rtTmpAccess(A_OFFSET + i * b0 + j+1, 5, 0, idx);
				rtTmpAccess(A_OFFSET + (i+1) * b0 + j-1, 6, 0, idx);
				rtTmpAccess(A_OFFSET + (i+1) * b0 + j, 7, 0, idx);
				rtTmpAccess(A_OFFSET + (i+1) * b0 + j+1, 8, 0, idx);
				rtTmpAccess(A_OFFSET + i * b0 + j, 9, 0, idx);
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

	seidel_2d_trace(A);

    dumpRIHistogram();
    
	return 0;
}
