import java.util.*;
import java.io.*;

class listNode {
        String data;
        listNode next;

        // Constructor to create a new node
        // Next is by default initialized
        // as null
        listNode(String data, listNode next) {
          this.data = data;
          this.next = next;
        }
    }



public class reverseLL{
  public static void main(String[] args) {
    // Opening Files
    Scanner inFile = null;
    PrintWriter outFile1 = null;
    PrintWriter outFile2 = null;
    // Error Catching
    try {
      inFile = new Scanner(new File(args[0]));
    } catch (FileNotFoundException err) {
      System.out.println("Error in opening inputFile: " + err);
    }

    try {
      outFile1 = new PrintWriter(args[1]);
    } catch (FileNotFoundException err) {
      System.out.println("Error in opening outFile1: " + err);
    }

    try {
      outFile2 = new PrintWriter(args[2]);
    } catch (FileNotFoundException err) {
      System.out.println("Error in opening outFile2: " + err);
    }

    // Creating listHead
    listNode listHead = new listNode("dummy", null);


    constructLL(listHead, inFile, outFile2);
    //Caption 1
    outFile1.println("Printing the original sorted list");
    printList(listHead, outFile1);

    LLreverse(listHead, outFile2);
    //Caption 2
    outFile1.println("Printing the reversed sorted list");
    printList(listHead, outFile1);

    // Closing Files
    inFile.close();
    outFile1.close();
    outFile2.close();
  }
  // Functions
    public static void constructLL(listNode listHead, Scanner inFile, PrintWriter outFile) {
      String data;
      while(inFile.hasNext()){
        data = inFile.next();
        listNode newNode = new listNode(data, null);
        listInsert(listHead, newNode);
        printList(listHead, outFile);
      }
    }

    public static void listInsert(listNode listHead, listNode newNode) {
      listNode spot = findSpot(listHead, newNode);
      newNode.next = spot.next;
      spot.next = newNode;
    }

    public static listNode findSpot(listNode listHead, listNode newNode) {
      listNode spot = listHead;
      //compareToIgnoreCase because 'A' should be equal to 'a'
      while(spot.next != null && ( spot.next.data.compareToIgnoreCase(newNode.data) < 0  )){
        spot = spot.next;
      }
      return spot;
    }

    // Doesn't need to be listHead, node is okay
    public static void printList(listNode node, PrintWriter outFile) {
      outFile.print("listHead-> ");
      while(node != null){
        if(node.next == null){ // Reading null.data causes an error
          outFile.print("(" + node.data + "," + node + "," + node.next + "," + "NULL" + ")");
        } else {
          outFile.print("(" + node.data + "," + node + "," + node.next + "," + node.next.data + ")-> ");
        }
        node = node.next;
      }
      outFile.println("-> NULL");
    }

    public static void LLreverse(listNode listHead, PrintWriter outFile) {
      listNode last = listHead.next;
      listNode spot = null;

      while(last.next != null){
        spot = last.next;
        last.next = spot.next; // Need this else it hangs bc of unlinking
        moveSpotNodeToFront(listHead, spot);
        printList(listHead, outFile);
      }
    }

    public static void moveSpotNodeToFront(listNode listHead, listNode spot) {
      spot.next = listHead.next;
      listHead.next = spot;
    }

    public static listNode findMiddleNode(listNode listHead, PrintWriter outFile) {
      listNode walk1 = listHead;
      listNode walk2 = listHead;

      while(walk2 != null && walk2.next != null) {
        printNode(walk1, outFile);
        walk1 = walk1.next;
        walk2 = walk2.next.next;
      }
      return walk1;
    }

    public static void printNode(listNode node, PrintWriter outFile) { // Same as printList except no loop
      if(node.next == null){ // Reading null.data causes an error
        outFile.print("(" + node.data + "," + node + "," + node.next + "," + "NULL" + ")");
      } else {
        outFile.print("(" + node.data + "," + node + "," + node.next + "," + node.next.data + ")->");
      }
    }

}
