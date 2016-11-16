#include <iostream>
#include "skrzynka.h"

using namespace std;


Skrzynka::Skrzynka(sizeOfPackage packageSize): size(packageSize), paczka(NULL), code(-1){
    //cout<< "Skrzynka created, size :" << size << endl;
}

Skrzynka::~Skrzynka(){
    if (paczka){
        delete paczka;
    }
    //cout<< "Skrzynka deleted, size :" << size << endl;
}

/*void Skrzynka::setPaczka(Paczucha *newPaczka){
    paczka = newPaczka;
    code = reinterpret_cast<int>(newPaczka);
    cout << "To collect the package enter the code: " << code << endl;
}*/

Paczucha* Skrzynka::getPaczka(){
    Paczucha *tmpPaczka = paczka;
    paczka = NULL;
    code = -1;
    return tmpPaczka;
}

void Skrzynka::operator>> (Paczucha* newPaczka){
    paczka = newPaczka;
    code = reinterpret_cast<int>(newPaczka);
    cout << "To collect the package enter the code: " << code << endl;
}

Paczucha* Skrzynka::operator--(){
    Paczucha *tmpPaczka = paczka;
    paczka = NULL;
    code = -1;
    return tmpPaczka;
}

Paczucha* Skrzynka::operator--(int){
    return --(*this);
}


