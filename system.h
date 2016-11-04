#ifndef SYSTEM_H_INCLUDED
#define SYSTEM_H_INCLUDED

#include "paczkomat.h"
#include "paczucha.h"


class System{
    static const int MAX_PACZKOMAT = 10;
    Paczkomat *paczkomat[MAX_PACZKOMAT];
    int freeIndex;

public:
    System();
    ~System();
    void run();


private:
    int getUserChoice();
    int getNoOfPendingPackages();
    void createPaczkomat();
    void listPaczkomats();
    void deletePaczkomat();
    void sendPackage();
    sizeOfPackage getPackageSize();
};

#endif // SYSTEM_H_INCLUDED
