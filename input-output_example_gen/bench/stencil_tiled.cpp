#include "./utility/rt.h"

int DIM_SIZE;
int TILE_SIZE;

void stencil_trace(int *a, int *b, unsigned int dim_size, unsigned int tile_size) {
    
    vector<int> idx;
    
	for (int i = 1; i < dim_size+1 ; i += tile_size) {
        for (int j = 1; j < dim_size+1; j += tile_size) {
           
            for (int i_tiled = i; i_tiled < min(i+tile_size, dim_size+1); i_tiled++) {
                for (int j_tiled = j; j_tiled < min(j+tile_size, dim_size+1); j_tiled++) {
                    idx.clear(); idx.push_back(i); idx.push_back(j); idx.push_back(i_tiled), idx.push_back(j_tiled);
                    
                    b[i_tiled* (DIM_SIZE + 2) +j_tiled] =  a[i_tiled* (DIM_SIZE + 2)+j_tiled] + a[i_tiled* (DIM_SIZE + 2)+j_tiled + 1] + a[i_tiled* (DIM_SIZE + 2)+j_tiled - 1] + a[(i_tiled-1)* (DIM_SIZE + 2) +j_tiled] + a[(i_tiled+1)* (DIM_SIZE + 2) +j_tiled];

                    rtTmpAccess(i_tiled * (DIM_SIZE + 2) + j_tiled, 0, 0, idx);
                    rtTmpAccess(i_tiled * (DIM_SIZE + 2) + j_tiled + 1, 1, 0, idx);
                    rtTmpAccess(i_tiled * (DIM_SIZE + 2) + j_tiled - 1, 2, 0, idx);
                    rtTmpAccess( (i_tiled-1) * (DIM_SIZE + 2) + j_tiled, 3, 0, idx);
                    rtTmpAccess( (i_tiled+1) * (DIM_SIZE + 2) + j_tiled, 4, 0, idx);
                    rtTmpAccess(i_tiled * (DIM_SIZE + 2) + j_tiled + (DIM_SIZE + 2)* (DIM_SIZE + 2), 5, 0, idx);

                }
            }
        }
    }
    return;
}



int main(int argc, char* argv[]) {
    
    if (argc != 3) {
        cout << "This benchmark needs 1 loop bounds" << endl;
        return 0;
    }
    for (int i = 1; i < argc; i++) {
        if (!isdigit(argv[i][0])) {
            cout << "arguments must be integer" << endl;
            return 0;
        }
    }
    
    DIM_SIZE = stoi(argv[1]);
    TILE_SIZE = stoi(argv[2]);
    
    int* a = (int*)malloc( (DIM_SIZE+2)* (DIM_SIZE+2)*sizeof(int));
    int* b = (int*)malloc( (DIM_SIZE+2)* (DIM_SIZE+2)*sizeof(int));

    for (int i = 0; i < (DIM_SIZE+2) * (DIM_SIZE+2); i++) {
            a[i] = i % 256;
    }

    stencil_trace(a, b, DIM_SIZE, TILE_SIZE);
    
    dumpRIHistogram();
    
    return 0;
}
