//‘exit’ was not declared in this scope
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
  int pid;
  /* fork another process */
   pid = fork();
   cout << "pid:" << pid << endl;
   
    if (pid < 0) 
    {
	  fprintf(stderr, "fork failed");
	  exit(-1);
    }
	else if ( pid == 0 ) 
	{
			/* child process */
		execlp("/bin/ls","ls",NULL);
	}
	else
	{
		printf("inwait");
		wait();
		printf("Child Complete");
		exit(0);
	}
}


