#ifndef PACZUCHA_H_INCLUDED
#define PACZUCHA_H_INCLUDED

#include <string>
#include "enums.h"

using namespace std;

class Paczucha{
    sizeOfPackage size;
    const string receiver;

public:
    Paczucha(sizeOfPackage packageSize, const string &receiverPaczkomat) ;
};

#endif // PACZUCHA_H_INCLUDED
