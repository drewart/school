#include <iostream>
#include <string.h>

using namespace std;

int main(int argc,char *argv[])
{
  if (argc < 1)
    cerr << "no param" << endl;

  //char arg[] = *argv[1];
  //char *a;

  //a = argv[1];
  //cout << "strlen" << strlen(*argv[1]);
  std::string word = argv[1];
  
  cout << word << endl;


 
  
  while(*argv[1] != '\0')
    cout << *argv[1]++;

  cout << endl;
  
}

