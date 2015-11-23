#include <iostream>
#include <string>
#include <cstring>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <cstdlib>
#include <vector>
#include <queue>
#include <sys/stat.h>

using namespace std;
//initialize array 
void printo(char** p){
    for(int c = 0; p[c] != NULL; c++){
        p[c] = NULL;
    }
    for(int i = 0; p[i] != NULL; i++){
        cout << p[i];
    }
    cout << endl;
}
void clr_argv(char** c){
    for(int i = 0; c[i] != NULL; i++){
        c[i] = NULL;
    }
}
//function that for test command
bool test(char *const symble[])
{
  struct stat sb;
  int flag = 0;

  if (*symble[0] == '-')
  {
     flag = 1;
  }

  if (stat(symble[flag], &sb) == -1)
  {
     return false;  
  }
   
  //checks result of stat command
  if ((sb.st_mode & S_IFMT) == S_IFREG){
    if ((strcmp(symble[0], "-e") == 0) || (strcmp(symble[0], "-f") == 0) || (flag == 0))                
    	{return true;}
    else
    	{return false;}
  }
  else if((sb.st_mode & S_IFMT) == S_IFDIR){
    if ((strcmp(symble[0], "-e") == 0) || (strcmp(symble[0], "-d") == 0) || (flag == 0))                
    	{return true;}
    else
	{return false;}
  }
  else 
    {return false;}
  return false;

}

//function that get input and output result
void execstack(char* username, char hostname[]){
	
	string input;
	char* cmdsave;
	cout << username << "@" << hostname << "$ ";
	getline (cin, input);

	// input nothing and input only comments	
	while(input.size() == 0 || input.at(0) == '#')
	{
		cout << username << "@" << hostname << "$ ";
		getline(cin, input);
	}

	 //get input
	char* cstr = new char [input.length() + 1];
	strcpy(cstr , input.c_str());
	cstr = strtok(cstr, "#"); //seprate input string by "#"
	vector<int> commands; //vector that save commands

		
	for(unsigned int i = 0; i < input.size()-1; i++)
	{
		//when type "&&"
		if(input.at(i) == '&' && input.at(i+1) == '&')
		{
			i++;
			commands.push_back(0);			
		}
		//when type "||"
		else if(input.at(i) == '|' && input.at(i+1) == '|')
		{
			i++;
			commands.push_back(1);
		}		
		//when type ";"
		else if(input.at(i) == ';')
		{
			commands.push_back(2);
		}
		
	}
	commands.push_back(2);
	
    	char* cmdl = strtok_r(cstr, ";&|", &cmdsave); //sepreate input string to commands
    	while(commands.size() != 0 && cmdl != NULL){
		bool cmdpass = true;
        	char* cmd = strtok(cmdl, " "); 
        	if(cmd == NULL){
           		commands.erase(commands.begin());
            		cmdl = strtok_r(NULL, "&|;", &cmdsave);
        	}
        	else{
      		char* argv[2048];
       		clr_argv(argv);
		argv[0] = cmd;
        	char* ctemp = strtok(NULL," ");

        	for(int i = 1; ctemp != NULL; i++){
       	    		argv[i]= ctemp;
            		ctemp = strtok(NULL, " ");
        	}
        	if(strcmp(cmd, "exit") == 0){
           		exit(0);
        	}
		int wchild;
		int pid = fork();
	
		if (pid == -1) {
			perror("fork failed");
			exit(1);
		} else if (pid == 0) {
			if (execvp(cmd, argv) == -1) {
				perror("execvp failed");
				exit(1);
			}
			exit(0);
		} else if(pid > 0){
            		int wpid = wait(&wchild);
            		if(wpid == -1){
                		perror("wait failed");
                		exit(1);
            		}
			if (wchild == 0){
                		cmdpass = true;
           	 	}
            		else{
                		cmdpass = false;
            		}
		}
        	if(commands.size() == 0)
            		return;
		//next command is executed only if the first one succeeds
       		if(commands.at(0) == 0){
            		if(cmdpass == false){
                		return;
           		}
        	}
		//next command is executed only if the first one fail
        	else if (commands.at(0) == 1){
            		if (cmdpass == true){
                		return;
           		}
		}

		commands.erase(commands.begin());
        	cmdl = strtok_r(NULL, "&|;", &cmdsave);
		}
	}
}
int main()
{
	//hostname and username
	char hostname [128];
	int host = gethostname(hostname, sizeof(hostname) - 1);
	if(host != 0)
	{
		perror("An error occured in gethostname");
	}

	char username [128];
	int login = getlogin_r(username, sizeof(username - 1));
	if(login != 0)
	{
		perror("An error occured in getlogin()");
	}
	while (1){
		execstack(username, hostname);
	}
	return 0;
}
