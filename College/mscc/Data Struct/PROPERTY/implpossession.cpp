#include "possession.h"
//overloading
ostream& operator<<(ostream& out, String40 s)
	{
   for(int x = 0; x < strlen(s); x++)
   	out<<*(s+x);
   return out;
   }

ostream& operator<<(ostream& out, DateType date)
	{
   out<<date.mo<<"-"<<date.day<<"-"<<date.yr;
   return out;
   }

ostream& operator<<(ostream& out, PropertyType ptype)
	{
   switch(ptype)
   	{
      case home: out<<"home"; break;
		case automobile: out<<"automobile"; break;
      case appliance: out<<"appliance"; break;
      case furniture: out<<"furniture"; break;
      case other: out<<"out"; break;
      };
   return out;
   }

ostream& operator<<(ostream& out, HouseType htype)
	{
   switch(htype)
   	{
      case ranch: out<<"ranch"; break;
      case twoStory: out<<"2Story"; break;
      case split: out<<"split"; break;
      case condo: out<<"condo"; break;
      };
   return out;
   }

ostream& operator<<(ostream& out, ColorType ctype)
	{
   switch(ctype)
   	{
      case red: out<<"red"; break;
      case orange: out<<"orange"; break;
      case yellow: out<<"yellow"; break;
      case green: out<<"green"; break;
      case blue: out<<"blue"; break;
      case brown: out<<"brown"; break;
      case purple: out<<"purple"; break;
      case white: out<<"white"; break;
      case black: out<<"black"; break;
      };
   return out;
   }

ostream& operator<<(ostream& out, CarType carT)
	{
   switch(carT)
   	{
      case sedan: out<<"sedan"; break;
      case staWagon: out<<"staWagon"; break;
      case van: out<<"van"; break;
      case sports: out<<"sports"; break;
      case offRoad: out<<"offRoad"; break;
      case pickup: out<<"pickup"; break;
      };
   return out;
   }

ostream& operator<<(ostream& out, ApplianceType aType)
	{
   switch(aType)
   	{
      case range: out<<"range"; break;
      case dishwasher: out<<"dishwasher"; break;
      case washer: out<<"washer"; break;
      case dryer: out<<"dryer"; break;
      };
   return out;
   }

ostream& operator<<(ostream& out, FurnitureType fType)
	{
   switch(fType)
   	{
      case sofa: out<<"sofa"; break;
      case table: out<<"table"; break;
      case chair: out<<"table"; break;
      case bed: out<<"bed"; break;
      case desk: out<<"desk"; break;
      case cabinet: out<<"cabinet"; break;
      };
   return out;
   }

ostream& operator<<(ostream& out, PropertyInfoType prop)
	{
	out<<"purchase date: "<<prop.purchaseDate<<endl
     	<<"hundredsVal: "<<prop.hundredsVal<<endl
      <<"article: "<<prop.article<<endl;
   switch(prop.article)
   	{
      case home:			out<<"House Style: "<<prop.house.style<<endl
      							<<"Area: "<<prop.house.sqFeet<<endl
            	         	<<"Date Built: "<<prop.house.dateBuilt;
      						break;
      case automobile:	out<<"Auto Style: "<<prop.car.style<<endl
      							<<"Color: "<<prop.car.color;
      						break;
      case appliance:	out<<"Appliance Type: "<<prop.appli.kind<<endl
      							<<"Color: "<<prop.appli.color;
                        break;
      case furniture:	out<<"Furniture Type: "<<prop.furn.kind; break;
      case other:			out<<"Description: "<<prop.oth.descrip; break;
      };
   return out;
   }
// end overloading
// start class Property functions
Property::Property()
	{
    ifstream fIn;
    fIn.open("Property.dat", ios::binary);
    for(count = 0; !fIn.eof() ; count++)
    	fIn.read((unsigned char *) &majorPossession, sizeof majorPossession);
    fIn.close();
	}

void Property::sort()
	{
   int sum(int, int, int);
   PropertyInfoType swap;
   for (int i = 0; i < count; i++)
   	{
      for(int j = i+1; j < count; j++)
      	{
         if(sum(majorPossession[i].purchaseDate.mo, majorPossession[i].purchaseDate.day, majorPossession[i].purchaseDate.yr)<sum(majorPossession[j].purchaseDate.mo, majorPossession[j].purchaseDate.day, majorPossession[j].purchaseDate.yr))
         	{
				swap = majorPossession[i];
            majorPossession[i] = majorPossession[j];
            majorPossession[j] = swap;
            }
         }
      }
   }

int sum(int x, int y, int z)
	{
   return ((x*100)+y+(z*1000));
   }

void Property::setFavorite(int x = 0)
	{
   favoritePossession = majorPossession[x];
   }

void Property::writeFile()
	{
   ofstream fOut;
   fOut.open("Property.txt");
   for(int x = 0; x <= count; x++)
   	fOut<<"Property:"<<endl<<majorPossession[x]<<endl;
   fOut<<"Favorite Property:"<<endl;
   fOut<<favoritePossession<<endl;
   fOut.close();
   }
//end class Property functions
