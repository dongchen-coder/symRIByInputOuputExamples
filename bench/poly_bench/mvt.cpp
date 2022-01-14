#include "../utility/rt.h"

int b0;

#define A_OFFSET 0
#define X1_OFFSET b0 * b0
#define X2_OFFSET b0 * b0 + b0
#define Y1_OFFSET b0 * b0 + b0 + b0
#define Y2_OFFSET b0 * b0 + b0 + b0 + b0

void runMvt_trace( double* a, double* x1, double* x2, double* y1, double* y2)
{
    int i, j;
    vector<int> idx;
    
    for (i=0; i< b0; i++)
    {
        for (j=0; j < b0; j++)
        {
            idx.clear(); idx.push_back(i); idx.push_back(j);
            //x1[i] = x1[i] + a[i][j] * y1[j];
            x1[i] = x1[i] + a[i * b0 + j] * y1[j];
		
			rtTmpAccess(X1_OFFSET + i, 0, 0, idx);
			rtTmpAccess(A_OFFSET + i * b0 + j, 1, 1, idx);
			rtTmpAccess(Y1_OFFSET + j, 2, 2, idx);
			rtTmpAccess(X1_OFFSET + i, 3, 0, idx);

        }
    }
    
    for (i=0; i < b0; i++)
    {
        for (j=0; j< b0; j++)
        {
            idx.clear(); idx.push_back(i); idx.push_back(j);
            //x2[i] = x2[i] + a[j][i] * y2[j];
            x2[i] = x2[i] + a[j * b0 + i] * y2[j];

			rtTmpAccess(X2_OFFSET + i, 4, 3, idx);
			rtTmpAccess(A_OFFSET + j * b0 + i, 5, 1, idx);
			rtTmpAccess(Y2_OFFSET + j, 6, 4, idx);
			rtTmpAccess(X2_OFFSET + i, 7, 3, idx);

        }
    }
    return;
}

int main(int argc, char const *argv[])
{
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
    
    double* a = (double*)malloc( (b0*b0) * sizeof(double));
    double* y1 = (double*)malloc( b0 * sizeof(double));
    double* x1 = (double*)malloc( b0 * sizeof(double));
    double* y2 = (double*)malloc( b0 * sizeof(double));
    double* x2 = (double*)malloc( b0 * sizeof(double));
    

    for (int i = 0; i < b0; ++i)
    {
        y1[i] = i % 256;
        y2[i] = i / 100;
    }

    for (int i = 0; i < b0*b0; ++i)
    {
        a[i] = i / 10;
    }

    runMvt_trace( a, x1, x2, y1, y2);
    
    dumpRIHistogram();
    
    return 0;
}
