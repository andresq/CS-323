#include <iostream>
#include <string> 
#include <fstream>

using namespace std;

// Data structure
class Scheduling {

    class Node {
    public:
    int jobId;
    int jobTime;
    int dependentCount;
    Node* next;
    Node(){

    }

    Node(int id, int time, int dCount){
        jobId = id;
        jobTime = time;
        dependentCount = dCount;
        next = NULL;
    }

    void printNode(ofstream& outFile){
        if(this->next == NULL){
            outFile << "(" << jobId << "," << jobTime << "," << dependentCount << "," << "NULL" << ") -> NULL";
        } else {
            outFile << "(" << jobId << "," << jobTime << "," << dependentCount << "," << next->jobId << ") ->";
        }
    }
};

class Job {
    public:
    int jobTime;
    int onWhichProc;
    int onOpen;
    int parentCount;
    int depedentCount;

    Job(){ // set all to zero?
        jobTime = 0;
        onWhichProc = 0;
        onOpen = 0;
        parentCount = 0;
        depedentCount = 0;
    }

};

class Proc {
    public:
    int doWhichJob = -1;
    int timeRemain = 0; // start at zero AKA available
};

// Scheduling attrivutes
    public:
    int numNodes;
    int numProcs;
    int procUsed;

    Job* jobAry;
    Proc* procAry;
    Node* Open;

    int** adjMatrix;
    int* parentCountAry;
    int* dependentCountAry;
    int* onGraphAry;
    int totalJobTimes;
    int** scheduleTable;

    int currentTime; // This could be outside the code however it will make passing the varible around an pain so KEEP IN CLASS!

    // Scheduling Methods
    int constructJobAry(ifstream& inputFile2){
        // 0
        int totalTime = 0;
        int numNode;
        inputFile2 >> numNode; // clear the header information
        //1 
        while(!inputFile2.eof()){
            int nodeID;
            int jobTime;

            inputFile2 >> nodeID;
            inputFile2 >> jobTime;

            totalTime += jobTime;

            // 2
            jobAry[nodeID].jobTime = jobTime;
            jobAry[nodeID].onWhichProc = -1;
            jobAry[nodeID].onOpen = 0;
            jobAry[nodeID].parentCount = parentCountAry[nodeID];
            jobAry[nodeID].depedentCount = dependentCountAry[nodeID];
        }


        return totalTime;

    }

    void computeParentCount(){
        for(int parent = 1; parent < numNodes+1; parent++){
            for(int dependent = 1; dependent < numNodes+1; dependent++){
                if(adjMatrix[parent][dependent] == 1){
                    parentCountAry[parent]++;
                }
            }
        }

    }

    void computeDependentCount(){
        for(int parent = 1; parent < numNodes+1; parent++){
            for(int dependent = 1; dependent < numNodes+1; dependent++){
                if(adjMatrix[parent][dependent] == 1){
                    dependentCountAry[dependent]++;
                }
            }
        }
    }

    int findOrphan(){
        return -22;
    }

    void listInsert(Node* listHead, Node* newNode){
        Node* Spot = findSpot(listHead, newNode);
        newNode->next = Spot->next;
        Spot->next = newNode;
    }

    Node* findSpot(Node* listHead, Node* newNode){
        Node* Spot = listHead;
        while(Spot->next != NULL && Spot->next->dependentCount < newNode->dependentCount){
            Spot = Spot->next;
        }
        return Spot;
    }



    void printList(ofstream& outFile2){
        outFile2 << "head" << "-> ";
        Node* printSpot = Open->next;
        while(printSpot != NULL){
            printSpot->printNode(outFile2);
            printSpot = printSpot->next;
        }
        outFile2 << endl;
    }


    void printScheduleTable(ofstream& outFile1){

    }

    int findProcessors(){

        return -22;
    }

    void putJobOnTable(int availProc, int currentTime, int jobId, int jobTime){

    }

    bool checkCycle(){
        return false;
    }

    void updateProcTime(){

    }

    int findDoneProc(){

        return -22;
    }

    void deleteFinishedNodes(){

    }

    void deleteEdge(int jobId){

    }

    void loadMatrix(ifstream& inputFile1){
        int parent = 0;
        int dependent = 0;
        while(!inputFile1.eof()){
            inputFile1 >> parent;
            inputFile1 >> dependent;
            adjMatrix[parent][dependent] = 1;
        }
    }


    void initialization(ifstream& inputFile1, ifstream& inputFile2, int numberOfProcs){
        // 0
        procUsed = 0;
        currentTime = 0; // Maybe be class variable? Does it get passed around?
        Open = new Node(0,0,0); // headList
        
        // 1
        numProcs = numberOfProcs; // from argument

        

        // 2 
        inputFile1 >> numNodes;
        if (numProcs > numNodes){
            numProcs = numNodes; //  because each node can have thier own processors
        }

        // 3
        adjMatrix = new int*[numNodes + 1];
        for(int i = 0; i < numNodes+1; i++){
            adjMatrix[i] = new int[numNodes+1];
        }

        

        jobAry = new Job[numNodes+1];
        procAry = new Proc[numProcs+1];

        scheduleTable = new int*[numProcs+1];
        for(int i = 0; i < numProcs+1; i++){
            scheduleTable[i] = new int[totalJobTimes+1];
        }

        

        // Init to zeros;
        for(int i  = 0; i < numNodes+1; i++){
            for(int j = 0; j < numNodes+1; j++){
                adjMatrix[i][j] = 0;
            }
        }

        

        for(int i  = 0; i < numProcs+1; i++){
            for(int j = 0; j < totalJobTimes+1; j++){
                scheduleTable[i][j] = 0;
            }
        }

        

        // 4 

        loadMatrix(inputFile1);


        

        // 5
        parentCountAry = new int[numNodes+1];
        for(int i = 0 ; i < numNodes+1; i++){parentCountAry[i] = 0;}
        computeParentCount();

        // 6
        dependentCountAry = new int[numNodes+1];
        for(int i = 0 ; i < numNodes+1; i++){dependentCountAry[i] = 0;}
        computeDependentCount();


        // 7 
        totalJobTimes = constructJobAry(inputFile2);

        



    }


};

int main(int argc, char* argv[]){
    // Inputs
    // 0
    
    ifstream inFile1(argv[1]);
    ifstream inFile2(argv[2]);
    int numberOfProc = stoi(argv[3]);
    ofstream outFile1(argv[4]);
    ofstream outFile2(argv[5]);


    // 1
    Scheduling S;
    S.initialization(inFile1, inFile2, numberOfProc);

    // //DEBUGSTUFF
    // for(int i  = 0; i < S.numNodes+1; i++){
    //         for(int j = 0; j < S.numNodes+1; j++){
    //             cout << S.adjMatrix[i][j]; 
    //         }
    //         cout << endl;
    //     }

    // for(int i  = 0; i < S.numNodes+1; i++){
    //     // cout << "parent " << i << " = " << S.parentCountAry[i] << endl;
    //     cout << "dependent " << i << " = " << S.dependentCountAry[i] << endl;
    // }




    // Closing the files
    inFile1.close();
    inFile2.close();
    outFile1.close();
    outFile2.close();
    

    

}