#include <iostream>
#include <fstream>
#include <string>

using namespace std;


class listNode {
public:
  int data;
  listNode* next;

  listNode(int parameterData, listNode* parameterNext){
    data = parameterData;
    next = parameterNext;
  };
};

// Prototypes
void printList(listNode* node, fstream& outFile);
listNode* findSpot(listNode* listHead, listNode* newNode);
void listInsert(listNode* listHead, listNode* newNode);
void constructLL(listNode* listHead, fstream& inFile, fstream& outFile2);
void printNode(listNode* node, fstream& outFile);
listNode* findMiddleNode(listNode* listHead, fstream& outFile);



int main(int argc, char* argv[]){
  fstream inFile(argv[1]);   // Input File
  fstream outFile1(argv[2], fstream::out); // Sorted LinkList AND Middle Node
  fstream outFile2(argv[3], fstream::out); // Debugging


  listNode* listHead = new listNode(-9999, NULL);

  constructLL(listHead, inFile, outFile2);

  printList(listHead, outFile1);

  // SEGMENT FAULT??
  listNode* middleNode = findMiddleNode(listHead, outFile2);
  printNode(middleNode, outFile1);


  //Closing all files
  inFile.close();
  outFile1.close();
  outFile2.close();
}

void constructLL(listNode* listHead, fstream& inFile,fstream& outFile2){
  int data;
  while(inFile >> data){ // same as eof
    listNode* newNode = new listNode(data, NULL);
    listInsert(listHead, newNode);
    printList(listHead, outFile2);
  }
}

void listInsert(listNode* listHead, listNode* newNode){
  listNode* Spot = findSpot(listHead, newNode);
  newNode->next = Spot->next;
  Spot->next = newNode;
}

listNode* findSpot(listNode* listHead, listNode* newNode){
  listNode* Spot = listHead;
  while(Spot->next != NULL && Spot->next->data < newNode->data){
      Spot = Spot->next;
  }

  return Spot;
}

void printList(listNode* node, fstream& outFile){
  outFile << "listHead ->";
  while(node != NULL){
    if(node->next == NULL){ // because NULL->data will cause a segment falt 11
      outFile << "(" << node->data << "," << node << "," << node->next << "," << "NULL" << ")";
    } else {
      outFile << "(" << node->data << "," << node << "," << node->next << "," << node->next->data << ") ->";
    }
    node = node->next;
  }
  outFile << "-> NULL" << endl;


}

listNode* findMiddleNode(listNode* listHead, fstream& outFile){
  listNode* walk1 = listHead;
  listNode* walk2 = listHead;

  while(walk2 !=  NULL && walk2->next != NULL){
    printNode(walk1, outFile);
    walk1 = walk1->next;
    walk2 = walk2->next->next;
  }

  return walk1;
}

void printNode(listNode* node, fstream& outFile){
  if(node->next == NULL){
      outFile << "(" << node->data << "," << node << "," << node->next << "," << "NULL" << ")";// because NULL->data will cause a segment falt 11
    } else {
      outFile << "(" << node->data << "," << node << "," << node->next << "," << node->next->data << ") ->";
    }
}
