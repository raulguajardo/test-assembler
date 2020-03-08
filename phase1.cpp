#include <iostream>
#include <cstdlib>
#include <cctype>
#include "phase1.h"

using namespace std;

int main()
{	
	//character array for command plus filename
	char command[100];
	//welcome message
	cout<<"Please enter a command.\n"<<endl;
	cout<<"For a list of commands type help.\n";
	
	//for loop
	int i = 0;
	
	//to keep asking until exit command is entered
	while(i == 0)
	{
		cout<<"\nCommand:";
		cin.getline (command, 100);	
		Commander(CommandCheck(command), command);
	}
	return 0;

}
