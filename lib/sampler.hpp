#ifndef SAMPLER_H
#define SAMPLER_H

#include <string>
#include <map>
#include <set>
#include <vector>
using namespace std;

class sampler {
public:
    sampler(double samplingRate);
    vector<map<string, int> > uniformSampling(vector<map<string, int> > inputOutputs);
    vector<map<string, int> > randomSampling(vector<map<string, int> > inputOutputs);
    
private:
    double _samplingRate;
};

#endif
