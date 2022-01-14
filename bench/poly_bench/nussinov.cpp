#include "../utility/rt.h"

#include <math.h>

int b0;

#define match(b1, b2) (((b1)+(b2)) == 3 ? 1 : 0)
#define max_score(s1, s2) ((s1 >= s2) ? s1 : s2)


#define TABLE_OFFSET 0
#define SEQ_OFFSET b0 * b0

void nussinov_trace(double* table, double* seq) {

	int i, j, k;
    vector<int> idx;

	for (i = b0 - 1; i >= 0; i--) {
		for (j=i+1; j < b0; j++) {
            idx.clear(); idx.push_back(i); idx.push_back(j);
			if (j-1>=0) {
				table[i * b0 + j] = max_score(table[i * b0 + j], table[i * b0 + j-1]);
				rtTmpAccess(TABLE_OFFSET + i * b0 + j, 0, 0, idx);
				rtTmpAccess(TABLE_OFFSET + i * b0 + j-1, 1, 0, idx);
				//if (table[i * b0 + j] > table[i * b0 + j-1])
				//	rtTmpAccess(TABLE_OFFSET + i * b0 + j, 2, 0);
				//else
				//	rtTmpAccess(TABLE_OFFSET + i * b0 + j-1, 3, 0);
				rtTmpAccess(TABLE_OFFSET + i * b0 + j, 2, 0, idx);
			}
			if (i+1 < b0) {
				table[i * b0 +j] = max_score(table[i * b0 + j], table[(i+1) * b0 + j]);
				rtTmpAccess(TABLE_OFFSET + i * b0 + j, 3, 0, idx);
				rtTmpAccess(TABLE_OFFSET + (i+1) * b0 + j, 4, 0, idx);
				//if (table[i * b0 + j] >= table[(i+1) * b0 + j])
				//	rtTmpAccess(TABLE_OFFSET + i * b0 + j, 7, 0);
				//else
				//	rtTmpAccess(TABLE_OFFSET + i * b0 + j, 8, 0);
				rtTmpAccess(TABLE_OFFSET + i * b0 + j, 5, 0, idx);
			}
			if (j-1>=0 && i+1 < b0) {
				/* don't allow adjacent elements to bond */
				if (i<j-1) {
					table[i * b0 + j] = max_score(table[i * b0 + j], table[(i+1) * b0 + j-1]+match(seq[i], seq[j]));
					rtTmpAccess(TABLE_OFFSET + i * b0 + j, 6, 0, idx);
					rtTmpAccess(TABLE_OFFSET + (i+1) * b0 + j-1, 7, 0, idx);
					rtTmpAccess(SEQ_OFFSET + i, 8, 1, idx);
					rtTmpAccess(SEQ_OFFSET + j, 9, 1, idx);
                    
					//if (table[i * b0 + j] >= table[(i+1) * b0 + j-1]+match(seq[i], seq[j])) {
					//	rtTmpAccess(TABLE_OFFSET + i * b0 + j, 14, 0);
					//} else {
					//	rtTmpAccess(TABLE_OFFSET + (i+1) * b0 + j-1, 15, 0);
                    //	rtTmpAccess(SEQ_OFFSET + i, 16, 1);
                    //	rtTmpAccess(SEQ_OFFSET + j, 17, 1);
					//}
					rtTmpAccess(TABLE_OFFSET + i * b0 + j, 10, 0, idx);
				} else {
					table[i * b0 + j] = max_score(table[i * b0 + j], table[(i+1) * b0 + j-1]);
					rtTmpAccess(TABLE_OFFSET + i * b0 + j, 11, 0, idx);
					rtTmpAccess(TABLE_OFFSET + (i+1) * b0 + j-1, 12, 0, idx);
					//if (table[i * b0 + j] >= table[(i+1) * b0 + j-1]) {
					//	rtTmpAccess(TABLE_OFFSET + i * b0 + j, 21, 0);
					//} else {
					//	rtTmpAccess(TABLE_OFFSET + i * b0 + j, 22, 0);
					//}
					rtTmpAccess(TABLE_OFFSET + i * b0 + j, 13, 0, idx);
				}
			}
			for (k=i+1; k<j; k++) {
				table[i * b0 + j] = max_score(table[i * b0 + j], table[i * b0 + k] + table[(k+1) * b0 + j]);
				rtTmpAccess(TABLE_OFFSET + i * b0 + j, 14, 0, idx);
				rtTmpAccess(TABLE_OFFSET + i * b0 + k, 15, 0, idx);
				rtTmpAccess(TABLE_OFFSET + (k+1) * b0 + j, 16, 0, idx);
				//if (table[i * b0 + j] >= table[i * b0 + k] + table[(k+1) * b0 + j]) {
				//	rtTmpAccess(TABLE_OFFSET + i * b0 + j, 27, 0);
				//} else {
				//	rtTmpAccess(TABLE_OFFSET + i * b0 + k, 28, 0);
                //	rtTmpAccess(TABLE_OFFSET + (k+1) * b0 + j, 29, 0);
				//}
				rtTmpAccess(TABLE_OFFSET + i * b0 + j, 17, 0, idx);
			}
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
    
	double* table = (double *)malloc(b0 * b0 * sizeof(double));
	double* seq = (double *)malloc(b0 * sizeof(double));

	for (int i = 0; i < b0; i++) {
		for (int j = 0; j < b0; j++) {
			table[i * b0 + j] = (i * b0 + j) % 128;
		}
		seq[i] = i % 64;
	}

	nussinov_trace(table, seq);

    dumpRIHistogram();
    
	return 0;
}
