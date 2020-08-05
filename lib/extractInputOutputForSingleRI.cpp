#include "extractInputOutputForSingleRI.hpp"

// ref_src_id -> ref_snk_id -> iter vector -> sizes vector -> ri;
map<uint64_t, map<uint64_t, map<vector<uint64_t>, map<vector<uint64_t>, uint64_t>* >* >* > all_ri;

size_t split(const std::string &txt, std::vector<std::string> &strs, char ch)
{
    size_t pos = txt.find( ch );
    size_t initialPos = 0;
    strs.clear();

    // Decompose statement
    while( pos != std::string::npos ) {
        strs.push_back( txt.substr( initialPos, pos - initialPos ) );
        initialPos = pos + 1;

        pos = txt.find( ch, initialPos );
    }

    // Add the last one
    strs.push_back( txt.substr( initialPos, std::min( pos, txt.size() ) - initialPos + 1 ) );

    return strs.size();
}

void processSingleRiFile(string name, string fileSuffix, vector<uint64_t> symbolic_bounds) {

    string fileName = name + fileSuffix;
	ifstream ifs;
    ifs.open("./inputoutput/raw_ris_per_size/"+ name + "/" + fileName, ifstream::in);
    if (ifs.is_open()) {
        cout << "./inputoutput/raw_ris_per_size/"+ name + "/" + fileName << " succeed " << endl;
    } else {
        cout << "./inputoutput/raw_ris_per_size/"+ name + "/" + fileName << " failed " << endl;
    }
    
    uint64_t ref_src_id;
    uint64_t ref_snk_id;
    uint64_t addr;
    vector<uint64_t> idx;
    uint64_t ri;
    if (ifs.is_open()) {
        string line;
        vector<string> lineList;
        while(getline(ifs, line)) {
            int lineListLen = split(line, lineList, ' ');
            if (lineListLen < 3) {
                cout << "Error in dumping RI" << endl;
                break;
            }
            ref_src_id = stoi(lineList[0]);
            ref_snk_id = stoi(lineList[1]);
            
            addr = stoi(lineList[2]);
            idx.clear();
            for (int i = 3; i < lineListLen-1; i++) {
                idx.push_back(stoi(lineList[i]));
            }
            ri = stoi(lineList[lineListLen-1]);
            
            if (all_ri.find(ref_src_id) == all_ri.end()) {
                all_ri[ref_src_id] = new map< uint64_t, map<vector<uint64_t>, map<vector<uint64_t>, uint64_t>* >* >;
            }
            if (all_ri[ref_src_id]->find(ref_snk_id) == all_ri[ref_src_id]->end()) {
                (*all_ri[ref_src_id])[ref_snk_id] = new map<vector<uint64_t>, map<vector<uint64_t>, uint64_t>* >;
            }
            if ((*all_ri[ref_src_id])[ref_snk_id]->find(idx) == (*all_ri[ref_src_id])[ref_snk_id]->end()) {
                (*(*all_ri[ref_src_id])[ref_snk_id])[idx] = new map<vector<uint64_t>, uint64_t>;
            }
            (*(*(*all_ri[ref_src_id])[ref_snk_id])[idx])[symbolic_bounds] = ri;
        }
    }
	ifs.close();
	return;

}

void readAllRi(string name, vector<uint64_t> sizes, int numOfSymbolicLoopBounds) {
    int numOfSizes = sizes.size();
    
    int numOfCombinations;
    if (numOfSizes == 0 || numOfSymbolicLoopBounds == 0) {
        numOfCombinations = 0;
    } else {
        numOfCombinations = 1;
    }
    for (int i = 0; i < numOfSymbolicLoopBounds; i++) {
        numOfCombinations *= numOfSizes;
    }
    
    for (int i = 0; i < numOfCombinations; i++) {
        string symbolic_bounds_str = "";
        vector<uint64_t> symbolic_bounds;
        int symbolic_bounds_idx = i;
        for (int j = 0; j < numOfSymbolicLoopBounds; j++) {
            symbolic_bounds_str += "_";
            symbolic_bounds_str += to_string(sizes[symbolic_bounds_idx % numOfSizes]);
            symbolic_bounds.push_back(sizes[symbolic_bounds_idx % numOfSizes]);
            symbolic_bounds_idx /= numOfSizes;
        }
        processSingleRiFile(name, symbolic_bounds_str + ".txt", symbolic_bounds);
    }
        
    return;
}

void dumpPerRefRi(vector<uint64_t> sizes) {
    /*
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
    */
    return;
}


void genInputOutputExample(string name, vector<uint64_t> sizes, int numOfSymbolicLoopBounds) {
    
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
    
    for (auto ref_src_it = all_ri.begin(), ref_src_eit = all_ri.end(); ref_src_it != ref_src_eit; ++ref_src_it) {
        ofstream ofs_perIterRefsrc;
        
        for (auto ref_snk_it = (ref_src_it->second)->begin(), ref_snk_eit = (ref_src_it->second)->end(); ref_snk_it != ref_snk_eit; ++ref_snk_it) {
            ofstream ofs_perIterRefsrcsnk;
            
            for (auto idx_it = (ref_snk_it->second)->begin(), idx_eit = (ref_snk_it->second)->end(); idx_it != idx_eit; ++idx_it) {
            
                vector<uint64_t> idx = idx_it->first;
                string idx_str = "";
                for (int i = 0; i < idx.size(); i++) {
                    idx_str += "_" + to_string(idx[i]);
                }
                
                /* create a file named by ref src ID and iteration vector */
                ofs_perIterRefsrc.open("./inputoutput/ris_per_iter_refsrc/" + name + "/" +name+"_refsrc_" + to_string(ref_src_it->first) + "_iter" + idx_str + ".txt", ofstream::out);
                /* create a file named by ref src/snk ID and iteration vector */
                ofs_perIterRefsrcsnk.open("./inputoutput/ris_per_iter_refsrcsnk/" + name + "/" +name+"_refsrc_" + to_string(ref_src_it->first) + "_refsnk_" + to_string(ref_snk_it->first) + "_iter" + idx_str + ".txt", ofstream::out);
                
                /* Check each sizes for symoblic bounds */
                int numOfSizes = sizes.size();
                int numOfCombinations;
                if (numOfSizes == 0 || numOfSymbolicLoopBounds == 0) {
                    numOfCombinations = 0;
                } else {
                    numOfCombinations = 1;
                }
                for (int i = 0; i < numOfSymbolicLoopBounds; i++) {
                    numOfCombinations *= numOfSizes;
                }
            
                for (int i = 0; i < numOfCombinations; i++) {
                    vector<uint64_t> symbolic_bounds;
                    int symbolic_bounds_idx = i;
                    for (int j = 0; j < numOfSymbolicLoopBounds; j++) {
                        symbolic_bounds.push_back(sizes[symbolic_bounds_idx % numOfSizes]);
                        symbolic_bounds_idx /= numOfSizes;
                    }
                
                    /* iteration vector is one of the inputs */
                    for (int j = 0; j < idx.size(); j++) {
                        ofs_perIterRefsrc << "I" + to_string(j) << " " << to_string(idx[j]) << " ";
                        ofs_perIterRefsrcsnk << "I" + to_string(j) << " " << to_string(idx[j]) << " ";
                    }
                
                    /* symbolic bounds is another input */
                    for (int j = 0; j < symbolic_bounds.size(); j++) {
                        ofs_perIterRefsrc << "B" + to_string(j) << " " << to_string(symbolic_bounds[j]) << " ";
                        ofs_perIterRefsrcsnk << "B" + to_string(j) << " " << to_string(symbolic_bounds[j]) << " ";
                    }
                
                    if ((*idx_it->second).find(symbolic_bounds) != (*idx_it->second).end()) {
                        ofs_perIterRefsrc << "_out " << (*idx_it->second)[symbolic_bounds] << endl;
                        ofs_perIterRefsrcsnk << "_out " << (*idx_it->second)[symbolic_bounds] << endl;
                    } else {
                        ofs_perIterRefsrc << "_out " << -1 << endl;
                        ofs_perIterRefsrcsnk << "_out " << -1 << endl;
                    }
                }
                
                ofs_perIterRefsrcsnk.close();
                ofs_perIterRefsrc.close();
            }
        }
    }
    
	return;
}
