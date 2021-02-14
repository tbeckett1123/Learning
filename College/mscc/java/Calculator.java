import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.text.*;
public class Calculator extends JFrame implements ActionListener
	{
	private JButton clr, eql, add, sub,mul, div, dec, clsFrm, neg;
	private JButton b0, b1, b2, b3, b4, b5, b6, b7, b8, b9;
	private JTextField screen;
	private String textNum = "0";
	private float operand, result = 0; 
	private int flag = 1;
	
	public static void main(String args[])
		{
		Calculator mainFrame = new Calculator();
		mainFrame.setTitle("Calculator");
		mainFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		mainFrame.setSize(250,200);
		mainFrame.setVisible(true);	
		}
		
	public Calculator()
		{
		
		neg = new JButton("neg");	
		dec = new JButton(".");
		clsFrm = new JButton("exit");
		clr = new JButton("clr");
		eql = new JButton("=");
		add = new JButton("+");
		sub = new JButton("-");
		mul = new JButton("*");
		div = new JButton("/");
		b0 = new JButton("0");
		b1 = new JButton("1");
		b2 = new JButton("2");
		b3 = new JButton("3");	
		b4 = new JButton("4");
		b5 = new JButton("5");
		b6 = new JButton("6");
		b7 = new JButton("7");
		b8 = new JButton("8");
		b9 = new JButton("9");
		
		neg.addActionListener(this);
		dec.addActionListener(this);
		clsFrm.addActionListener(this);
		clr.addActionListener(this);
		eql.addActionListener(this);
		add.addActionListener(this);
		sub.addActionListener(this);
		mul.addActionListener(this);
		div.addActionListener(this);
		b0.addActionListener(this);
		b1.addActionListener(this);
		b2.addActionListener(this);
		b3.addActionListener(this);
		b4.addActionListener(this);
		b5.addActionListener(this);
		b6.addActionListener(this);
		b7.addActionListener(this);
		b8.addActionListener(this);
		b9.addActionListener(this);
	
		Container container = getContentPane();
		container.setLayout(new BorderLayout());
	
		JPanel p1 = new JPanel();
		JPanel p2 = new JPanel();
		screen = new JTextField("0", 22);
		screen.setEditable(false);
		screen.setHorizontalAlignment(SwingConstants.RIGHT);
		
	
		p1.add(screen);
		p2.setLayout(new GridLayout(5,4));
		p2.add(b7); p2.add(b8);	p2.add(b9);	p2.add(add);
		p2.add(b4);	p2.add(b5);	p2.add(b6);	p2.add(sub);
		p2.add(b1); p2.add(b2); p2.add(b3); p2.add(mul);
		p2.add(b0); p2.add(dec); p2.add(eql); p2.add(div);
		p2.add(neg); p2.add(clr); p2.add(clsFrm);
			
		container.add(p1, BorderLayout.NORTH);
		container.add(p2, BorderLayout.SOUTH);
		}		
	

	public void actionPerformed(ActionEvent e) 
		{
		if(e.getSource() == neg)
			{
			String tempText = "-"+textNum;
			textNum = tempText;
			printLcd(convert());	
			}
		else if(e.getSource() == dec)
			{
			textNum +=	".";
			printLcd(convert());
			}
		else if(e.getSource() == b0)
			{
			textNum += "0";
			printLcd(convert());
			}
		else if(e.getSource() == b1)
			{
			textNum += "1";	
			printLcd(convert());
			}		
		else if(e.getSource() == b2)
			{
			textNum += "2";	
			printLcd(convert());
			}
		else if(e.getSource() == b3)
			{
			textNum += "3";		
			printLcd(convert());
			}
		else if(e.getSource() == b4)
			{
			textNum += "4";	
			printLcd(convert());
			}
		else if(e.getSource() == b5)
			{
			textNum += "5";		
			printLcd(convert());
			}
		else if(e.getSource() == b6)
			{
			textNum += "6";		
			printLcd(convert());
			}
		else if(e.getSource() == b7)
			{
			textNum += "7";		
			printLcd(convert());
			}
		else if(e.getSource() == b8)
			{
			textNum += "8";		
			printLcd(convert());
			}
		else if(e.getSource() == b9)
			{
			textNum += "9";		
			printLcd(convert());
			}
		
		else if(e.getSource() == eql)
			{
			 eqlOp();
			}
		else if(e.getSource() == clr)
			{
			 clrOp();
			}
		else if(e.getSource() == add)
			{
			eqlOp(); 
			printLcd(result);	
			flag = 1;
			}
		else if(e.getSource() == sub)
			{
			eqlOp();
			printLcd(result);		
			flag = 2;
			}
		else if(e.getSource() == mul)
			{
			eqlOp();
			printLcd(result);		
			flag = 3;
			}
		else if(e.getSource() == div)
			{
			eqlOp();
			printLcd(result);	
			flag = 4;
			}
		else System.exit(0);		
		}
	
	private void addOp()
		{
		operand = convert();
		if(result > 0.00001 || result < -0.00001)
			result = result + operand;
		else result = operand;
		reset();
		}
	private void subOp()
		{
		operand = convert();
		if(result > 0.00001 || result < -0.00001)
			result = result - operand;
		else result = operand;
		reset();
		}
	private void mulOp()
		{
		operand = convert();
		if(result > 0.00001 || result < -0.00001)
			result = result * operand;
		else result = operand;
		reset();
		}
	private void divOp()
		{
		operand = convert();
		if(operand < 0.00001 && operand > -0.00001)
			clrOp(); 			
		else if(result >  0.00001 || result < -0.00001)
			 result = result /operand;
		else result = operand;
		reset();
		}		
	private void reset()
		{
		textNum = "0";	
		}
	private void clrOp()
		{
		 textNum = "0";
		 operand = 0;
		 result = 0;
		 printLcd(result);
		 flag = 1;	
		}
	private void eqlOp()
		{
		switch(flag)
			{
			case 1: addOp();printLcd(result);break;
			case 2: subOp();printLcd(result);break;
			case 3: mulOp();printLcd(result);break;
			case 4: divOp();
					if(operand > 0.0001)
						printLcd(result);
					else screen.setText("ERROR");
			}
		}
	private float convert()
		{
		return Float.parseFloat(textNum);	
		}
	private void printLcd(float temp)
		{
		NumberFormat numberForm = NumberFormat.getNumberInstance();
		DecimalFormat df = (DecimalFormat)numberForm;
		df.applyPattern("0.000");
		screen.setText(""+df.format(temp));	
		}
	}

			
