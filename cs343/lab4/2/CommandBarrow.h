#ifndef COMMANDBARROW_H
#define COMMANDBARROW_H

#include "Command.h"
#include "Movie.h"
#include "Store.h"

//------------------------------------------------------------------------------
// CommandBarrow
// command for barrowing an item
//
//
class CommandBarrow : public Command
{

public:
  CommandBarrow();

  virtual ~CommandBarrow();

  virtual bool run(Store*);

  virtual bool setData(ifstream&);

  virtual void write(ostream&) const;

  virtual Command* createInstance();

  static char Letter;

protected:

  Item* item;


};

#endif

