/*  Programmer:     Timothy Beckett 
 *  Class:          CSCI 4150       
 *  Instructor:     Dr. Cripps      
 *  Assignmt:       assign05        
 *  Variables:      Name            Type                Location                Purpose
 *                  args            string array        Program(main())         stores file name in element 0
 *                  doubleSumSqr    double              Grades (StdDeviation()) store the sum of the squares
 *                  doubleSqrSum    double              Grades (StdDeviation()) store the square of the sums
 *                  FileStream      StreamReader        Program(ReadData())     stores the file stream
 *                  grdScores       Grades              Program(Program)        stores scores and handles stats
 *                  i               int                 Grades (Lowest())       store the low score
 *                                                      Grades (Highest())      store the high score
 *                  intArrGrades    int array           Grades (Grades)         store the scores
 *                  intBar          int                 Grades (BarGraph())     Counter for printing bars
 *                  intBuffer       int                 Program(ReadData())     stores the parsed (string to int) score
 *                  intCnt          int                 Grades (NumberOf())     store the number of score
 *                                                      Program(ReadData())     used to delimit line dump from reading data
 *                  intGrd          int                 Grades (NubmerOf())     itorator for intArrGrades
 *                  intI            int                 Grades (Constructor)    itorator for intArrGrades
 *                  intIndex        int                 Grades (StdDeviation()) itorator for intArrGrades
 *                  intItr          int                 Grades (BarGraph())     itorator for intArrGrades
 *                  retVal          double              Grades (StdDeviation()) store the standard deviation
 *                                  bool                Program(ReadData())     used to store success for reading data from file
 *                  strFileName     string              Program(ReadData())     stores the file name
 *                  strReadLine     string              Program(ReadData())     get data from FileStream
 *                  total           double              Grades (Average())      store the sum
 */

using System;
using System.Collections.Generic;
using System.Text;
using System.IO;
using grade;

namespace grade
{
    class Grades
    {
        public int[] intArrGrades;

        //Class constructor
        //intializes intArrGrades as an array of 101 ints
        //and intializes each element to zero
        public Grades()
        {
            intArrGrades = new int[101];

            for (int intI = 0; intI < intArrGrades.Length; intI++)
            {
                intArrGrades[intI] = 0;
            }
        }

        ~Grades()
        { }

        //returns the lowest grade
        public int Lowest()
        {
            int i = 0;

            for (; intArrGrades[i] == 0 && i < 100; i++);

            return i;
        }

        //returns the highest grade
        public int Highest()
        {
            int i = 100;

            for (; intArrGrades[i] == 0 && i > 0; i--);

            return i;
        }

        //returns the standard deviation
        public double StdDeviation()
        {
            double doubleSumSqr = 0, doubleSqrSum = 0;

            //tallies the sum of the squares
            for(int intIndex = 0; intIndex < 101; intIndex++)
            { 
                    doubleSumSqr += intIndex*intIndex*intArrGrades[intIndex];
            }
            
            //tallies the square of the sum
            for (int intIndex = 0; intIndex < 101; intIndex++)
            {
                    doubleSqrSum += intArrGrades[intIndex]*intIndex;
            }

            doubleSqrSum *= doubleSqrSum;
            //end square of the sum

            double retVal = 0.0;

            try
            {
                //find the standard deviation
                retVal = Math.Sqrt(((NumberOf() * doubleSumSqr - doubleSqrSum) / (double)(NumberOf() * (NumberOf() - 1))));
            }
            catch(DivideByZeroException d)
            {
                //-1 is the default error message
                retVal = -1.0;
            }

            return retVal;
         
        }

        //returns the average score
        public double Average()
        {
            double total = 0.0;

            //find the sum of all the grades
            for (int intItr = 0; intItr < 101; intItr++)
            {
                total += (double)(intItr * intArrGrades[intItr]);
            }

            try
            {
                //return the averave score   
                return total / (double)NumberOf();
            }
            catch(DivideByZeroException d)
            {
                return (double)-1.0;
            }
        }

        //return the total number of grades
        public int NumberOf()
        { 
            int intCnt = 0;
            
            foreach(int intGrd in intArrGrades)
            {
            
                intCnt += intGrd;
            }
            
            return intCnt;
        }

        //produces a bar graph of the grades
        public void BarGraph()
        {
            Console.Write("\n");
            for(int intItr = Highest(); intItr >= Lowest(); intItr--)
            {
                Console.Write("{0,3} ", intItr);               

                for (int intBar = 0; intBar < intArrGrades[intItr]; intBar++)
                    Console.Write("%");

                Console.Write("\n");
            }
        }

    }
}



namespace assign05
{
    class Program
    {
        static Grades grdScores = new Grades();

        public static void Main(string[] args)
        {
            if (ReadData(args[0]))
            {
                Console.Write("\n");
                grdScores.BarGraph();
                Console.Write("\nThe lowest score is " + grdScores.Lowest() + "\n");
                Console.Write("The highest score is " + grdScores.Highest() + "\n");
                Console.Write("The average score is {0:F1}\n", grdScores.Average());
                Console.Write("The standard deviation is {0:F}\n", grdScores.StdDeviation());
                Console.Write("The number of scores is " + grdScores.NumberOf() + "\n");
            }
            else
                Console.Write("There were no grades to calculate.\n");

          
        } 

        static bool ReadData(string strFilename)
        {
 
            StreamReader FileStream;
            
            try //try to open the file
            {
                FileStream = new StreamReader(strFilename);
            }
            catch (FileNotFoundException exc)
            {
                Console.WriteLine(exc.Message + "\nInput File Not Found");
                return false;
            }

            string strReadLine;

            strReadLine = FileStream.ReadLine(); //read intial value

            int intBuffer = -2, intCnt = 0;
            bool retValue = false;

            
            while (strReadLine != null)
            {

                try //Convert from string to Int
                {
                    intBuffer = Int32.Parse(strReadLine);

                
                }
                catch (FormatException e)//set index out of range
                {
                    intBuffer = -2;
                }

                try //try to increament the score
                {
                    grdScores.intArrGrades[intBuffer]++;

                    intCnt++;
                    
                    Console.Write("{0,4}",strReadLine); //write grade to console

                    if (intCnt == 10)
                    {
                        Console.Write("\n");
                        intCnt = 0;
                    }
                }
                catch(IndexOutOfRangeException i)
                {
                    //do nothing
                }

           
                strReadLine = FileStream.ReadLine();

                retValue = true;    
            }    
            
            FileStream.Close();

            return retValue;
        }
    }
}
