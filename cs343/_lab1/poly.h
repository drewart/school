// Poly object holds array of Polynomial terms of coefficient &  exponent

#ifndef POLY_H
#define POLY_H
#include <iostream>
using namespace std;

//---------------------------------------------------------------------------
// Poly is a array storage representation of a Polynomial .
//      Poly allows one to add, subtract, multiply the Polynomial. 
//       one can set terms in the Polynomial with setCoeff
//
// Assumptions:
//   -- Polynomial are stored as integer coefficient and exponent in a array
//   -- exponents are non-negitive numbers
//   -- exponent is less than POLY_MAX_SIZE=1000
//   --  
//---------------------------------------------------------------------------


//default array size
const int POLY_INIT_SIZE=25;

//max exponent
const int POLY_MAX_SIZE=25000;

class Poly 
{

// overloaded <<: to print Polynomial object
friend ostream& operator<<(ostream&, const Poly&);

// overloaded >>: 
friend istream& operator>>(istream&, Poly&);

public:
   // default constructor:  parameters are coefficient and exponent resp.
   Poly(int = 0, int = 0 );                        
   
   Poly(const Poly &p);
   ~Poly();

   void setCoeff(int = 0,int = 0);
   int getCoeff(int) const;

   //output helper
   ostream& write(ostream&) const;

   // arithmetic operators
   Poly operator+(const Poly &) const;   // add 2 Polynomial
   Poly operator-(const Poly &) const;   // subtract 2 Polynomial
   Poly operator*(const Poly &) const;   // multiply 2 Polynomial

   // boolean comparison operators
   bool operator==(const Poly &) const;      // is object == parameter?
   bool operator!=(const Poly &) const;      // is object != parameter?

   // assignment operators
   Poly& operator+=(const Poly &);       // current object += parameter
   Poly& operator-=(const Poly &);       // current object -= parameter
   Poly& operator*=(const Poly &);       // current object *= parameter

   Poly& operator=(const Poly &);       // current object = parameter
                                                 
   //private members and functions                                                 
private:
   int* _polyArray;              //pointer to array
   int _maxExponent;             // store max exponent
   int _polyArraySize;           // store array size 
   void buildArray(int);         // method to re-size array
   void init();                  // Initialize members
   void init(const Poly&);       // Initialize members from Poly
   bool isEmpty() const;

};

#endif
