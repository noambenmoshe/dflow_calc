/* 046267 Computer Architecture - Winter 2019/20 - HW #3 */
/* Implementation (skeleton)  for the dataflow statistics calculator */

#include "dflow_calc.h"
#include <map>
#include <iostream>

// meta-instructions for dependencies
#define ENTRY -1 // must not change !!! value used in getInstDeps
#define INVALID -2
#define EXIT -3
#define DEBUG 0 // change to 0
//typedef std::map<int,int>::iterator mapIt;
typedef std::pair<int,int> regPair;
using std::map;
using std::cout;
using std::endl;
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

    // default c'tor (for array)
    instruction(): instKey(INVALID), instTime(INVALID),dstIdx(INVALID), src1Idx(INVALID), src2Idx(INVALID),
                    dependency1(INVALID), dependency2(INVALID), depth(INVALID) {}
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
    int maxDepth;

    instGraph(unsigned int numOfInsts): numOfInsts(numOfInsts), maxDepth(0){
        //this->numOfInsts = numOfInsts;
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
        if(it == regMap.end()){ // register not exist - no one write for it
            return ENTRY;
        }
        else return it->second;
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
    // update maxDepth if input time is longer
    void updateMaxDepth(int depTime, int instTime){
        if(depTime + instTime > maxDepth)
            maxDepth=depTime + instTime;

        if(DEBUG)
            std::cout << "max depth is: " << maxDepth << std::endl;
    }
    // return keyDep instruction min execution time
    int calcDepthTime(int keyDep){
        if(keyDep == ENTRY)
            return 0;
        else return instArray[keyDep].depth + instArray[keyDep].instTime;
    }

    //return max depth time between instruction keyDep1, keyDep2
    int calcDepth(int keyDep1, int keyDep2){
        int dep1Time =calcDepthTime(keyDep1);
        int dep2Time =calcDepthTime(keyDep2);;

        if( dep1Time > dep2Time){
            return dep1Time;
        }
        else{
            return dep2Time;
        }
   }

    // get all information about the instruction and call the instruction c'tor
    void insertInst(InstInfo inst, int key, int latency){
        int dep1Key = findDepInRegMap(inst.src1Idx);
        int dep2Key = findDepInRegMap(inst.src2Idx);
        int depth = calcDepth(dep1Key,dep2Key);

        instArray[key] = instruction(key,latency,inst.dstIdx,inst.src1Idx, inst.src2Idx,dep1Key,dep2Key,depth);
        updateRegMap(inst.dstIdx, key);
        updateMaxDepth(depth, latency); // update only if longer
       // updateRegMap(inst.src2Idx, key);

    };



};




//*****************************************************************************************************//
//    API
//****************************************************************************************************//
instGraph * pProgGraph;
ProgCtx analyzeProg(const unsigned int opsLatency[], const InstInfo progTrace[], unsigned int numOfInsts) {
    pProgGraph = new instGraph(numOfInsts);

    for(int i=0; (unsigned int) i < numOfInsts; i++){
        int instKey = i;
        int instLatency = opsLatency[progTrace[i].opcode];
        pProgGraph->insertInst(progTrace[i], instKey, instLatency);
    }
    return (void *)(pProgGraph); // return void* (API)
}

void freeProgCtx(ProgCtx ctx) {
    delete pProgGraph;
}

int getInstDepth(ProgCtx ctx, unsigned int theInst) {
    if(ctx == PROG_CTX_NULL)
        return -1;
    instGraph * pGraph = (instGraph *)ctx;
//    if(pGraph->instArray[theInst].dependency1 == ENTRY &&
//            pGraph->instArray[theInst].dependency2 == ENTRY){
//        return 0; // return -1 if not dependent in anything
//    }
    int numOfInsts = pGraph->numOfInsts;
    if (theInst < 0 || theInst >= (unsigned int) numOfInsts){
        return -1; // illegal instruction
    }
    int instDepth = pGraph->instArray[theInst].depth; // return instruction's depth
    return instDepth; // verify that return 0 if no depth
}

int getInstDeps(ProgCtx ctx, unsigned int theInst, int *src1DepInst, int *src2DepInst) {
    if(ctx == PROG_CTX_NULL)
        return -1;
    instGraph * pGraph = (instGraph *)ctx;
    int numOfInsts = pGraph->numOfInsts;
    if (theInst < 0 || theInst >= (unsigned int) numOfInsts) {
        return -1; // illegal instruction
    }
    *src1DepInst = pGraph->instArray[theInst].dependency1;
    *src2DepInst = pGraph->instArray[theInst].dependency2;

    return 0;
}

int getProgDepth(ProgCtx ctx) {
    instGraph * pGraph = (instGraph *)ctx;
    return pGraph->maxDepth;
}


