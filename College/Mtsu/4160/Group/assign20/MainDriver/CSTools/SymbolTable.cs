using System;
using System.Collections;
using System.Text;

namespace SymbolTable
{
    /**************************************************************************************
        This class will encompass our symbol table functionality.
     **************************************************************************************/
    public class classSymbolTable
    {
        private Hashtable hashSymbolTable = new Hashtable();// Internal hash table of symbols
        private Stack stackScopes = new Stack(); // Internal stack of current scopes

        /*************** classSymbolTable::MangleName() *****************************************************
            This method is inteded to create a unique key for the internal hash table.
            This key is simply the concatenation of the scope, a colon, and the lexeme.

            Routine Written By:    James Arnott, Luke Eitneier
            Start Alpha Code Date: 9/14/06 16:00
            End Alpha Code Date:   9/14/06 16:01
            Routine Tested By:     Emal Sakwall
            Routine Documented By: Luke Eitneier
			
            strScope:  The scope to use a part of the mangled name. If the scope is null, the scope
                       currently on the stack will be used.
            strLexeme: The lexeme to use a part of the mangled name.
        *****************************************************************************************************/
        private string MangleName(string strScope, string strLexeme)
        {
            // If the scope is null, prepend the current scope name, otherwise
            // use the provided scope name.
            return ((strScope == null ? stackScopes.Peek() : strScope) + ":" + strLexeme);
        }

        /*************** classSymbolTable::classSymbolTable() ***********************************************
         * Constuctor added by Rodney Kincaid on 10/10/06 18:30
         * Initializes symbol table with a default scope named "InitialScope"
         ***************************************************************************************************/
        public classSymbolTable()
        {
            BeginScope("default");

        }

        /*************** classSymbolTable::BeginScope() *****************************************************
            This method is intended to notify the symbol table of the beginning of a new scope.
            Upon notification, the symbol table will add the specified scope to the internal scope stack.

            Routine Written By:    James Arnott
            Start Alpha Code Date: 9/14/06 16:00
            End Alpha Code Date:   9/21/06 16:00
            Routine Tested By:     Emal Sakwall
            Routine Documented By: Luke Eitneier
			
            strScope: Name of the scope/namespace that is beginning.
        *****************************************************************************************************/
        public void BeginScope(string strScope)
        {
            stackScopes.Push(strScope);
        }
        /*************** classSymbolTable::EndScope() *****************************************************
            This method is intended to notify the symbol table of the end of the current scope.
            Upon notification, the symbol table will remove the current scope and make the previous
            scope the current scope.

            Routine Written By:    James Arnott
            Start Alpha Code Date: 9/14/06 16:00
            End Alpha Code Date:   9/21/06 16:00
            Routine Tested By:     Emal Sakwall
            Routine Documented By: Luke Eitneier
        *****************************************************************************************************/
        public void EndScope()
        {
            stackScopes.Pop();
        }
        /*************** classSymbolTable::Insert() *********************************************************
            This method will create a new identifier based on the scope, lexeme, type, and value passed in.
            Initially, the symbol table is checked to make sure the identifier does not already exist.
            If the scope is not specified, the current scope will be used as the identifing scope of the
            new identifier.

            Routine Written By:    James Arnott
            Start Alpha Code Date: 9/14/06 16:00
            End Alpha Code Date:   9/21/06 16:00
            Routine Tested By:     Emal Sakwall
            Routine Documented By: Luke Eitneier
			
            strScope:  Scope that the identifier should be identified under (can be null)
            strLexeme: Lexeme that the identifier is being created for
            strType:   The type of the symbol
            objValue:  Initial value to assign to the identifier (can be null)
        *****************************************************************************************************/
        public void Insert(string strScope, string strLexeme, string strType, object objValue)
        {
            if (!Contains(strScope, strLexeme))
                hashSymbolTable[MangleName(strScope, strLexeme)] = new Bucket((strScope == null ? (string)stackScopes.Peek() : strScope), strLexeme, strType, objValue);
            else
                throw new exceptionIdentifierAlreadyExists();
        }
        /*************** classSymbolTable::Put() ************************************************************
            This method will change the type and value of an identifier. That is, if the parameter strType
            is null, the internally maintained string representation of the type will remain unchanged;
            otherwise, it will be assigned strType.
            This particular implementation, with the absence of index specification, will replace the
            value of the internally maintianed value with objValue.

            Routine Written By:    James Arnott & Luke Eitneier
            Start Alpha Code Date: 9/14/06 16:00
            End Alpha Code Date:   9/21/06 16:00
            Routine Tested By:     Emal Sakwall
            Routine Documented By: Luke Eitneier
			
            strScope:  Scope that the identifier belongs to (can be null)
            strLexeme: Lexeme that identifies the identifier to change
            strType:   The type of the symbol (can be null)
            objValue:  Value to assign to the identifier (can be null)
        *****************************************************************************************************/
        public void Put(string strScope, string strLexeme, string strType, object objValue)
        {
            Bucket idSymbol = (Bucket)Get(strScope, strLexeme);//Symbol whose value is to change

            if (idSymbol != null)
            {
                if (strType != null)
                    idSymbol.Type = strType;

                idSymbol.Value = objValue;
            }
        }
        /*************** classSymbolTable::Put() ************************************************************
            This method will change the type and value of an identifier. That is, if the parameter strType
            is null, the internally maintained string representation of the type will remain unchanged;
            otherwise, it will be assigned strType.
            This particular implementation, with the specification of an index, will replace the
            value of the element of the object array.

            Routine Written By:    James Arnott & Luke Eitneier
            Start Alpha Code Date: 9/14/06 16:00
            End Alpha Code Date:   9/21/06 16:00
            Routine Tested By:     Emal Sakwall
            Routine Documented By: Luke Eitneier
			
            strScope:  Scope that the identifier belongs to (can be null)
            strLexeme: Lexeme that identifies the identifier to change
            strType:   The type of the symbol (can be null)
            objValue:  Value to assign to the identifier (can be null)
            intIndex:  Element index in the array whose value should be changed to objValue
        *****************************************************************************************************/
        public void Put(string strScope, string strLexeme, string strType, object objValue, int intIndex)
        {
            Bucket idSymbol = (Bucket)Get(strScope, strLexeme);//Symbol whose value is to change

            // Set the type is provided
            if (strType != null)
                idSymbol.Type = strType;

            if (idSymbol.Value != null)
            {
                if (idSymbol.Value.GetType().IsArray)
                {
                    if (intIndex >= 0 && intIndex < ((Array)idSymbol.Value).Length)
                        ((Array)idSymbol.Value).SetValue(objValue, intIndex);
                    else
                        throw new exceptionIndexOutOfRange();
                }
                else
                    throw new exceptionNotAnArray();
            }
            else
                throw new exceptionNullObjectReference();
        }
        /*************** classSymbolTable::Contains() *******************************************************
            This method will assertain whether or not the identifier identified by strScope and strLexeme
            currently exists within the symbol table. If strScope is null, the stack of current scopes
            is searched in order to find the identifier.
		
            Routine Written By:    James Arnott & Luke Eitneier
            Start Alpha Code Date: 9/14/06 16:00
            End Alpha Code Date:   9/21/06 16:00
            Routine Tested By:     Emal Sakwall
            Routine Documented By: Luke Eitneier
			
            strScope:  Scope that the identifier belongs to (can be null)
            strLexeme: Lexeme that identifies the identifier to find
        *****************************************************************************************************/
        public bool Contains(string strScope, string strLexeme)
        {
            bool bContains = false;//Truth value returned to driver

            //Because we don't what the exception to pass this point,
            //we will absorb it.
            try
            {
                bContains = (Get(strScope, strLexeme) != null);
            }
            catch (SymbolTableException) { }

            return (bContains);
        }
        /*************** classSymbolTable::Get() *******************************************************
            This method will retreive the identifier specified by the scope and lexeme.
            If the scope is null, the internal stack of scopes is searched for the identifier identified
            by the lexeme.
            An exception is thrown if the identifier is not found.
            This method can be used by the driver of this class to discover the stored scope and type.
		
            Routine Written By:    James Arnott & Luke Eitneier
            Start Alpha Code Date: 9/14/06 16:00
            End Alpha Code Date:   9/21/06 16:00
            Routine Tested By:     Emal Sakwall
            Routine Documented By: Luke Eitneier
			
            strScope:  Scope that the identifier belongs to (can be null)
            strLexeme: Lexeme that identifies the identifier to find
        *****************************************************************************************************/
        public Bucket Get(string strScope, string strLexeme)
        {
            Bucket idTarget = null;//Target identifier to locate

            //If the scope is specified, then use it; otherwise, look down the stack
            //in all the scopes for the lexeme and get the first one found.
            if (strScope != null)
                idTarget = (Bucket)hashSymbolTable[MangleName(strScope, strLexeme)];
            else
            {
                foreach (object stackIterator in stackScopes)
                {
                    idTarget = (Bucket)hashSymbolTable[MangleName(stackIterator.ToString(), strLexeme)];
                    if (idTarget != null) break;
                }
            }
            if (idTarget == null)
                throw new exceptionUnknownIdentifier();

            return (idTarget);
        }
        /*************** classSymbolTable::GetValue() *******************************************************
            This method will retreive the value associated with an identifier.
            Notice, this method is the non-array implementation.
		
            Routine Written By:    James Arnott & Luke Eitneier
            Start Alpha Code Date: 9/14/06 16:00
            End Alpha Code Date:   9/21/06 16:00
            Routine Tested By:     Emal Sakwall
            Routine Documented By: Luke Eitneier
			
            strScope:  Scope that the identifier belongs to (can be null)
            strLexeme: Lexeme that identifies the identifier whose value is to be located
        *****************************************************************************************************/
        public object GetValue(string strScope, string strLexeme)
        {
            return (Get(strScope, strLexeme).Value);
        }
        /*************** classSymbolTable::GetValue() *******************************************************
            This method will retreive the value contained at a particular index within an array.
            If the index is out of range, an exception is thrown.
            If the internal object is not an array, an exception is thrown.
					
            Routine Written By:    James Arnott & Luke Eitneier
            Start Alpha Code Date: 9/14/06 16:00
            End Alpha Code Date:   9/21/06 16:00
            Routine Tested By:     Emal Sakwall
            Routine Documented By: Luke Eitneier
			
            strScope:  Scope that the identifier belongs to (can be null)
            strLexeme: Lexeme that identifies the identifier whose value is to be located
            intIndex:  Index of the element of the array whose value is to be returned
        *****************************************************************************************************/
        public object GetValue(string strScope, string strLexeme, int intIndex)
        {
            Bucket idTarget = Get(strScope, strLexeme);//Target identifier to locate
            object objTarget = null;//Object value returned to driver

            if (idTarget.Value.GetType().IsArray)
            {
                if (intIndex >= 0 && intIndex < ((Array)idTarget.Value).Length)
                    objTarget = ((Array)idTarget.Value).GetValue(intIndex);
                else
                    throw new exceptionIndexOutOfRange();
            }
            else
                throw new exceptionNotAnArray();

            return (objTarget);
        }
        /*************** classSymbolTable::Dump() *******************************************************
            This method will print a table containg the key, scope, lexeme, type, and value of all
            the identifiers currently loaded in the symbol table.
					
            Routine Written By:    James Arnott & Luke Eitneier
            Start Alpha Code Date: 9/14/06 16:00
            End Alpha Code Date:   9/21/06 16:00
            Routine Tested By:     Emal Sakwall
            Routine Documented By: Luke Eitneier
        *****************************************************************************************************/
        public void Dump()
        {
            Bucket idSymbol;//Current identifier being printed
            string strFormat = "{0,-21} {1, -10} {2, -10} {3, -10} ";//User for formatting

            Console.WriteLine("\n");
            Console.WriteLine(strFormat + "{4, -32}", "Key", "Scope", "Lexeme", "Type", "Value(s)");

            //Iterate through each key of the hash table, get the identifier identified
            // by the key and print out the information.
            foreach (string strKey in hashSymbolTable.Keys)
            {
                idSymbol = (Bucket)hashSymbolTable[strKey];
                Console.Write(strFormat, strKey,
                    idSymbol.Scope == null ? "null" : idSymbol.Scope,
                    idSymbol.Lexeme == null ? "null" : idSymbol.Lexeme,
                    idSymbol.Type == null ? "null" : idSymbol.Type);

                if (idSymbol.Value != null)
                {
                    if (idSymbol.Value.GetType().IsArray)
                    {
                        foreach (object objObject in (Array)idSymbol.Value)
                            Console.Write((objObject == null ? "0" : objObject.ToString()) + " ");
                    }
                    else
                        Console.Write(idSymbol.Value.ToString());
                }
                else
                    Console.Write("null");

                Console.WriteLine("");
            }
        }
    }
    /**************************************************************************************
        This class represents a symbol/identifier that will be house in our symbol table's
        hash table.
     **************************************************************************************/
    public class Bucket
    {
        private string strScope; //Scope representing this identifier
        private string strLexeme;//Lexeme representing this identifier
        private string strType;  //Type representing this identifier
        private object objValue; //Value of the identifier

        /*************** Bucket::Bucket() ***********************************************************
            This is the intializing constructor for the Bucket class.
					
            Routine Written By:    James Arnott & Luke Eitneier
            Start Alpha Code Date: 9/14/06 16:00
            End Alpha Code Date:   9/21/06 16:00
            Routine Tested By:     Emal Sakwall
            Routine Documented By: Luke Eitneier
			
            strScope:  Scope of identifier
            strLexeme: lexeme
            strType:   Internal type if identifier
            objValue:  Value associated with identifier
        *****************************************************************************************************/
        public Bucket(string strScope, string strLexeme, string strType, object objValue)
        {
            Scope = strScope;
            Lexeme = strLexeme;
            Type = strType;
            Value = objValue;
        }
        /*************** Bucket::Bucket() ***********************************************************
            This is the default constructor for the Bucket class.
					
            Routine Written By:    James Arnott & Luke Eitneier
            Start Alpha Code Date: 9/14/06 16:00
            End Alpha Code Date:   9/21/06 16:00
            Routine Tested By:     Emal Sakwall
            Routine Documented By: Luke Eitneier
        *****************************************************************************************************/
        public Bucket()
        {
            Scope = "";
            Lexeme = "";
            Type = "";
            Value = null;
        }
        /*************** Bucket::Scope() ****************************************************************
            This is an accessor method for the internal scope.
					
            Routine Written By:    James Arnott & Luke Eitneier
            Start Alpha Code Date: 9/14/06 16:00
            End Alpha Code Date:   9/21/06 16:00
            Routine Tested By:     Emal Sakwall
            Routine Documented By: Luke Eitneier
        *****************************************************************************************************/
        public string Scope
        {
            get { return strScope; }
            set { strScope = value; }
        }
        /*************** Bucket::Lexeme() ***************************************************************
            This is an accessor method for the internal lexeme.
					
            Routine Written By:    James Arnott & Luke Eitneier
            Start Alpha Code Date: 9/14/06 16:00
            End Alpha Code Date:   9/21/06 16:00
            Routine Tested By:     Emal Sakwall
            Routine Documented By: Luke Eitneier
        *****************************************************************************************************/
        public string Lexeme
        {
            get { return strLexeme; }
            set { strLexeme = value; }
        }
        /*************** Bucket::Type() *****************************************************************
            This is an accessor method for the internal type.
					
            Routine Written By:    James Arnott & Luke Eitneier
            Start Alpha Code Date: 9/14/06 16:00
            End Alpha Code Date:   9/21/06 16:00
            Routine Tested By:     Emal Sakwall
            Routine Documented By: Luke Eitneier
        *****************************************************************************************************/
        public string Type
        {
            get { return strType; }
            set { strType = value; }
        }
        /*************** Bucket::Value() ****************************************************************
            This is an accessor method for the internal value.
					
            Routine Written By:    James Arnott & Luke Eitneier
            Start Alpha Code Date: 9/14/06 16:00
            End Alpha Code Date:   9/21/06 16:00
            Routine Tested By:     Emal Sakwall
            Routine Documented By: Luke Eitneier
        *****************************************************************************************************/
        public object Value
        {
            get { return objValue; }
            set { objValue = value; }
        }
    }
    public class SymbolTableException : System.ApplicationException
    {
        /*************** SymbolTableException::SymbolTableException() ***************************************
            This is the initializing constructor of SymbolTableException.
					
            Routine Written By:    Luke Eitneier
            Start Alpha Code Date: 9/14/06 16:00
            End Alpha Code Date:   9/21/06 16:00
            Routine Tested By:     Emal Sakwall
            Routine Documented By: Luke Eitneier
			
            strMessage: Internal message will be set to strMessage.
        *****************************************************************************************************/
        public SymbolTableException(string strMessage)
            : base(strMessage)
        {
        }
    }
    public class exceptionIndexOutOfRange : SymbolTableException
    {
        /*************** exceptionIndexOutOfRange::exceptionIndexOutOfRange() *******************************************
            This is the default constructor of exceptionIndexOutOfRange.
					
            Routine Written By:    Luke Eitneier
            Start Alpha Code Date: 9/14/06 16:00
            End Alpha Code Date:   9/21/06 16:00
            Routine Tested By:     Emal Sakwall
            Routine Documented By: Luke Eitneier
        *****************************************************************************************************/
        public exceptionIndexOutOfRange()
            : base("Index out of range")
        {
        }
    }
    public class exceptionNotAnArray : SymbolTableException
    {
        /*************** exceptionNotAnArray::exceptionNotAnArray() *****************************************************
            This is the default constructor of exceptionNotAnArray.
					
            Routine Written By:    Luke Eitneier
            Start Alpha Code Date: 9/14/06 16:00
            End Alpha Code Date:   9/21/06 16:00
            Routine Tested By:     Emal Sakwall
            Routine Documented By: Luke Eitneier
        *****************************************************************************************************/
        public exceptionNotAnArray()
            : base("Object not an array")
        {
        }
    }
    public class exceptionNullObjectReference : SymbolTableException
    {
        /*************** exceptionNullObjectReference::exceptionNullObjectReference() ***********************************
            This is the default constructor of exceptionNullObjectReference.
					
            Routine Written By:    Luke Eitneier
            Start Alpha Code Date: 9/14/06 16:00
            End Alpha Code Date:   9/21/06 16:00
            Routine Tested By:     Emal Sakwall
            Routine Documented By: Luke Eitneier
        *****************************************************************************************************/
        public exceptionNullObjectReference()
            : base("Object is null")
        {
        }
    }
    public class exceptionUnknownIdentifier : SymbolTableException
    {
        /*************** exceptionUnknownIdentifier::exceptionUnknownIdentifier() *****************************************
            This is the default constructor of exceptionUnknownIdentifier.
					
            Routine Written By:    Luke Eitneier
            Start Alpha Code Date: 9/14/06 16:00
            End Alpha Code Date:   9/21/06 16:00
            Routine Tested By:     Emal Sakwall
            Routine Documented By: Luke Eitneier
        *****************************************************************************************************/
        public exceptionUnknownIdentifier()
            : base("Unknown Identifier")
        {
        }
    }
    public class exceptionIdentifierAlreadyExists : SymbolTableException
    {
        /*************** exceptionIdentifierAlreadyExists::exceptionIdentifierAlreadyExists() ***************************
            This is the default constructor of exceptionIdentifierAlreadyExists.
					
            Routine Written By:    Luke Eitneier
            Start Alpha Code Date: 9/14/06 16:00
            End Alpha Code Date:   9/21/06 16:00
            Routine Tested By:     Emal Sakwall
            Routine Documented By: Luke Eitneier
        *****************************************************************************************************/
        public exceptionIdentifierAlreadyExists()
            : base("Identifier already exists")
        {
        }
    }
}
