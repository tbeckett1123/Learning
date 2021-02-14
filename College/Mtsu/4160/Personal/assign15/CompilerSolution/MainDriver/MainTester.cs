using System;
using System.Collections.Generic;
using System.Text;
using System.IO;
using Tools;
using Example;
using SymbolTable;


namespace assign15
{


    namespace MainDriver
    {
        public class MainTester
        {
            public static classSymbolTable symTable = new classSymbolTable();
            public static void Main(string[] args)
            {
                // we need an object, otherwise we won't be able
                // to refer back to it when we are in the lexer.
                new MainTester().parse(args[0]);
            }
            void parse(string s)
            {
                Lexer lexer = new tokens();
                lexer.Start(new StreamReader(s));
                TOKEN mytoken;
                try
                {
                    while ((mytoken = lexer.Next()) != null)
                    {
                        //(mytoken.Pos);
                        Console.WriteLine("{0,-20}, {1,-20}, {2,-20}, {3,-20}", 
                            mytoken.Pos,
                            mytoken.yyname,
                            mytoken.yytext,
                            (mytoken.yylval == null) ? "No Value" : mytoken.yylval);
                    }
                }
                catch
                {
                    Console.WriteLine("A regural expresion error has occured.\nShutting down the lexer");
                }
            }
        }
    }

}
