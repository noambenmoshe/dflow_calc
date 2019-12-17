/* 046267 Computer Architecture - Winter 2019/20 - HW #3 */
/* Implementation (skeleton)  for the dataflow statistics calculator */

#include "dflow_calc.h"
#include <map>


using std::map;

//******************************************************************************************************//
// help classes
//******************************************************************************************************//
class instruction{
public:
    unsigned int opcode;
    int dstIdx;
    unsigned int src1Idx;
    unsigned int src2Idx;
    int depth;
    int instKey;

};

class instGraph{
public:
    int** depsMatrix;
    instruction* instArray;
    map<int, int> regMap;

    instGraph(unsigned int numOfInsts){};
    ~instGraph(){};
    /*
     * initial instruction instance
     * look for register deps. in regMap (input reg)
     * update matrix
     * update regMap (dest register)
     * calculate depth
     * */
    void insertInst(){};



};




//*****************************************************************************************************//
//    API
//****************************************************************************************************//
ProgCtx analyzeProg(const unsigned int opsLatency[], const InstInfo progTrace[], unsigned int numOfInsts) {



    return PROG_CTX_NULL;
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


