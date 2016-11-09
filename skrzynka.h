#ifndef SKRZYNKA_H_INCLUDED
#define SKRZYNKA_H_INCLUDED

#include "enums.h"
#include "paczucha.h"

class Skrzynka{
    sizeOfPackage size;
    Paczucha *paczka;
    int code;
    Skrzynka(const Skrzynka& other);
public:
    Skrzynka(sizeOfPackage packageSize);
    ~Skrzynka();
    sizeOfPackage getSizeOfPackage() {return size;}
    bool isFree(){return paczka == NULL;}
    //void setPaczka(Paczucha *newPaczka);
    int getCode(){return code;}
    Paczucha* getPaczka();
    void operator>>(Paczucha *newPaczka);
    Paczucha* operator--();
    Paczucha* operator--(int);


};

#endif // SKRZYNKA_H_INCLUDED
