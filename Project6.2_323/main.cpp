#include <iostream>
#include <string>
#include <fstream>
using namespace std;

// Prototypes
void decodeMethod1(fstream& encodeFile, fstream& decodeFile, int numRows, int numCols);
void decodeMethod4(fstream& encodeFile, fstream& decodeFile, int numRows, int numCols);

int main(int argc, char* argv[]){
  // 0
  string nameEncodeFile = argv[1];
  fstream encodeFile(argv[1]);

  // cout << nameEncodeFile << endl; // DEBUGSTUFF
  // 1
  int numRows, numCols, minVal, maxVal, whichMethod;
  encodeFile >> numRows;
  encodeFile >> numCols;
  encodeFile >> minVal;
  encodeFile >> maxVal;
  // 2
  encodeFile >> whichMethod;
  if(whichMethod != 1 && whichMethod !=4){
    cout << "ERROR: data is not encoded properly" << endl;
    exit(1);
  }
  // 3
  int pos = nameEncodeFile.find(".txt");
  nameEncodeFile = nameEncodeFile.substr(0,pos);
  string nameDecodeFile = nameEncodeFile + "_Decoded.txt";
  fstream decodeFile(nameDecodeFile, fstream::out);
  // 4
  decodeFile << numRows << " " << numCols << " " << minVal << " " << maxVal << endl;

  // 5
  if(whichMethod == 1){
    decodeMethod1(encodeFile, decodeFile, numRows, numCols);
  } else if (whichMethod == 4) {
    decodeMethod4(encodeFile, decodeFile, numRows, numCols);
  } else {
    cout << "ERROR: data is not encoded properly" << endl;
    exit(1);
  }
  // 6
  encodeFile.close();
  decodeFile.close();
  return 0;
}


// My Functions
void decodeMethod4(fstream& encodeFile, fstream& decodeFile, int numRows, int numCols){
  int rowCount = 0, colCount = 0;// these are the position of the 'read head'
  int startRow, startCol, color, length;
  encodeFile >> startRow;
  encodeFile >> startCol;
  encodeFile >> color;
  encodeFile >> length;

  // read from image, if row&col match print color for length run
  // else print zero and move colCOunt++

  while(!encodeFile.eof() && rowCount < numRows){

    if(rowCount == startRow && colCount == startCol){
      for(int i = 0; i < length; i++){
        decodeFile << color << " ";
        colCount++;
        if(colCount == numCols){ // because we keep wrap around
          decodeFile << endl;
          colCount = 0;
          rowCount++;
        }
      }

      encodeFile >> startRow;
      encodeFile >> startCol;
      encodeFile >> color;
      encodeFile >> length;
    } else {
      decodeFile << 0 << " ";
      colCount++;
      if(colCount == numCols){ // wrap around AKA newline
        decodeFile << endl;
        colCount = 0;
        rowCount++;
      }
    }
  }

  //if eof but still some Rows left, fill with zero
  while(rowCount < numRows){
    decodeFile << 0 << " ";
    colCount++;
    if(colCount == numCols){ // because we keep wrap around
      decodeFile << endl;
      colCount = 0;
      rowCount++;
    }
  }

}

void decodeMethod1(fstream& encodeFile, fstream& decodeFile, int numRows, int numCols){
  // cout << "Calling decodeMethod1" << endl; // DEBUGSTUFF
  int rowCount = 0, colCount = 0;
  // 0
  rowCount = 0;
  colCount = 0; // here because we reset to zero when we are at the last column only;
  int startRow, startCol, color, length;

  while(!encodeFile.eof() && rowCount < numRows){
    encodeFile >> startRow;
    encodeFile >> startCol;
    encodeFile >> color;
    encodeFile >> length;
    // cout << startRow << " " << startCol << " " << color << " " << length << endl; // DEBUGSTUFF
    // 3
    for(int i = 0; i < length; i++){
      decodeFile << color << " ";
      colCount++;
      if(colCount == numCols){ // because we keep wrap around
        decodeFile << endl;
        colCount = 0;
        rowCount++;
      }
    }
  }
}
