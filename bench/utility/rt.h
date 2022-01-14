#include<iostream>
#include<map>
#include<set>
#include<vector>
#include"rt_conf.h"
using namespace std;

//#define CLS 32
//#define DS 8
//#define TRACE
//#define PROFILE
//#define PROGILE_IBOUND

//#define PROFILE_CSV
//#define PROFILE_IBOUND_CSV

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

bool csv_first_row = true;

void rtTmpAccess(uint64_t addr, uint64_t ref_id, uint64_t array_id, vector<int> idx) {
    uint64_t index = addr;
	addr = addr * DS / CLS;
    refT++;
    
#ifdef PROFILE_IBOUND
    cout << ref_id << ",";
    for (int i = 0; i < idx.size(); i++) {
        cout << idx[i];
        if (i != idx.size() - 1) {
            cout << " ";
        } else {
            cout << endl;
        }
    }
#endif
    
#ifdef PROFILE_IBOUND_CSV
    if (csv_first_row) {
        cout << "source reference ID,iteration vector\n";
        csv_first_row = false;
    }
    
    cout << ref_id << ",";
    for (int i = 0; i < idx.size(); i++) {
        cout << idx[i];
        cout << " ";
    }
    cout << "\n";
#endif

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
        cout << CLS << ",";
        cout << DS << ",";
		cout << ri << endl;
#endif
     
#ifdef PROFILE_CSV
        if (csv_first_row) {
            cout << "address,source reference ID,source iteration vector,sink reference ID,sink iteration vector,source cacheline postion,sink cacheline position,cache line size,data size,reuse interval\n";
            csv_first_row = false;
        }
        
        cout << addr << ",";

        cout << srcRef[addr] << ",";
        
        for (int i = 0; i < srcIter[addr].size(); i++) {
            cout << srcIter[addr][i];
            if (i+1 != srcIter[addr].size()) cout << " ";
            else cout << ",";
        }
        
        cout << ref_id << ",";
        
        for (int i = 0; i < idx.size(); i++) {
            cout << idx[i];
            if (i+1 != idx.size()) cout << " ";
            else cout << ",";
        }
        cout << cachePos[addr] << ",";
        cout << index % (CLS/DS) << ",";
        cout << CLS << ",";
        cout << DS << ",";
        cout << ri << "\n";
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
