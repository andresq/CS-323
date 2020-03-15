import java.util.Scanner;
import java.io.*;

public class NewRead {
	public static void main(String[] args){

		String fileName = args[0];
		// Console i/o
		Scanner input = new Scanner(System.in);
		int dataIn = input.nextInt();


		Scanner inFile = null;
		try {
			inFile = new Scanner(new File(fileName));
			while(inFile.hasNext()) {
				System.out.println(inFile.nextLine());
			}
		} catch (FileNotFoundException err) {
			System.out.println("Error in opening file: " + err);
		}

		inFile.close();
	}
}
