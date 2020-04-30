#include <iostream> 
#include <string>
#include <fstream>
using namespace std;

class selectionSort{
    public:
    int* Ary;
    int N;


    void getN(ifstream& inFile){
        int count = 0;
        while(!inFile.eof()){
            int value;
            inFile >> value;
            count++;
        }
        N = count;
        inFile.close();
    }

    void loadAry(ifstream& inFile){
        Ary = new int[N];

        int input;
        for(int i = 0; i < N; i++){
            inFile >> input;
            Ary[i] = input;
        }
    }

    void selectionSorting(){
        int lowestFound;

       
    // Selection Sort?
        for(int i = 0; i < N-1; i++){
            lowestFound = i;
            for(int j = i+1; j < N; j++){
                if(Ary[j] < Ary[lowestFound]){
                    int temp = Ary[lowestFound];
                    Ary[lowestFound] = Ary[j];
                    Ary[j] = temp;
                }
            }

        }
    // Expansive bubble sort?
    //    while(position < N){
    //         for(int i = position+1; i < N; i++){
    //             if(Ary[i] < Ary[position]){
    //                 int temp = Ary[position];
    //                 Ary[position] = Ary[i];
    //                 Ary[i] = temp;
    //             }
    //         }
    //         position++;
    //     }
    

    }

    void printAry(ofstream& outFile){
        for(int i =0; i < N; i++){
            outFile << Ary[i] << endl;
        }
    }

};


int main(int argc, char* argv[]){
    ifstream inFile(argv[1]);
    ofstream outFile(argv[2]);
    selectionSort S;

    S.getN(inFile);
    inFile.open(argv[1]);
    S.loadAry(inFile);
    S.selectionSorting();
    S.printAry(outFile);

    inFile.close();
    outFile.close();
    return 0;
}