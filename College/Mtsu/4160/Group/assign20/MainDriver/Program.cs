using System;
using System.IO;
using Tools;
using Template;
using SymbolTable;

namespace MainDriver
{
    public class MainTester
    {
        public static classSymbolTable symTable = new classSymbolTable();
        public static void Main(string[] args)
        {
            // we need an object, otherwise we won't be able
            // to refer back to it when we are in the lexer.

            new MainTester().Parse(args[0]);
        }

        void Parse(string s)
        {

            Parser parserMyParser = new syntax();
            //parserMyParser.m_symbols.EOFSymbol.
            parserMyParser.Parse(new StreamReader(s));
            symTable.Dump();

        }

/*
            void Parse(string s)
            {
                Lexer lexer = new tokens();
                lexer.Start(new StreamReader(s));
                TOKEN mytoken;
                while ((mytoken = lexer.Next()) != null)
                {
                    Console.WriteLine("{0} {1} {2}", mytoken.yyname, mytoken.yytext, (mytoken.yylval == null) ? "" : mytoken.yylval);
                }
                MainTester.symTable.Dump();
            }
*/
    }
}