import javax.swing.JOptionPane;
public class Stnd {
	public static void out(String outMessage){
	JOptionPane.showMessageDialog(null, outMessage, "standard output dialog box", JOptionPane.INFORMATION_MESSAGE);
	}

	public static String getStr(String outMessage) {
	String temp;

	for(;;)
	{
	temp = JOptionPane.showInputDialog(null, outMessage, "standard input dialog box", JOptionPane.QUESTION_MESSAGE);
		
	//checking to see if temp has something in it		
	if(temp == null) 
			out("YOU MUST ENTER SOMETHING TO PROGRESS ANY FURTHER.");
	else if(temp.length() <= 0)
			out("YOU MUST ENTER SOMETHING TO PROGRESS ANY FURTHER.");			
	else break;
		
	
	}
	return temp;
	}

	public static byte getB(String passMessage){
	return Byte.parseByte(getStr(passMessage)); 
	}

	public static int getI(String passMessage){
	return Integer.parseInt(getStr(passMessage));
	}

	public static short getS(String passMessage){
	return Short.parseShort(getStr(passMessage));	
	}

	public static long getL(String passMessage){
	return Long.parseLong(getStr(passMessage));
	}

	public static float getF(String passMessage){
	return Float.parseFloat(getStr(passMessage));
	}

	public static double getD(String passMessage){
	return Double.parseDouble(getStr(passMessage));
	}

}