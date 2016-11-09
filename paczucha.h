#ifndef PACZUCHA_H_INCLUDED
#define PACZUCHA_H_INCLUDED

#include <string>
#include "enums.h"

using namespace std;

class Paczucha{
    sizeOfPackage size;
    const string receiver;


public:
    Paczucha(sizeOfPackage packageSize, const string &receiver) ;
    ~Paczucha();
    const string& getReceiverId() {return receiver;}
    sizeOfPackage getSize() {return size;}
    void setSize(sizeOfPackage size) {this->size = size;}
};

#endif // PACZUCHA_H_INCLUDED
