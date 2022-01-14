#include "../utility/rt.h"

int b0;
int b1;

#define A_OFFSET 0
#define S_OFFSET b0 * b1
#define Q_OFFSET b0 * b1 + b1
#define R_OFFSET b0 * b1 + b1 + b0
#define P_OFFSET b0 * b1 + b1 + b0 + b0


void bicg_cpu_trace(double* A, double* r, double* s, double* p, double* q, unsigned int nx, int ny) {
 
	int i,j;
    vector<int> idx;

    for (i = 0; i < b1; i++)
    {
        idx.clear(); idx.push_back(i);
        s[i] = 0.0;
    	rtTmpAccess(S_OFFSET + i, 0, 0, idx);
	}

    for (i = 0; i < b0; i++)
    {
        idx.clear(); idx.push_back(i);
        q[i] = 0.0;
		rtTmpAccess(Q_OFFSET + i, 1, 1, idx);
        for (j = 0; j < b1; j++)
        {
            idx.clear(); idx.push_back(i); idx.push_back(j);
            s[j] = s[j] + r[i] * A[i * b1 + j];
            q[i] = q[i] + A[i * b1 + j] * p[j];
        	rtTmpAccess(S_OFFSET + j, 2, 0, idx);
			rtTmpAccess(R_OFFSET + i, 3, 2, idx);
			rtTmpAccess(A_OFFSET + i * b1 + j, 4, 3, idx);
			rtTmpAccess(S_OFFSET + j, 5, 0, idx);
			rtTmpAccess(Q_OFFSET + i, 6, 1, idx);
			rtTmpAccess(A_OFFSET + i * b1 + j, 7, 3, idx);
			rtTmpAccess(P_OFFSET + j, 8, 4, idx);
			rtTmpAccess(Q_OFFSET + i, 9, 1, idx);
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
    
    double* A = (double*)malloc( (b0*b1)*sizeof(double));
    double* r = (double*)malloc( b0*sizeof(double));
    double* s = (double*)malloc( b1*sizeof(double));
    double* q = (double*)malloc( b0*sizeof(double));
    double* p = (double*)malloc( b1*sizeof(double));

    for (int i = 0; i < b0; i++) {
        r[i] = i % 256;
    }

    for (int i = 0; i< b1; i++) {
        p[i] = i % 256;
    }

    for (int i = 0; i< b1*b0; i++) {
        A[i] = i % 128;
    }

    bicg_cpu_trace(A, r, s, p ,q, b0, b1);

    dumpRIHistogram();
    
    return 0;
}
