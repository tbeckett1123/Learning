import java.io.*;
import java.net.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class LoanServer	extends JFrame
{
	private JTextArea LSscreen = new JTextArea();
	
	public static void main(String[] args)
		{
		new LoanServer();
		}
		
	public LoanServer()
		{
		getContentPane().setLayout(new BorderLayout());
		getContentPane().add(new JScrollPane(LSscreen), BorderLayout.CENTER);  
		setTitle("Loan Server");
		setSize(500,300);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setVisible(true);
		try
			{
			ServerSocket ss = new ServerSocket(2000);
			int clientNo = 1;
			LSscreen.append("Loan Server Started \n");
			while(true)
				{
				Socket connect = ss.accept();
				LSscreen.append("new client logged on\n");	
				Client thread = new Client(connect, clientNo);
				thread.start();
				if(thread.isAlive() == false)
					LSscreen.append("a client has logged off\n");
				clientNo++;
				}
			}
		catch(IOException ex)
			{}			
		}			
	
	
class Client extends Thread
	{
	private Socket clientSocket;
	private int clientNo;
	
	public Client(Socket connect, int number)
		{
		clientSocket = connect;
		clientNo = number;	
		}
	public void run()
		{
		try
			{
			DataInputStream fromClient = new DataInputStream(clientSocket.getInputStream());  
        	DataOutputStream toClient = new DataOutputStream(clientSocket.getOutputStream()); 
        
        	while(true)
        		{
        		LSscreen.append("data recieved from client "+clientNo+"\n");
        		double rate = fromClient.readDouble();
        		double years = fromClient.readDouble();
        		double amount = fromClient.readDouble();
        		double i = rate / 100 * years	* amount;
        		double payment = (i + amount)/(years * 12);
        		toClient.writeDouble(payment);
        		toClient.writeDouble(i+amount);        	        	
        		}			
        	}
        catch(IOException e)
        	{}
		}
	}
}