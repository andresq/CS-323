import java.util.Scanner;
import java.io.*;

public class NewWrite {
	public static void main(String[] args){
		String fileName = args[0];

		// Opening file MUST include catching FileNotFoundEXception
		PrintWriter outFile = null;
		try {
			outFile = new PrintWriter(fileName);
		} catch (FileNotFoundException err) {
			System.out.println("Error in opening file: " + err);
		}


		for(int i=0;i<50;i++){
			outFile.println(i);

}

		outFile.close();
	}
}
