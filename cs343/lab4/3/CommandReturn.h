#ifndef COMMANDRETURN_H
#define COMMANDRETURN_H

#include "Movie.h"
#include "Command.h"



class CommandReturn : public Command
{

public:
  CommandReturn();
  //ReturnCommand(const ReturnCommand&);
  virtual ~CommandReturn();

  virtual bool run(Store*);

  virtual bool setData(ifstream&);

  virtual void write(ostream&) const;

  virtual Command* createInstance();

  static char Letter;

protected:

  Item* item;


};

#endif

