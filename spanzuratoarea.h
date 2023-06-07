#ifndef SPANZURATOAREA_H
#define SPANZURATOAREA_H
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <conio.h>

using namespace std;

class game
{
public:
    int introducereLitera(char, string, string &);
    void spanzuratoarea(int dif);
};

class meniu
{
public:
    char afisare_meniu();
};

class meniu2
{
public:
    char afisare_meniu2();
};

class joc : public game
{
public:
    void start_joc();
};

#endif // SPANZURATOAREA_H
