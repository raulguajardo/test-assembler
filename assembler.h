#include <iostream>
#include <cstdlib>
#include <cctype>
#include <sstream>
#include <string>
#include <fstream>
#include <cstring>
#include "funcs.h"

using namespace std;

void pass1(string s)
{
  //variable declarations and opening files
  string line;
  ifstream afile;
  afile.open (s.c_str());
  ofstream file;
  file.open ("Intermediate File.txt", ios::app);
  int tsize = 29;
  int LOCCTR;
  int error = 0;
  string SYMTAB[503][2];
  
  

  if(afile.is_open())
    {
      //lbl to store LABEL, opc to store OPCODE, ope to store OPERAND
      string lbl, opc, ope;
      
      //will keep getting a line until it finds a line without a period
      do
	{
	  getline(afile,line);
	}while(ispunct(line.at(0)));
      
      //used to separate the line into lbl, opc, and ope
      istringstream iss(line);
      file<<line<<"\n"<<endl;
      iss>>lbl;
      iss>>opc;
      iss>>ope;
      
      //Starting address
      int SA;
      
      //to convert operand into hex
      stringstream convert (ope);
      
      //will set LOCCTR to the operand else set it to 0
      //and flag as error
      if(opc == "START")
	{
	  convert>> std::hex >> SA; 
	  LOCCTR = SA;
	}
      else
	{
	  LOCCTR = 0;
	  //error = to 1 when START isnt found in the program
	  error = 1;
	}

      
      //for all lines that are not the first one
      while (afile.good())
	{
	  getline (afile,line);
	  
	  if(line.empty())
	    break;
	  
	  istringstream iss(line);
	  
	  //will check if line is a comment  
	  if(ispunct(line.at(0)))
	    {
	      lbl = " ";
	      opc = " ";
	      ope = " ";	
	    }
	  else if(isspace(line.at(0)))
	    {
	      //for line without a label
	      file<<line<<endl;
	      iss>>opc;
	      if(opc == "RSUB")
		ope = " ";
	      else
		iss>>ope;
	      
	      //search OPTAB for OPCODE
	      error = searchOPTAB(opc);
	    
	      //to end the program if directive END is found
	      if(opc == "END")
		break;
	      //write in the parts needed for intermediate file
	      file<<ope<<endl;
	      file<<hex<<LOCCTR<<endl;
	      LOCCTR += 3;
	      
	      //so that if theres no error nothing will be inserted 
	      //into the intermediate file
	      if(error == 0)
		file<<" "<<endl;
	      else
		file<<error<<endl;
	    }
	  else
	    {
	      //for line with a label
	      file<<line<<endl;
	      iss>>lbl;
		
	      iss>>opc;
	      if(opc == "RSUB")
		ope = " ";
	      else	  
		iss>>ope;

	      //check the label and operands for errors
	      if(lbl.length() > 7)
		error = 4;
	      else if(isalpha(lbl.at(0) != 1))
		error = 5;
	      else if(ope.empty() & opc != "RSUB")
		error = 6;
	      

	      //writing to intermediate file
	      file<<ope<<endl;
	      file<<hex<<LOCCTR<<endl;
	 
	      //index coming from has function
	      int index;
	      index = hash(lbl, 503);
	      
	      //to prevent collisions
	      for(int f = 1; f<10; f++)
		{
		  if(SYMTAB[index^f%503][0].empty())
		    {
		      //to convert LOCCTR to hex
		      stringstream ss;
		      ss<<hex<<LOCCTR;
		      string result = ss.str();

		      //writing label and its location couter to the symtab
		      SYMTAB[index][0] = lbl;
		      SYMTAB[index][1] = result;
		      break;
		    }
		  else if(SYMTAB[index^f%503][0] == lbl)
		    {
		      //error if duplicate labels
		      error = 7;
		      break;
		    }
		}
	      

	      //for use with BYTE directive
	      stringstream convert (ope);
	      int ope1;
	      convert>> std::hex >> ope1; 

	      //statements are for the diretives
	      if(opc == "WORD")
		{
		  file<<"WORD"<<endl;
		  LOCCTR += 3;
		}
	      else if(opc == "RESB")
		{
		  file<<"RESB"<<endl;
		  LOCCTR += ope1;
		}
	      else if(opc == "RESW")
		{
		  file<<"RESW"<<endl;
		  LOCCTR += 3 * ope1;
		}
	      else if(opc == "BYTE")
		{
		  file<<"BYTE"<<endl;
		  LOCCTR += sizeof(ope1);
		}
	      else
		{
		  //check OPTAB for OPCODE
		  error = searchOPTAB(opc);
		  LOCCTR += 3;
		}

	      if(error == 0)
		file<<" "<<endl;
	      else
		file<<error<<endl;
	    }

	}
      //close the source file
      afile.close();
      int progsize = LOCCTR - SA;
      cout<<hex<<progsize<<endl; 
    }
  else cout<<"Unable to open file";
  
 
  
  //close the intermediate file
  file.close();
}

int pass2()
{



  return 0;

}
