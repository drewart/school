//‘exit’ was not declared in this scope
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

using namespace std;

int main(int argc, char *argv[])
{
  int pid;
  int fd[2];
   
  /* fork another process */
	
    if ( pipe(fd) < 0 )
    {
      perror("pipe error");
    }
    else if ((pid = fork()) < 0) 
    {
      fprintf(stderr, "fork failed");
      exit(-1);
    }
    else if ( pid == 0 ) 
    {
     close( fd[0] ); //close file desc 0
	/* child process */
      execlp("/bin/ls","ls",NULL);
		//should write to fd[1]
    }
    else
    {
	wait( NULL );     //wait for child
        close (fd[1]);    // close fd[1] pipe
	int n = read(fd[1], line,1000);
        printf("output:");
        printf(line);
		
	  exit(0);
	}
}


