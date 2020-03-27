#include <iostream>
#include <fstream>
#include <string>
using namespace std;


// Prototypes
void encodeMethod1(fstream &inFile, fstream& encodeFile, int numRows, int numCols);
void enocdeMethod4(fstream& inFile, fstream& encodeFile, int numRows, int numCols);
int skipZeros(fstream& inFile, int& row, int& col, int& zeroCount, int numCols);

int main(int argc, char* argv[]){
  fstream inFile(argv[1]);

  //Varibles
  int numRows, numCols, minVal, maxVal;
  int whichMethod;

  // Reading image header from inFile
  inFile >> numRows;
  inFile >> numCols;
  inFile >> minVal;
  inFile >> maxVal;

  whichMethod = stoi(argv[2]);

  string fileName = argv[1];
  string methodNumber = argv[2];
  string nameEncodeFile = fileName + "_EncodeMethod" + methodNumber + ".txt";

  fstream encodeFile(nameEncodeFile, fstream::out);

  //Writing image header to encodeFile
  encodeFile << numRows << " " << numCols << " " << minVal << " " << maxVal << endl;
  encodeFile << whichMethod << endl;

  if (whichMethod == 1){
    encodeMethod1(inFile, encodeFile, numRows, numCols);
  } else if (whichMethod == 4) {
    enocdeMethod4(inFile, encodeFile, numRows, numCols);
  } else {
    encodeFile << "Error in endcoding" << endl;
  }


//closing files
inFile.close();
encodeFile.close();
}

// Functions
int skipZeros(fstream& inFile, int& row, int& col, int& zeroCount, int numCols){
  int pixelVal;
  zeroCount = 0;
  inFile >> pixelVal;


  while(pixelVal == 0){

    inFile >> pixelVal;
    col++;
    if(col == numCols){
      col = 0;
      row++;
    }

    if(pixelVal == 0){
      zeroCount++;
    }


  }
  return pixelVal;
}


void enocdeMethod4(fstream& inFile, fstream& encodeFile, int numRows, int numCols){
  int nextVal, zeroCount;

  int row = 0;
  int col = 0;
  int length = 1;

  int lastVal = skipZeros(inFile, row, col, zeroCount, numCols);
  encodeFile << row << " " << col << " " << lastVal << " ";

  while(inFile >> nextVal){
    col++;
    if(col == numCols){
      col = 0;
      row++;
    }

    if(nextVal == 0){
      inFile >> nextVal;
      col++;
      if(col == numCols){
        col = 0;
        row++;
      }
      lastVal = 0;
    } else if(nextVal == lastVal){
      length++;
    } else {
      encodeFile << length << endl;
      encodeFile << row << " " << col << " " << nextVal << " ";
      length = 1;
      lastVal = nextVal;
    }

  }

  encodeFile << length << endl;


}

void encodeMethod1(fstream& inFile, fstream& encodeFile, int numRows, int numCols){
  int row, col, length, currVal, nextVal;

  row = 0;
  while (row < numRows){
    //1
    col = 0;
    length = 0;
    inFile >> currVal;
    encodeFile << row << " " << col << " " << currVal << " "; // first output before an checks
    length++;

    while(col < numCols-1){ //negative one to count for the offset of outputing once already
      //2
      col++;
      //3
      inFile >> nextVal;
      //4
      if(nextVal == currVal){
        length++;
      } else {

        encodeFile << length << endl;
        currVal = nextVal;
        encodeFile << row << " " << col << " " << currVal << " ";
        length = 1;
      }
    } // 5 (loop)
    //6
    encodeFile << length << endl;
    row++;
  }
}














//
