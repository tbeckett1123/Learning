/* Programmer:          Timothy Beckett (Coder) */
using System;
using System.Collections.Generic;
using System.Text;
using System.IO;
using SymbolTable;


namespace symbolexample
{
    class Program
    {
        static classSymbolTable objSymbolTable = new classSymbolTable();

        static void Main(string[] args)
        {
            try
            {
                DebugSymbolTable(args[0]);
            }
            catch (IndexOutOfRangeException exceptionArgsIsEmpty)
            {
                Console.Write(exceptionArgsIsEmpty.ToString());
            }

            objSymbolTable.Dump();
                        
        }
        
        /* Variable             Type            Purpose
         * boolChoose           bool            used in the switch under case P
         *                                      used to determine which put method to choose
         * boolPF               bool            used in the switch under case P
         *                                      It determines the success or failure ot the put method
         * charArray            char[]          It used in several places to as the value of the split operatoin of strings
         * FileStream           StreamReader    for reading data from the file
         * idEntry              IDENTIFIER      Used in the switch under case I
         *                                      It stores the Lexeme to be stored in the hash table
         * intValue             int             used in the switch under case G
         *                                      it is used to store the index number of an array that is to be retreived
         * strArray             string[]        it is used through out the method to store substrings derived from a split
         *                                      operation.
         * strEntry             string          it is used through out the method to store the hash key of interest
         * strRetVal            string          it is used in the switch under case G
         *                                      it is used to store the returned value
         * strScope             string          it id used through out the switch statement to store the scope of interest
         * strToken             string          it is used in the switch under case P
         *                                      it store the token to be put into the desired IDENTIFIER
         * strValue             string          it is used in the switch under case P
         *                                      it stores the value to be put into the desired IDENTIFIER
         */
        static void DebugSymbolTable(string strFilename)
        {
            
            StreamReader FileStream; //used for reading the file
            string strEntry, //used for querries of the table
                   strScope, //used for keep track of scope
                   strRetVal = "NOT_FOUND"; //used to catch the return value of get operation
            string[] strArray = new string[1]; //used for string splitting
            char[] charArray = new char[1]; //used for string splitting
            int intValue = 0; //used for store value for get operation
            IDENTIFIER idEntry = new IDENTIFIER();  //used for inserting item to table
            string strToken = "", //used in the put operation
                   strValue = ""; //used in the put operation
            bool boolChoose = false, //used in the put operation to choose put method
                 boolPF = false; //used in the put operation to determine sucess or failure of put method

            charArray[0] = ' '; //space delimited strings

            try
            {
                FileStream = new StreamReader(strFilename);
            }
            catch (FileNotFoundException exceptionFileNotFound)
            {
                Console.WriteLine(exceptionFileNotFound.Message + "\nInput File Not Found");
                return;
            }

            string strReadLine;

            strReadLine = FileStream.ReadLine();

                     
            while (strReadLine != null)
            {
                Console.Write("\n" + strReadLine + "\n");

                //determine action to be preformed
                switch (strReadLine[0])
                {
                    case 'B':
                        //begin a scope
                        objSymbolTable.scopeTracker.Begin(strReadLine.Substring(2, strReadLine.Length-2));
                        
                        break; //end of case 'B'
                    
                    case 'C':
                        //check current scope for desired entry
                        //it must be provided with a scope as stated in class
                        strEntry = objSymbolTable.hashKey(strReadLine);



                        if(objSymbolTable.contains(strEntry))
                            Console.Write("Found entry " + strEntry + "\n");
                        else
                            Console.Write("Did not find entry " + strEntry +"\n");
                         
                        break; //end of case 'C'
                    
                    case 'D':
                        //dump the hash table to the screen
                        objSymbolTable.Dump();
            
                        break;
                    
                    case 'E': 
                        //end the scope
                        objSymbolTable.scopeTracker.End();
                        
                        break; //end of case 'E'
                    
                    case 'G':

                        //get the value from the hash table
                        
                        strEntry = objSymbolTable.hashKey(strReadLine);  //get hash table key

                        //determine if there is a given value in the string

                        strArray = strReadLine.Split(charArray);

                        bool looper = true;

                        if (strArray.Length > 3) //check for value
                        {
                            boolChoose = true;

                            if(strArray.Length > 8) //get value
                            { intValue = Int32.Parse(strArray[8]); }
                            else if (strArray.Length > 6 && strArray[5] == "V")
                            { intValue = Int32.Parse(strArray[6]); }
                            else if (strArray[3] == "V")
                            { intValue = Int32.Parse(strArray[4]); }
                            else
                            { boolChoose = false; }

                            //strRetVal = objSymbolTable.get(strEntry, intValue);

                            strScope = objSymbolTable.scopeTracker.Current();

                            

                            while (looper && strScope != objSymbolTable.scopeTracker.NO_SCOPE)
                            {
                                try
                                {
                                    looper = false;

                                    if (boolChoose)
                                        strRetVal = objSymbolTable.get(strEntry, intValue);
                                    else
                                        strRetVal = objSymbolTable.get(strEntry);
                                }
                                //if the search fails to find the item in the table
                                //then search the parent scopes of the current scope
                                catch (IndexOutOfRangeException)
                                {
                                    looper = true;

                                    strScope = objSymbolTable.scopeTracker.Parent(strScope);

                                    strEntry = objSymbolTable.hashKey(strReadLine, strScope); //rehash


                                }

                            }
                        }
                        else // no scope  or no value provided
                        {
                            //strRetVal = objSymbolTable.get(strEntry);

                            strScope = objSymbolTable.scopeTracker.Current();

                            while (looper && strScope != objSymbolTable.scopeTracker.NO_SCOPE)
                            {
                                //if the search fails to find the item in the table
                                //then search the parent scopes of the current scope
                                try
                                {
                                    looper = false;                                   

                                    strRetVal = objSymbolTable.get(strEntry);
                                }
                                catch (IndexOutOfRangeException)
                                {
                                    looper = true;
                                    strEntry = objSymbolTable.hashKey(strReadLine, strScope); //rehash
                                    strScope = objSymbolTable.scopeTracker.Parent(strScope);
                                }
                            }
                        }
                                      
                        Console.Write("The returned value is " + strRetVal + "\n");

                        strRetVal = "NOT_FOUND";

                        break;  //end of case 'G'
                        
                    case 'I':
                        //insert new item to the table
                        strEntry = objSymbolTable.hashKey(strReadLine); //get hash table key

                        idEntry = new IDENTIFIER(strReadLine); //set up lexeme

                        if (!objSymbolTable.contains(strEntry)) //check if lexeme is in table
                        {
                            objSymbolTable.Insert(idEntry, strEntry); //if unique insert
                            Console.Write("Added to table: " + idEntry.Scope + " "
                                                             + idEntry.Lexeme + " "
                                                             + idEntry.Token + " "
                                                             + idEntry.Value + "\n");
                        }
                        else
                            Console.Write("The Lexeme "+ strEntry +" is already in the table\n");

                        break; //end of case 'I'
                    
                    case 'P':
                        // change the value of an table item

                        strArray = strReadLine.Split(charArray); //split the sub strings

                        strEntry = objSymbolTable.hashKey(strReadLine); //get first hash key

                        strScope = objSymbolTable.scopeTracker.Current(); //get the current scope

                        if (strArray.Length > 8)
                        {// provided scope
                            if (strArray.Length > 9)
                            {// two values
                                strToken = strArray[6];
                                intValue = Int32.Parse(strArray[8]);
                                strValue = strArray[9];
                                boolChoose = false;
                            }
                            else
                            {// one value
                                boolChoose = true;
                                strValue = strArray[8];
                                strToken = strArray[6];
                            }                            
                        }
                        //no scope provided for the following cases
                        else if (strArray.Length > 6)
                        {// Provided token and value

                            if (strArray.Length > 7)
                            {// two values
                                strToken = strArray[4];
                                intValue = Int32.Parse(strArray[6]);
                                strValue = strArray[7];
                                boolChoose = false;
                            }
                            else
                            {// one value
                                boolChoose = true;
                                strValue = strArray[6];
                                strToken = strArray[4];
                            }
                        }
                        else
                        {   
                            if (strArray[3] == "T")
                            { //provided a token change

                                boolChoose = false;
                                strValue = objSymbolTable.KEEP;
                                strToken = strArray[4];                                
                            }
                            else
                            { //provided a value change
                                if (strArray.Length > 5)
                                //two values provided
                                {
                                    intValue = Int32.Parse(strArray[4]);
                                    boolChoose = false;
                                    strToken = objSymbolTable.KEEP;
                                    strValue = strArray[5];
                                }
                                else
                                { // one value provided
                                    boolChoose = true;
                                    strValue = strArray[4];
                                    strToken = objSymbolTable.KEEP;
                                }
                            }
                        }

                        boolPF = false;

                        if(boolChoose)
                        {//one value put
                            
                            while (!boolPF && strScope != objSymbolTable.scopeTracker.NO_SCOPE)
                            {
                                try
                                {
                                    boolPF = objSymbolTable.put(strEntry, strToken, strValue);
                                }
                                catch (IndexOutOfRangeException)
                                { 
                                
                                }
                                
                                strScope = objSymbolTable.scopeTracker.Parent(strScope);

                                strEntry = objSymbolTable.hashKey(strReadLine, strScope);
                            }
                        }
                        else
                        {//two value put
                             while (!boolPF && strScope != objSymbolTable.scopeTracker.NO_SCOPE)
                             {
                                 try
                                 {
                                     boolPF = objSymbolTable.put(strEntry, strToken, intValue, strValue);
                                 }
                                 catch (IndexOutOfRangeException)
                                 { 
                                 
                                 }
                                 
                                 strScope = objSymbolTable.scopeTracker.Parent(strScope);

                                 strEntry = objSymbolTable.hashKey(strReadLine, strScope);
                             }
                        }

                        if (boolPF)
                            Console.Write("Operation Sucessful\n");
                        else
                            Console.Write("Operation Failed\n");

                        break; //end of case 'P'
                    
                };

               strReadLine = FileStream.ReadLine(); //get next command from the file
                
            }
            FileStream.Close();
        }
    }

}
