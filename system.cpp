#include <iostream>
#include "system.h"
#include "enums.h"
#include <cassert>


using namespace std;

enum {
    NOT_VALID = 0,
    LIST,
    DELETE,
    CREATE,
    RECEIVE,
    SEND,
    EXIT
};

System::System(): paczkomat(), freeIndex(0){
    cout << "Constructed" << endl;
}

System::~System(){
    for (int i = 0; i < freeIndex; i++){
        delete  paczkomat[i];
    }
    cout << "Destructed" << endl;

}
void System::run(){
    cout << "Welcome to Paczkomat system 1.0 Copyright Anna Gernand" << endl;
    cout << "\n" << endl;
    int userChoice = NOT_VALID;

    do{
        userChoice = getUserChoice();

        if (userChoice == CREATE){
            createPaczkomat();
        }else if (userChoice == LIST){
            listPaczkomats();
        }else if (userChoice == DELETE){
            deletePaczkomat();
        }else if (userChoice == SEND){
            sendPackage();
        }

    }while(userChoice != EXIT);

}

int System::getUserChoice(){
    cout << "\n" << endl;
    cout << "OPTIONS: " << endl;
    cout << "1 - List available Paczkomats (" << freeIndex  <<  "/" << MAX_PACZKOMAT << ")" << endl;
    cout << "2 - Delete a paczkomat" << endl;
    cout << "3 - Create a new paczkomat" << endl;
    cout << "4 - Receive a package (pending packages: " << getNoOfPendingPackages() <<  ")" << endl;
    cout << "5 - Send a package" << endl;
    cout << "6 - Exit" << endl;

    int userChoice;
    cin >> userChoice;
    while (cin.fail() || (userChoice > EXIT || userChoice < LIST)) {
        cin.clear(); // put us back in 'normal' operation mode
        cin.ignore(32767,'\n'); // and remove the bad input
        cout  << "You have chosen unsupported option, please try again: " << endl;
        cin >> userChoice;
    }
    return userChoice;
}



int System::getNoOfPendingPackages(){
    int sumOfPendingPackages = 0;
    for (int i = 0; i < freeIndex; i++){
        sumOfPendingPackages += paczkomat[i]->getPendingPackagesInPaczkomat();
    }
    return sumOfPendingPackages;
}

void System::createPaczkomat(){
    if (freeIndex == MAX_PACZKOMAT ){
        cout << "\n" << endl;
        cout << "You have reached the maximum available number of Paczkomats. You cannot create new one." << endl;
        cout << "\n" << endl;
        return;
    }

    cout << "Enter the name of new Paczkomat: " << endl;
    string paczkomatId;
    cin.ignore(32767, '\n');
    getline(cin,paczkomatId);
    for (int i=0; i < freeIndex; i++){
        if (paczkomat[i]->getPaczkomatId() == paczkomatId){
            cout << "This name " << paczkomatId << " is already used" << endl;
            cout << "\n" << endl;
            return;
        }
    }
    paczkomat[freeIndex++] = new Paczkomat(paczkomatId);
}

void System::listPaczkomats(){
    if (freeIndex == 0){
        cout << "\n" << endl;
        cout << "There are no Paczkomats created yet." << endl;
        cout << "\n" << endl;
        return;
    }
    cout << "\n" << endl;
    cout << "List of existing paczkomats:" << endl;
    for (int i = 0; i < freeIndex; i++){
        cout << i+1 << ") " << paczkomat[i]->getPaczkomatId() << " (pending: " << paczkomat[i]->getPendingPackagesInPaczkomat()  << ")" << endl;

    }


}

void System::deletePaczkomat(){
    listPaczkomats();
    if (freeIndex > 0){
        cout << "Choose the number between 1 and " << freeIndex << endl;
        int userChoice;
        cin >> userChoice;
        while (cin.fail() || (userChoice <= 0 || userChoice > freeIndex)) {
            cin.clear(); // put us back in 'normal' operation mode
            cin.ignore(32767,'\n'); // and remove the bad input
            cout  << "You have chosen unsupported option, please try again: " << endl;
            cin >> userChoice;
        }
        delete paczkomat[userChoice-1];
        freeIndex--;
        paczkomat[userChoice-1] = paczkomat[freeIndex];
        paczkomat[freeIndex] = NULL;
    }
}

int System::getPackageSize(){
    cout << "What size is your package? (0 - SMALL, 1 - MEDIUM, 2 - LARGE)" << endl;
    int userChoice;
    cin >> userChoice;
    while (cin.fail() || (userChoice > LARGE || userChoice < SMALL)) {
        cin.clear(); // put us back in 'normal' operation mode
        cin.ignore(32767,'\n'); // and remove the bad input
        cout  << "You have chosen unsupported option, please try again: " << endl;
        cin >> userChoice;
    }
    return userChoice;
}

void System::sendPackage(){
    cout << "Where do you want to sent the package from (choose number)?" << endl;
    listPaczkomats();
    int sendingPaczkomat;
    cin >> sendingPaczkomat;
    int package;
    package = getPackageSize();
    sizeOfPackage packageSize;
    if (package == 0){
        packageSize = SMALL;
    }else if (package == 1){
        packageSize = MEDIUM;
    }else if (package ==2){
        packageSize = LARGE;
    }

    //check if in given Paczkomat there is a free place of given size
    //if there is a place get information where to send this package
    cout << "Where do you want to send the package to?" << endl;
    listPaczkomats();
    string receiverPaczkomat;
    cin.ignore(32767, '\n');
    getline(cin,receiverPaczkomat);
    Paczucha paczka(packageSize, receiverPaczkomat);

}


