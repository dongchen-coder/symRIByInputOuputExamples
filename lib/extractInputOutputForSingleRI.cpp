#include "extractInputOutputForSingleRI.hpp"

// ref_src_id -> souce pos -> ref_snk_id -> sink pos -> src iter vector -> snk iter vector -> sizes vector -> ri;
map<uint64_t, map<uint64_t, map<uint64_t, map<uint64_t, map<vector<uint64_t>, map<vector<uint64_t>, map<vector<uint64_t>, uint64_t>* >* >* >* >* >* > all_ri;

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

void filterSrcIter() {
    /* Need fitering rules */
    /*
    for (const auto ref_src_id_it : all_ri) {
        uint64_t ref_src_id = *(ref_src_id_it.first);
        for (const auto ref_snk_id_it : *(ref_src_id_it.second)) {
            uint64_t ref_snk_id = *(ref_src_id_it.first;
            for (const auto src_iter_it : *(ref_snk_id_it.second)) {
                vector<uint64_t> src_iter = *(src_iter_it.first);
                for (const auto snk_iter_it : *(src_iter_it.second)) {
                    vector<uint64_t> snk_iter = *(snk_iter_it.first);
                    uint64_t ri = *(snk_iter_it.second);
                }
            }
        }
    }
     */
}

vector<vector<uint64_t> > getAllNeighborIdxs(vector<uint64_t> idx) {
    vector<vector<uint64_t> > neighborIdxs;
    for (const auto i : idx) {
        if (neighborIdxs.empty()) {
            neighborIdxs.push_back({i});
            neighborIdxs.push_back({i-1});
            neighborIdxs.push_back({i+1});
        } else {
            vector<vector<uint64_t> > neighborIdxs_new;
            for (auto j : neighborIdxs) {
                vector<uint64_t> cur_j = j;
                cur_j.push_back(i);
                neighborIdxs_new.push_back(cur_j);
                cur_j = j;
                cur_j.push_back(i-1);
                neighborIdxs_new.push_back(cur_j);
                cur_j = j;
                cur_j.push_back(i+1);
                neighborIdxs_new.push_back(cur_j);
            }
            neighborIdxs = neighborIdxs_new;
        }
    }
    
    if (find(neighborIdxs.begin(), neighborIdxs.end(), idx) != neighborIdxs.end()) {
        neighborIdxs.erase(find(neighborIdxs.begin(), neighborIdxs.end(), idx));
    }
    
    return neighborIdxs;
}

vector<vector<uint64_t> > samplingBorderInner(vector<vector<uint64_t> > idxs, double samplingRate) {
    if (samplingRate == 1.0) {
        return idxs;
    }
    if (idxs.empty()) {
        return idxs;
    }
    cout << "all src idxs size " << idxs.size() << endl;
    vector<vector<uint64_t> > borderIdxs;
    vector<vector<uint64_t> > innerIdxs;
    for (const auto idx : idxs) {
        
        vector<vector<uint64_t> > neighborIdxs = getAllNeighborIdxs(idx);
        bool innerFlag = true;
        for (const auto neighborIdx : neighborIdxs) {
            if (find(idxs.begin(), idxs.end(), neighborIdx) == idxs.end()) {
                borderIdxs.push_back(idx);
                innerFlag = false;
                break;
            }
        }
        
        if (innerFlag) {
            innerIdxs.push_back(idx);
        }
    }
    cout << "border size " << borderIdxs.size() << " inner size " << innerIdxs.size() << endl;
    
    int numOfLoops = idxs.front().size();
    
    uint64_t numOfBorderSamples = borderIdxs.size() * samplingRate;
    uint64_t numOfInnerSamples = innerIdxs.size() * samplingRate;
    for (int i = 1; i < numOfLoops; i++) {
        numOfInnerSamples = numOfInnerSamples * samplingRate;
    }
    
    cout << "border size " << numOfBorderSamples << " inner size " << numOfInnerSamples << endl;
    
    set<int> borderSamples;
    set<int> innerSamples;
    
    for (int i = 0; i < numOfBorderSamples; i++) {
        int offset = rand() % borderIdxs.size();
        while (borderSamples.find(offset) != borderSamples.end()) {
            offset = rand() % borderIdxs.size();
        }
        borderSamples.insert(offset);
    }
    for (int i = 0; i < numOfInnerSamples; i++) {
        int offset = rand() % innerIdxs.size();
        while (innerSamples.find(offset) != innerSamples.end()) {
            offset = rand() % innerIdxs.size();
        }
        innerSamples.insert(offset);
    }
    
    vector< vector<uint64_t> > sampled_idxs;
    for (auto i : borderSamples) {
        sampled_idxs.push_back(borderIdxs[i]);
    }
    for (auto i : innerSamples) {
        sampled_idxs.push_back(innerIdxs[i]);
    }
    
    return sampled_idxs;
}

vector<vector<uint64_t> > samplingRandom(vector< vector<uint64_t> > idxs, double samplingRate) {
    if (samplingRate == 1.0) {
        return idxs;
    }
    if (idxs.empty()) {
        return idxs;
    }
    
    int numOfLoops = idxs.front().size();
    uint64_t numOfSamples = idxs.size() * samplingRate;
    for (int i = 1; i < numOfLoops; i++) {
        numOfSamples = numOfSamples * samplingRate;
    }
    
    set<int> samples;
    for (int i = 0; i < numOfSamples; i++) {
        int offset = rand() % idxs.size();
        while (samples.find(offset) != samples.end()) {
            offset = rand() % idxs.size();
        }
        samples.insert(offset);
        if (samples.size() == idxs.size()) {
            break;
        }
    }
    
    vector< vector<uint64_t> > sampled_idxs;
    for (auto i : samples) {
        sampled_idxs.push_back(idxs[i]);
    }
    
    return sampled_idxs;
}

void processSingleRiFile(string cacheConfig, string name, string fileSuffix, vector<uint64_t> symbolic_bounds) {

    string fileName = name + fileSuffix;
	ifstream ifs;
    ifs.open("./inputoutput/raw_ris_per_size_" + cacheConfig + "/"+ name + "/" + fileName, ifstream::in);
    if (ifs.is_open()) {
        cout << "./inputoutput/raw_ris_per_size_" + cacheConfig + "/"+ name + "/" + fileName << " succeed " << endl;
    } else {
        cout << "./inputoutput/raw_ris_per_size_" + cacheConfig + "/"+ name + "/" + fileName << " failed " << endl;
    }
    
    uint64_t ref_src_id;
    uint64_t ref_snk_id;
    uint64_t addr;
    vector<uint64_t> idx_src;
    vector<uint64_t> idx_snk;
    uint64_t sourcePos;
    uint64_t sinkPos;
    uint64_t ri;
    if (ifs.is_open()) {
        string line;
        vector<string> lineList;
        while(getline(ifs, line)) {
            int lineListLen = split(line, lineList, ',');
            //cout << line << endl;
            if (lineListLen < 4) {
                cout << "Error in dumping RI" << endl;
                break;
            }
            
            vector<string> srcIDIterV;
            int srcIDIterVLen = split(lineList[1], srcIDIterV, ' ');
            vector<string> snkIDIterV;
            int snkIDIterVLen = split(lineList[2], snkIDIterV, ' ');
            
            //cout << "srcIDIterVLen " << srcIDIterVLen << " snkIDIterVLen " << snkIDIterVLen << endl;
            
            ref_src_id = stoi(srcIDIterV[0]);
            ref_snk_id = stoi(snkIDIterV[0]);
            
            addr = stoi(lineList[1]);
            
            idx_src.clear();
            idx_snk.clear();
            
            for (int i = 1; i < srcIDIterVLen; i++) {
                idx_src.push_back(stoi(srcIDIterV[i]));
            }
            for (int i = 1; i < snkIDIterVLen; i++) {
                idx_snk.push_back(stoi(snkIDIterV[i]));
            }
            
            sourcePos = stoi(lineList[lineListLen-3]);
            sinkPos = stoi(lineList[lineListLen-2]);
            ri = stoi(lineList[lineListLen-1]);
            
            if (all_ri.find(ref_src_id) == all_ri.end()) {
                all_ri[ref_src_id] = new map<uint64_t, map<uint64_t, map<uint64_t, map<vector<uint64_t>, map<vector<uint64_t>, map<vector<uint64_t>, uint64_t>* >* >* >* >* >;
            }
            if (all_ri[ref_src_id]->find(sourcePos) == all_ri[ref_src_id]->end()) {
                (*all_ri[ref_src_id])[sourcePos] = new map<uint64_t, map<uint64_t, map<vector<uint64_t>, map<vector<uint64_t>, map<vector<uint64_t>, uint64_t>* >* >* >* >;
            }
            if ((*all_ri[ref_src_id])[sourcePos]->find(ref_snk_id) ==  (*all_ri[ref_src_id])[sourcePos]->end()) {
                (*(*all_ri[ref_src_id])[sourcePos])[ref_snk_id] = new map<uint64_t, map<vector<uint64_t>, map<vector<uint64_t>, map<vector<uint64_t>, uint64_t>* >* >* >;
            }
            if ((*(*all_ri[ref_src_id])[sourcePos])[ref_snk_id]->find(sinkPos) == (*(*all_ri[ref_src_id])[sourcePos])[ref_snk_id]->end()) {
                (*(*(*all_ri[ref_src_id])[sourcePos])[ref_snk_id])[sinkPos] = new map<vector<uint64_t>, map<vector<uint64_t>, map<vector<uint64_t>, uint64_t>* >* >;
            }
            if ((*(*(*all_ri[ref_src_id])[sourcePos])[ref_snk_id])[sinkPos]->find(idx_src) == (*(*(*all_ri[ref_src_id])[sourcePos])[ref_snk_id])[sinkPos]->end()) {
                (*(*(*(*all_ri[ref_src_id])[sourcePos])[ref_snk_id])[sinkPos])[idx_src] = new map<vector<uint64_t>, map<vector<uint64_t>, uint64_t>* >;
            }
            if ((*(*(*(*all_ri[ref_src_id])[sourcePos])[ref_snk_id])[sinkPos])[idx_src]->find(idx_snk) == (*(*(*(*all_ri[ref_src_id])[sourcePos])[ref_snk_id])[sinkPos])[idx_src]->end()) {
                (*(*(*(*(*all_ri[ref_src_id])[sourcePos])[ref_snk_id])[sinkPos])[idx_src])[idx_snk] = new map<vector<uint64_t>, uint64_t>;
            }
            (*(*(*(*(*(*all_ri[ref_src_id])[sourcePos])[ref_snk_id])[sinkPos])[idx_src])[idx_snk])[symbolic_bounds] = ri;
        }
    }
	ifs.close();
	return;

}

void readAllRi(string cacheConfig, string name, vector<uint64_t> sizes, int numOfSymbolicLoopBounds) {
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
        processSingleRiFile(cacheConfig, name, symbolic_bounds_str + ".txt", symbolic_bounds);
    }
        
    return;
}

void dumpPerRefRi(vector<uint64_t> sizes) {
    // ref_src_id -> ref_snk_id -> src iter vector -> snk iter vector -> sizes vector -> ri;
    for (auto ref_src_it : all_ri) {
        for (auto ref_snk_it : (*ref_src_it.second)) {
            for (auto idx_src_it : (*ref_snk_it.second)) {
                for (auto idx_snk_it : (*idx_src_it.second)) {
                    for (auto cur_sizes_ri : (*idx_snk_it.second)) {
                        /*
                        {
                            cout << "RefSrc " << ref_src_it.first << " RefSnk " << ref_snk_it.first << " ";
                            cout << "IdxSrc ";
                            for (auto idx : idx_src_it.first) cout << idx << " ";
                            cout << "IdxSnk ";
                            for (auto idx : idx_snk_it.first) cout << idx << " ";
                            cout << "Sizes ";
                            for (auto size : cur_sizes_ri.first) cout << size << " ";
                            cout << "RI ";
                            cout << cur_sizes_ri.second << endl;
                         }
                         */
                    }
                }
            }
        }
    }
    
    return;
}

void genInOutWithFormatSrcIterPos(string cacheConfig, string name, vector<uint64_t> sizes, int numOfSymbolicLoopBounds, double samplingRate) {
    
	if (sizes.size() <= 0) {
		return;
	}
    
    // ref_src_id -> souce pos -> ref_snk_id -> sink pos -> src iter vector -> snk iter vector -> sizes vector -> ri;
    for (auto ref_src_it : all_ri) {
        for (auto src_pos_it : (*ref_src_it.second)) {
            
            ofstream ofs_Refsrc_Isrc_Psrc;
            // sample src idxs
            vector<vector<uint64_t> > all_src_idxs;
            for (auto ref_snk_it : (*src_pos_it.second)) {
                for (auto snk_pos_it : (*ref_snk_it.second)) {
                    for (const auto idx_src_it : (*snk_pos_it.second)) {
                        if (find(all_src_idxs.begin(), all_src_idxs.end(), idx_src_it.first) == all_src_idxs.end()) {
                            all_src_idxs.push_back(idx_src_it.first);
                        }
                    }
                }
            }
            
            vector<vector<uint64_t> > sampled_idxs = samplingRandom(all_src_idxs, samplingRate);
            map<vector<uint64_t>, map<vector<uint64_t>, uint64_t>* > srciterSizeRi;
        
            for (auto ref_snk_it : (*src_pos_it.second)) {
                for (auto snk_pos_it : (*ref_snk_it.second)) {
                    for (auto idx_src_it : (*snk_pos_it.second)) {
                        if (find(sampled_idxs.begin(), sampled_idxs.end(), idx_src_it.first) == sampled_idxs.end()) {
                            continue;
                        }
                        vector<uint64_t> idx_src = idx_src_it.first;
                        // snk iter vector -> sizes vector -> ri;
                        for (auto idx_snk_it : (*idx_src_it.second) ) {
                            // sizes vector -> ri;
                            for (auto cur_sizes_it : (*idx_snk_it.second)) {
                                vector<uint64_t> cur_sizes = cur_sizes_it.first;
                                if (srciterSizeRi.find(idx_src) == srciterSizeRi.end()) {
                                    srciterSizeRi[idx_src] = new map<vector<uint64_t>, uint64_t>;
                                }
                                (*srciterSizeRi[idx_src])[cur_sizes] = cur_sizes_it.second;
                            }
                        }
                    }
                }
            }
        
            for (auto elm : srciterSizeRi) {
            
                vector<uint64_t> idx_src = elm.first;
                map<vector<uint64_t>, uint64_t> sizes_ri = *(elm.second);
            
                string idx_src_str = "";
                for (int i = 0; i < idx_src.size(); i++) {
                    idx_src_str += "_" + to_string(idx_src[i]);
                }
                
                ofs_Refsrc_Isrc_Psrc.open("./inputoutput/ris_refsrc_Isrc_Psrc/" + name + "/" + name +
                "_refsrc_" + to_string(ref_src_it.first) +
                "_Isrc" + idx_src_str +
                "_Psrc_" + to_string(src_pos_it.first) +
                ".RI." + cacheConfig, ofstream::out);
            
                // Check each sizes for symoblic bounds
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
        
                    if (sizes_ri.find(symbolic_bounds) != sizes_ri.end()) {
                        // iteration vector is one of the inputs
                        for (int j = 0; j < idx_src.size(); j++) {
                            ofs_Refsrc_Isrc_Psrc << "Isrc" + to_string(j) << " " << to_string(idx_src[j]) << " ";
                        }
                        // symbolic bounds is another input
                        for (int j = 0; j < symbolic_bounds.size(); j++) {
                            ofs_Refsrc_Isrc_Psrc << "B" + to_string(j) << " " << to_string(symbolic_bounds[j]) << " ";
                        }
                        ofs_Refsrc_Isrc_Psrc << "_out " << sizes_ri[symbolic_bounds] << endl;
                    } else {
                        for (int j = 0; j < idx_src.size(); j++) {
                            ofs_Refsrc_Isrc_Psrc << "Isrc" + to_string(j) << " " << to_string(idx_src[j]) << " ";
                        }
                        for (int j = 0; j < symbolic_bounds.size(); j++) {
                            ofs_Refsrc_Isrc_Psrc << "B" + to_string(j) << " " << to_string(symbolic_bounds[j]) << " ";
                        }
                        ofs_Refsrc_Isrc_Psrc << "_out " << 0 << endl;
                    }
                }
                
                ofs_Refsrc_Isrc_Psrc.close();
            }
        }
    }
    
	return;
}

void genInOutWithFormatSrcIterPosSnk(string cacheConfig, string name, vector<uint64_t> sizes, int numOfSymbolicLoopBounds, double samplingRate) {
    if (sizes.size() <= 0) {
        return;
    }
    // ref_src_id -> souce pos -> ref_snk_id -> sink pos -> src iter vector -> snk iter vector -> sizes vector -> ri;
    for (auto ref_src_it : all_ri) {
        for (auto src_pos_it : (*ref_src_it.second)) {
            for (auto ref_snk_it : (*src_pos_it.second)) {
                
                ofstream ofs_Refsrc_Isrc_Psrc_Refsnk;
                // sample src idxs
                vector<vector<uint64_t> > all_src_idxs;
                for (auto snk_pos_it : (*ref_snk_it.second)) {
                    for (const auto idx_src_it : (*snk_pos_it.second)) {
                        if (find(all_src_idxs.begin(), all_src_idxs.end(), idx_src_it.first) == all_src_idxs.end()) {
                            all_src_idxs.push_back(idx_src_it.first);
                        }
                    }
                }
                vector<vector<uint64_t> > sampled_idxs = samplingRandom(all_src_idxs, samplingRate);
                map<vector<uint64_t>, map<vector<uint64_t>, uint64_t>* > srciterSizeRi;
                
                for (auto snk_pos_it : (*ref_snk_it.second)) {
                    for (auto idx_src_it : (*snk_pos_it.second)) {
                        if (find(sampled_idxs.begin(), sampled_idxs.end(), idx_src_it.first) == sampled_idxs.end()) {
                            continue;
                        }
                        vector<uint64_t> idx_src = idx_src_it.first;
                        // snk iter vector -> sizes vector -> ri;
                        for (auto idx_snk_it : (*idx_src_it.second) ) {
                            // sizes vector -> ri;
                            for (auto cur_sizes_it : (*idx_snk_it.second)) {
                                vector<uint64_t> cur_sizes = cur_sizes_it.first;
                                if (srciterSizeRi.find(idx_src) == srciterSizeRi.end()) {
                                    srciterSizeRi[idx_src] = new map<vector<uint64_t>, uint64_t>;
                                }
                                (*srciterSizeRi[idx_src])[cur_sizes] = cur_sizes_it.second;
                            }
                        }
                    }
                }
                
                for (auto elm : srciterSizeRi) {
                    
                        vector<uint64_t> idx_src = elm.first;
                        map<vector<uint64_t>, uint64_t> sizes_ri = *(elm.second);
                    
                        string idx_src_str = "";
                        for (int i = 0; i < idx_src.size(); i++) {
                            idx_src_str += "_" + to_string(idx_src[i]);
                        }
                        
                        // create a file named by ref src ID and iteration vector
                        ofs_Refsrc_Isrc_Psrc_Refsnk.open("./inputoutput/ris_refsrc_Isrc_Psrc_refsnk/" + name + "/" + name +
                                               "_refsrc_" + to_string(ref_src_it.first) +
                                               "_Isrc" + idx_src_str +
                                               "_Psrc_" + to_string(src_pos_it.first) +
                                               "_refsnk_" + to_string(ref_snk_it.first) +
                                               ".RI." + cacheConfig, ofstream::out);
                        
                        // Check each sizes for symoblic bounds
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
                
                        if (sizes_ri.find(symbolic_bounds) != sizes_ri.end()) {
                            // iteration vector is one of the inputs
                            for (int j = 0; j < idx_src.size(); j++) {
                                ofs_Refsrc_Isrc_Psrc_Refsnk << "Isrc" + to_string(j) << " " << to_string(idx_src[j]) << " ";
                            }
                            // symbolic bounds is another input
                            for (int j = 0; j < symbolic_bounds.size(); j++) {
                                ofs_Refsrc_Isrc_Psrc_Refsnk << "B" + to_string(j) << " " << to_string(symbolic_bounds[j]) << " ";
                            }
                            ofs_Refsrc_Isrc_Psrc_Refsnk << "_out " << sizes_ri[symbolic_bounds] << endl;
                        } else {
                            for (int j = 0; j < idx_src.size(); j++) {
                                ofs_Refsrc_Isrc_Psrc_Refsnk << "Isrc" + to_string(j) << " " << to_string(idx_src[j]) << " ";
                            }
                            for (int j = 0; j < symbolic_bounds.size(); j++) {
                                ofs_Refsrc_Isrc_Psrc_Refsnk << "B" + to_string(j) << " " << to_string(symbolic_bounds[j]) << " ";
                            }
                            ofs_Refsrc_Isrc_Psrc_Refsnk << "_out " << 0 << endl;
                        }
                    }
                    
                    ofs_Refsrc_Isrc_Psrc_Refsnk.close();
                }
            }
        }
    }
}

void genInOutWithFormatSrcIterPosSnkIterPos(string cacheConfig, string name, vector<uint64_t> sizes, int numOfSymbolicLoopBounds, double samplingRate) {
    if (sizes.size() <= 0) {
        return;
    }
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
    
    // ref_src_id -> souce pos -> ref_snk_id -> sink pos -> src iter vector -> snk iter vector -> sizes vector -> ri;
    for (auto ref_src_it : all_ri) {
        for (auto src_pos_it : (*ref_src_it.second)) {
            for (auto ref_snk_it : (*src_pos_it.second)) {
                
                // sample src idxs
                vector<vector<uint64_t> > all_src_idxs;
                for (auto snk_pos_it : (*ref_snk_it.second)) {
                    for (const auto idx_src_it : (*snk_pos_it.second)) {
                        if (find(all_src_idxs.begin(), all_src_idxs.end(), idx_src_it.first) == all_src_idxs.end()) {
                            all_src_idxs.push_back(idx_src_it.first);
                        }
                    }
                }
                
                vector<vector<uint64_t> > sampled_idxs = samplingRandom(all_src_idxs, samplingRate);
                
                // gen example for RI
                uint64_t sinkIterSize;
                map<vector<uint64_t>, map< vector<uint64_t>, vector<uint64_t> >* > srciterSizeSnkiter;
                map<vector<uint64_t>, map<vector<uint64_t>, map<vector<uint64_t>, uint64_t>* >* > srciterSizeSnkiterRi;
                
                for (auto snk_pos_it : (*ref_snk_it.second)) {
                    for (auto idx_src_it : (*snk_pos_it.second)) {
                        if (find(sampled_idxs.begin(), sampled_idxs.end(), idx_src_it.first) == sampled_idxs.end()) {
                            continue;
                        }
                        vector<uint64_t> idx_src = idx_src_it.first;
                        // snk iter vector -> sizes vector -> ri;
                        for (auto idx_snk_it : (*idx_src_it.second) ) {
                            vector<uint64_t> idx_snk = idx_snk_it.first;
                            sinkIterSize = idx_snk.size();
                            // sizes vector -> ri;
                            for (auto cur_sizes_it : (*idx_snk_it.second)) {
                                vector<uint64_t> cur_sizes = cur_sizes_it.first;
                                if (srciterSizeSnkiterRi.find(idx_src) == srciterSizeSnkiterRi.end()) {
                                    srciterSizeSnkiterRi[idx_src] = new map<vector<uint64_t>, map<vector<uint64_t>, uint64_t>* >;
                                }
                                if ((*srciterSizeSnkiterRi[idx_src]).find(cur_sizes) == (*srciterSizeSnkiterRi[idx_src]).end()) {
                                    (*srciterSizeSnkiterRi[idx_src])[cur_sizes] = new map<vector<uint64_t>, uint64_t>;
                                }
                                (*(*srciterSizeSnkiterRi[idx_src])[cur_sizes])[idx_snk] = cur_sizes_it.second;
                                
                                if (srciterSizeSnkiter.find(idx_src) == srciterSizeSnkiter.end()) {
                                    srciterSizeSnkiter[idx_src] = new map< vector<uint64_t>, vector<uint64_t> >;
                                }
                                (*srciterSizeSnkiter[idx_src])[cur_sizes] = idx_snk;
                            }
                        }
                    }
                }
                ofstream ofs_Refsrc_Isrc_Psrc_Refsnk_RI;
                for (auto elm : srciterSizeSnkiterRi) {
                    
                    vector<uint64_t> idx_src = elm.first;
                    map<vector<uint64_t>, map<vector<uint64_t>, uint64_t>* > sizes_idxsnk_ri = *(elm.second);
                    
                    string idx_src_str = "";
                    for (int i = 0; i < idx_src.size(); i++) {
                        idx_src_str += "_" + to_string(idx_src[i]);
                    }
                    
                    // create a file named by ref src ID and iteration vector
                    ofs_Refsrc_Isrc_Psrc_Refsnk_RI.open("./inputoutput/ris_refsrc_Isrc_Psrc_refsnk_Isnk_Psnk/" + name + "/" + name +
                                               "_refsrc_" + to_string(ref_src_it.first) +
                                               "_Isrc" + idx_src_str +
                                               "_Psrc_" + to_string(src_pos_it.first) +
                                               "_refsnk_" + to_string(ref_snk_it.first) +
                                               ".RI." + cacheConfig, ofstream::out);
                        
                    // Check each sizes for symoblic bounds
                    
                    for (int i = 0; i < numOfCombinations; i++) {
                        vector<uint64_t> symbolic_bounds;
                        int symbolic_bounds_idx = i;
                        for (int j = 0; j < numOfSymbolicLoopBounds; j++) {
                            symbolic_bounds.push_back(sizes[symbolic_bounds_idx % numOfSizes]);
                            symbolic_bounds_idx /= numOfSizes;
                        }
                        
                        if (sizes_idxsnk_ri.find(symbolic_bounds) != sizes_idxsnk_ri.end()) {
                            // iteration vector is one of the inputs
                            for (int j = 0; j < idx_src.size(); j++) {
                                ofs_Refsrc_Isrc_Psrc_Refsnk_RI << "Isrc" + to_string(j) << " " << to_string(idx_src[j]) << " ";
                            }
                            for (auto idxsnk_ri : *sizes_idxsnk_ri[symbolic_bounds]) {
                                vector<uint64_t> idx_snk = idxsnk_ri.first;
                                for (int j = 0; j < idx_snk.size(); j++) {
                                    ofs_Refsrc_Isrc_Psrc_Refsnk_RI << "Isnk" + to_string(j) << " " << to_string(idx_snk[j]) << " ";
                                }
                                for (int j = 0; j < symbolic_bounds.size(); j++) {
                                    ofs_Refsrc_Isrc_Psrc_Refsnk_RI << "B" + to_string(j) << " " << to_string(symbolic_bounds[j]) << " ";
                                }
                                ofs_Refsrc_Isrc_Psrc_Refsnk_RI << "_out " << (*sizes_idxsnk_ri[symbolic_bounds])[idx_snk] << endl;
                            }
                        } else {
                            for (int j = 0; j < idx_src.size(); j++) {
                                ofs_Refsrc_Isrc_Psrc_Refsnk_RI << "Isrc" + to_string(j) << " " << to_string(idx_src[j]) << " ";
                            }
                            for (int j = 0; j < idx_src.size(); j++) {
                                ofs_Refsrc_Isrc_Psrc_Refsnk_RI << "Isnk" + to_string(j) << " " << to_string(idx_src[j]) << " ";
                            }
                            for (int j = 0; j < symbolic_bounds.size(); j++) {
                                ofs_Refsrc_Isrc_Psrc_Refsnk_RI << "B" + to_string(j) << " " << to_string(symbolic_bounds[j]) << " ";
                            }
                            ofs_Refsrc_Isrc_Psrc_Refsnk_RI << "_out " << 0 << endl;
                        }
                    }
                    ofs_Refsrc_Isrc_Psrc_Refsnk_RI.close();
                }
                
                
                // gen example for Isnk
                for (int sinkIdx = 0; sinkIdx < sinkIterSize; sinkIdx++) {
                    for (auto elm : srciterSizeSnkiter) {
                        vector<uint64_t> idx_src = elm.first;
                        map<vector<uint64_t>, vector<uint64_t> > sizes_idxsnk = *(elm.second);
                        
                        string idx_src_str = "";
                        for (int i = 0; i < idx_src.size(); i++) {
                            idx_src_str += "_" + to_string(idx_src[i]);
                        }
                        
                        // create a file named by ref src ID and iteration vector
                        string fileName = "./inputoutput/ris_refsrc_Isrc_Psrc_refsnk_Isnk_Psnk/" + name + "/" + name +
                                      "_refsrc_" + to_string(ref_src_it.first) +
                                      "_Isrc" + idx_src_str +
                                      "_Psrc_" + to_string(src_pos_it.first) +
                                      "_refsnk_" + to_string(ref_snk_it.first) +
                                      ".Isnk" + to_string(sinkIdx) +
                                      "." + cacheConfig;
                        
                        ofstream ofs_Refsrc_Isrc_Psrc_Refsnk_Isnk;
                        ofs_Refsrc_Isrc_Psrc_Refsnk_Isnk.open(fileName, ofstream::out);
                        
                        for (int i = 0; i < numOfCombinations; i++) {
                            vector<uint64_t> symbolic_bounds;
                            int symbolic_bounds_idx = i;
                            for (int j = 0; j < numOfSymbolicLoopBounds; j++) {
                                symbolic_bounds.push_back(sizes[symbolic_bounds_idx % numOfSizes]);
                                symbolic_bounds_idx /= numOfSizes;
                            }
                            
                            if (sizes_idxsnk.find(symbolic_bounds) != sizes_idxsnk.end()) {
                                for (int j = 0; j < idx_src.size(); j++) {
                                    ofs_Refsrc_Isrc_Psrc_Refsnk_Isnk << "Isrc" + to_string(j) << " " << to_string(idx_src[j]) << " ";
                                }
                                for (int j = 0; j < symbolic_bounds.size(); j++) {
                                    ofs_Refsrc_Isrc_Psrc_Refsnk_Isnk << "B" + to_string(j) << " " << to_string(symbolic_bounds[j]) << " ";
                                }
                                ofs_Refsrc_Isrc_Psrc_Refsnk_Isnk << "_out " << sizes_idxsnk[symbolic_bounds][i] << endl;
                            } else {
                                for (int j = 0; j < idx_src.size(); j++) {
                                    ofs_Refsrc_Isrc_Psrc_Refsnk_Isnk << "Isrc" + to_string(j) << " " << to_string(idx_src[j]) << " ";
                                }
                                for (int j = 0; j < symbolic_bounds.size(); j++) {
                                    ofs_Refsrc_Isrc_Psrc_Refsnk_Isnk << "B" + to_string(j) << " " << to_string(symbolic_bounds[j]) << " ";
                                }
                                ofs_Refsrc_Isrc_Psrc_Refsnk_Isnk << "_out " << 0 << endl;
                            }
                            
                        }
                        ofs_Refsrc_Isrc_Psrc_Refsnk_Isnk.close();
                    }
                }
            }
        }
    }
}

/* ISSUE: For shape here, we only consider the relation between min/max and Bounds.
          For each loop, the induction variables of outer loop should also be considered.
          How the shape relates to scaling the iteration point */
void genInOutWithFormatSrcShape(string cacheConfig, string name, vector<uint64_t> sizes, int numOfSymbolicLoopBounds) {
    if (sizes.size() <= 0) {
        return;
    }
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
    
    // ref_src_id -> souce pos -> ref_snk_id -> sink pos -> src iter vector -> snk iter vector -> sizes vector -> ri;
    for (auto ref_src_it : all_ri) {
        
        // refsnk->sizes->IMin
        uint64_t IsrcLen = 0;
        map<uint64_t, map < vector<uint64_t>, vector<uint64_t> >* > srcsnk_IsrcMin;
        map<uint64_t, map < vector<uint64_t>, vector<uint64_t> >* > srcsnk_IsrcMax;
        
        for (auto src_pos_it : (*ref_src_it.second)) {
            for (auto ref_snk_it : (*src_pos_it.second)) {
                uint64_t ref_snk = ref_snk_it.first;
                if (srcsnk_IsrcMin.find(ref_snk) == srcsnk_IsrcMin.end()) {
                    srcsnk_IsrcMin[ref_snk] = new map< vector<uint64_t>, vector<uint64_t> >;
                }
                if (srcsnk_IsrcMax.find(ref_snk) == srcsnk_IsrcMax.end()) {
                    srcsnk_IsrcMax[ref_snk] = new map< vector<uint64_t>, vector<uint64_t> >;
                }
                for (auto snk_pos_it : (*ref_snk_it.second)) {
                    for (auto idx_src_it : (*snk_pos_it.second)) {
                        vector<uint64_t> Isrc = idx_src_it.first;
                        IsrcLen = Isrc.size();
                        
                        for (auto idx_snk_it : (*idx_src_it.second) ) {
                            for (auto cur_sizes_it : (*idx_snk_it.second)) {
                                vector<uint64_t> cur_sizes = cur_sizes_it.first;
                                if ((*srcsnk_IsrcMin[ref_snk]).find(cur_sizes) == (*srcsnk_IsrcMin[ref_snk]).end()) {
                                    (*srcsnk_IsrcMin[ref_snk])[cur_sizes] = Isrc;
                                    (*srcsnk_IsrcMax[ref_snk])[cur_sizes] = Isrc;
                                } else {
                                    for (int i = 0; i < (*srcsnk_IsrcMin[ref_snk])[cur_sizes].size(); i++) {
                                        (*srcsnk_IsrcMin[ref_snk])[cur_sizes][i] = min(Isrc[i], (*srcsnk_IsrcMin[ref_snk])[cur_sizes][i]);
                                    }
                                    for (int i = 0; i < (*srcsnk_IsrcMax[ref_snk])[cur_sizes].size(); i++) {
                                        (*srcsnk_IsrcMax[ref_snk])[cur_sizes][i] = max(Isrc[i], (*srcsnk_IsrcMax[ref_snk])[cur_sizes][i]);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        
        map< vector<uint64_t>, vector<uint64_t> > src_IsrcMin;
        map< vector<uint64_t>, vector<uint64_t> > src_IsrcMax;
        
        for (auto elm : srcsnk_IsrcMin) {
            uint64_t ref_snk = elm.first;
            for (int I_idx = 0; I_idx < IsrcLen; I_idx++) {
                ofstream ofs_Refsrc_Refsnk_Imin;
                ofstream ofs_Refsrc_Refsnk_Imax;
                ofs_Refsrc_Refsnk_Imin.open("./inputoutput/ris_Ibound/" + name + "/" + name +
                                        "_refsrc_" + to_string(ref_src_it.first) +
                                        "_refsnk_" + to_string(ref_snk) +
                                        ".Imin" + to_string(I_idx) + "." + cacheConfig, ofstream::out);
                ofs_Refsrc_Refsnk_Imax.open("./inputoutput/ris_Ibound/" + name + "/" + name +
                                        "_refsrc_" + to_string(ref_src_it.first) +
                                        "_refsnk_" + to_string(ref_snk) +
                                        ".Imax" + to_string(I_idx) + "." + cacheConfig, ofstream::out);
                
                for (int i = 0; i < numOfCombinations; i++) {
                    vector<uint64_t> symbolic_bounds;
                    int symbolic_bounds_idx = i;
                    for (int j = 0; j < numOfSymbolicLoopBounds; j++) {
                        symbolic_bounds.push_back(sizes[symbolic_bounds_idx % numOfSizes]);
                        symbolic_bounds_idx /= numOfSizes;
                    }
                    
                    for (int j = 0; j < symbolic_bounds.size(); j++) {
                        ofs_Refsrc_Refsnk_Imin << "B" + to_string(j) << " " << to_string(symbolic_bounds[j]) << " ";
                        ofs_Refsrc_Refsnk_Imax << "B" + to_string(j) << " " << to_string(symbolic_bounds[j]) << " ";
                    }
                    if ((*srcsnk_IsrcMin[ref_snk]).find(symbolic_bounds) != (*srcsnk_IsrcMin[ref_snk]).end()) {
                        ofs_Refsrc_Refsnk_Imin << "_out " << (*srcsnk_IsrcMin[ref_snk])[symbolic_bounds][I_idx] << endl;
                        ofs_Refsrc_Refsnk_Imax << "_out " << (*srcsnk_IsrcMax[ref_snk])[symbolic_bounds][I_idx] << endl;
                        if (src_IsrcMin.find(symbolic_bounds) != src_IsrcMin.end()) {
                            for (int j = 0; j < src_IsrcMin[symbolic_bounds].size(); j++) {
                                src_IsrcMin[symbolic_bounds][j] = min((*srcsnk_IsrcMin[ref_snk])[symbolic_bounds][j], src_IsrcMin[symbolic_bounds][j]);
                                src_IsrcMax[symbolic_bounds][j] = max((*srcsnk_IsrcMax[ref_snk])[symbolic_bounds][j], src_IsrcMax[symbolic_bounds][j]);
                            }
                        } else {
                            src_IsrcMin[symbolic_bounds] = (*srcsnk_IsrcMin[ref_snk])[symbolic_bounds];
                            src_IsrcMax[symbolic_bounds] = (*srcsnk_IsrcMax[ref_snk])[symbolic_bounds];
                        }
                    } else {
                        ofs_Refsrc_Refsnk_Imin << "_out " << 0 << endl;
                        ofs_Refsrc_Refsnk_Imax << "_out " << 0 << endl;
                    }
                    
                }
                ofs_Refsrc_Refsnk_Imin.close();
                ofs_Refsrc_Refsnk_Imax.close();
            }
        }
        
        for (int I_idx = 0; I_idx < IsrcLen; I_idx++) {
            ofstream ofs_Refsrc_Imin;
            ofstream ofs_Refsrc_Imax;
            ofs_Refsrc_Imin.open("./inputoutput/ris_Ibound/" + name + "/" + name +
                                "_refsrc_" + to_string(ref_src_it.first) +
                                ".Imin" + to_string(I_idx) + "." + cacheConfig, ofstream::out);
            ofs_Refsrc_Imax.open("./inputoutput/ris_Ibound/" + name + "/" + name +
                                "_refsrc_" + to_string(ref_src_it.first) +
                                ".Imax" + to_string(I_idx) + "." + cacheConfig, ofstream::out);
        
            for (int i = 0; i < numOfCombinations; i++) {
                vector<uint64_t> symbolic_bounds;
                int symbolic_bounds_idx = i;
                for (int j = 0; j < numOfSymbolicLoopBounds; j++) {
                    symbolic_bounds.push_back(sizes[symbolic_bounds_idx % numOfSizes]);
                    symbolic_bounds_idx /= numOfSizes;
                }
                for (int j = 0; j < symbolic_bounds.size(); j++) {
                    ofs_Refsrc_Imin << "B" + to_string(j) << " " << to_string(symbolic_bounds[j]) << " ";
                    ofs_Refsrc_Imax << "B" + to_string(j) << " " << to_string(symbolic_bounds[j]) << " ";
                    if (src_IsrcMin.find(symbolic_bounds) != src_IsrcMin.end()) {
                        ofs_Refsrc_Imin << "_out " << src_IsrcMin[symbolic_bounds][I_idx] << endl;
                        ofs_Refsrc_Imax << "_out " << src_IsrcMax[symbolic_bounds][I_idx] << endl;
                    } else {
                        ofs_Refsrc_Imin << "_out " << 0 << endl;
                        ofs_Refsrc_Imax << "_out " << 0 << endl;
                    }
                }
            }
            ofs_Refsrc_Imin.close();
            ofs_Refsrc_Imax.close();
        }
    }
}
