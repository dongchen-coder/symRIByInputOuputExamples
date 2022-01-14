#include "../utility/rt.h"

int b0;
int b1;
int b2;
int b3;

#define TMP_OFFSET 0
#define A_OFFSET b0 * b1
#define B_OFFSET b0 * b1 + b0 * b2
#define D_OFFSET b0 * b1 + b0 * b2 + b1 * b2
#define C_OFFSET b0 * b1 + b0 * b2 + b1 * b2 + b0 * b3

void mm2_trace(double* tmp, double* A, double* B, double* C, double* D, double alpha, double beta) {

    int i, j, k;
    vector<int> idx;
    
    for (i = 0; i < b0; i++) {
        for (j = 0; j < b1; j++) {
            idx.clear(); idx.push_back(i); idx.push_back(j);
            
            tmp[i * b1 + j] = 0.0;
            rtTmpAccess(TMP_OFFSET + i * b1 + j, 0, 0, idx);
            for (k = 0; k < b2; ++k) {
                idx.clear(); idx.push_back(i); idx.push_back(j); idx.push_back(k);
                
                tmp[i * b1 + j] += alpha * A[i * b2 + k] * B[k * b1 + j];
				rtTmpAccess(A_OFFSET + i * b2 + k, 1, 1, idx);
				rtTmpAccess(B_OFFSET + k * b1 + j, 2, 2, idx);
				rtTmpAccess(TMP_OFFSET + i * b1 + j, 3, 0, idx);
				rtTmpAccess(TMP_OFFSET + i * b1 + j, 4, 0, idx);
            }
        }
    }
    for (i = 0; i < b0; i++) {
        for (j = 0; j < b3; j++) {
            idx.clear(); idx.push_back(i); idx.push_back(j);
            
            D[i * b3 + j] *= beta;
			rtTmpAccess(D_OFFSET + i * b3 + j, 5, 3, idx);
            rtTmpAccess(D_OFFSET + i * b3 + j, 6, 3, idx);
            for (k = 0; k < b1; ++k) {
                idx.clear(); idx.push_back(i); idx.push_back(j); idx.push_back(k);
                
                D[i * b3 + j] += tmp[i * b1 + k] * C[k * b3 + j];
            	rtTmpAccess(TMP_OFFSET + i * b1 + k, 7, 0, idx);
				rtTmpAccess(C_OFFSET + k * b3 + j, 8, 4, idx);
				rtTmpAccess(D_OFFSET + i * b3 + j, 9, 3, idx);
				rtTmpAccess(D_OFFSET + i * b3 + j, 10, 3, idx);
			}
        }
    }
}


int main(int argc, char* argv[]) {
	
    if (argc != 5) {
        cout << "This benchmark needs 4 loop bounds" << endl;
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
    b3 = stoi(argv[4]);
    
	double* tmp = (double*)malloc( b0 * b1 * sizeof(double));
	double* A = (double*)malloc( b0 * b2 * sizeof(double));
	double* B = (double*)malloc( b2 * b1 * sizeof(double));
	double* C = (double*)malloc( b1 * b3 * sizeof(double));
	double* D = (double*)malloc( b0 * b3 * sizeof(double));
	double alpha = 0.1;
	double beta = 0.5;
	
	mm2_trace(tmp, A, B, C, D, alpha, beta);

    dumpRIHistogram();
    
	return 0;
}

