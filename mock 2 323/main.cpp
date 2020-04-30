#include <iostream> 
#include <string>
#include <fstream>
using namespace std;

class Node{
    public:
    int data = -9999;
    Node* prev;
    Node* next;

    Node(int d){
        data = d;
        next = NULL;
    }
};

class selectionSort{
    public:
    Node* head = new Node(-9999);
    int N = 0;

    void createList(ifstream& inFile){
        int data;
        while(!inFile.eof()){
            inFile >> data;
            Node* newNode = new Node(data);
            N++;

            Node* temp = head->next;
            head->next = newNode;
            newNode->prev = head;
            newNode->next = temp;
        }
    }

    void selectionSorting(){
        Node* position = head->next;
        while(position->next->next != NULL){
            Node* lowestFound = position;
            Node* findingNode = position->next;

            while(findingNode->next != NULL){
                if(findingNode->data < lowestFound->data){
                    lowestFound = findingNode;
                }
                findingNode = findingNode->next;
            }

            if(lowestFound->data < position->data){

                Node* temp;
                temp->next = lowestFound->next;
                temp->prev = lowestFound->prev;

                lowestFound->next = position->next;
                lowestFound->prev = position->prev;

                position->next = temp->next;
                position->prev = temp->prev;

                delete temp;


            }

            position = position->next;

        }
    }

    void printList(ofstream& outFile){
        Node* spot = head->next->next;
        while(spot->next != NULL){
            outFile << spot->data << endl;
            spot = spot->next;
        }
    }
};

int main(int argc, char* argv[]){
    ifstream inFile(argv[1]);
    ofstream outFile(argv[2]);

    selectionSort S;
    S.createList(inFile);
    // S.selectionSorting(); 
    S.printList(outFile);

    inFile.close();
    outFile.close();
}

