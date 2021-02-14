/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *  *
 *Program Name:	intbst.exe                                                  *
 *	 Programmer:	Tim Beckett                                                 *
 *			 Date:	5-2-03                                                      *
 *		Language:	Borland C++                                                 *
 *	  Flowchart:	n/a                                                         *
 *		Function:	this program reads data from a file preforms collects the   *
 *						data and then preforms the nessary opperations              *
 *		  Inputs:	char action code and int value                              *
 *		 Outputs:	traversal of tree inorder and postorder                     *
 * Other                                                                      *
 *	  Programs                                                                 *
 *   	 	 Used:	n/a                                                         *
 *Data                                                                        *
 *Restrictions:	file must contain a char a pace and a int                   *
 * 	  Method:	read action code from the file                              *
 *						read int from file if nessary                               *
 *                preform requested operation                                 *
 * 	Printed                                                                 *
 * 	  Output:	program is in the share file under data structers becketT   *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *  */

# include <ctype.h>
# include <fstream.h>
# include "intbst.h"
# include <stdlib.h>
// * the main function reads a char action command and then data if nessary  *
// * from a file and then it preforms the requested action                   *
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
void main()
	{
   Btree tree;
   char command;
   int data;
   bool flag = true;

	ifstream fIn;
   fIn.open("binary.txt", ios::nocreate);
   if(fIn.fail())
   	cout<<"* * * file error: could not find binary.txt * * *\n";
   else
   	{
      while(!fIn.eof() && flag == true)
      	{
			fIn>>command;
			command = tolower(command);
         switch(command)
         	{
            case 'i': fIn>>data; tree.insert(data); break;
            case 'd': fIn>>data; tree.del(data); break;
            case 't': tree.traverse(); break;
            case 'c': tree.clear(); break;
            default: cout<<"Quit\n"; flag = false;
            }
         }
      fIn.close();
      }
   system("PAUSE");
   }