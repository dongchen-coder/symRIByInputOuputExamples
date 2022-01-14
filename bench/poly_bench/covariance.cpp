#include "../utility/rt.h"

int b0;
int b1;

#define DATA_OFFSET 0
#define MEAN_OFFSET b0 * b1
#define SYMMAT_OFFSET b0 * b1 + b0

#define FLOAT_N 3214212.01
#define EPS 0.005

void covariance_trace(double* data, double* mean, double* symmat, unsigned int m, unsigned int n) {

	int j, i, j1, j2;
    vector<int> idx;
    
    /* Determine mean of column vectors of input data matrix */
    for (j = 0; j < b0; j++)
    {
        idx.clear(); idx.push_back(j);
        mean[j] = 0.0;
        rtTmpAccess(MEAN_OFFSET + j, 0, 0, idx);
        
        for (i = 0; i < b1; i++)
        {
            idx.clear(); idx.push_back(j); idx.push_back(i);
            mean[j] = mean[j] + data[i * b0 + j];
            rtTmpAccess(DATA_OFFSET + i * b0 + j, 1, 1, idx);
            rtTmpAccess(MEAN_OFFSET + j, 2, 0, idx);
            rtTmpAccess(MEAN_OFFSET + j, 3, 0, idx);
        }
        idx.clear(); idx.push_back(j);
        mean[j] = mean[j] / FLOAT_N;
        rtTmpAccess(MEAN_OFFSET + j, 4, 0, idx);
        rtTmpAccess(MEAN_OFFSET + j, 5, 0, idx);
    }
    
    /* Center the column vectors. */
    for (i = 0; i < b1; i++)
    {
        for (j = 0; j < b0; j++)
        {
            idx.clear(); idx.push_back(i); idx.push_back(j);
            data[i * b0 + j] = data[i * b0 + j] - mean[j];
            rtTmpAccess(MEAN_OFFSET + j, 6, 0, idx);
            rtTmpAccess(DATA_OFFSET + i * b0 + j, 7, 1, idx);
            rtTmpAccess(DATA_OFFSET + i * b0 + j, 8, 1, idx);
        }
    }
    
    /* Calculate the m * m covariance matrix. */
    for (j1 = 0; j1 < b0; j1++)
    {
        for (j2 = j1; j2 < b0; j2++)
        {
            idx.clear(); idx.push_back(j1); idx.push_back(j2);
            symmat[j1 * b0 + j2] = 0.0;
            rtTmpAccess(SYMMAT_OFFSET + j1 * b0 + j2, 9, 2, idx);
            
            for (i = 0; i < b1; i++)
            {
                idx.clear(); idx.push_back(j1); idx.push_back(j2); idx.push_back(i);
                symmat[j1 * b0 + j2] = symmat[j1 * b0 + j2] + data[i * b0 + j1] * data[i * b0 + j2];
                rtTmpAccess(DATA_OFFSET + i * b0 + j1, 10, 1, idx);
                rtTmpAccess(DATA_OFFSET + i * b0 + j2, 11, 1, idx);
                rtTmpAccess(SYMMAT_OFFSET + j1 * b0 + j2, 12, 2, idx);
                rtTmpAccess(SYMMAT_OFFSET + j1 * b0 + j2, 13, 2, idx);
            }
            
            idx.clear(); idx.push_back(j1); idx.push_back(j2);
            symmat[j2 * b0 + j1] = symmat[j1 * b0 + j2];
            rtTmpAccess(SYMMAT_OFFSET + j1 * b0 + j2, 14, 2, idx);
            rtTmpAccess(SYMMAT_OFFSET + j2 * b0 + j1, 15, 2, idx);
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
    
    double* data = (double*)malloc( (b0*b1)*sizeof(double));
    double* mean = (double*)malloc( b0*sizeof(double));
    double* symmat = (double*)malloc( (b0*b0)*sizeof(double));

    for (int i = 0; i < b0*b1; i++) {
        data[i] = i % 256;
    }

    covariance_trace(data, mean, symmat, b0, b1);
    
    dumpRIHistogram();
    
    return 0;
}
