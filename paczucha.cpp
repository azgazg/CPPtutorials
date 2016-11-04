#include "paczucha.h"
#include "enums.h"
#include <iostream>

using namespace std;


Paczucha::Paczucha(sizeOfPackage packageSize, const string &receiver):size(packageSize), receiver(receiver) {
    cout << "Paczucha has been created. Size: " << size << "receiver Paczkomat: " <<  receiver << endl;
}

Paczucha::~Paczucha(){
    cout << "Paczucha has been deleted " << endl;
}
