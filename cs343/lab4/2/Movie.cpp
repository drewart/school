//Movie
#include "Movie.h"

Movie::Movie()
{
  movieType = '0';
  year = 0;
  inventory = DEFAULT_MOVIE_INVENTORY;
  inventoryOut = 0;
  media = "dvd";
}

Movie::~Movie()
{
   //cout << "~Movie()" << endl;
}


//-----------------------------------------------------------------------------
//
// setData
//  base method for setting data from a stream for a movie
//
//
bool Movie::setData(ifstream& stream)
{
  stream >> movieType;
  stream.ignore(1);  //skip space

  //store Movie line input in description
  getline(stream,  description);

  //parse description
  size_t firstComma,lastComma;

  firstComma = description.find_first_of(",");
  lastComma = description.find_last_of(",");

  director = description.substr(0,firstComma);
  title = description.substr(firstComma+2,lastComma-firstComma-2);

  int len = description.length();

  string yearStr = description.substr(len-4,4);

  //parse string to int
  year = atoi(yearStr.c_str());

  sku += movieType;
  sku += yearStr.substr(2,2);
  sku += director.substr(0,1);
  sku += title.substr(0,3);

  return !stream.eof();
}

bool Movie::valid()
{
  //add error
  return (title.length() > 0 && director.length() && year > 0 && year < 2013 && sku.length() > 0);
}

void Movie::write(ostream& out) const
{
 out << right << setw(4) << inventory << " " << setw(4) << inventoryOut  << "  ";
 writeBasic(out);
}

void Movie::writeBasic(ostream& out) const
{

  out << setw(MAX_TITLE_DISPLAY_WIDTH+1) << left << title.substr(0,MAX_TITLE_DISPLAY_WIDTH) 
      << setw(MAX_DIRECTOR_DISPLAY_WIDTH+1) << left << director.substr(0,MAX_DIRECTOR_DISPLAY_WIDTH) << right << setw(5) << year; 

}

int Movie::compareTo(Movie* rhs) const
{
   if (movieType == rhs->movieType)
   {
     if (year == rhs->year)
     {
		   if (this->director == rhs->director)
		   {
			   if (this->title == rhs->title) 
				   return 0;
			   else if (this->title < rhs->title)
				   return -1;
			   else
				   return 1;
		   }
       else if (this->director < rhs->director)
         return -1;
       else 
         return 1;
     }
     else if (year < rhs->year)
       return -1;
     else 
       return 1;
   }
   else if (movieType < rhs->movieType)
     return -1;
   else 
     return 1; 
}

/*bool Movie::operator<(const Movie& rhs) const
{
  return (sortString < rhs.sortString);
}

bool Movie::operator>(const Movie& rhs) const
{
  return (sortString > rhs.sortString);
}
*/
  

bool Movie::operator==(const Movie& rhs) const
{
   if (movieType == rhs.movieType
     && year == rhs.year
		 && this->director == rhs.director
     && this->title == rhs.title 
     && sortString == rhs.sortString)
       return true;
   else
     return false;
}//end ==



Movie* Movie::createInstance()
{
  return new Movie();
}

