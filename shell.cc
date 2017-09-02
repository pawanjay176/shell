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

void shell()
{
    cout << "Hey, I'm REBASH (rebourne shell!)" << endl;
    while(1)
    {
        cout << "$ ";
        char linebuffer[256];
        cin.getline(linebuffer, sizeof(linebuffer));
        if(cin.eof())
            break;
        if(!strcmp(linebuffer,"exit"))
            break;
        char *args[MAX_ARGS];

        char *token = strtok(linebuffer," ");
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

}
