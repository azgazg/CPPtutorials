#include <iostream>
#include "skrzynka.h"

using namespace std;


Skrzynka::Skrzynka(sizeOfPackage packageSize): size(packageSize), paczka(NULL), code(-1){
    cout<< "Skrzynka created, size :" << size << endl;
}

Skrzynka::~Skrzynka(){
    cout<< "Skrzynka deleted, size :" << size << endl;
}

void Skrzynka::setPaczka(Paczucha *newPaczka){
    paczka = newPaczka;
    code = reinterpret_cast<int>(newPaczka);
    cout << "To receive package enter the code: " << code << endl;
}



