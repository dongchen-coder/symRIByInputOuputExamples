#include<iostream>
#include<map>
#include<set>
#include<vector>
using namespace std;

#define CLS 1
#define DS 1

uint64_t refT = 0;

/* last access time */
std::map<uint64_t, uint64_t> lat;

/* source reference Id */
std::map<uint64_t, uint64_t> srcRef;

/* source iteration vector */
std::map<uint64_t, vector<int> > srcIter;

void rtTmpAccess(uint64_t addr, uint64_t ref_id, uint64_t array_id, vector<int> idx) {
    addr = addr * DS / CLS;
    refT++;
    
    if (lat.find(addr) != lat.end()) {
        uint64_t ri = refT - lat[addr];
        
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
		cout << ri << endl;
	}
    /*
    else {
		cout << ref_id << " " << addr << " ";
        for (int i = 0; i < idx.size(); i++) {
            cout << idx[i];
            cout << " ";
        }
        cout << 0 << endl;
	}
     */
    lat[addr] = refT;
    srcRef[addr] = ref_id;
    srcIter[addr] = idx;

    return;
}
