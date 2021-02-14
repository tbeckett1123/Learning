using System;
using System.Collections.Generic;
using System.Text;
using System.Collections;
using Example;


namespace SymbolTable
{
    /// <summary>
    /// Summary description for Class1.
    /// </summary>
    public class classSymbolTable
    {
        public Hashtable hashSymbolTable = new Hashtable();
        public int get(IDENTIFIER id)
        { return (int)hashSymbolTable[id.Lexeme]; }
        public void put(IDENTIFIER id, int val)
        { hashSymbolTable[id.Lexeme] = val; }
        public void insert(string strLexeme)
        { hashSymbolTable[strLexeme] = -1; }
        public bool contains(string strLexeme)
        { return hashSymbolTable.Contains(strLexeme); }
        public void Dump()
        {
            Console.WriteLine("\n\n\nSymbol Table");
            foreach (string strItem in hashSymbolTable.Keys)
                Console.WriteLine(strItem);
            return;
        }
    }
}
