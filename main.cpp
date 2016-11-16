#include "system.h"
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
    System system;

    cout << argc << endl;
    for (int i = 1; i < argc; i++){
        cout << argv[i] << endl;
        system.loadFromFile(argv[i]);
    }

    system.run();

    return 0;
}
