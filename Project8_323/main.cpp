#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <cmath>       
using namespace std;

// Data structures
class Point{
    public:
    double Xcoord;
    double Ycoord;
    int Label = 0;
    double Distance = 99999.00;
};


// Prototypes
void loadPointSet(ifstream& inFile, Point* pointSet);
void PlotDisplayAry(Point* pointSet, int** displayAry, int numPts);
void PrettyPrint(int** displayAry, ofstream& outFile, int iteration, int rows, int cols);
void kMeansClustering(Point* pointSet, int K, Point* KcentroidAry, int** displayAry, ofstream& outFile1, ofstream&  outFile2, int numPts, int numRows, int numCols, int changes);

void selectKcentroids(Point* pointSet, int K, Point* KcentroidAry, int numPts);
int DistanceMinLabel(Point& pt, Point* KcentroidAry, double& minDist, int K);
double computeDist(Point pt, Point centroid);
void computeCentroids(Point* pointSet, Point* KcentroidAry, int K, int numPts);
void PrintResult(Point* pointSet, ofstream& outFile1, int numRows, int numCols, int numPts);





int main(int argc, char* argv[]){
    ifstream inFile(argv[1]);
    int K = stoi(argv[2]);
    ofstream outFile1(argv[3]);
    ofstream outFile2(argv[4]);

    // Variables
    // 1
    int numRows, numCols, numPts, changes = 0;
    inFile >> numRows;
    inFile >> numCols;
    inFile >> numPts;

    int** displayAry = new int*[numRows];
    for(int i = 0; i < numRows; i++){
        displayAry[i] = new int[numCols];
    }

    Point* pointSet = new Point[numPts];
    Point* KcentroidAry = new Point[K+1];
    for(int i = 0; i < K+1; i++){
        KcentroidAry[i].Distance = 0.0;
    }

    loadPointSet(inFile, pointSet);
    kMeansClustering(pointSet, K, KcentroidAry, displayAry, outFile1, outFile2, numPts, numRows, numCols, changes);
    PrintResult(pointSet, outFile2, numRows, numCols, numPts);

    // Closing Files
    inFile.close();
    outFile1.close();
    outFile2.close();
}



// Functions

void PrintResult(Point* pointSet, ofstream& outFile2, int numRows, int numCols, int numPts){
    outFile2 << numRows << " " << numCols << endl;
    outFile2 << numPts << endl;

    for(int i = 0; i < numPts; i++){
        outFile2 << pointSet[i].Xcoord << " " << pointSet[i].Ycoord << " " << pointSet[i].Label << endl;
    }
}

void computeCentroids(Point* pointSet, Point* KcentroidAry, int K, int numPts){
    double sumX[K+1];
    double sumY[K+1];
    int totalPt[K+1];
    for(int i = 0; i < K+1; i++){
        sumX[i] = 0.0;
        sumY[i] = 0.0;
        totalPt[i] = 0;
    }

    // 1
    int index = 0;
    int label = 0;

    

    while(index < numPts){
        //2 
        label = pointSet[index].Label;
        sumX[label] += pointSet[index].Xcoord;
        sumY[label] += pointSet[index].Ycoord;
        totalPt[label]++;

        // 3
        index++;
    } // 4

    // 5
    label = 1;

    

    while(label <= K){ // <= K because we need K elements and we start label at 1
        // 6
        if(totalPt[label] > 0.0){
            KcentroidAry[label].Xcoord = (sumX[label]/totalPt[label]);
            KcentroidAry[label].Ycoord = (sumY[label]/totalPt[label]);
        }

        // 7
        label++;
    }


}

double computeDist(Point pt, Point centroid){
    double result = sqrt(     pow( (pt.Xcoord-centroid.Xcoord), 2)    +   pow( (pt.Ycoord-centroid.Ycoord), 2)   );
    return result;
}

int DistanceMinLabel(Point& pt, Point* KcentroidAry, double& minDist, int K){
    // minDist = 99999.0;
    int minLabel = 0;

    int label = 1;

    while (label <= K){
        // Point whichCentroid = KcentroidAry[label];

        double dist = computeDist(pt, KcentroidAry[label]);

        if(dist < minDist){
            minLabel = label;
            minDist = dist;
        }
        label++;
    }
    return minLabel;
}

void selectKcentroids(Point* pointSet, int K, Point* KcentroidAry, int numPts){
    // creating data structure
    bool checkedPoints[numPts];
    for(int i = 0; i < numPts; i++){ checkedPoints[i] = false;}

    int index = rand() % numPts;
    // bool repeatYN = false;
    int Kcnt = 0;
    while(Kcnt < K){
        while(checkedPoints[index]){
            index = rand() % numPts;
            // repeatYN = checkedPoints[index];
        }
        Kcnt++;
        KcentroidAry[Kcnt].Xcoord = pointSet[index].Xcoord;
        KcentroidAry[Kcnt].Ycoord = pointSet[index].Ycoord;
        KcentroidAry[Kcnt].Label = Kcnt;
        KcentroidAry[Kcnt].Distance = 0.0;

        checkedPoints[index] = true;
    }

}



void kMeansClustering(Point* pointSet, int K, Point* KcentroidAry, int** displayAry, ofstream& outFile1, ofstream&  outFile2, int numPts, int numRows, int numCols, int changes){
    // 0
    int iteration = 0;
    int index = 0;
    int doOnce = 1;

    // 1
    selectKcentroids(pointSet, K, KcentroidAry, numPts);

    while (iteration < 25 || doOnce > 0) { // 2 - 9
        doOnce--;
        // 2
        index = 0;
        iteration++;

        

       

        while (index < numPts){ // 4 - 7
            // 4
            Point pt = pointSet[index];
            double minDist = pointSet[index].Distance;

            // 5
            int minLabel = DistanceMinLabel(pt, KcentroidAry, minDist, K);
            // pointSet[index].Distance = minDist;

            // 6
            if(pointSet[index].Label != minLabel){
                
                pointSet[index].Label = minLabel;
                pointSet[index].Distance = minDist;
                changes++;
            }
            // 7
            index++;
        } // 8 loop


        

        // 9 
        if (changes > 2) {
            computeCentroids(pointSet, KcentroidAry, K, numPts);
            changes = 0;
        }

        // // 3
       
        PlotDisplayAry(pointSet, displayAry, numPts);
        PrettyPrint(displayAry, outFile1, iteration, numRows, numCols);

         
        


    }// 10 loop

}

void PrettyPrint(int** displayAry, ofstream& outFile1, int iteration, int rows, int cols){
    outFile1 << "\t*************** Result of iteration " << iteration << " ***************" << endl;
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            if(displayAry[i][j] > 0 ){
                outFile1 << displayAry[i][j];
            } else {
                outFile1 << " ";
            }
        }
        outFile1 << endl;
    }
}


void PlotDisplayAry(Point* pointSet, int** displayAry, int numPts){
    // X is the row
    // Y is the col
    for(int i = 0 ; i < numPts; i++){
        displayAry
        [(int) pointSet[i].Xcoord]
        [(int) pointSet[i].Ycoord] = pointSet[i].Label;
    }
}

void loadPointSet(ifstream& inFile, Point* pointSet){
    int index = 0;
    int x,y;
    while(!inFile.eof()){
        inFile >> x;
        inFile >> y;

        pointSet[index].Xcoord = (double) x;
        pointSet[index].Ycoord = (double) y;
        pointSet[index].Label = 0;
        pointSet[index].Distance = 99999.0;

        index++;
    }
}