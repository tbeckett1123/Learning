import javax.swing.JOptionPane;
public class tempConvert {
	public static void main (String args[]){
	double f, c;
	
	String temp = JOptionPane.showInputDialog(null, "What is the temperature in fahrenheit?", "temperature coversion", JOptionPane.QUESTION_MESSAGE);
	
	f = Double.parseDouble(temp);
	
	c = 5.0/9.0*(f-32);

	String ctemp = f+" degrees fahrenheit is "+c+" degrees celsius\n END OF LINE";

	JOptionPane.showMessageDialog(null, ctemp, "temperature coversion", JOptionPane.INFORMATION_MESSAGE);
	
	System.out.print("END OF LINE");	
	
	System.exit(0);
	}
}