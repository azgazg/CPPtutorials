#ifndef PACZKOMAT_H_INCLUDED
#define PACZKOMAT_H_INCLUDED

#include <string>
#include <vector>
#include "skrzynka.h"

using namespace std;

class Paczkomat{
    const string paczkomatId;
    //int m_boxesNo;
    int pendingPackages;
    vector<Skrzynka*> skrzynki;
    void addSkrzynki(sizeOfPackage size);
    int getReceivingSkrzynka(int collectionCode);

public:

    Paczkomat(const string &paczkomatId);
    ~Paczkomat();
    const string& getPaczkomatId(){return paczkomatId;} //?
    const int getPendingPackagesInPaczkomat(){return pendingPackages;}
    int getFreeSkrzynka(sizeOfPackage size);
    void storePaczka(int index, Paczucha *newPaczka);
    int getNumberOfSkrzynki(){return skrzynki.size();}

    Paczucha* getPaczka (int collectionCode);
    Skrzynka& operator[] (int index);


};


#endif // PACZKOMAT_H_INCLUDED
