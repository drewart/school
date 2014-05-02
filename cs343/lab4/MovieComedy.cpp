
#include "MovieComedy.h"

const char MovieComedy::Letter = 'F';


MovieComedy::MovieComedy()
{

}

MovieComedy::~MovieComedy()
{
  //cout << "~MovieComedy()" << endl;
}


//{{{write
//------------------------------------------------------------------------------
//
//
//
void MovieComedy::write(ostream& out) const
{
  Movie::write(out);
}
//}}}

//{{{setData
//------------------------------------------------------------------------------
//
//
//
bool MovieComedy::setData(ifstream& stream)
{
    if (Movie::setData(stream))
    {
      //sort title,year
      stringstream out;
      out << movieType;
      out << " ";
      out << title;
      out << ", ";
      out << year;
      sortString = out.str();

      return true;

    }
    return false;

}
//}}}

/*int MovieComedy::compareTo(Item* item) const
{
  if (typeid(*item).name() == typeid(MovieComedy).name())
  {
    MovieComedy * rhs = static_cast<MovieComedy*>(item);
    return -1;
  }
  else
  {
    Movie * rhs = static_cast<Movie*>(item);
    return Movie::compareTo(rhs);
    
  } 

}*/

/*
int MovieComedy::compareTo(const MovieComedy& rhs) const
{
  if (this->sortString == rhs.sortString)
    return 0;
  else if (this->sortString < rhs.sortString)
    return -1;
  else
    return 1;
}
*/


//{{{compare
//
/*bool MovieComedy::operator<(const MovieComedy& rhs) const
{
  //return (compareTo(rhs) == -1);
  cout << "todo" << endl;
  return true;
}


bool MovieComedy::operator>(const MovieComedy& rhs) const
{
 cout << "todo" << endl;
  return true;
}



bool MovieComedy::operator==(const MovieComedy& rhs) const
{
 cout << "todo" << endl;
  return true;
}
//}}}
*/



Movie* MovieComedy::createInstance()
{
  return new MovieComedy();
}

