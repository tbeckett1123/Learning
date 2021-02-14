# include <iostream.h>;
# include <fstream.h>;

extern int t;

void writeFile(char tOperand[2], char temp, int t)
	{
   ofstream fOut;
   fOut.open("OutPut.txt", ios::app);
   if(temp == 'T')
   	fOut<<tOperand[0]<<tOperand[1]<<" Temp"<<t<<endl;
	else
      fOut<<tOperand[0]<<tOperand[1]<<" "<<temp<<endl;
   fOut.close();
   }

void writeFile(char[], char, int);

void ld(char registr)
	{
   if(registr == 'T')
   	cout<<"LD Temp"<<(t-1)<<endl;
   else
	   cout<<"LD "<<registr<<endl;
   writeFile("LD", registr, (t-1));
   }

void st()
	{
   t++;
   cout<<"ST Temp"<<t<<endl;
   writeFile("ST", 'T', t);
   }

void ld(char), st();
char ad(char temp, char operand)
	{
   ld(temp);
   if(operand == 'T')
   	cout<<"AD Temp"<<t<<endl;
   else
	   cout<<"AD "<<operand<<endl;
	writeFile("AD", operand, t);
   st();
   return 'T';
   }
char ml(char temp, char operand)
	{
   ld(temp);
   if(operand == 'T')
   	cout<<"ML Temp"<<t<<endl;
   else
	   cout<<"ML "<<operand<<endl;
	writeFile("ML", operand, t);
   st();
   return 'T';
   }
char sb(char temp, char operand)
	{
   ld(temp);
   if(operand == 'T')
   	cout<<"SB Temp"<<t<<endl;
   else
	   cout<<"SB "<<operand<<endl;
	writeFile("SB", operand, t);
   st();
   return 'T';
   }
char dv(char temp, char operand)
	{
   ld(temp);
   if(operand == 'T')
   	cout<<"DV Temp"<<t<<endl;
   else
	   cout<<"DV "<<operand<<endl;
	writeFile("DV", operand, t);
   st();
   return 'T';
   }

