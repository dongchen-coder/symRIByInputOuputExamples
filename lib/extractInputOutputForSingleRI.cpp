#include "extractInputOutputForSingleRI.hpp"

// ref_src_id -> ref_snk_id -> src iter vector -> snk iter vector -> sizes vector -> ri;
map<uint64_t, map<uint64_t, map<vector<uint64_t>, map<vector<uint64_t>, map<vector<uint64_t>, uint64_t>* >* >* >* > all_ri;

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
    vector<uint64_t> idx_src;
    vector<uint64_t> idx_snk;
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
            
            ri = stoi(lineList[lineListLen-1]);
            
            if (all_ri.find(ref_src_id) == all_ri.end()) {
                all_ri[ref_src_id] = new map< uint64_t, map<vector<uint64_t>, map<vector<uint64_t>, map<vector<uint64_t>, uint64_t>* >* >* >;
            }
            if (all_ri[ref_src_id]->find(ref_snk_id) == all_ri[ref_src_id]->end()) {
                (*all_ri[ref_src_id])[ref_snk_id] = new map<vector<uint64_t>, map<vector<uint64_t>, map<vector<uint64_t>, uint64_t>* >* >;
            }
            if ((*all_ri[ref_src_id])[ref_snk_id]->find(idx_src) == (*all_ri[ref_src_id])[ref_snk_id]->end()) {
                (*(*all_ri[ref_src_id])[ref_snk_id])[idx_src] = new map<vector<uint64_t>, map<vector<uint64_t>, uint64_t>* >;
            }
            if ((*(*all_ri[ref_src_id])[ref_snk_id])[idx_src]->find(idx_snk) == (*(*all_ri[ref_src_id])[ref_snk_id])[idx_src]->end()) {
                (*(*(*all_ri[ref_src_id])[ref_snk_id])[idx_src])[idx_snk] = new map<vector<uint64_t>, uint64_t>;
            }
            
            (*(*(*(*all_ri[ref_src_id])[ref_snk_id])[idx_src])[idx_snk])[symbolic_bounds] = ri;
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

void genInputOutputExample(string name, vector<uint64_t> sizes, int numOfSymbolicLoopBounds, double samplingRate) {
    
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
    
    
    // ref_src_id -> ref_snk_id -> src iter vector -> snk iter vector -> sizes vector -> ri;
    for (auto ref_src_it = all_ri.begin(), ref_src_eit = all_ri.end(); ref_src_it != ref_src_eit; ++ref_src_it) {
        ofstream ofs_perIterRefsrc;
        
        map<vector<uint64_t>, vector<uint64_t> > ref_src_min_idx;
        map<vector<uint64_t>, vector<uint64_t> > ref_src_max_idx;
        
        // ref_snk_id -> src iter vector -> snk iter vector -> sizes vector -> ri;
        for (auto ref_snk_it = (ref_src_it->second)->begin(), ref_snk_eit = (ref_src_it->second)->end(); ref_snk_it != ref_snk_eit; ++ref_snk_it) {
            ofstream ofs_perIterRefsrcsnk;
            
            /* sizes -> min */
            map<vector<uint64_t>, vector<uint64_t> > ref_srcsnk_srcmin_idx;
            map<vector<uint64_t>, vector<uint64_t> > ref_srcsnk_srcmax_idx;
            map<vector<uint64_t>, vector<uint64_t> > ref_srcsnk_snkmin_idx;
            map<vector<uint64_t>, vector<uint64_t> > ref_srcsnk_snkmax_idx;
            
            /* sample src idxs */
            vector<vector<uint64_t> > all_src_idxs;
            for (const auto idx_src_it : *(ref_snk_it->second)) {
                all_src_idxs.push_back(idx_src_it.first);
            }
            
            //vector<vector<uint64_t> > sampled_idxs = samplingBorderInner(all_src_idxs, samplingRate);
            vector<vector<uint64_t> > sampled_idxs = samplingRandom(all_src_idxs, samplingRate);
            
            // src iter vector -> snk iter vector -> sizes vector -> ri;
            for (auto idx_src_it = (ref_snk_it->second)->begin(), idx_src_eit = (ref_snk_it->second)->end(); idx_src_it != idx_src_eit; ++idx_src_it) {
                
                bool genFlag = true;
                if (find(sampled_idxs.begin(), sampled_idxs.end(), idx_src_it->first) == sampled_idxs.end()) {
                    genFlag = false;
                }
                
                for (auto idx_snk_it = (idx_src_it->second)->begin(), idx_snk_eit = (idx_src_it->second)->end(); idx_snk_it != idx_snk_eit; ++idx_snk_it) {
                    
                    vector<uint64_t> idx_src = idx_src_it->first;
                    string idx_src_str = "";
                    for (int i = 0; i < idx_src.size(); i++) {
                        idx_src_str += "_" + to_string(idx_src[i]);
                    }
                    
                    vector<uint64_t> idx_snk = idx_snk_it->first;
                    string idx_snk_str = "";
                    for (int i = 0; i < idx_snk.size(); i++) {
                        idx_snk_str += "_" + to_string(idx_snk[i]);
                    }
                    
                    for (auto cur_sizes_it = (idx_snk_it->second)->begin(), cur_sizes_eit = (idx_snk_it->second)->end(); cur_sizes_it != cur_sizes_eit; ++cur_sizes_it) {
                        
                        vector<uint64_t> cur_sizes = cur_sizes_it->first;
                        
                        if (ref_srcsnk_srcmin_idx.find(cur_sizes) == ref_srcsnk_srcmin_idx.end()) {
                            ref_srcsnk_srcmin_idx[cur_sizes] = idx_src;
                        } else {
                            for (int i = 0; i < ref_srcsnk_srcmin_idx[cur_sizes].size(); i++) {
                                ref_srcsnk_srcmin_idx[cur_sizes][i] = min(ref_srcsnk_srcmin_idx[cur_sizes][i], idx_src[i]);
                            }
                        }
                        if (ref_srcsnk_srcmax_idx.find(cur_sizes) == ref_srcsnk_srcmax_idx.end()) {
                            ref_srcsnk_srcmax_idx[cur_sizes] = idx_src;
                        } else {
                            for (int i = 0; i < ref_srcsnk_srcmax_idx[cur_sizes].size(); i++) {
                                ref_srcsnk_srcmax_idx[cur_sizes][i] = max(ref_srcsnk_srcmax_idx[cur_sizes][i], idx_src[i]);
                            }
                        }
                        if (ref_srcsnk_snkmin_idx.find(cur_sizes) == ref_srcsnk_snkmin_idx.end()) {
                            ref_srcsnk_snkmin_idx[cur_sizes] = idx_snk;
                        } else {
                            for (int i = 0; i < ref_srcsnk_snkmin_idx[cur_sizes].size(); i++) {
                                ref_srcsnk_snkmin_idx[cur_sizes][i] = min(ref_srcsnk_snkmin_idx[cur_sizes][i], idx_snk[i]);
                            }
                        }
                        if (ref_srcsnk_snkmax_idx.find(cur_sizes) == ref_srcsnk_snkmax_idx.end()) {
                            ref_srcsnk_snkmax_idx[cur_sizes] = idx_snk;
                        } else {
                            for (int i = 0; i < ref_srcsnk_snkmax_idx[cur_sizes].size(); i++) {
                                ref_srcsnk_snkmax_idx[cur_sizes][i] = max(ref_srcsnk_snkmax_idx[cur_sizes][i], idx_snk[i]);
                            }
                        }
                        
                        if (ref_src_min_idx.find(cur_sizes) == ref_src_min_idx.end()) {
                            ref_src_min_idx[cur_sizes] = idx_src;
                        } else {
                            for (int i = 0; i < ref_src_min_idx[cur_sizes].size(); i++) {
                                ref_src_min_idx[cur_sizes][i] = min(ref_src_min_idx[cur_sizes][i], idx_src[i]);
                            }
                        }
                        if (ref_src_max_idx.find(cur_sizes) == ref_src_max_idx.end()) {
                            ref_src_max_idx[cur_sizes] = idx_src;
                        } else {
                            for (int i = 0; i < ref_src_max_idx[cur_sizes].size(); i++) {
                                ref_src_max_idx[cur_sizes][i] = max(ref_src_max_idx[cur_sizes][i], idx_src[i]);
                            }
                        }
                        
                    }
                     
                    if (genFlag) {
                        /* create a file named by ref src ID and iteration vector */
                        ofs_perIterRefsrc.open("./inputoutput/ris_per_iter_refsrc/" + name + "/" +name+"_refsrc_" + to_string(ref_src_it->first) + "_itersrc" + idx_src_str + ".txt", ofstream::out | ofstream::app);
                        /* create a file named by ref src/snk ID and iteration vector */
                        ofs_perIterRefsrcsnk.open("./inputoutput/ris_per_iter_refsrcsnk/" + name + "/" +name+"_refsrc_" + to_string(ref_src_it->first) + "_refsnk_" + to_string(ref_snk_it->first) + ".txt", ofstream::out | ofstream::app);
                    
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
                            for (int j = 0; j < idx_src.size(); j++) {
                                ofs_perIterRefsrc << "Isrc" + to_string(j) << " " << to_string(idx_src[j]) << " ";
                                ofs_perIterRefsrcsnk << "Isrc" + to_string(j) << " " << to_string(idx_src[j]) << " ";
                            }
                
                            for (int j = 0; j < idx_snk.size(); j++) {
                                ofs_perIterRefsrcsnk << "Isnk" + to_string(j) << " " << to_string(idx_snk[j]) << " ";
                            }
                        
                            /* symbolic bounds is another input */
                            for (int j = 0; j < symbolic_bounds.size(); j++) {
                                ofs_perIterRefsrc << "B" + to_string(j) << " " << to_string(symbolic_bounds[j]) << " ";
                                ofs_perIterRefsrcsnk << "B" + to_string(j) << " " << to_string(symbolic_bounds[j]) << " ";
                            }
                
                            if ((*idx_snk_it->second).find(symbolic_bounds) != (*idx_snk_it->second).end()) {
                                ofs_perIterRefsrc << "_out " << (*idx_snk_it->second)[symbolic_bounds] << endl;
                                ofs_perIterRefsrcsnk << "_out " << (*idx_snk_it->second)[symbolic_bounds] << endl;
                            } else {
                                ofs_perIterRefsrc << "_out " << 0 << endl;
                                ofs_perIterRefsrcsnk << "_out " << 0 << endl;
                            }
                        }
                        
                        ofs_perIterRefsrcsnk.close();
                        ofs_perIterRefsrc.close();
                    }
                }
            }
            
            ofstream ofs_Srcsnk_src_IVMin;
            ofstream ofs_Srcsnk_src_IVMax;
            ofstream ofs_Srcsnk_snk_IVMin;
            ofstream ofs_Srcsnk_snk_IVMax;
            
            for (auto sizesToImin : ref_srcsnk_srcmin_idx) {
                vector<uint64_t> cur_sizes = sizesToImin.first;
                vector<uint64_t> cur_Imin = sizesToImin.second;
                for (int i = 0; i < cur_Imin.size(); i++) {
                    ofs_Srcsnk_src_IVMin.open("./inputoutput/IMinMax/" + name + "/" +name+ "_refsrc_" + to_string(ref_src_it->first) + "_refsnk_" + to_string(ref_snk_it->first) + "_I" + to_string(i) + "_src_min.txt", ofstream::out | ofstream::app);
                    
                    string cur_sizes_str = "";
                    for (int j = 0; j < cur_sizes.size(); j++) {
                        cur_sizes_str += "B" + to_string(j) + " " + to_string(cur_sizes[j]) + " ";
                    }
                    
                    ofs_Srcsnk_src_IVMin << cur_sizes_str + "_out " + to_string(cur_Imin[i]) << endl;
                    ofs_Srcsnk_src_IVMin.close();
                }
            }
            for (auto sizesToImax : ref_srcsnk_srcmax_idx) {
                vector<uint64_t> cur_sizes = sizesToImax.first;
                vector<uint64_t> cur_Imax = sizesToImax.second;
                for (int i = 0; i < cur_Imax.size(); i++) {
                    ofs_Srcsnk_src_IVMax.open("./inputoutput/IMinMax/" + name + "/" +name+"_refsrc_" + to_string(ref_src_it->first) + "_refsnk_" + to_string(ref_snk_it->first) + "_I" + to_string(i) + "_src_max.txt", ofstream::out | ofstream::app);
                    
                    string cur_sizes_str = "";
                    for (int j = 0; j < cur_sizes.size(); j++) {
                        cur_sizes_str += "B" + to_string(j) + " " + to_string(cur_sizes[j]) + " ";
                    }
                    
                    ofs_Srcsnk_src_IVMax << cur_sizes_str + "_out " + to_string(cur_Imax[i]) << endl;
                    ofs_Srcsnk_src_IVMax.close();
                }
            }
            
            for (auto sizesToImin : ref_srcsnk_snkmin_idx) {
                vector<uint64_t> cur_sizes = sizesToImin.first;
                vector<uint64_t> cur_Imin = sizesToImin.second;
                for (int i = 0; i < cur_Imin.size(); i++) {
                    ofs_Srcsnk_snk_IVMin.open("./inputoutput/IMinMax/" + name + "/" +name + "_refsrc_" + to_string(ref_src_it->first) + "_refsnk_" + to_string(ref_snk_it->first) + "_I" + to_string(i) + "_snk_min.txt", ofstream::out | ofstream::app);
                    
                    string cur_sizes_str = "";
                    for (int j = 0; j < cur_sizes.size(); j++) {
                        cur_sizes_str += "B" + to_string(j) + " " + to_string(cur_sizes[j]) + " ";
                    }
                    
                    ofs_Srcsnk_snk_IVMin << cur_sizes_str + "_out " + to_string(cur_Imin[i]) << endl;
                    ofs_Srcsnk_snk_IVMin.close();
                }
            }
            for (auto sizesToImax : ref_srcsnk_snkmax_idx) {
                vector<uint64_t> cur_sizes = sizesToImax.first;
                vector<uint64_t> cur_Imax = sizesToImax.second;
                for (int i = 0; i < cur_Imax.size(); i++) {
                    ofs_Srcsnk_snk_IVMax.open("./inputoutput/IMinMax/" + name + "/" +name + "_refsrc_" + to_string(ref_src_it->first) + "_refsnk_" + to_string(ref_snk_it->first) + "_I" + to_string(i) + "_snk_max.txt", ofstream::out | ofstream::app);
                    
                    string cur_sizes_str = "";
                    for (int j = 0; j < cur_sizes.size(); j++) {
                        cur_sizes_str += "B" + to_string(j) + " " + to_string(cur_sizes[j]) + " ";
                    }
                    
                    ofs_Srcsnk_snk_IVMax << cur_sizes_str + "_out " + to_string(cur_Imax[i]) << endl;
                    ofs_Srcsnk_snk_IVMax.close();
                }
            }
            
        }
        
        ofstream ofs_perRefsrcIVMin;
        ofstream ofs_perRefsrcIVMax;
        
        for (auto sizesToImin : ref_src_min_idx) {
            vector<uint64_t> cur_sizes = sizesToImin.first;
            vector<uint64_t> cur_Imin = sizesToImin.second;
            for (int i = 0; i < cur_Imin.size(); i++) {
                ofs_perRefsrcIVMin.open("./inputoutput/IMinMax/" + name + "/" +name+ "_refsrc_" + to_string(ref_src_it->first) + "_I" + to_string(i) + "_src_min.txt", ofstream::out | ofstream::app);
                
                string cur_sizes_str = "";
                for (int j = 0; j < cur_sizes.size(); j++) {
                    cur_sizes_str += "B" + to_string(j) + " " + to_string(cur_sizes[j]) + " ";
                }
                
                ofs_perRefsrcIVMin << cur_sizes_str + "_out " + to_string(cur_Imin[i]) << endl;
                ofs_perRefsrcIVMin.close();
            }
        }
        
        for (auto sizesToImax : ref_src_max_idx) {
            vector<uint64_t> cur_sizes = sizesToImax.first;
            vector<uint64_t> cur_Imax = sizesToImax.second;
            for (int i = 0; i < cur_Imax.size(); i++) {
                ofs_perRefsrcIVMax.open("./inputoutput/IMinMax/" + name + "/" +name+"_refsrc_" + to_string(ref_src_it->first) + "_I" + to_string(i) + "_src_max.txt", ofstream::out | ofstream::app);
                
                string cur_sizes_str = "";
                for (int j = 0; j < cur_sizes.size(); j++) {
                    cur_sizes_str += "B" + to_string(j) + " " + to_string(cur_sizes[j]) + " ";
                }
                
                ofs_perRefsrcIVMax << cur_sizes_str + "_out " + to_string(cur_Imax[i]) << endl;
                ofs_perRefsrcIVMax.close();
            }
        }
        
    }
    
	return;
}
