#include "poly.h"


/*********************************** << ***********************************
* Description: overload <<
*
*   
*/
ostream& operator<<(ostream &output, const Poly &p) 
{
   //call public write helper
   p.write(output);  

   return output;
}

/*********************************** >> ***********************************
* Description: input stream handler
*
*   
*/
istream& operator>>(istream &input, Poly &p) 
{
   int coefficient,exponent;
	
	do
	{
		input >> coefficient;		//read int
      input >> exponent;
		
		if (coefficient > POLY_MAX_SIZE || exponent > POLY_MAX_SIZE || (coefficient == 0 && exponent == 0))	//range check
			break;
		else 
         p.setCoeff(coefficient,exponent);					//insert

	} while(input.peek() != '\n');				//end while stop read on enter/return 

   return input;
}


/*********************************** {function} ***********************************
* Description: Constructor for Poly takes a coefficient and exponent
*
*   need to handle A() A(1), A(1,1)
*/
Poly::Poly(int coefficient,int exponent)
{
   init();  //inistialize variables

   //max check & min check
   if (exponent > POLY_MAX_SIZE || exponent < 0)
      return;  

   buildArray(exponent);   //build array

   //use setCoeff to set array
   this->setCoeff(coefficient,exponent);
}

/*********************************** ~Poly()  ***********************************
* Description: Destructor 
*
*   
*/
Poly::~Poly() 
{
   //de-allocate array memory
   if (_polyArray != NULL)
   {
	   delete []_polyArray;
	   _polyArray = NULL;
   }
}//end ~Poly() 


/*********************************** Poly(const Poly &p) **********************
* Description: Poly copy constructor
*
*   
*/
Poly::Poly(const Poly &p)
{
   if (this != &p)
   {
      init();
      init(p);
   }
}//end Poly

/*********************************** init() ***********************************
* Description: init is a private method for initiaizing 
*
*   
*/
void Poly::init()
{
   _polyArraySize = POLY_INIT_SIZE;
   _polyArray = NULL;   
   _maxExponent = 0;    

}//end init

/*********************************** init(Poly) ***********************************
* Description: method for init a Poly with a Poly aka copy constructor
*
*   
*/
void Poly::init(const Poly &p)
{
   
   //clean memory if not null 
   if (_polyArray != NULL)
      delete[] _polyArray;

   _polyArray = new int[p._polyArraySize+1];
   
   
   //copy Poly array member & zero array
   for(int i = 0; i <= p._polyArraySize; i++) //limit to _maxExponent
   {
      _polyArray[i] = (i <= p._maxExponent) ? p._polyArray[i] : 0;
   }

   //set array size and max exponent
   _polyArraySize = p._polyArraySize;
   _maxExponent = p._maxExponent;

}


/*********************************** isEmpty() ***********************************
* Description: returns if the Poly object is empty, nothing set
*
*   
*/
bool Poly::isEmpty() const
{
   return (_maxExponent == 0 && getCoeff(0) == 0);
}

/*********************************** write(ostream) ***********************************
* Description: helper for << output
*
*   
*/
ostream& Poly::write(ostream& output) const
{
   //IsEmpty
   if (isEmpty())
      output << " 0";

   for(int i = _maxExponent; i >= 0; i--)
   {
      //only write non-zero coefficient
      if (_polyArray[i] != 0)
      {
         //space & + for positive number
         cout << ((_polyArray[i] > 0) ? " +" : " ") << _polyArray[i];
         
         if (i == 1)                //case ^1
            output << "x";
         else if (i != 0)           //case not ^0 
            output << "x^" << i;
      }
   }
   return output;
}//end write


/*********************************** buildArray(int) ***********************************
* Description: private method to build/grow the poly array
*
*   
*/
void Poly::buildArray(int size)
{
   //remember the old size
   int _oldSize = _polyArraySize;
   //check if new size is bigger
   _polyArraySize = (size > _polyArraySize) ? size : _polyArraySize;
   
   //get max exponent
   _maxExponent = (size > _maxExponent) ? size :_maxExponent;

   //create array
   if (_polyArray == NULL)
   {
      _polyArray = new int[_polyArraySize+1];
         
      //set init 0
      for(int i = _polyArraySize; i >= 0; i--)
         _polyArray[i] = 0;
   }
   else
   {
      //grow array
      int* tempPolyArray = new int[_polyArraySize+1];
      
      //copy array
      for(int i = 0; i < _polyArraySize; i++)
      {
         //test <= upper bound
         tempPolyArray[i] = (i < _oldSize) ? _polyArray[i] : 0; 
      }

      //clean up old array
      delete []_polyArray;
      //set new array
      _polyArray = tempPolyArray;
   }
      
}//end buildArray


/*********************************** setCoeff ***********************************
* Description: set Poly array
*
*    
*/
void Poly::setCoeff(int coefficient,int exponent)
{
   //coefficient should not be 0
   if (coefficient == 0)
      return;

      //max check & min check
   if (exponent > POLY_MAX_SIZE || exponent < 0)
      return;

   if (exponent > _polyArraySize) //check upper bound & grow array
      buildArray(exponent);

   if (exponent > _maxExponent)
      _maxExponent = exponent;

   _polyArray[exponent] = coefficient;
}


/*********************************** getCoeff ***********************************
* Description: get coefficient from array
*
*    
*/
int Poly::getCoeff(int exponent) const
{
   //check upper & lower bounds 
   if (exponent > _maxExponent || exponent < 0 ) 
      return 0;

   return _polyArray[exponent];
}


/*********************************** operator+ ***********************************
* Description: adds two poly
*
*    
*/
Poly Poly::operator+(const Poly &p) const   // add 2 Rationals
{

   Poly temp;
         
   int size = (p._polyArraySize > _polyArraySize) ? p._polyArraySize : _polyArraySize;
   int max = (p._maxExponent > _maxExponent) ? p._maxExponent : _maxExponent;

   if (size > _polyArraySize)
      temp.buildArray(size);    
      
   for(int i = max; i >= 0; i--) 
   {
      int A,B;
      A = _polyArray[i];
      B = p._polyArray[i];

      temp._polyArray[i] = A + B;
      
      if (i > 0 == max && temp._polyArray[i] == 0)
      {
         max--;
      }
   }

   temp._polyArraySize = size;
   temp._maxExponent = max;
   
   //DEBUG cout << temp << endl;

   return temp;
}

/*********************************** operator- ***********************************
* Description: subtract two poly
*
*    
*/
Poly Poly::operator-(const Poly &p) const   // subtract 2 
{
   Poly temp;
         
   int size = (p._polyArraySize > _polyArraySize) ? p._polyArraySize : _polyArraySize;
   int max = (p._maxExponent > _maxExponent) ? p._maxExponent : _maxExponent;

   if (size > _polyArraySize)
      temp.buildArray(size);    
      
   for(int i = max; i >= 0; i--) 
   {
      //for VS debuging
      int A,B;
      //set coefficient
      temp._polyArray[i] = _polyArray[i] - p._polyArray[i];
         
      //check for new max !TEST! case  3x^3 + -3x^3 
      if (i > 0 == max && temp._polyArray[i] == 0)
      {
         max--;
      }
   }

   temp._polyArraySize = size;
   temp._maxExponent = max;
   
   cout << temp << endl;

   return temp;
}


/*********************************** operator* ***********************************
* Description: multiply two Poly objects
*
*    
*/
Poly Poly::operator*(const Poly &p) const   // multiply 2 Polynomial
{
   Poly product;
      
   //Loop each of this terms
   for ( int x = _maxExponent; x >= 0; x--)
   {
      //ignore terms with 0
      if (_polyArray[x] != 0)    
      {
         //loop each of right side terms
         for( int y = p._maxExponent; y >= 0; y--)
         {
            //ignore terms with 0
            if (p._polyArray[y] != 0)     
            {
               int exponent = x + y;
               int coefficient = _polyArray[x] * p._polyArray[y];

               if (product.getCoeff(exponent) == 0)
                  product.setCoeff(coefficient,exponent);
               else
                  product._polyArray[exponent] = product._polyArray[exponent] + coefficient;

               

               //DEBUG cout << "product" << product << endl;
            }

         }//end for *this
      }
   }//end for right side
      
   return product;
}


/*********************************** operator== ***********************************
* Description: comparison
*
*    
*/
bool Poly::operator==(const Poly &p) const      // is object == parameter?
{
   if (this == &p)
      return true;

   int max = (p._maxExponent > _maxExponent) ? p._maxExponent : _maxExponent;
      
   //quick way max Exponent != max Exponent
   if (p._maxExponent != _maxExponent)
      return false;

   for( int i = 0; i <= max; i++)
   {
      if (i <= p._maxExponent && i <= _maxExponent && p._polyArray[i] != _polyArray[i])
         return false;
   }

   return true;
}

/*********************************** operator!= ***********************************
* Description: comparison
*
*    
*/
bool Poly::operator!=(const Poly &p) const      // is object != parameter?
{
   if (this == &p)
      return false;

   int max = (p._maxExponent > _maxExponent) ? p._maxExponent : _maxExponent;

   for( int i = 0; i <= max; i++)
   {
      if (i <= p._maxExponent && i <= _maxExponent && p._polyArray[i] != _polyArray[i])
         return true;
   }
   return false;
}
   

/*********************************** operator+= ***********************************
* Description: add right poly to self
*
*    
*/
Poly& Poly::operator+=(const Poly &p)       // current object += parameter
{
   //cheat *this for A = A + A;
   Poly p1(*this),p2(p);
   *this = p1 + p2;
   return *this;
}

/*********************************** operator+= ***********************************
* Description: subtract right poly to self
*
*    
*/
Poly& Poly::operator-=(const Poly &p)       // current object -= parameter
{
   
   Poly p1(*this),p2(p);
   *this = p1 + p2;
   return *this;
}


/*********************************** operator+= ***********************************
* Description: multiply right poly to self
*
*    
*/
Poly& Poly::operator*=(const Poly &p)       // current object *= parameter
{
   Poly p1(*this),p2(p);
   *this = p1 * p2;
   return *this;
}
   
/*********************************** operator+= ***********************************
* Description: set this object with Poly
*
*    
*/
Poly& Poly::operator=(const Poly &p)       // current object /= parameter
{
   //A = A check
	if (this == &p)
		return *this;	

   init(p);

   return *this;
}
