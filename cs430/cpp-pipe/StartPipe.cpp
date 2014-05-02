#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <iostream>

using namespace std;

int StartPipe(char INPUT[]); 
 
int main(int argc,char *argv[])
{
  char foo[1000];
  StartPipe(foo);
  int end = strlen(foo);
  for(int i = 0; i < end; i++)
    cout << foo[i];
 
  cout << endl;
  
} 

int StartPipe(char INPUT[])
{
    int fd1[2];
    int fd2[2];
    pid_t pid;
    char line[1000];

    if ( (pipe(fd1) < 0) || (pipe(fd2) < 0) )
    {
        cerr << "PIPE ERROR" << endl;
        return -2;
    }
    if ( (pid = fork()) < 0 )
    {
        cerr << "FORK ERROR" << endl;
        return -3;
    }
    else  if (pid == 0)     // CHILD PROCESS
    {
        close(fd1[1]);
        close(fd2[0]);

        if (fd1[0] != STDIN_FILENO)
        {
            if (dup2(fd1[0], STDIN_FILENO) != STDIN_FILENO)
            {
                cerr << "dup2 error to stdin" << endl;
            }
            close(fd1[0]);
        }

        if (fd2[1] != STDOUT_FILENO)
        {
            if (dup2(fd2[1], STDOUT_FILENO) != STDOUT_FILENO)
            {
                cerr << "dup2 error to stdout" << endl;
            }
            close(fd2[1]);
        }

        if ( execlp("/usr/bin/who", "who", NULL) < 0 )
        {
            cerr << "system error" << endl;
            return -4;
        }

        return 0;
    }
    else        // PARENT PROCESS
    {
        int rv;
        close(fd1[0]);
        close(fd2[1]);

        if ( write(fd1[1], INPUT, strlen(INPUT) ) != strlen(INPUT) )
        {
            cerr << "READ ERROR FROM PIPE" << endl;
        }

        if ( (rv = read(fd2[0], line, 1000)) < 0 )
        {
            cerr << "READ ERROR FROM PIPE" << endl;
        }
        else if (rv == 0)
        {
            cerr << "Child Closed Pipe" << endl;
            return 0;
        }

        cout << "OUTPUT of who is: " << line;

        return 0;
    }
    return 0;
}
