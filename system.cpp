#include <iostream>
#include "system.h"
#include "enums.h"
#include <cassert>
#include "paczkomat.h"
#include <fstream>
#include <stdlib.h>
#include <string.h>

using namespace std;

enum {
    NOT_VALID = 0,
    LIST,
    DELETE,
    CREATE,
    RECEIVE,
    SEND,
    LIST_S,
    LOAD_FROM_FILE,
    WRITE_TO_FILE,
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
        }else if (userChoice == RECEIVE){
            receivePackage();
        }else if (userChoice == LIST_S){
            listSkrzynki();
        }else if (userChoice == LOAD_FROM_FILE){
            string path;
            cout << "Which file do you want to load (provide file path)?" << endl;
            cin.ignore(32767, '\n');
            getline(cin,path);
            loadFromFile(path.c_str());
        }else if (userChoice == WRITE_TO_FILE){
            writeToFile();
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
    cout << "6 - List Skrzynki in Paczkomat" << endl;
    cout << "7 - Create Paczkomats from file" << endl;
    cout << "8 - Save existing Paczkomats in a new file" << endl;
    cout << "9 - Exit" << endl;

    return getInt(EXIT, LIST);
}

void System::loadFromFile(const char *filePath){
    ifstream inf(filePath);
    cout << inf << endl;
    if (!inf){
        // Print an error and exit
        cout << "Uh oh, " << filePath << " could not be opened for reading!" << endl;
        return;
    }
    while (inf){
        // read stuff from the file into a string and print it
        string strInput;
        inf >> strInput;
        if (strInput.length() != 0){
            const string &name = strInput.substr (0, strInput.find(":"));
            const string &numbers = strInput.substr (strInput.find(":")+1);
            char c_numbers[10];
            strcpy (c_numbers, numbers.c_str());
            char* number = strtok (c_numbers, ",");
            vector<int> int_vector;
            while (number != NULL){
                int i_number = atoi(number);
                int_vector.push_back(i_number);
                number = strtok (NULL, ",");
            }
            if (int_vector.size() == 3 && name.length() > 0){
                createPaczkomat(name, int_vector[0], int_vector[1], int_vector[2]);
            }
        }
    }
}

int System::getInt(int max, int min){
    int userChoice;
    cin >> userChoice;
    while (cin.fail() || (userChoice > max || userChoice < min)) {
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

void System::createPaczkomat(const string &name, int noOfSmall, int noOfMedium, int noOfLarge){
    bool isFromFile = name.length();

    if (freeIndex == MAX_PACZKOMAT ){
        cout << "\n" << endl;
        cout << "You have reached the maximum available number of Paczkomats. You cannot create new one." << endl;
        cout << "\n" << endl;
        return;
    }
    if (!isFromFile){
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
        noOfSmall = getNoOfSkrzynki("small");
        noOfMedium = getNoOfSkrzynki("medium");
        noOfLarge = getNoOfSkrzynki("large");
        paczkomat[freeIndex++] = new Paczkomat(paczkomatId, noOfSmall, noOfMedium, noOfLarge);
    }else{
        for (int i=0; i < freeIndex; i++){
            if (paczkomat[i]->getPaczkomatId() == name){
                cout << "This name " << name << " is already used" << endl;
                cout << "\n" << endl;
                return;
            }
        }
        paczkomat[freeIndex++] = new Paczkomat(name, noOfSmall, noOfMedium, noOfLarge);
    }


}

int System::getNoOfSkrzynki(const char *sizeOf){
    cout << "Enter the number of " << sizeOf << " Skrzynki:" << endl;
    return getInt(Paczkomat::MAX_NO_OF_SKRZYNKI, 1);
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
        cout << i+1 << ") " << paczkomat[i]->getPaczkomatId() << " (pending: " << paczkomat[i]->getPendingPackagesInPaczkomat()  << ")";
        cout << " S: " << paczkomat[i]->getNumberOfSkrzynkiInSize(SMALL);
        cout << " M: " << paczkomat[i]->getNumberOfSkrzynkiInSize(MEDIUM);
        cout << " L: " << paczkomat[i]->getNumberOfSkrzynkiInSize(LARGE) << endl;
    }
}

void System::writeToFile(){
        cout << "Enter the name of file:" << endl;
        cin.ignore(32767, '\n');
        string fileName;
        getline(cin,fileName);
        ofstream outf(fileName);
        if (!outf){
            // Print an error and exit
            cout << "Uh oh, Sample.dat could not be opened for writing!" << endl;
            return;
        }
        for (int i = 0; i < freeIndex; i++){
            outf << paczkomat[i]->getPaczkomatId() << ":" ;
            outf << paczkomat[i]->getNumberOfSkrzynkiInSize(SMALL) << "," ;
            outf << paczkomat[i]->getNumberOfSkrzynkiInSize(MEDIUM) << "," ;
            outf << paczkomat[i]->getNumberOfSkrzynkiInSize(LARGE) << endl;
        }
}

void System::deletePaczkomat(){
    listPaczkomats();
    if (freeIndex > 0){
        cout << "Choose the number between 1 and " << freeIndex << endl;
        int userChoice = getInt(freeIndex, 1);
        delete paczkomat[userChoice-1];
        freeIndex--;
        paczkomat[userChoice-1] = paczkomat[freeIndex];
        paczkomat[freeIndex] = NULL;
    }
}

sizeOfPackage System::getPackageSize(){
    cout << "What size is your package? (0 - SMALL, 1 - MEDIUM, 2 - LARGE)" << endl;
    return static_cast<sizeOfPackage>(getInt(LARGE, SMALL));
}

void System::sendPackage(){
    listPaczkomats();
    if (freeIndex == 0){
        return;
    }
    cout << "Where do you want to send the package to ?" << endl;
    int receiverPaczkomat = getInt(freeIndex, 1);
    sizeOfPackage packageSize = getPackageSize();

    cout << paczkomat[receiverPaczkomat-1]->getPaczkomatId() << endl;

    cout << paczkomat[receiverPaczkomat-1]->getFreeSkrzynka(packageSize) << endl;
    int freeIndex = paczkomat[receiverPaczkomat-1]->getFreeSkrzynka(packageSize);
    if (freeIndex != -1){
        Paczucha *newPaczka = new Paczucha (packageSize, paczkomat[receiverPaczkomat-1]->getPaczkomatId());
        paczkomat[receiverPaczkomat-1]->storePaczka(freeIndex, newPaczka);
    }else{
        cout << "There are no free Skrzynka in Paczkomat " << paczkomat[receiverPaczkomat-1]->getPaczkomatId() << endl;
    }
}

void System::receivePackage(){
    listPaczkomats();
    if( freeIndex == 0){
        return;
    }
    cout << "Which Paczkomat you want to collect package from?" << endl;
    int receiverPaczkomat = getInt(freeIndex, 1);
    cout << "Enter the code to collect the package" << endl;
    int collectionCode;
    cin.ignore(32767, '\n');
    cin >> collectionCode;
    Paczucha *collectedPaczka = paczkomat[receiverPaczkomat-1]->getPaczka(collectionCode);
    if (collectedPaczka == NULL){
        return;
    }
    cout << "Package has been collected from Paczkomat: " << collectedPaczka->getReceiverId() << " Tha package size is: " <<   collectedPaczka->getSize() << endl;
    delete collectedPaczka;
}

void System::listSkrzynki(){
    listPaczkomats();
    cout << "Which Paczkomat you want to list from?" << endl;
    int receiverPaczkomat = getInt(freeIndex, 1);
    Paczkomat &p = *paczkomat[receiverPaczkomat-1];
    int numberOfSkrzynki = p.getNumberOfSkrzynki();
    for (int i = 0; i < numberOfSkrzynki; i++){
        cout << p.getPaczkomatId() << ": skrzynka[" << i << "] size[" << p[i].getSizeOfPackage()  << "] " ;
        if(p[i].isFree()){
            cout << "free";
        }else{
            cout << "code: " << p[i].getCode();
        }
        cout << endl;
    }
}



