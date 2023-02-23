#include "../utility/rt.h"

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

    int n = stoi(argv[1]);
    double* a = (double*)malloc(n * sizeof(double));

    vector<int> idx;
    
    for (int i = 0, j = 0, i2 = n >> 1; i<n-1; i++) {
        if (i < j) {
            swap(a[i], a[j]);
            rtTmpAccess(i, 0, 0, {i, j});   
            rtTmpAccess(j, 1, 0, {i, j});
        }
        int k = i2;
      	while (k <= j) {
           j -= k;
           k >>= 1;
        }
        j += k; 
     }

    dumpRIHistogram();

    return 0;
}
