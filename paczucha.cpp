#include "paczucha.h"
#include "enums.h"
#include <iostream>

using namespace std;


Paczucha::Paczucha(sizeOfPackage packageSize, const string &receiverPaczkomat):receiver(receiverPaczkomat),size(packageSize) {
    cout << "Paczucha has been sent. Size: " << size << ", receiver Paczkomat: " << receiver << endl;
}
