#ifndef SKRZYNKA_H_INCLUDED
#define SKRZYNKA_H_INCLUDED

#include "enums.h"
#include "paczucha.h"

class Skrzynka{
    sizeOfPackage size;
    Paczucha *paczka;
    Skrzynka(const Skrzynka& other);
public:
    Skrzynka(sizeOfPackage packageSize);
    ~Skrzynka();

};

#endif // SKRZYNKA_H_INCLUDED
