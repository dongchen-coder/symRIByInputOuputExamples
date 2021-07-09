#include "sampler.hpp"

sampler::sampler(double samplingRate) {
    _samplingRate = samplingRate;
}

vector<map<string, int> > sampler::uniformSampling(vector<map<string, int> > inputOutputs) {
    return inputOutputs;
}

vector<map<string, int> > sampler::randomSampling(vector<map<string, int> > inputOutputs) {
    
    int numOfSamples = _samplingRate * inputOutputs.size();
    set<int> record;
    
    for (int i = 0; i < numOfSamples; i++) {
        int inputOutputsId = rand() % inputOutputs.size();
        while (find(record.begin(), record.end(), inputOutputsId) != record.end()) {
            inputOutputsId = rand() % inputOutputs.size();
        }
        record.insert(inputOutputsId);
    }
    
    vector<map<string, int> > inputOutputsSampled;
    for (auto it = record.begin(), eit = record.end(); it != eit; ++it) {
        inputOutputsSampled.push_back(inputOutputs[*it]);
    }
    
    return inputOutputsSampled;
}
