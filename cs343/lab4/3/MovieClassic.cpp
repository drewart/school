
#include "MovieClassic.h"

const char MovieClassic::Letter = 'C';


MovieClassic::MovieClassic()
{
  month = 0;
}

MovieClassic::~MovieClassic()
{
  //cout << "~MovieClassic()" << endl;
}

//{{{write
//------------------------------------------------------------------------------
//
//
//
void MovieClassic::write(ostream& out) const
{
  Movie::write(out);
}

void MovieClassic::writeBasic(ostream& out) const
{
  Movie::writeBasic(out);
  out << right << setw(3) << month << " " << actor;

}
//}}}

//{{{setData
//------------------------------------------------------------------------------
//
//
//
bool MovieClassic::setData(ifstream& stream)
{
   //set main data
   Movie::setData(stream);

   size_t pos = description.find_last_of(',');
   
   actor = description.substr(pos+2,(description.length() - pos) -9);

   //parse month
   string monthStr = description.substr(description.length() -6, 1);

   month = atoi(monthStr.c_str());
   
   sku += actor.substr(0,3);

   std::stringstream out;

   out << movieType;
   out << " ";
   out << month;
   out << " ";
   out << year;
   out << " ";
   out << actor;

   sortString = out.str();  

   return valid();
}
//}}}


bool MovieClassic::valid() 
{
  if (month == 2 && year == 1975)
  {
    this->error = "Invalid Month and Year";
    return false;
  }
  else 
    return Movie::valid();
}

/*
int MovieClassic::compareTo(MovieClassic* rhs) const
{
  cout << "MovieClassicd::compareTo" << endl;
  return Movie::compareTo(rhs);
}
*/


//{{{compare
//
/*bool MovieClassic::operator<(const MovieClassic& rhs) const
{
   return true;
}


bool MovieClassic::operator>(const MovieClassic& rhs) const
{
   
}
*/

//MovieClassic
bool MovieClassic::operator==(const MovieClassic& rhs) const
{
 if (movieType == rhs.movieType
     && year == rhs.year
		 && this->director == rhs.director
     && this->title == rhs.title 
     && sortString == rhs.sortString
     && actor == rhs.actor
     && month == rhs.month

     )
       return true;
   else
     return false;
}
//}}}


Movie* MovieClassic::createInstance()
{
  return new MovieClassic();
}

