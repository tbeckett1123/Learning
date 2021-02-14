/*
  Class Name:   TempConvertor
  Programmer:	Tim Beckett
        Date:   2-11-03
    Language:	sun's sdk.1.4.1_01 java
   Flowchart:	See Flowchart
    Function:   This program prints out to a popup box a table of Celsius
                temps and each equavelant Fahrenheit temp
      Inputs:   n\a
     Outputs:   table of celsuis and fahreneit temps
Other
  Classes
        Used:   Stnd
Data
Restrictions:   n\a
      Method:   c = 40.0
                loop while c > 30.0
                c--
                calculate fahreneit temp
                format c and =temp "00.00"
                add to message
                goto loop
                print message
                
Printed
      Output:   see printed out put
*/


import java.text.*;

public class TempConvertor {
   public static void main (String args[]) {
   double c = 40.0;
   final String SP5 = "     ";
   String message = "Cels Temp."+SP5+"Fahr Temp.\n";

   NumberFormat numberForm = NumberFormat.getNumberInstance();
   DecimalFormat df = (DecimalFormat)numberForm;
   df.applyPattern("00.00");

   for(;c>30.0; message +=df.format(c)+SP5+SP5+SP5+SP5+df.format(celsToFahr(c))+ "\n", c--);
   Stnd.out(message);
   System.exit(0);
   }

   public static double celsToFahr(double x) {
   return ((9.0/5.0) * x + 32.0);
   }
}
