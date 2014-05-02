#ifndef MOVIESTORE_H
#define MOVIESTORE_H

#include <string>
#include "Store.h"

class MediaStore : public Store
{

public:
  MediaStore(string s) : Store(s) {}
  ~MediaStore();
  bool loadMedia(ifstream&);
  bool findMedia(Media*,Media*&);

private
  //Movie* movieCollection;				//pointer to a Movie Collection

};


#endif

