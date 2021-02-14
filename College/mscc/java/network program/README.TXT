  Class Name:	Loan calculator and Loan server
  Programmer:	Tim Beckett
        Date:	April 29, 2003
    Language:	sun's sdk.1.4.1_01 java
   Flowchart:	See Flowchart
    Function:	Loan calculator collects data from a remote user and
		sends the data to the Loan server to calculate the 
		interest to be charged monthly payments and total of
		all the payments
      Inputs:	apr, number of years, and loan amount
     Outputs:	apr, number of years, loan amount, monthly payments,
		and total of payments
Other
  Classes
        Used:	stnd.class
Data
Restrictions:	apr must be enter in % format, all other numbers are
		doubles regardless of how you enter them.
      Method:	the server must be up and running.
		the user must enter the host IP address.
		the loan calculator will establish a connection to the
		server.
		the loan calculator then waits for the user to enter
		the loan data and click submit.
		it then transmits the data to the server.
		the server calculates the the interest charged, the
		monthly payment, and the total of payments.
		the server then send the new data back to the loan
		calculator.
		the loan calculator then prints the data for the user
		to view.
Printed
      Output: 	N/A
