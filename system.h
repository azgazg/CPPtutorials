#ifndef SYSTEM_H_INCLUDED
#define SYSTEM_H_INCLUDED

#include "paczkomat.h"
#include "paczucha.h"


class System{
    static const int MAX_PACZKOMAT = 100;
    Paczkomat *paczkomat[MAX_PACZKOMAT];
    int freeIndex;


public:
    System();
    ~System();
    void run();
    void loadFromFile(const char *filePath);



private:
    int getUserChoice();
    int getNoOfPendingPackages();
    void createPaczkomat(const string &name = "", int noOfSmall = 0, int noOfMedium = 0, int noOfLarge = 0);
    void listPaczkomats();
    void deletePaczkomat();
    void sendPackage();
    sizeOfPackage getPackageSize();
    void receivePackage();
    void listSkrzynki();
    int getNoOfSkrzynki(const char *sizeOf);
    int getInt(int min, int max);
    void writeToFile();

};


#endif // SYSTEM_H_INCLUDED
