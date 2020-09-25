#include<iostream>
#include<map>
#include<set>
#include<vector>
using namespace std;

#define CLS 64
#define DS 8
//#define TRACE
#define PROFILE

uint64_t refT = 0;

/* last access time */
map<uint64_t, uint64_t> lat;

/* source reference Id */
map<uint64_t, uint64_t> srcRef;

/* source iteration vector */
map<uint64_t, vector<int> > srcIter;

/* RI histogram */
map<uint64_t, uint64_t> RI;

/* Cache pos */
map<uint64_t, uint64_t> cachePos;

void rtTmpAccess(uint64_t addr, uint64_t ref_id, uint64_t array_id, vector<int> idx) {
    uint64_t index = addr;
	addr = addr * DS / CLS;
    refT++;
    
    if (lat.find(addr) != lat.end()) {
        uint64_t ri = refT - lat[addr];

#ifdef TRACE
		if (RI.find(ri) != RI.end()) {
			RI[ri] += 1;
		} else {
			RI[ri] = 1;
		}
#endif

#ifdef PROFILE
        cout << addr << ",";

        cout << srcRef[addr] << " ";
        
        for (int i = 0; i < srcIter[addr].size(); i++) {
            cout << srcIter[addr][i];
            if (i != srcIter[addr].size() - 1) {
                cout << " ";
            } else {
                cout << ",";
            }
        }
        
        cout << ref_id << " ";
        
		for (int i = 0; i < idx.size(); i++) {
			cout << idx[i];
            if (i != idx.size() - 1) {
                cout << " ";
            } else {
                cout << ",";
            }
		}
		cout << cachePos[addr] << ",";
		cout << index % (CLS/DS) << ",";
		cout << ri << endl;
#endif
	}
    
	lat[addr] = refT;
    srcRef[addr] = ref_id;
    srcIter[addr] = idx;
	cachePos[addr] = index % (CLS/DS);

    return;
}

void dumpRIHistogram() {
	for (auto ri : RI) {
		cout << ri.first << " " << ri.second << endl;
	}
	return;
}
