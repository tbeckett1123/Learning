import java.io.*;
import java.net.*;
import java.util.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class LoanCalculator extends JFrame implements ActionListener 
	{
	private JTextField rateField = new JTextField();
	private JTextField amountField = new JTextField();
	private JTextField timeField = new JTextField();
	private JTextArea output = new JTextArea();
	private JButton submit = new JButton("submit");
	private JButton close = new JButton("close");
	
	DataInputStream fromServer;
	DataOutputStream toServer;
	
	public static void main(String[] args)
		{
		new LoanCalculator();	
		}
		
	public LoanCalculator()
		{
		JPanel dataPanel = new JPanel();
		dataPanel.setLayout(new GridLayout(2, 0)); 
		dataPanel.add(new JLabel("Annual Interest Rate"));
		dataPanel.add(rateField);
		dataPanel.add(new JLabel("Nuber of Years"));
		dataPanel.add(timeField);
		dataPanel.add(new JLabel("Amount of Loan"));
		dataPanel.add(amountField);
		dataPanel.add(submit);
		dataPanel.add(close);
		
		getContentPane().setLayout(new BorderLayout());
		getContentPane().add(dataPanel, BorderLayout.NORTH);
		getContentPane().add(new JScrollPane(output));
		setTitle("Loan Calculator");
		setSize(500,300);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setVisible(true);
		
		submit.addActionListener(this);
		close.addActionListener(this);
		
		try
			{
			String serverIP = Stnd.getStr("enter the host IP address:");
			Socket serverSocket = new Socket(serverIP, 2000);
			
			fromServer = new DataInputStream(serverSocket.getInputStream());
			toServer = new DataOutputStream(serverSocket.getOutputStream());
			
			output.append("* * * * Conection Established * * * * \n"); 
			}
		catch(IOException ex)
			{
			output.append("  * * * * Connection Failed * * * * \n");	
			}			
		}
	public void actionPerformed(ActionEvent e)
		{
		if(e.getSource() == close)
			System.exit(0);
		else if(e.getSource() == submit);
			{
			try
				{
				double rate = Double.parseDouble(rateField.getText().trim());
				double years = Double.parseDouble(timeField.getText().trim());
				double amount = Double.parseDouble(amountField.getText().trim());
				toServer.writeDouble(rate);
				toServer.flush();
				toServer.writeDouble(years);
				toServer.flush();
				toServer.writeDouble(amount);
				toServer.flush();
				double payment = fromServer.readDouble();
				double tPayment = fromServer.readDouble();
				
				output.append("rate: "+rate+"\nyears: "+years+"\namount: "+amount+"\nmonthly payment: "+payment+"\ntotal payments: "+tPayment+"\n");				
				}
			catch(IOException exz)
				{}	
			}
		}
	}