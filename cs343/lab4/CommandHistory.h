#ifndef COMMANDHISTORY_H
#define COMMANDHISTORY_H

#include "Command.h"

//------------------------------------------------------------------------------
// CommandHistory 
//   command to list the history for a customer
//
//
class CommandHistory : public Command
{

public:
  CommandHistory();
  virtual ~CommandHistory();

  virtual bool run(Store*);

  virtual bool setData(ifstream&);

  virtual void write(ostream&) const;

  virtual Command* createInstance();

  static char Letter;

private:
  int customerId;
};

#endif

