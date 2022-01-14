#include "../utility/rt.h"
#include<math.h>

int b0;
int b1;

#define FLOAT_N 3214212.01
#define EPS 0.005

#define DATA_OFFSET 0
#define MEAN_OFFSET b0 * b1
#define STDDEV_OFFSET b0 * b1 + b0
#define SYMMAT_OFFSET b0 * b1 + b0 + b0

void correlation_trace(double* data, double* mean, double* stddev, double* symmat) {

	int i, j, j1, j2;
    vector<int> idx;

    // Determine mean of column vectors of input data matrix
    for (j = 0; j < b0; j++)
    {
        idx.clear(); idx.push_back(j);
        mean[j] = 0.0;
		rtTmpAccess(MEAN_OFFSET + j, 0, 0, idx);

        for (i = 0; i < b1; i++)
        {
            idx.clear(); idx.push_back(j); idx.push_back(i);
            mean[j] += data[i * b0 + j];
            rtTmpAccess(DATA_OFFSET + i * b0 + j, 1, 1, idx);
        	rtTmpAccess(MEAN_OFFSET + j, 2, 0, idx);
			rtTmpAccess(MEAN_OFFSET + j, 3, 0, idx);
		}

        idx.clear(); idx.push_back(j);
        mean[j] /= (double)FLOAT_N;
    	rtTmpAccess(MEAN_OFFSET + j, 4, 0, idx);
		rtTmpAccess(MEAN_OFFSET + j, 5, 0, idx);
	}

    // Determine standard deviations of column vectors of data matrix.
    for (j = 0; j < b0; j++)
    {
        idx.clear(); idx.push_back(j);
        stddev[j] = 0.0;
		rtTmpAccess(STDDEV_OFFSET + j, 6, 2, idx);

        for (i = 0; i < b1; i++)
        {
            idx.clear(); idx.push_back(j); idx.push_back(i);
            stddev[j] += (data[i * b0 + j] - mean[j]) * (data[i * b0 + j] - mean[j]);
        	
			rtTmpAccess(DATA_OFFSET + i * b0 + j, 7, 1, idx);
			rtTmpAccess(MEAN_OFFSET + j, 8, 0, idx);
			rtTmpAccess(DATA_OFFSET + i * b0 + j, 9, 1, idx);
			rtTmpAccess(MEAN_OFFSET + j, 10, 0, idx);
            rtTmpAccess(STDDEV_OFFSET + j, 11, 2, idx);
			rtTmpAccess(STDDEV_OFFSET + j, 12, 2, idx);
		}

        idx.clear(); idx.push_back(j);
        stddev[j] /= FLOAT_N;
//        stddev[j] = sqrt_of_array_cell(stddev, j);
		stddev[j] = sqrt(stddev[j]);

        stddev[j] = stddev[j] <= EPS ? 1.0 : stddev[j];
    	rtTmpAccess(STDDEV_OFFSET + j, 13, 2, idx);
		rtTmpAccess(STDDEV_OFFSET + j, 14, 2, idx);
		rtTmpAccess(STDDEV_OFFSET + j, 15, 2, idx);
		rtTmpAccess(STDDEV_OFFSET + j, 16, 2, idx);
        
        if (stddev[j] > EPS) {
            rtTmpAccess(STDDEV_OFFSET + j, 17, 2, idx);
        }
		rtTmpAccess(STDDEV_OFFSET + j, 18, 2, idx);
	}

	// Center and reduce the column vectors.
    for (i = 0; i < b1; i++)
    {
        for (j = 0; j < b0; j++)
        {
            idx.clear(); idx.push_back(i); idx.push_back(j);
            data[i * b0 + j] -= mean[j];
            data[i * b0 + j] /= (sqrt(FLOAT_N)*stddev[j]) ;
            
            rtTmpAccess(MEAN_OFFSET + j, 19, 0, idx);
			rtTmpAccess(DATA_OFFSET + i * b0 + j, 20, 1, idx);
			rtTmpAccess(DATA_OFFSET + i * b0 + j, 21, 1, idx);
            rtTmpAccess(STDDEV_OFFSET + j, 22, 2, idx);
			rtTmpAccess(DATA_OFFSET + i * b0 + j, 23, 1, idx);
			rtTmpAccess(DATA_OFFSET + i * b0 + j, 24, 1, idx);
        }
    }

    // Calculate the m * m correlation matrix.
    for (j1 = 0; j1 < b0-1; j1++)
    {
        idx.clear(); idx.push_back(j1);
        symmat[j1 * b0 + j1] = 1.0;
		rtTmpAccess(SYMMAT_OFFSET + j1 * b0 + j1, 25, 3, idx);

        for (j2 = j1+1; j2 < b0; j2++)
        {
            idx.clear(); idx.push_back(j1); idx.push_back(j2);
            symmat[j1 * b0 + j2] = 0.0;
			rtTmpAccess(SYMMAT_OFFSET + j1 * b0 + j2, 26, 3, idx);

            for (i = 0; i < b1; i++)
            {
                idx.clear(); idx.push_back(j1); idx.push_back(j2); idx.push_back(i);
                symmat[j1 * b0 + j2] += (data[i * b0 + j1] * data[i * b0 + j2]);
                rtTmpAccess(DATA_OFFSET + i * b0 + j1, 27, 1, idx);
                rtTmpAccess(DATA_OFFSET + i * b0 + j2, 28, 1, idx);
                rtTmpAccess(SYMMAT_OFFSET + j1 * b0 + j2, 29, 3, idx);
				rtTmpAccess(SYMMAT_OFFSET + j1 * b0 + j2, 30, 3, idx);
            }

            idx.clear(); idx.push_back(j1); idx.push_back(j2);
            symmat[j2 * b0 + j1] = symmat[j1 * b0 + j2];
			rtTmpAccess(SYMMAT_OFFSET + j1 * b0 + j2, 31, 3, idx);
			rtTmpAccess(SYMMAT_OFFSET + j2 * b0 + j1, 32, 3, idx);
        }
    }
    
    idx.clear();
    symmat[(b0-1) * b0 + b0 - 1] = 1.0;
	rtTmpAccess(SYMMAT_OFFSET + (b0-1) * b0 + b0 - 1, 33, 3, idx);

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
    double* stddev = (double*)malloc( b0*sizeof(double));
    double* symmat = (double*)malloc( (b0*b0)*sizeof(double));

    for (int i = 0; i < b0; i++) {
        data[i] = i % 256;
    }

    correlation_trace(data, mean, stddev, symmat);

    dumpRIHistogram();
    
    return 0;
}
