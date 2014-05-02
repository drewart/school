#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <iostream>

using namespace std;

int main(int argc,char *argv[])
{
 string searchTerm;
 int ps_pid,grep_pid;

 if (argc < 2 )
 {
    cerr << "missing search term" << endl;
    exit(-1);
 }
 else
   searchTerm = argv[1];

  int psfd[2];

  pipe(psfd);   // create ps pipe fd

  // ps fork
  if ( (ps_pid = fork()) < 0)
  {
     perror("fork failure");
     exit(-1);
  }

  // parent pid
  if (ps_pid == 0) {

    int grepfd[2];

    close(psfd[1]);  // close write fd
    dup2(psfd[0], 0); //dup read fd to std in
    close(psfd[0]);  // close read fd

    pipe(grepfd);   // create grep pipe fd

    // grep fork
    if ((grep_pid = fork()) < 0)
    {
      perror("fork failure in grep");
      exit(EXIT_FAILURE);
    }

    if (grep_pid == 0)
    {
       close(grepfd[0]);    // close grep read fd
       dup2(grepfd[1],1); // dup std out  to fd
       close(grepfd[1]);  //close grep write fd
       
       execlp("grep", "grep", searchTerm.c_str() ,NULL);

    }
    else
    {
        // close pipe and read in grep fd
	close(grepfd[1]);   // close grep write fd
        dup2(grepfd[0],0);  //dup grep read fd to std in 
        close(grepfd[0]);   // close grep read fd

        execlp("wc","wc","-l",NULL);
    }

  } else {
    close(psfd[0]);  //close read fd
    dup2(psfd[1], 1); //dup write fd to std out
    close(psfd[1]);
    execlp("ps", "ps","-A",NULL) ;
  }
}
