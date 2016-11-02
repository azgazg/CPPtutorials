#include <iostream>
#include "skrzynka.h"

using namespace std;


Skrzynka::Skrzynka(sizeOfPackage packageSize): size(packageSize), paczka(NULL){
    cout<< "Skrzynka created, size :" << size << endl;
}

Skrzynka::~Skrzynka(){
    cout<< "Skrzynka deleted, size :" << size << endl;
}
