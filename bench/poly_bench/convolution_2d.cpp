#include "../utility/rt.h"

int b0;
int b1;

#define A_OFFSET 0
#define B_OFFSET b0 * b1

void conv2D_trace(double* A, double* B)
{
    int i, j;
    double c11, c12, c13, c21, c22, c23, c31, c32, c33;
    vector<int> idx;
    
    c11 = +0.2;  c21 = +0.5;  c31 = -0.8;
    c12 = -0.3;  c22 = +0.6;  c32 = -0.9;
    c13 = +0.4;  c23 = +0.7;  c33 = +0.10;
    
    
    for (i = 1; i < b0 - 1; ++i) // 0
    {
        for (j = 1; j < b1 - 1; ++j) // 1
        {
            idx.clear(); idx.push_back(i); idx.push_back(j);
            
            B[i * b1 + j] =  c11 * A[(i - 1) * b1 + (j - 1)]
                    +  c12 * A[(i + 0) * b1 + (j - 1)]
                    +  c13 * A[(i + 1) * b1 + (j - 1)]
                    +  c21 * A[(i - 1) * b1 + (j + 0)]
                    +  c22 * A[(i + 0) * b1 + (j + 0)]
                    +  c23 * A[(i + 1) * b1 + (j + 0)]
                    +  c31 * A[(i - 1) * b1 + (j + 1)]
                    +  c32 * A[(i + 0) * b1 + (j + 1)]
                    +  c33 * A[(i + 1) * b1 + (j + 1)];

            rtTmpAccess(A_OFFSET + (i - 1) * b1 + (j - 1), 0, 0, idx);
            rtTmpAccess(A_OFFSET + (i + 0) * b1 + (j - 1), 1, 0, idx);
            rtTmpAccess(A_OFFSET + (i + 1) * b1 + (j - 1), 2, 0, idx);
            rtTmpAccess(A_OFFSET + (i - 1) * b1 + (j + 0), 3, 0, idx);
            rtTmpAccess(A_OFFSET + (i + 0) * b1 + (j + 0), 4, 0, idx);
            rtTmpAccess(A_OFFSET + (i + 1) * b1 + (j + 0), 5, 0, idx);
            rtTmpAccess(A_OFFSET + (i - 1) * b1 + (j + 1), 6, 0, idx);
            rtTmpAccess(A_OFFSET + (i + 0) * b1 + (j + 1), 7, 0, idx);
            rtTmpAccess(A_OFFSET + (i + 1) * b1 + (j + 1), 8, 0, idx);
            rtTmpAccess(B_OFFSET + i * b1 + j, 9, 1, idx);

        }
    }
}

int main(int argc, char* argv[]) 
{
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
    
    double* A = (double*)malloc( (b0 * b1)*sizeof(double));
    double* B = (double*)malloc( (b0 * b1)*sizeof(double));

    for (int i = 0; i < (b0 * b1); i++) {
            A[i] = i % 256;
    }

    conv2D_trace(A, B);

    dumpRIHistogram();
    
    return 0;
}
