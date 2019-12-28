/* 046267 Computer Architecture - Winter 2019/20 - HW #3 */
/* Implementation (skeleton)  for the dataflow statistics calculator */

#include "dflow_calc.h"
#include <map>

// meta-instructions for dependencies
#define ENTRY -1
#define EXIT -2
//typedef std::map<int,int>::iterator mapIt;
typedef std::pair<int,int> regPair;
using std::map;

//******************************************************************************************************//
// help classes
//******************************************************************************************************//
class instruction{
public:
    int instKey;
    int instTime; // inst execute time
    int dstIdx;
    unsigned int src1Idx;
    unsigned int src2Idx;
    int dependency1;
    int dependency2;
    int depth; // time until inst. can be executed


    instruction(int instKey, int instTime, int dstIdx, unsigned int src1Idx, unsigned int src2Idx,
                int dependency1, int dependency2, int depth) : instKey(instKey), instTime(instTime),
                                                               dstIdx(dstIdx), src1Idx(src1Idx), src2Idx(src2Idx),
                                                               dependency1(dependency1), dependency2(dependency2),
                                                               depth(depth) {}
};

class instGraph{
public:
//    int** depsMatrix;
    instruction* instArray;
    map<int, int> regMap; // val - last op writing to REG (key)
    unsigned int numOfInsts; // total number of inst. in prog.

    instGraph(unsigned int numOfInsts){
        this->numOfInsts = numOfInsts;

        //initial matrix
//        int rows = numOfInsts + 2, cols = numOfInsts + 2; // +2 for EXIT and ENTRY
//        depsMatrix = new int*[rows];
//        for (int i = 0; i < rows; ++i)
//            depsMatrix[i] = new int[cols] {0};

        // initial instruction array
        instArray = new instruction[numOfInsts];
    };
    ~instGraph(){
        //delete matrix
//        for (int i = 0; i < numOfInsts + 2; ++i)
//            delete [] depsMatrix[i];
//        delete [] depsMatrix;

        //delete instArray
        delete[] instArray;

    };



   // * look for register deps. in regMap (input reg)
    int findDepInRegMap(int srcIdx){
        auto it = regMap.find(srcIdx);
        if(it == regMap.end()){
            return ENTRY;
        }
        else return it->first;
    }

    //* update regMap (dest register)
    void updateRegMap(int reg, int instKey){
        auto it = regMap.find(reg);
        if(it == regMap.end()){
            regMap.insert ( regPair(reg,instKey) );
        }
        else{
            it->second = instKey;
        }
    }

    //  * calculate depth
    int calcDepth(int keyDep1, int keyDep2){
        int dep1Time = instArray[keyDep1].depth + instArray[keyDep1].instTime;
        int dep2Time = instArray[keyDep2].depth + instArray[keyDep2].instTime;

    }


    /*
     * initial instruction instance
     * look for register deps. in regMap (input reg)
     * update matrix
     * update regMap (dest register)
     * calculate depth
     * */

    // get all information about the instruction and call the instruction c'tor
    void insertInst(InstInfo inst, int key, int latency){
        int dep1Key = findDepInRegMap(inst.src1Idx);
        int dep2Key = findDepInRegMap(inst.src2Idx);
        int depth = calcDepth(dep1Key,dep2Key);

        instArray[key] = instruction(key,latency,inst.dstIdx,inst.src1Idx, inst.src2Idx,dep1Key,dep2Key,depth);
        updateRegMap(inst.src1Idx, key);
        updateRegMap(inst.src2Idx, key);

    };



};




//*****************************************************************************************************//
//    API
//****************************************************************************************************//
ProgCtx analyzeProg(const unsigned int opsLatency[], const InstInfo progTrace[], unsigned int numOfInsts) {
    instGraph graph = instGraph(numOfInsts);

    for(int i=0; i<numOfInsts; i++){
        int instKey = i;
        int instLatency = opsLatency[]
        graph.insertInst(progTrace[i], i, )
    }



    return (void *)(&graph); // return void* (API)
}

void freeProgCtx(ProgCtx ctx) {
}

int getInstDepth(ProgCtx ctx, unsigned int theInst) {
    return -1;
}

int getInstDeps(ProgCtx ctx, unsigned int theInst, int *src1DepInst, int *src2DepInst) {
    return -1;
}

int getProgDepth(ProgCtx ctx) {
    return 0;
}


