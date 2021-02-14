# include <iostream.h>

struct leaf;

typedef leaf* leafPtr;
typedef int treeType;

struct leaf
	{
   treeType data;
   leafPtr left;
   leafPtr right;
   };

class Btree
	{
   private: leafPtr home, locPtr, parent, left;
   			bool search(treeType);
            void shift(), inOrder(leafPtr), postOrder(leafPtr);
            void clr(leafPtr);
   public:	Btree();
   			~Btree();
   			void insert(treeType), del(treeType), clear(), traverse();
   };
