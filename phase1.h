#include <iostream>
#include <cstdlib>
#include <cctype>
#include <string>
#include <sstream>
#include <fstream>
#include <cstring>
#include "assembler.h"

using namespace std;

//Checks the command and designates its decimal code
int CommandCheck(char* c)
{
	int i = 0;
	string comm;

	//takes first 3 letters in lowercase of command and adds them to comm
	for (i; i<3; i++)
	{
		c[i] = tolower(c[i]);
		comm = comm + c[i];
	}


	//command to decimal converter
	if(comm == "loa")
		return 1;
	else if(comm == "exe")
		return 2;
	else if(comm == "deb")
		return 3;
	else if(comm == "dum")
		return 4;
	else if(comm == "hel")
		return 5;
	else if(comm == "ass")
		return 6;
	else if(comm == "dir")
		return 7;
	else if(comm == "exi")
		return 8;
	else return 0;
}

//load command
void load(char* c)
{	
	//checks if parameters exist also used in dump and assemble
	if(c[4] == '\0'||c[3] == '\0')
	{
		cout<<"Please try again but with the commands appropriate parameters!";
		return;
	}

	//s and e signal start and end of filename
	int s = 0 , e = 0;

	//to be used to save the filename into
	string filename;
	
	//next two loops used to figure out where filename begins and ends
	for(int i = 0; ; i++)
	{
		if(isspace(c[i]))
		{
			//+1 is due to the next character is the start of the filename
			//same throughout the rest of the code ^^
			s = i + 1;
			break;
		}
	}

	for(int i = s; ; i++)
	{
		if(c[i] == '\0')
		{
			//-1 is due to the character before is the end of the filename
			//same throughout the rest of the code ^^
			e = i -1;
			break;
		}
	}
	
	//puts the filename from the array to the string
	for(int i = s; i <= e; i++)
	{
		filename = filename + c[i];
	}
	
	cout<<filename<<" cannot be loaded at the moment because\n";
	cout<<"load command hasn't been implemented yet"<<endl;
}

//execute command
void execute()
{
	cout<<"Execute command hasn't been implemented yet"<<endl;
}

//debug command
void debug()
{
	cout<<"Debug command hasn't been implemented yet"<<endl;
}

//dump command
void dump(char* c)
{	
	//checks if parameters exist
	if(c[4] == '\0'||c[3] == '\0')
	{
		cout<<"Please try again but with the commands appropriate parameters!";
		return;
	}

	//s1, s2, e1 and  e2 will signify beginning and end of each parameter
	int s1 = 0 ,s2 = 0, e1 = 0, e2 = 0;

	string start, end;
	
	//first four loops get the values for s1, s2, e1 and e2
	for(int i = 0; ; i++)
	{
		if(isspace(c[i]))
		{	
			s1 = i + 1;
			break;
		}
	}

	for(int i = s1; ; i++)
	{
		if(isspace(c[i]))
		{	
			e1 = i - 1;
			break;
		}
	}
	
	for(int i = e1; ; i++)
	{
		if(isspace(c[i]))
		{	
			s2 = i + 1;
			break;
		}
	}

	for(int i = s2; ; i++)
	{
		if(c[i] == '\0')
		{	
			e2 = i - 1;	
			break;
		}
	}

	//creates start string for first parameter
	for(int i = s1; i <= e1; i++)
	{
		start = start + c[i];
	}

	//creates end string for last parameter
	for(int i = s2; i <= e2; i++)
	{
		end = end + c[i];
	}
	
	cout<<"Dump from "<<start<<" to "<<end;
	cout<<" cannot be done because dump command hasn't been implemented."<<endl;
}
//help command
void help()
{
	cout<<"\t>>Type command you want to use without <>.\n";
	cout<<"\t>>Feel free to only input the first 3 letters of any command.\n";
	cout<<"\t>>Make sure there is only one space between parameters.\n";
	cout<<"<load filname>"<<endl;
	cout<<"\t\t\tLoads file of filename specified.\n";
	cout<<"<execute>"<<endl;
	cout<<"\t\t\tExecutes file loaded in memory with the computer\n";
	cout<<"\t\t\tsimulation program.\n";
	cout<<"<debug>"<<endl;
	cout<<"\t\t\tAllows execution in debug mode.\n";
	cout<<"<dump start end>"<<endl;
	cout<<"\t\t\tCalls dump function, pushing the values start and end.\n";
	cout<<"\t\t\tstart and end must be Hexadecimal values\n";
	cout<<"<help>"<<endl;
	cout<<"\t\t\tYou're in it!!\n";
	cout<<"<assemble filename>"<<endl;
	cout<<"\t\t\tAssembles an SIC assembly language program.\n";
	cout<<"<directory>"<<endl;
	cout<<"\t\t\tLists files in current directory.\n";
	cout<<"<exit>"<<endl;
	cout<<"\t\t\tExits the simulator.\n";
}

//assemble command
void assemble(char* c)
{

	if(c[3] == '\0'||c[4] == '\0'||c[5] == '\0'||c[6] == '\0'||c[7] == '\0'||c[8] == '\0')
	{
		cout<<"Please try again but with the commands appropriate parameters!";
		return;
	}

	//s=start of filename, e=end of filename
	int s = 0 , e = 0;

	//filename will be saved to this string
	string filename;


	//following two loops will help in checking the start and end of the filename
	for(int i = 0; ; i++)
	{
		if(isspace(c[i]))
		{
			s = i + 1;
			break;
		}
	}

	for(int i = s; ; i++)
	{
		if(c[i] == '\0')
		{	
			e = i -1;	
			break;
		}
	}

	//this loop gets the filename from the character array
	for(int i = s; i <= e; i++)
	{
		filename = filename + c[i];
	}
	
	pass1(filename);
      
}

//directory command
void directory()
{
	//shows files in directory
	system("ls");
}

void Commander(int c, char* comm)
{
	//switch case that can run all commands
	switch (c){
	case 1:
		load(comm);
		break;
	case 2:
		execute();
		break;
	case 3:
		debug();
		break;
	case 4:
		dump(comm);
		break;
	case 5:
		help();
		break;
	case 6:
		assemble(comm);
		break;
	case 7:
		directory();
		break;
	case 8:
		cout<<"Goodbye!!"<<endl;
		//this function is already included in the libraries
		exit(1);
		break;
	case 0:
		//in case of command being input wrong
		cout<<"Not a valid command.\n";
		break;
	default:
		//unforseen errors
		cout<<"Something went horribly wrong.";
	}
}
