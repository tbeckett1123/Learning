/*
Class Name: Sums
Programmer: Tim Beckett
Languaage: sun's sdk1.4.1_01 java
flowchart: see flowchart
function: this program sums all the int's in a 2d array and prints the sum
Inputs: na
Output: sum of the ints
Other classes used: Stnd
Data Restrictions: na
*/

public class sums {

	public static void main (String args[]) {
	int[][] theNums = {{1,2,3,4,5},{6,7,8,9},{10,11,12,13},{14,15,16,17}};
	int sum = 0;
	for(int x = 0; x < theNums.length; x++)
		{
		for(int y = 0; y < theNums[x].length; y++)
			sum  += theNums[x][y];
			
		}	
	Stnd.out("the sum of all the Ints in theNums is "+sum);
	System.exit(0);
	}
}