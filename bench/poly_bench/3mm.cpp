#include "../utility/rt.h"

int b0;
int b1;
int b3;
int b2;
int b4;

#define A_OFFSET 0
#define B_OFFSET b2 * b0
#define C_OFFSET b2 * b0 + b2 * b1
#define D_OFFSET b2 * b0 + b2 * b1 + b1 * b4
#define E_OFFSET b2 * b0 + b2 * b1 + b1 * b4 + b4 * b3
#define F_OFFSET b2 * b0 + b2 * b1 + b1 * b4 + b4 * b3 + b0 * b1
#define G_OFFSET b2 * b0 + b2 * b1 + b1 * b4 + b4 * b3 + b0 * b1 + b1 * b3

void mm3_cpu_trace(int *A, int *B, int *C, int *D, int *E, int *F, int *G) {
    
	int i, j, k;
    vector<int> idx;

    /* E := A*B */
    for (i = 0; i < b0; i++)
    {
        for (j = 0; j < b1; j++)
        {
            idx.clear(); idx.push_back(i); idx.push_back(j);
            E[i * b1 + j] = 0;
			
			rtTmpAccess(E_OFFSET + i * b1 + j, 0, 0, idx);
	
            for (k = 0; k < b2; ++k)
            {
                idx.clear(); idx.push_back(i); idx.push_back(j); idx.push_back(k);
                E[i * b1 + j] += A[i * b2 + k] * B[k * b1 + j];
				rtTmpAccess(A_OFFSET + i * b2 + k, 1, 1, idx);
				rtTmpAccess(B_OFFSET + k * b1 + j, 2, 2, idx);
				rtTmpAccess(E_OFFSET + i * b1 + j, 3, 0, idx);
				rtTmpAccess(E_OFFSET + i * b1 + j, 4, 0, idx);
            }
        }
    }

    /* F := C*D */
    for (i = 0; i < b1; i++)
    {
        for (j = 0; j < b3; j++)
        {
            idx.clear(); idx.push_back(i); idx.push_back(j);
            F[i * b3 + j] = 0;

			rtTmpAccess(F_OFFSET + i * b3 + j, 5, 3, idx);
			
            for (k = 0; k < b4; ++k)
            {
                idx.clear(); idx.push_back(i); idx.push_back(j); idx.push_back(k);
                F[i * b3 + j] += C[i * b4 + k] * D[k * b3 + j];
				rtTmpAccess(C_OFFSET + i * b4 + k, 6, 4, idx);
				rtTmpAccess(D_OFFSET + k * b3 + j, 7, 5, idx);
				rtTmpAccess(F_OFFSET + i * b3 + j, 8, 3, idx);
				rtTmpAccess(F_OFFSET + i * b3 + j, 9, 3, idx);
			}
        }
    }

    /* G := E*F */
    for (i = 0; i < b0; i++)
    {
        for (j = 0; j < b3; j++)
        {
            idx.clear(); idx.push_back(i); idx.push_back(j);
            G[i * b3 + j] = 0;

			rtTmpAccess(G_OFFSET + i * b3 + j, 10, 6, idx);

            for (k = 0; k < b1; ++k)
            {
                idx.clear(); idx.push_back(i); idx.push_back(j); idx.push_back(k);
                G[i * b3 + j] += E[i * b1 + k] * F[k * b3 + j];
				rtTmpAccess(E_OFFSET + i * b1 + k, 11, 0, idx);
				rtTmpAccess(F_OFFSET + k * b3 + j, 12, 3, idx);
				rtTmpAccess(G_OFFSET + i * b3 + j, 13, 6, idx);
				rtTmpAccess(G_OFFSET + i * b3 + j, 14, 6, idx);
			}
        }
    }

    return;
}



int main(int argc, char* argv[]) {
    
    if (argc != 6) {
        cout << "This benchmark needs 5 loop bounds" << endl;
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
    b4 = stoi(argv[5]);
    
    int* a = (int*)malloc( b2 * b0 * sizeof(int) );
    int* b = (int*)malloc( b2 * b1 * sizeof(int) );
    int* c = (int*)malloc( b1 * b4 * sizeof(int) );
    int* d = (int*)malloc( b4 * b3 * sizeof(int) );
    int* e = (int*)malloc( b0 * b1 * sizeof(int) );
    int* f = (int*)malloc( b1 * b3 * sizeof(int) );
    int* g = (int*)malloc( b0 * b3 * sizeof(int) );

    for (int i = 0; i < b2 * b0; i++) {
            a[i] = i % 256;
    }

	for (int i = 0; i < b2 * b1; i++) {
            b[i] = i % 256;
    }

	for (int i = 0; i < b1 * b4; i++) {
            c[i] = i % 256;
    }

	for (int i = 0; i < b4 * b3; i++) {
            d[i] = i % 256;
    }

    mm3_cpu_trace(a, b, c, d, e, f, g);
    
    dumpRIHistogram();
    
    return 0;
}
