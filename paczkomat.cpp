#include <iostream>
#include "paczkomat.h"


using namespace std;



Paczkomat::Paczkomat(const string &paczkomatId, int noOfSmall, int noOfMedium, int noOfLarge): paczkomatId(paczkomatId), pendingPackages(0){

    addSkrzynki(SMALL, noOfSmall);
    addSkrzynki(MEDIUM, noOfMedium);
    addSkrzynki(LARGE, noOfLarge);
    //cout << skrzynki.size() << endl;
    cout << "Paczkomat constructed. Name: " << paczkomatId << endl;
}

Paczkomat::~Paczkomat(){
    for (unsigned int i = 0; i < skrzynki.size(); i++){
        delete skrzynki[i];
    }
    cout << "Paczkomat destructed" << endl;
}

void Paczkomat::addSkrzynki(sizeOfPackage size, int noOfSkrzynki){
    for (int i = 0; i < noOfSkrzynki; i++){
        skrzynki.push_back(new Skrzynka(size));
    }
}

int Paczkomat::getFreeSkrzynka(sizeOfPackage size){
    for (unsigned int i = 0; i < skrzynki.size(); i++){
        if (skrzynki[i]->getSizeOfPackage() == size && skrzynki[i]->isFree()){
            return i;
        }
    }
    return -1;
}

void Paczkomat::storePaczka(int index, Paczucha *newPaczka){
    (*skrzynki[index])>>newPaczka;
    pendingPackages++;
}

int Paczkomat::getReceivingSkrzynka(int collectionCode){
    for (unsigned int i = 0; i < skrzynki.size(); i++){
        if (skrzynki[i]->getCode() == collectionCode){
            return i;
        }
    }
    return -1;
}

Paczucha* Paczkomat::getPaczka (int collectionCode){
    int receivingSkrzynka = getReceivingSkrzynka(collectionCode);
    if (receivingSkrzynka == -1){
        cout << "Your collection code does not match any package" << endl;
        return NULL;
    }
    pendingPackages--;
    cout << "The receiving Skrzynka number is: " << receivingSkrzynka << endl;
    return (*skrzynki[receivingSkrzynka])--;
}

Skrzynka& Paczkomat::operator[] (int index){
    return *skrzynki[index];
}

int Paczkomat::getNumberOfSkrzynkiInSize (sizeOfPackage size){
    int countSkrzynki = 0;
    for (unsigned int i = 0; i < skrzynki.size(); i++){
        if (skrzynki[i]->getSizeOfPackage() == size){
             countSkrzynki++;
        }
    }
    return countSkrzynki;
}



