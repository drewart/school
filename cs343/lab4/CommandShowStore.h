#ifndef COMMANDSHOWSTORE_H
#define COMMANDSHOWSTORE_H
//CommandShowStore

#include "Command.h"

class CommandShowStore : public Command
{

public: 
  CommandShowStore();
  virtual ~CommandShowStore();

  virtual bool run(Store*);

  virtual bool setData(ifstream&);

  virtual void write(ostream&) const;

  virtual Command* createInstance();

  static char Letter;
  
};

#endif

