#include <iostream>
#include "paczkomat.h"


using namespace std;



Paczkomat::Paczkomat(const string &paczkomatId): paczkomatId(paczkomatId), pendingPackages(0){
    cout << skrzynki.size() << endl;
    addSkrzynki(SMALL);
    addSkrzynki(MEDIUM);
    addSkrzynki(LARGE);

    cout << skrzynki.size() << endl;

    cout << "Paczkomat constructed. Name: " << paczkomatId << endl;
}

Paczkomat::~Paczkomat(){
    for (unsigned int i = 0; i < skrzynki.size(); i++){
        delete skrzynki[i];
    }
    cout << "Paczkomat destructed" << endl;
}

void Paczkomat::addSkrzynki(sizeOfPackage size){
    for (int i = 0; i < 10; i++){
        new Skrzynka(size);
        skrzynki.push_back(new Skrzynka(size));
    }
}
