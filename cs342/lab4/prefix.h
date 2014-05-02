// You add all appropriate comments describing the ADT and class assumptions.
// Add all member comments as well.

#ifndef PREFIX_H
#define PREFIX_H
#include <iostream>
#include <fstream>
using namespace std;

int const MAXSIZE = 100;

class Prefix {
    friend ostream& operator<<(ostream&, const Prefix&);

public:
    Prefix();
    void setPrefix(ifstream& infile);
    int evaluatePrefix() const;
    void outputAsPostfix(ostream&) const;

private:
    char expr[MAXSIZE+1];
    int evaluatePrefixHelper(int&) const;
    void toPostfix(int&, char [], int&) const;
};

#endif


