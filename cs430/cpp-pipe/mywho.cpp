//‘exit’ was not declared in this scope
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
  int pid;
  int fd[2];
  char line[1000];
  /* fork another process */

   
    if ((pipe(fd)) < 0)
    {
	perror("pipe failure");	
	exit(-1);
    }
    //fork
    else if ((pid = fork() ) < 0) 
    {
	  fprintf(stderr, "fork failed");
	  exit(-1);
    }
    else if ( pid == 0 ) 
    {
      /* child process */
      //if (dup2(
      close(fd[0]);
      if ((dup2(fd[1],STDOUT_FILENO)) < 0)
      {
        cerr << "dup2 error" << endl;

      }
      execlp("/usr/bin/who","who",NULL);
    }
    else
    {
      wait(NULL);
      close(fd[1]);
      int n = read(fd[1],line,1000);
      printf("line");
      write(1,line,n);
      printf("pid");
      cout << pid << endl;
      printf("Child Complete\n");
      exit(0);
    }
}


