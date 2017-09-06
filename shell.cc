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


char *read_line()
{
	char *linebuffer, c;
    linebuffer = new char[BUFFER_SIZE];
    int i=0;
    while(1)
    {
    	if(cin.eof())
        	exit(0);
    	cin.get(c);
    	if(c=='\n'){
    		linebuffer[i++]='\0';
    		break;
    	}
    	else
    		linebuffer[i++]=c;
    }
    if(!strcmp(linebuffer,"exit"))
        exit(0);
    return linebuffer;
}

char **tokenize_line(char *line, int &status)
{
	char **args;
	args = new char*[MAX_ARGS];
    char *token = strtok(line," ");
    int ind=0;
    while(token)
    {
        args[ind++] = token;
        token = strtok(0," ");
    }
    args[ind]='\0';
    status = ind;
    return args;
}

int process_line(char **args, int length)
{
	int status;
    FILE *fp;
    if(!strcmp(args[0],"cd"))
    {
    	if(chdir(args[1])!=0)
    		perror("cd error");
    	else
    		return 1;
    }
    else
    {
    	pid_t pid = fork();
        if(pid==0)
        {
			for(int i=0;i<length;i++)
			{
				if(strcmp(args[i],">")==0)
				{
					if(i==length)
					{
						perror("Not enough arguements");
						exit(1);
					}
					fp = fopen(args[i+1],"w");
					dup2(fileno(fp), fileno(stdout));
					args[i]='\0';
					break;
				}
				else if(strcmp(args[i],"<")==0)
				{
					if(i==length)
					{
						perror("Not enough arguements");
						exit(1);
					}
					fp = fopen(args[i+1],"r");
					dup2(fileno(fp), fileno(stdin));
					args[i]='\0';
					break;
				}
			}
        	if(execvp(args[0], &args[0])==-1)
        		perror("some other process error");
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
	return 1;
}

void shell()
{
	char *line, **args;
	int status, length;
    cout << "Hey, I'm REBASH (rebourne shell!)" << endl;
    while(1)
    {
        fflush(stdout);
        cout << "$ ";
        fflush(stdout);
        line = read_line();
        if(!strcmp(line,""))
            continue;
        args = tokenize_line(line, length);
 		status = process_line(args, length);
 		if(status==0)
 			break;
    }
}



int main(int argc, char **argv)
{
    shell();
}
