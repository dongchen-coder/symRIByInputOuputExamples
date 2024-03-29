#include "../utility/rt.h"

int b0;

void stencil_trace(int *a, int *b, unsigned int dim_size) {
    
    vector<int> idx;
    
	for (int i = 1; i < dim_size+1; i++) {
        for (int j = 1; j < dim_size+1; j++) {
			idx.clear(); idx.push_back(i); idx.push_back(j);
            
            b[i* (b0 + 2) +j] =  a[i* (b0 + 2)+j] + a[i* (b0 + 2)+j + 1] + a[i* (b0 + 2)+j - 1] + a[(i-1)* (b0 + 2) +j] + a[(i+1)* (b0 + 2) +j];

            rtTmpAccess(i * (b0 + 2) + j, 0, 0, idx);
            rtTmpAccess(i * (b0 + 2) + j + 1, 1, 0, idx);
            rtTmpAccess(i * (b0 + 2) + j - 1, 2, 0, idx);
            rtTmpAccess( (i-1) * (b0 + 2) + j, 3, 0, idx);
            rtTmpAccess( (i+1) * (b0 + 2) + j, 4, 0, idx);
            rtTmpAccess(i * (b0 + 2) + j + (b0 + 2)* (b0 + 2), 5, 0, idx);
        }
    }
    return;
}



int main(int argc, char* argv[]) {
    
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
    
    int* a = (int*)malloc( (b0+2)* (b0+2)*sizeof(int));
    int* b = (int*)malloc( (b0+2)* (b0+2)*sizeof(int));

    for (int i = 0; i < (b0+2) * (b0+2); i++) {
            a[i] = i % 256;
    }

    stencil_trace(a, b, b0);
    
    dumpRIHistogram();
    
    return 0;
}
