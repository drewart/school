#include "Customer.h"
#include "Command.h"


Customer::Customer()
{
  id = 0;
}

Customer::Customer(const Customer& cust)
{
  id = cust.id;

  //copy history
}

//destroy Customer
Customer::~Customer()
{
  cout << "~Customer()" << endl;
}

int Customer::getId()
{
  return id;
}

void Customer::addHistory(Command* cmd)
{
  history.add(cmd);
}

void Customer::printHistory()
{
  history.printList();
}

//compare <
bool Customer::operator<(const Customer& rhs) const
{
  return (id < rhs.id);
}

//compare >
bool Customer::operator>(const Customer& rhs) const
{
  return (id > rhs.id);
}

//compare ==
bool Customer::operator==(const Customer& rhs) const
{
  return (id == rhs.id);
}

//setData from stream
bool Customer::setData(ifstream& stream)
{
  stream >> id;
  if (stream.eof())
    return false;

  if (id >= 9999 || id <= 999 || stream.eof())
  {
    cout << "Customer Id out of range " << endl;
    return false;
  }
  stream.ignore(1);

  getline(stream,name);
  
  return !stream.eof();
}

void Customer::write(ostream& out) const
{
  out << id;
  out << " " << name;
}


ostream& operator<< (ostream& out, const Customer& cust)
{
  cust.write(out);

  return out;
}


