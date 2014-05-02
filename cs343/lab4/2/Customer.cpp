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
  //cout << "~Customer()" << endl;
}

string Customer::getName() const
{
  return name;
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


  stream.ignore(1);

  getline(stream,name);

  if (stream.eof())
    return false;
  
  //validate
  if (id >= 9999 || id <= 999)
  {
    cout << "Customer Id: " << id << " out of range " << endl;
    return false;
  }
  
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


