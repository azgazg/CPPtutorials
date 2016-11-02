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

public:

    Paczkomat(const string &paczkomatId);
    ~Paczkomat();
    const string& getPaczkomatId(){return paczkomatId;} //?
    const int getPendingPackagesInPaczkomat(){return pendingPackages;}





};


#endif // PACZKOMAT_H_INCLUDED
