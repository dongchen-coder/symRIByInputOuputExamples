#include "../utility/rt.h"

int b0;

#define PATH_OFFSET 0

void floyd_warshall_trace(double* path) {

	int k, i, j;
    vector<int> idx;

	for (k = 0; k < b0; k++)
		for(i = 0; i < b0; i++)
			for (j = 0; j < b0; j++) {
                idx.clear(); idx.push_back(k); idx.push_back(i); idx.push_back(j);
				//path[i * b0 + j] = path[i * b0 + j] < path[i * b0 + k] + path[k * b0 + j] ? path[i * b0 + j] : path[i * b0 + k] + path[k * b0 + j];
				rtTmpAccess(PATH_OFFSET + i * b0 + j, 0, 0, idx);
				rtTmpAccess(PATH_OFFSET + i * b0 + k, 1, 0, idx);
				rtTmpAccess(PATH_OFFSET + k * b0 + j, 2, 0, idx);
				if (path[i * b0 + j] < path[i * b0 + k] + path[k * b0 + j]) {
					path[i * b0 + j] = path[i * b0 + j];
					rtTmpAccess(PATH_OFFSET + i * b0 + j, 3, 0, idx);
				} else {
					path[i * b0 + j] = path[i * b0 + k] + path[k * b0 + j];
					rtTmpAccess(PATH_OFFSET + i * b0 + k, 4, 0, idx);
					rtTmpAccess(PATH_OFFSET + k * b0 + j, 5, 0, idx);
					rtTmpAccess(PATH_OFFSET + i * b0 + j, 6, 0, idx);
				}
			}
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
    
	double* path = (double *)malloc(b0 * b0 * sizeof(double));

	floyd_warshall_trace(path);

    dumpRIHistogram();
    
	return 0;
}
