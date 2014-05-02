#include "Store.h"

Store::~Store()
{
  cout << "~Store()" << endl;
}
/*Store::Store(string name)
{
  this->name = name;
}*/

/*bool Store::runCommand(Command& cmd)
{
  //read store commands
  return true;
}
*/

bool Store::addCustomer(Customer* customer)
{
  if (customerHash.containsKey(customer->getId()))
  {
    cout << "Customer exists with ID " << customer->getId()  << endl;
    return false;
  }
  return customerHash.add(customer->getId(),customer);
}

bool Store::getCustomer(int id,Customer *& customer)
{
  if (customerHash.containsKey(id))
  {

    customer = customerHash.get(id);
    return true;
  }

    cout << "Unable to find customer with id " << id << endl;
    return false;
}

