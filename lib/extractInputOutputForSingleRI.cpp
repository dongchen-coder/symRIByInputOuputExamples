#include "extractInputOutputForSingleRI.hpp"

// ref_id->isize->jsize->i->j->ri;
map<uint64_t, map<uint64_t, map<uint64_t, map<uint64_t, map<uint64_t, uint64_t>* >* >* >* > all_ri;

void processSingleRiFile(string name, int isize, int jsize) {
	
	ifstream ifs;
    ifs.open("./ris/"+name+"_" + to_string(isize) + "_" + to_string(jsize) + ".txt", ifstream::in);
	cout << "Open " << "../ris/"+name+"_" + to_string(isize) + "_" + to_string(jsize) + ".txt" << endl;   
	
    uint64_t ref_id;
    uint64_t addr;
    uint64_t i;
    uint64_t j;
    uint64_t ri;
    while (!ifs.eof()) {
        ifs >> ref_id;
        ifs >> addr;
        ifs >> i;
        ifs >> j;
        ifs >> ri;
        if(ifs.eof())
            break;
        //cout << ref_id << " " << addr << " " << i << " " << j << " " << ri << endl;
        
        if (all_ri.find(ref_id) == all_ri.end()) {
            all_ri[ref_id] = new map<uint64_t, map<uint64_t, map<uint64_t, map<uint64_t, uint64_t>* >* >* >;
        }
        if (all_ri[ref_id]->find(isize) == all_ri[ref_id]->end()) {
            (*all_ri[ref_id])[isize] = new map<uint64_t, map<uint64_t, map<uint64_t, uint64_t>* >* >;
        }
        if ((*all_ri[ref_id])[isize]->find(jsize) == (*all_ri[ref_id])[isize]->end()) {
			(*(*all_ri[ref_id])[isize])[jsize] = new map<uint64_t, map<uint64_t, uint64_t>* >;
		}
		if ((*(*all_ri[ref_id])[isize])[jsize]->find(i) == (*(*all_ri[ref_id])[isize])[jsize]->end()) {
			(*(*(*all_ri[ref_id])[isize])[jsize])[i] = new map<uint64_t, uint64_t>;
		}
    	(*(*(*(*all_ri[ref_id])[isize])[jsize])[i])[j] = ri;
	}

	ifs.close();
	return;
}

void readAllRi(string name, vector<int> sizes) {
    for (int i = 0; i < sizes.size(); i++) {
        for (int j = 0; j < sizes.size(); j++) {
            processSingleRiFile(name, sizes[i], sizes[j]);
        }
    }
    return;
}

void dumpPerRefRi(vector<int> sizes) {
    for (auto it = all_ri.begin(), eit = all_ri.end(); it != eit; ++it) {
        for (int si = 0; si < sizes.size(); si++) {
            for (int sj = 0; sj < sizes.size(); sj++) {
                cout << "ref_id " << (*it).first << " isize " << sizes[si] << " jsize " << sizes[sj] << endl;
                for (int i = 0; i < sizes[si]; i++) {
                    for (int j = 0; j < sizes[sj]; j++) {
                        
                        if ((*it->second).find(sizes[si]) != (*it->second).end() &&
                        (*(*it->second)[sizes[si]]).find(sizes[sj]) != (*(*it->second)[sizes[si]]).end() &&
                        (*(*(*it->second)[sizes[si]])[sizes[sj]]).find(i) != (*(*(*it->second)[sizes[si]])[sizes[sj]]).end() &&
                        (*(*(*(*it->second)[sizes[si]])[sizes[sj]])[i]).find(j) != (*(*(*(*it->second)[sizes[si]])[sizes[sj]])[i]).end() ) {
                            cout << setw(5) << (*(*(*(*it->second)[sizes[si]])[sizes[sj]])[i])[j] << " ";
                        } else {
                            cout << "    X ";
                        }
                    }
                    cout << endl;
                }
            }
        }
    }
    return;
}


void genInputOutputExample(string name, vector<int> sizes) {
	if (sizes.size() <= 0) {
		return;
	}
	int minSize = sizes[0];
    int maxSize = sizes[0];
	for (int i = 1; i < sizes.size(); i++) {
        if (sizes[i] < minSize) {
			minSize = sizes[i];
		}
        if (sizes[i] > maxSize) {
            maxSize = sizes[i];
        }
	}
    
	for (auto it = all_ri.begin(), eit = all_ri.end(); it != eit; ++it) {
        for (int i = 0; i < maxSize; i++) {
            for (int j = 0; j < maxSize; j++) {
                ofstream ofs;
                ofs.open("./inputoutput/"+name+"_ref_" + to_string(it->first) + "_iter_" + to_string(i) + "_" + to_string(j) + ".txt", ofstream::out);
                for (vector<int>::iterator it_i = sizes.begin(), eit_i = sizes.end(); it_i != eit_i; ++it_i) {
                    for (vector<int>::iterator it_j = sizes.begin(), eit_j = sizes.end(); it_j != eit_j; ++it_j) {
                        
                        ofs << "i " << i << " ";
                        ofs << "j " << j << " ";
                        ofs << "sizei " << *it_i << " ";
                        ofs << "sizej " << *it_j << " ";
                        
                        ofs << "_out ";
                        if ((*it->second).find(*it_i) != (*it->second).end() &&
                            (*(*it->second)[*it_i]).find(*it_j) != (*(*it->second)[*it_i]).end() &&
                            (*(*(*it->second)[*it_i])[*it_j]).find(i) != (*(*(*it->second)[*it_i])[*it_j]).end() &&
                            (*(*(*(*it->second)[*it_i])[*it_j])[i]).find(j) != (*(*(*(*it->second)[*it_i])[*it_j])[i]).end() ) {
                            ofs << (*(*(*(*all_ri[it->first])[*it_i])[*it_j])[i])[j];
                        } else {
                            ofs << "X";
                        }
                        ofs << endl;
                    }
                }
                ofs.close();
            }
        }
    }
    
	return;
}
