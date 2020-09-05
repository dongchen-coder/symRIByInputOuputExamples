#include <iostream>
#include <mutex>
#include <vector>
#include <cstdlib>
#include <filesystem>
#include "../lib/tPool.hpp"
using namespace std;
 
mutex cout_lock;
#define trace(x) { scoped_lock<mutex> lock(cout_lock); cout << x << endl; }
 
const int COUNT = thread::hardware_concurrency() * 4;
const int WORK = 10000000;

void run(string cmd) {
    cout << cmd << endl;
    system(cmd.c_str());
    return;
}

int main(int argc, char** argv)
{
    srand((unsigned int)time(NULL));
    thread_pool pool;
    
    /*
    auto result = pool.enqueue_task([](int i) { return i; }, 0xFF);
    result.get();
    
    for(int i = 1; i <= COUNT; ++i) {
        pool.enqueue_work(  [](int workerNumber) {
            int workOutput = 0;
            int work = WORK + (rand() % (WORK));
            trace("work item " << workerNumber << " starting " << work << " iterations...");
            for(int w = 0; w < work; ++w)
                workOutput += rand();
            trace("work item " << workerNumber << " finished");
        }, i);
    }
    */
    
    vector<string> benches = {"stencil", "2mm", "3mm", "adi", "atax", "bicg", "cholesky", "correlation", "covariance", "deriche", "doitgen", "durbin", "fdtd_2d", "floyd_warshall", "gemm", "gemver", "gesummv", "gramschmidt", "heat_3d", "jacobi_1d", "jacobi_2d", "lu", "ludcmp", "mvt", "nussinov", "seidel_2d", "symm", "syr2d", "syrk", "trisolv", "trmm", "convolution_2d", "convolution_3d", "trangle"};
    
    for (auto bench : benches) {
        
        vector<string> cmdList;
        
        string exe = "./bin/symRiSymthesiser ";
        for(auto& p: filesystem::directory_iterator("./inputoutput/ris_per_iter_refsrc/" + bench)) {
            string cmd = exe + " -FILE " + p.path().u8string() + " " + "-CONSTANTSPRED 1 2 -INTOPSTERM VAR NUM PLUS TIMES MINUS -MODE PerSrcIter -SEARCHTIMEFORTERMSINSECONDS 40 -SEARCHTIMEFORPREDSINSECONDS 80";
            cmdList.push_back(cmd);
        }
        
        for (auto cmd : cmdList) {
            pool.enqueue_work(&run, cmd);
        }
    }
    
    return 1;
}
