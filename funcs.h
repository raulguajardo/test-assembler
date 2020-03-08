#include <iostream>
#include <cstdlib>
#include <cctype>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

//funtion to searh the Opcode Table for Opcode
int searchOPTAB(string s)
{
  ofstream file;
  file.open ("Intermediate File.txt", ios::app);
  string OPTAB[25][2] = {{"ADD","18"},{"AND","58"},{"COMP","28"},{"DIV","24"},{"J","3C"},
			 {"JEQ","30"},{"JGT","34"},{"JLT","38"},{"JSUB","48"},{"LDA","00"},
			 {"LDCH","50"},{"LDL","08"},{"LDX","04"},{"MUL","20"},{"OR","44"},
			 {"RD","D8"},{"RSUB","4C"},{"STA","0C"},{"STCH","54"},{"STL","14"},
			 {"STX","10"},{"SUB","1C"},{"TD","E0"},{"TIX","2C"},{"WD","DC"}};
  string opc;
  opc = s;
  int l, u, m, flag = 0;
  l = 0;
  u = 24;

  while(l <= u)
    {
      m = (l+u)/2;
      if(opc == OPTAB[m][0])
	{
	  file<<OPTAB[m][1]<<endl;
	  flag = 1;
	  return 0;
	}
      else
	{
	  if(OPTAB[m][0] < opc)
	    l = m + 1;
	  else
	    u = m - 1;
	}
    }
  if(flag == 0)
    return 3;
  file.close();
}

//hash function for Symbol table
int hash(string str, int table_size)
{
  int sum, x;
  for(int i = 0; i<6; i++)
    {
      x = str.at(0);
      sum += x;
    }   
  return sum % table_size;
  
}
