
#include "MovieDrama.h"

const char MovieDrama::Letter = 'D';

MovieDrama::MovieDrama()
{
}

MovieDrama::~MovieDrama()
{
  cout << "~MovieDrama()" << endl;
}
//{{{write
//------------------------------------------------------------------------------
//
//
//
/*void MovieDrama::write(ostream& out) const
{
}
*/
//}}}

//{{{setData
//------------------------------------------------------------------------------
//
//
//
bool MovieDrama::setData(ifstream& stream)
{
    if (Movie::setData(stream) && valid())
    {
      std::stringstream out;

      out << movieType;
      out << " ";
      out << this->director;
      out << ", ";
      out << this->title;
      out << ",";
      sortString = out.str();
      return true;
    }
    return false;
}
//}}}

#pragma region compare {{{

/*int MovieDrama::compareTo(const MovieDrama& rhs) const
{
  return Movie::compareTo(rhs); 
}*/

//------------------------------------------------------------------------------
//
//
//
/*
bool MovieDrama::operator<(const MovieDrama& rhs) const
{
  return (this->sortString < rhs.sortString);
}

//------------------------------------------------------------------------------
//
//
//
bool MovieDrama::operator>(const MovieDrama& rhs) const
{
   return (this->sortString > rhs.sortString);
}

//------------------------------------------------------------------------------
//
//
//
bool MovieDrama::operator==(const MovieDrama& rhs) const
{

}
//}}}
#pragma endregion compare }}}
*/

//------------------------------------------------------------------------------
// createInstance()
//
//
Movie* MovieDrama::createInstance()
{
  return new MovieDrama();
}

