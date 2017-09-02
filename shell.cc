#include <iostream>
#include <unistd.h>
#include <sstream>
#include <cstring>
#include <errno.h>
#include <sys/wait.h>
#include <cstdlib>
#include <stdio.h>
using namespace std;

const int MAX_ARGS = 10;
const int BUFFER_SIZE = 256;

// char **tokenize(char *line)
// {
// 	char *args[MAX_ARGS];

//     char *token = strtok(line," ");
//     int ind=0;
//     while(token)
//     {
//         args[ind++] = token;
//         token = strtok(0," ");
//     }
//     args[ind++]='\0';
// }

char *read_line()
{
	char *linebuffer = new char[BUFFER_SIZE];
    cin.getline(linebuffer, sizeof(linebuffer));
    if(cin.eof())
        exit(0);
    if(!strcmp(linebuffer,"exit"))
        exit(0);
    return linebuffer;
}


void shell()
{
	char *line, **args;
    cout << "Hey, I'm REBASH (rebourne shell!)" << endl;
    while(1)
    {
        cout << "$ ";
        line = read_line();
        char *args[MAX_ARGS];

	    char *token = strtok(line," ");
	    int ind=0;
	    while(token)
	    {
	        args[ind++] = token;
	        token = strtok(0," ");
	    }
	    args[ind++]='\0';
        int status, estatus;
        if(!strcmp(args[0],"cd"))
        {
        	chdir(args[1]);
        }
        else
        {
        	pid_t pid = fork();
	        if(pid==0)
	        {
	            execvp(args[0], &args[0]);
	            _exit(0);
	        }
	        
	        else
	        {
	            wait(&status);
	            if(status==-1)
	            {
	                perror("I give u the rebourne ultimatum");
	                exit(1);
	            }

	        }
	    }
    }
}



int main(int argc, char **argv)
{
    shell();
    cout << "asdsa"<<endl;

}
