/* 046267 Computer Architecture - Winter 2019/20 - HW #3 */
/* Implementation (skeleton)  for the dataflow statistics calculator */

#include "dflow_calc.h"
#include <map>

// meta-instructions for dependencies
#define ENTRY -1
#define EXIT -2

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
    int depth; // time until inst. can be executed
    int instKey;
    // new
    int dependency1;
    int dependency2;
    int instTime; // inst execute time
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
    /*
     * initial instruction instance
     * look for register deps. in regMap (input reg)
     * update matrix
     * update regMap (dest register)
     * calculate depth
     * */
    void insertInst(InstInfo inst, int key, int latency){};



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


