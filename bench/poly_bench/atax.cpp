#include "../utility/rt.h"

int b0;
int b1;


#define A_OFFSET 0
#define X_OFFSET b0 * b1
#define Y_OFFSET b0 * b1 + b1
#define TMP_OFFSET b0 * b1 + b1 + b1


void atax_cpu_trace(double* A, double* x, double* y, double* tmp, unsigned int dim_size_x, unsigned int dim_size_y) {
    
	int i,j;
    vector<int> idx;

    for (i= 0; i < b1; i++)
    {
        idx.clear(); idx.push_back(i);
        y[i] = 0;
    	rtTmpAccess(Y_OFFSET + i, 0, 0, idx);
	}

    for (i = 0; i < b0; i++)
    {
        idx.clear(); idx.push_back(i);
        tmp[i] = 0;
        rtTmpAccess(TMP_OFFSET + i, 1, 1, idx);
            
        for (j = 0; j < b1; j++) {
            idx.clear(); idx.push_back(i); idx.push_back(j);
            tmp[i] = tmp[i] + A[i * b1 + j] * x[j];
            rtTmpAccess(TMP_OFFSET + i, 2, 1, idx);
            rtTmpAccess(A_OFFSET + i * b1 + j, 3, 2, idx);
            rtTmpAccess(X_OFFSET + j, 4, 3, idx);
            rtTmpAccess(TMP_OFFSET + i, 5, 1, idx);
        }

        for (j = 0; j < b1; j++) {
            idx.clear(); idx.push_back(i); idx.push_back(j);
            y[j] = y[j] + A[i * b1 + j] * tmp[i];
            rtTmpAccess(Y_OFFSET + j, 6, 0, idx);
            rtTmpAccess(A_OFFSET + i * b1 + j, 7, 2, idx);
            rtTmpAccess(TMP_OFFSET + i, 8, 1, idx);
            rtTmpAccess(Y_OFFSET + j, 9, 0, idx);
        }
    }

	return;
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
    
    double* A = (double*)malloc( (b0 * b1) * sizeof(double) );
    double* x = (double*)malloc( b0 * sizeof(double) );
    double* y = (double*)malloc( b1 * sizeof(double) );
    double* tmp = (double*)malloc( b0 * sizeof(double) );

    for (int i = 0; i < (b0 * b1); i++) {
        A[i] = i % 256;
    }

    for (int i = 0; i < b0; i++) {
        x[i] = i % 256;
    }

    atax_cpu_trace(A, x, y, tmp, b0, b1);

    dumpRIHistogram();
    
    return 0;
}
