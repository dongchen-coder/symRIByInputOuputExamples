#include "../utility/rt.h"

int b0;
int b1;

#define P_OFFSET 0
#define Q_OFFSET 0 + b0 * b0
#define V_OFFSET 0 + b0 * b0 + b0 * b0
#define U_OFFSET 0 + b0 * b0 + b0 * b0 + b0 * b0

void adi_trace(double* p, double* q, double* v, double* u) {

	int t, i, j;
	double DX, DY, DT, B1, B2, mul1, mul2, a, b, c, d, e, f;
    vector<int> idx;

	DX = 1.0 / b0;
	DY = 1.0 / b0;
	DT = 1.0 / b1;
	B1 = 2.0;
	B2 = 1.0;
	mul1 = B1 * DT / (DX * DX);
	mul2 = B2 * DT / (DY * DY);

	a = -mul1 / 2.0;
	b = 1.0 + mul1;
	c = a;
	d = -mul2 / 2.0;
	e = 1.0 + mul2;
	f = d;

	for (t=1; t <= b1; t++) {
	//Column Sweep
		for (i=1; i< b0-1; i++) {
            idx.clear(); idx.push_back(t); idx.push_back(i);
			v[0 * b0 + i] = 1.0;
			p[i * b0 + 0] = 0.0;
			q[i * b0 + 0] = v[0 * b0 + i];
			rtTmpAccess(V_OFFSET + 0 * b0 + i, 0, 0, idx);
			rtTmpAccess(P_OFFSET + i * b0 + 0, 1, 1, idx);
			rtTmpAccess(V_OFFSET + 0 * b0 + i, 2, 0, idx);
			rtTmpAccess(Q_OFFSET + i * b0 + 0, 3, 2, idx);
			for (j=1; j< b0-1; j++) {
                idx.clear(); idx.push_back(t); idx.push_back(i); idx.push_back(j);
				p[i * b0 + j] = -c / (a*p[i * b0 + j-1]+b);
				q[i * b0 + j] = (-d*u[j * b0 + i-1]+(1.0 + 2.0 * d)*u[j * b0 + i] - f*u[j * b0 + i+1]-a*q[i * b0 + j-1])/(a*p[i * b0 + j-1]+b);
				rtTmpAccess(P_OFFSET + i * b0 + j-1, 4, 1, idx);
				rtTmpAccess(P_OFFSET + i * b0 + j, 5, 1, idx);
				rtTmpAccess(U_OFFSET + j * b0 + i-1, 6, 3, idx);
				rtTmpAccess(U_OFFSET + j * b0 + i, 7, 3, idx);
				rtTmpAccess(U_OFFSET + j * b0 + i+1, 8, 3, idx);
				rtTmpAccess(Q_OFFSET + i * b0 + j-1, 9, 2, idx);
				rtTmpAccess(P_OFFSET + i * b0 + j-1, 10, 1, idx);
				rtTmpAccess(Q_OFFSET + i * b0 + j, 11, 2, idx);
			}
            idx.clear(); idx.push_back(t); idx.push_back(i);
			v[(b0 - 1) * b0 + i] = 1.0;
			rtTmpAccess(V_OFFSET + (b0 - 1) * b0 + i, 12, 0, idx);
			for (j= b0-2; j>=1; j--) {
                idx.clear(); idx.push_back(t); idx.push_back(i); idx.push_back(j);
				v[j * b0 + i] = p[i * b0 + j] * v[(j+1) * b0 + i] + q[i * b0 + j];
				rtTmpAccess(P_OFFSET + i * b0 + j, 13, 1, idx);
				rtTmpAccess(V_OFFSET + (j+1) * b0 + i, 14, 0, idx);
				rtTmpAccess(Q_OFFSET + i * b0 + j, 15, 2, idx);
				rtTmpAccess(V_OFFSET + j * b0 + i, 16, 0, idx);
			}
		}
		//Row Sweep
		for (i=1; i < b0 - 1; i++) {
            idx.clear(); idx.push_back(t); idx.push_back(i);
			u[i * b0 + 0] = 1.0;
			p[i * b0 + 0] = 0.0;
			q[i * b0 + 0] = u[i * b0 + 0];
			rtTmpAccess(U_OFFSET + i * b0 + 0, 17, 3, idx);
			rtTmpAccess(P_OFFSET + i * b0 + 0, 18, 1, idx);
			rtTmpAccess(U_OFFSET + i * b0 + 0, 19, 3, idx);
			rtTmpAccess(Q_OFFSET + i * b0 + 0, 20, 2, idx);
			for (j=1; j< b0 - 1; j++) {
                idx.clear(); idx.push_back(t); idx.push_back(i); idx.push_back(j);
				p[i * b0 + j] = -f / (d*p[i * b0 + j-1]+e);
				q[i * b0 + j] = (-a*v[(i-1) * b0 + j]+(1.0 + 2.0 * a)*v[i * b0 + j] - c*v[(i+1) * b0 + j]-d*q[i * b0 + j-1])/(d*p[i * b0 + j-1]+e);
				rtTmpAccess(P_OFFSET + i * b0 + j-1, 21, 1, idx);
				rtTmpAccess(P_OFFSET + i * b0 + j, 22, 1, idx);
				rtTmpAccess(V_OFFSET + (i-1) * b0 + j, 23, 0, idx);
				rtTmpAccess(V_OFFSET + i * b0 + j, 24, 0, idx);
				rtTmpAccess(V_OFFSET + (i+1) * b0 + j, 25, 0, idx);
				rtTmpAccess(Q_OFFSET + i * b0 + j-1, 26, 2, idx);
				rtTmpAccess(P_OFFSET + i * b0 + j-1, 27, 1, idx);
				rtTmpAccess(Q_OFFSET + i * b0 + j, 28, 2, idx);
			}
            idx.clear(); idx.push_back(t); idx.push_back(i);
			u[i * b0 + b0 - 1 ] = 1.0;
			rtTmpAccess(U_OFFSET + i * b0 + b0 - 1, 29, 3, idx);
			for (j= b0 - 2; j>=1; j--) {
                idx.clear(); idx.push_back(t); idx.push_back(i); idx.push_back(j);
				u[i * b0 + j] = p[i * b0 + j] * u[i * b0 + j+1] + q[i * b0 + j];
				rtTmpAccess(P_OFFSET + i * b0 + j, 30, 1, idx);
				rtTmpAccess(U_OFFSET + i * b0 + j+1, 31, 3, idx);
				rtTmpAccess(Q_OFFSET + i * b0 + j, 32, 2, idx);
				rtTmpAccess(U_OFFSET + i * b0 + j, 33, 3, idx);
			}
		}
	}
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
    
	double * p = (double *) malloc(b0 * b0 * sizeof(double));
	double * q = (double *) malloc(b0 * b0 * sizeof(double));
	double * v = (double *) malloc(b0 * b0 * sizeof(double));
	double * u = (double *) malloc(b0 * b0 * sizeof(double));

	adi_trace(p, q, v, u);

    dumpRIHistogram();
    
	return 0;
}


