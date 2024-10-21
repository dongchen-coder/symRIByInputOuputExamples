#include "../utility/rt.h"

int b0;
int b1;
int b2;

#define A_OFFSET 0
#define B_OFFSET b0 * b1 * b2

void conv3D_trace(double* A, double* B)
{
    int i, j, k;
    double c11, c12, c13, c21, c22, c23, c31, c32, c33;
    vector<int> idx;
    
    c11 = +2;  c21 = +5;  c31 = -8;
    c12 = -3;  c22 = +6;  c32 = -9;
    c13 = +4;  c23 = +7;  c33 = +10;

    for (int i = 1; i < b0 - 1; ++i) // 0
    {
        for (int j = 1; j < b1 - 1; ++j) // 1
        {
            for (int k = 1; k < b2 -1; ++k) // 2
            {
                idx.clear(); idx.push_back(i); idx.push_back(j); idx.push_back(k);
                /*
                B[i][j][k] = c11 * A[(i - 1)][(j - 1)][(k - 1)]  +  c13 * A[(i + 1)][(j - 1)][(k - 1)]
                +   c21 * A[(i - 1)][(j - 1)][(k - 1)]  +  c23 * A[(i + 1)][(j - 1)][(k - 1)]
                +   c31 * A[(i - 1)][(j - 1)][(k - 1)]  +  c33 * A[(i + 1)][(j - 1)][(k - 1)]
                +   c12 * A[(i + 0)][(j - 1)][(k + 0)]  +  c22 * A[(i + 0)][(j + 0)][(k + 0)]
                +   c32 * A[(i + 0)][(j + 1)][(k + 0)]  +  c11 * A[(i - 1)][(j - 1)][(k + 1)]
                +   c13 * A[(i + 1)][(j - 1)][(k + 1)]  +  c21 * A[(i - 1)][(j + 0)][(k + 1)]
                +   c23 * A[(i + 1)][(j + 0)][(k + 1)]  +  c31 * A[(i - 1)][(j + 1)][(k + 1)]
                +   c33 * A[(i + 1)][(j + 1)][(k + 1)];
                 */
                B[i * b1 * b2 + j * b2 + k] = c11 * A[(i - 1) * b1 * b2 + (j - 1) * b2 + (k - 1)]
                                            +   c13 * A[(i + 1) * b1 * b2 + (j - 1) * b2 + (k - 1)]
                                            +   c21 * A[(i - 1) * b1 * b2 + (j - 1) * b2 + (k - 1)]
                                            +   c23 * A[(i + 1) * b1 * b2 + (j - 1) * b2 + (k - 1)]
                                            +   c31 * A[(i - 1) * b1 * b2 + (j - 1) * b2 + (k - 1)]
                                            +   c33 * A[(i + 1) * b1 * b2 + (j - 1) * b2 + (k - 1)]
                                            +   c12 * A[(i + 0) * b1 * b2 + (j - 1) * b2 + (k + 0)]
                                            +   c22 * A[(i + 0) * b1 * b2 + (j + 0) * b2 + (k + 0)]
                                            +   c32 * A[(i + 0) * b1 * b2 + (j + 1) * b2 + (k + 0)]
                                            +   c11 * A[(i - 1) * b1 * b2 + (j - 1) * b2 + (k + 1)]
                                            +   c13 * A[(i + 1) * b1 * b2 + (j - 1) * b2 + (k + 1)]
                                            +   c21 * A[(i - 1) * b1 * b2 + (j + 0) * b2 + (k + 1)]
                                            +   c23 * A[(i + 1) * b1 * b2 + (j + 0) * b2 + (k + 1)]
                                            +   c31 * A[(i - 1) * b1 * b2 + (j + 1) * b2 + (k + 1)]
                                            +   c33 * A[(i + 1) * b1 * b2 + (j + 1) * b2 + (k + 1)];

                rtTmpAccess(A_OFFSET + (i - 1) * b1 * b2 + (j - 1) * b2 + (k - 1), 0, 0, idx);
                rtTmpAccess(A_OFFSET + (i + 1) * b1 * b2 + (j - 1) * b2 + (k - 1), 1, 0, idx);
                rtTmpAccess(A_OFFSET + (i - 1) * b1 * b2 + (j - 1) * b2 + (k - 1), 2, 0, idx);
                rtTmpAccess(A_OFFSET + (i + 1) * b1 * b2 + (j - 1) * b2 + (k - 1), 3, 0, idx);
                rtTmpAccess(A_OFFSET + (i - 1) * b1 * b2 + (j - 1) * b2 + (k - 1), 4, 0, idx);
                rtTmpAccess(A_OFFSET + (i + 1) * b1 * b2 + (j - 1) * b2 + (k - 1), 5, 0, idx);
                rtTmpAccess(A_OFFSET + (i + 0) * b1 * b2 + (j - 1) * b2 + (k + 0), 6, 0, idx);
                rtTmpAccess(A_OFFSET + (i + 0) * b1 * b2 + (j + 0) * b2 + (k + 0), 7, 0, idx);
                rtTmpAccess(A_OFFSET + (i + 0) * b1 * b2 + (j + 1) * b2 + (k + 0), 8, 0, idx);
                rtTmpAccess(A_OFFSET + (i - 1) * b1 * b2 + (j - 1) * b2 + (k + 1), 9, 0, idx);
                rtTmpAccess(A_OFFSET + (i + 1) * b1 * b2 + (j - 1) * b2 + (k + 1), 10, 0, idx);
                rtTmpAccess(A_OFFSET + (i - 1) * b1 * b2 + (j + 0) * b2 + (k + 1), 11, 0, idx);
                rtTmpAccess(A_OFFSET + (i + 1) * b1 * b2 + (j + 0) * b2 + (k + 1), 12, 0, idx);
                rtTmpAccess(A_OFFSET + (i - 1) * b1 * b2 + (j + 1) * b2 + (k + 1), 13, 0, idx);
                rtTmpAccess(A_OFFSET + (i + 1) * b1 * b2 + (j + 1) * b2 + (k + 1), 14, 0, idx);
                rtTmpAccess(B_OFFSET + (i * b1 * b2 + j * b2 + k), 15, 1, idx);
            }
        }
    }

}

int main(int argc, char* argv[]) 
{
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
    
    double* A = (double*)malloc( (b0 * b1 * b2)*sizeof(double));
    double* B = (double*)malloc( (b0 * b1 * b2)*sizeof(double));

    for (int i = 0; i < (b0 * b1 * b2); i++) {
            A[i] = i % 256;
    }

    conv3D_trace(A, B);

    dumpRIHistogram();
    
    return 0;
}
