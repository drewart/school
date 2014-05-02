//‘exit’ was not declared in this scope
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <iostream>

using namespace std;

//
//    who | 
//   
//


//int ps(int fd[]);
void grep(int fd[],char *filter);
void wc(int fd[]);
int old();
//void ps1();


int main(int argc, char *argv[])
{
  string wordSearch = NULL;
 
  if (argc > 1)
    wordSearch = argv[1];

  

  int pfd[2];

  if (pipe(pfd) < 0) 
  { 
    perror("pipe error");
    exit(-1);
  }

  if (fork() == 0) // child
  {
    close(pfd[1]); //close the write
    dup2(pfd[0], 0);   // ? this creating the right file descriptor
    close(pfd[0]);     //close the read
    execlp("wc", "wc","-l",NULL);  // wc
    exit(0);
  } 
  else  //parent
  {
    close(pfd[0]);  //close read
    dup2(pfd[1], 1);  //clone write to std out
    close(pfd[1]);    // close std out
    execlp("ps", "ps", "-A",NULL);   //ps
    exit(0);
  }

}//end ps1





int old()
{
	int n, fd[2];
	int pid;
	char line[1000];
	
	if ( pipe(fd) < 0 ) 		// 1: pipe created
		perror("pipe error");
	else if ( ( pid = fork() ) < 0) 	// 2: child forked
		perror( "fork error" );
	else if ( pid > 0 ) //parent
	{
		close( fd[0] );
		write( fd[1], "hello world\n", 12 );
	}
	else
	{
		close(fd[1]); // 4: child's fd[1] closed
		n = read( fd[0], line, 1000);
		write(1,line,n);
	}
	exit(0);
}


//
// runs ps command and puts it in the pipe
//
/*int ps(int fd[])
{
  fork();

  if ( execlp("/usr/bin/ps", "ps","-A" ) < 0 )
  {
            cerr << "system error" << endl;
            return -1;
  }
}
*/

void grep(int fd[],char filter[])
{
  
}

void wc(int fd[])
{
  
}
