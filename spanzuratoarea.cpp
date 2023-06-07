#include "spanzuratoarea.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <conio.h>
#include <stdio.h>
#include <windows.h>
#include <fstream>
#include <dos.h>
#define MaxNo_Menu 6

using namespace std;

HANDLE con = GetStdHandle(STD_OUTPUT_HANDLE); //obtine un descriptor de fisier pentru consola

void gotoxy(int x, int y) //pozitia in consola a cursorului
{
    COORD Coord;
    Coord.X = x;
    Coord.Y = y;
    SetConsoleCursorPosition(con, Coord);
}

void textattr(int color)
{
    SetConsoleTextAttribute(con, color); //atributiile textului in consola
}

const int MAXIM_INCERCARI = 6;  //initializez numarul de incercari

int game::introducereLitera(char nimerire, string secretliteraa, string &nimerireliteraa) //verifica daca litera introdusa se afla in cuvantul secret
{
    int i, nimeriri = 0, len = secretliteraa.length();
    for(i = 0; i < len; i++)
    {
        if(nimerire == nimerireliteraa[i])
            return 0;
        if(nimerire == secretliteraa[i])
        {
            nimerireliteraa[i] = nimerire;
            nimeriri++;
        }
    }
    return nimeriri;
}

int get_code() //citire sageti
{
    int ch = getch();
    if(ch == 0 || ch == 224)
        ch = 256 + getch();
    return ch;
}

enum
{
    KEY_ESC = 27,
    ARROW_UP = 256 + 72,
    ARROW_DOWN = 256 + 80,
    ARROW_LEFT = 256 + 75,
    ARROW_RIGHT = 256 + 77
};

char meniu::afisare_meniu()
{
    char op = 'm';
    //ascundere cursor
    HANDLE hConsoleOutput;
    CONSOLE_CURSOR_INFO structCursorInfo;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleCursorInfo(hConsoleOutput, &structCursorInfo);
    structCursorInfo.bVisible = false;
    SetConsoleCursorInfo(hConsoleOutput, &structCursorInfo);
    string menu_list[MaxNo_Menu] = {"\tJOC NOU", "\tINSTRUCTIUNI", "\tDIFICULTATE", "\tMANUAL DE UTILIZARE", "\tINFORMATII AUTOR", "\tIESIRE"};
    int i, xpos = 1, ypos[MaxNo_Menu] = {3, 6, 9, 12, 15, 18};
    //afisez meniul
    for(i = 0; i < MaxNo_Menu; i++)
    {
        gotoxy(xpos, ypos[i]);
        textattr(10);
        cout<<menu_list[i];
    }
    for(i = 1; i < 20; i++) //verticala dreapta
    {
        gotoxy(21, i);
        textattr(1000);
        cout<<"\t\t||\n";
    }
    for(i = 1; i < 20; i++) //verticala stanga
    {
        gotoxy(0, i);
        textattr(1000);
        cout<<"||\n";
    }
    for(i = 0; i < 21; i++) //orizontala sus
    {
        gotoxy(i, 20);
        cout<<"==============\n";
        textattr(1000);
    }
    for(i = 0; i < 21; i++) //orizontala jos
    {
        gotoxy(i, 0);
        cout<<"==============\n";
        textattr(1000);
    }
    textattr(44);
    gotoxy(35, 1);
    //aleg optiuni din meniu
    i = 0;
    while(1)
    {
        gotoxy(xpos, ypos[i]);
        textattr(225);
        cout<<menu_list[i];
        int action;
        switch(action = get_code())
        {
        case ARROW_UP:
            if(i > 0)
            {
                gotoxy(xpos, ypos[i]);
                textattr(14);
                cout<<menu_list[i] ;
                i--;
            }
            break;
        case ARROW_DOWN:
            if(i < MaxNo_Menu - 1)
            {
                gotoxy(xpos, ypos[i]);
                textattr(14);
                cout<<menu_list[i] ;
                i++;
            }
            break;
        case 13:
            if(i == 0)
            {
                gotoxy(20, 7);
                fflush(stdin);
                op = 'A';
                textattr(14);
            }
            if(i == 1)
            {
                gotoxy(20, 7);
                fflush(stdin);
                op = 'I';
                textattr(14);
            }
            if(i == 2)
            {
                gotoxy(20, 7);
                fflush(stdin);
                op = 'D';
                textattr(14);
            }
            if(i == 3)
            {
                gotoxy(20, 7);
                fflush(stdin);
                op = 'M';
                textattr(14);
            }
            if(i == 4)
            {
                gotoxy(20,7);
                fflush(stdin);
                op = 'T';
                textattr(14);
            }
            if(i == 5)
            {
                gotoxy(20, 7);
                fflush(stdin);
                op = 'X';
                gotoxy(20, 21);
                textattr(15);
                exit(0);
            }
            break;
        }
        if(op != 'm')
        {
            system("cls");
            return op;
        }
    }
    return 0;
}

char meniu2::afisare_meniu2()
{
    char op2;
    cout<<"\n\n\n\t\tSunteti sigur ca doriti sa parasiti jocul?:";
    cout<<"\n\t\t\tD-Da";
    cout<<"\n\t\t\tN-Nu"<<endl<<"\t->";
    op2 = toupper(getche());
    return op2;
}

void game::spanzuratoarea(int dif) //transmit prin parametru dificultatea jocului
{
    string name;
    char litera;
    int nr_incercari_nereusite = 0;
    string literaa;
    char gresit[255];  //memorez literele introduse de la tastatura
    int liber = 0;
    string cuvinte_usor[] =
    {
        "mare",
        "universitate",
        "abracadabra",
        "televiziune",
        "oxigen",
        "abecedar",
        "alfabet",
        "inteligenta",
        "electromagnetic",
        "fluorescent",
        "telecomanda",
        "navigatie",
        "electromotor",
        "leopard",
        "management",
        "economie",
        "responsabilitate",
    };
    string cuvinte_mediu[] =
    {
        "abracadabra",
        "televiziune",
        "oxigen",
        "abecedar",
        "temperament",
        "alfabet",
        "inteligenta",
        "electromagnetic",
        "fluorescent",
        "telecomanda",
        "navigatie",
        "electromotor",
        "leopard",
        "decodor",
        "management",
        "economie",
        "responsabilitate",
        "didactic",
        "temperatura",
    };
    string cuvinte_greu[] =
    {
        "sternocleidomastoidian",
        "dezoxiribonucleic",
        "electroglotospectrografie",
        "teleenciclopedie",
        "neinteligibil",
        "schizofrenie",
        "ortopantomografie",
        "lichefiabile",
        "zbenghi",
        "picnomorf",
        "valvulotomie",
        "izdat",
        "turgid",
    };
    srand(time(NULL));
    int n = rand() % 10;
    if(dif == 1)
        literaa = cuvinte_usor[n];
    else if(dif == 2)
        literaa = cuvinte_mediu[n];
    else if(dif == 3)
        literaa = cuvinte_greu[n];
    string unknown(literaa.length(), '-');
    cout<<"\n\n\t\t\t\t SPANZURATOAREA\n";
    cout<<"********************************************************************************";
    cout<<"\nAi "<<MAXIM_INCERCARI<<" incercari sa ghicesti cuvantul.";
    while(nr_incercari_nereusite < MAXIM_INCERCARI)
    {
        cout<<"\n\n\tLitere incercate, gresite: ";
        for(int i = 0; i < liber; i++)
            cout<<gresit[i]<<" ";
        cout<<"\n\n"<<unknown;
        cout<<"\nGhiceste litera: ";
        cin>>litera;
        if(introducereLitera(litera, literaa, unknown) == 0)
        {
            nr_incercari_nereusite++;
            if(nr_incercari_nereusite == 1)
            {
                gresit[liber] = litera;
                liber ++;
                cout<<"\n Litere gresite: "<<litera;
                cout<<endl;
                cout<<"           ";
                cout<<(char)220<<(char)220<<(char)220<<(char)220<<(char)220<<(char)220<<(char)220<<(char)220<<(char)220<<(char)220<<endl;
                cout<<"           ";
                cout<<(char)219;
                cout<<"        ";
                cout<<(char)221;
                cout<<endl;
                cout<<"           ";
                cout<<(char)219;
                cout<<"      o o o"<<endl;
                cout<<"           ";
                cout<<(char)219;
                cout<<"     o * * o"<<endl;
                cout<<"           ";
                cout<<(char)219;
                cout<<"     o  |  o"<<endl;
                cout<<"           ";
                cout<<(char)219;
                cout<<"      o o o"<<endl;
                cout<<"           ";
                cout<<(char)219;
                cout<<"        |"<<endl;
                cout<<"           ";
                cout<<(char)219;
                cout<<"        o"<<endl;
                cout<<"           ";
                cout<<(char)219;
                cout<<"         "<<endl;
                cout<<"           ";
                cout<<(char)219;
                cout<<"         "<<endl;
                cout<<"           ";
                cout<<(char)219;
                cout<<"        "<<endl;
                cout<<"           ";
                cout<<(char)219;
                cout<<"        "<<endl;
                cout<<"           ";
                cout<<(char)219;
                cout<<"        "<<endl;
                cout<<"           ";
                cout<<(char)219;
                cout<<"         "<<endl;
                cout<<"           ";
                cout<<(char)219;
                cout<<"          "<<endl;
                cout<<"           ";
                cout<<(char)219;
                cout<<endl;
                cout<<"           ";
                cout<<(char)219;
                cout<<endl;
                cout<<"           ";
                cout<<(char)219;
                cout<<(char)219;
                cout<<(char)219;
                cout<<(char)219;
                cout<<(char)219;
                cout<<endl;
                cout<<endl<<"Nu ai ghicit!"<<endl;
            }
            if(nr_incercari_nereusite == 2)
            {
                gresit[liber] = litera;
                liber ++;
                system("cls");
                cout<<"\n Litere gresite: "<<litera<<endl;
                cout<<"           ";
                cout<<(char)220<<(char)220<<(char)220<<(char)220<<(char)220<<(char)220<<(char)220<<(char)220<<(char)220<<(char)220<<endl;
                cout<<"           ";
                cout<<(char)219;
                cout<<"        ";
                cout<<(char)221;
                cout<<endl;
                cout<<"           ";
                cout<<(char)219;
                cout<<"      o o o"<<endl;
                cout<<"           ";
                cout<<(char)219;
                cout<<"     o * * o"<<endl;
                cout<<"           ";
                cout<<(char)219;
                cout<<"     o  |  o"<<endl;
                cout<<"           ";
                cout<<(char)219;
                cout<<"      o o o"<<endl;
                cout<<"           ";
                cout<<(char)219;
                cout<<"        |"<<endl;
                cout<<"           ";
                cout<<(char)219;
                cout<<"        o"<<endl;
                cout<<"           ";
                cout<<(char)219;
                cout<<"        o"<<endl;
                cout<<"           ";
                cout<<(char)219;
                cout<<"        o  "<<endl;
                cout<<"           ";
                cout<<(char)219;
                cout<<"        o"<<endl;
                cout<<"           ";
                cout<<(char)219;
                cout<<"        o"<<endl;
                cout<<"           ";
                cout<<(char)219;
                cout<<"        "<<endl;
                cout<<"           ";
                cout<<(char)219;
                cout<<"        "<<endl;
                cout<<"           ";
                cout<<(char)219;
                cout<<"         "<<endl;
                cout<<"           ";
                cout<<(char)219;
                cout<<endl;
                cout<<"           ";
                cout<<(char)219;
                cout<<endl;
                cout<<"           ";
                cout<<(char)219;
                cout<<(char)219;
                cout<<(char)219;
                cout<<(char)219;
                cout<<(char)219;
                cout<<endl;
                cout<<endl<<"Nu ai ghicit!"<<endl;
            }
            if(nr_incercari_nereusite == 3)
            {
                gresit[liber] = litera;
                liber ++;
                system("cls");
                cout<<"           ";
                cout<<(char)220<<(char)220<<(char)220<<(char)220<<(char)220<<(char)220<<(char)220<<(char)220<<(char)220<<(char)220<<endl;
                cout<<"           ";
                cout<<(char)219;
                cout<<"        ";
                cout<<(char)221;
                cout<<endl;
                cout<<"           ";
                cout<<(char)219;
                cout<<"      o o o"<<endl;
                cout<<"           ";
                cout<<(char)219;
                cout<<"     o * * o"<<endl;
                cout<<"           ";
                cout<<(char)219;
                cout<<"     o  |  o"<<endl;
                cout<<"           ";
                cout<<(char)219;
                cout<<"      o o o"<<endl;
                cout<<"           ";
                cout<<(char)219;
                cout<<"        |"<<endl;
                cout<<"           ";
                cout<<(char)219;
                cout<<"        o"<<endl;
                cout<<"           ";
                cout<<(char)219;
                cout<<"     oooo"<<endl;
                cout<<"           ";
                cout<<(char)219;
                cout<<"     o  o  "<<endl;
                cout<<"           ";
                cout<<(char)219;
                cout<<"        o"<<endl;
                cout<<"           ";
                cout<<(char)219;
                cout<<"        o"<<endl;
                cout<<"           ";
                cout<<(char)219;
                cout<<"        o"<<endl;
                cout<<"           ";
                cout<<(char)219;
                cout<<"        "<<endl;
                cout<<"           ";
                cout<<(char)219;
                cout<<"          "<<endl;
                cout<<"           ";
                cout<<(char)219;
                cout<<endl;
                cout<<"           ";
                cout<<(char)219;
                cout<<endl;
                cout<<"           ";
                cout<<(char)219;
                cout<<(char)219;
                cout<<(char)219;
                cout<<(char)219;
                cout<<(char)219;
                cout<<endl;
                cout<<endl<<"Nu ai ghicit!"<<endl;
            }
            if(nr_incercari_nereusite == 4)
            {
                gresit[liber] = litera;
                liber ++;
                system("cls");
                cout<<"           ";
                cout<<(char)220<<(char)220<<(char)220<<(char)220<<(char)220<<(char)220<<(char)220<<(char)220<<(char)220<<(char)220<<endl;
                cout<<"           ";
                cout<<(char)219;
                cout<<"        ";
                cout<<(char)221;
                cout<<endl;
                cout<<"           ";
                cout<<(char)219;
                cout<<"      o o o"<<endl;
                cout<<"           ";
                cout<<(char)219;
                cout<<"     o * * o"<<endl;
                cout<<"           ";
                cout<<(char)219;
                cout<<"     o  |  o"<<endl;
                cout<<"           ";
                cout<<(char)219;
                cout<<"      o o o"<<endl;
                cout<<"           ";
                cout<<(char)219;
                cout<<"        |"<<endl;
                cout<<"           ";
                cout<<(char)219;
                cout<<"        o"<<endl;
                cout<<"           ";
                cout<<(char)219;
                cout<<"     ooooooo"<<endl;
                cout<<"           ";
                cout<<(char)219;
                cout<<"     o  o  o"<<endl;
                cout<<"           ";
                cout<<(char)219;
                cout<<"        o"<<endl;
                cout<<"           ";
                cout<<(char)219;
                cout<<"        o"<<endl;
                cout<<"           ";
                cout<<(char)219;
                cout<<"        o"<<endl;
                cout<<"           ";
                cout<<(char)219;
                cout<<"         "<<endl;
                cout<<"           ";
                cout<<(char)219;
                cout<<"          "<<endl;
                cout<<"           ";
                cout<<(char)219;
                cout<<endl;
                cout<<"           ";
                cout<<(char)219;
                cout<<endl;
                cout<<"           ";
                cout<<(char)219;
                cout<<(char)219;
                cout<<(char)219;
                cout<<(char)219;
                cout<<(char)219;
                cout<<endl;
                cout<<endl<<"Nu ai ghicit!"<<endl;
            }
            if(nr_incercari_nereusite == 5)
            {
                gresit[liber] = litera;
                liber ++;
                system("cls");
                cout<<"           ";
                cout<<(char)220<<(char)220<<(char)220<<(char)220<<(char)220<<(char)220<<(char)220<<(char)220<<(char)220<<(char)220<<endl;
                cout<<"           ";
                cout<<(char)219;
                cout<<"        ";
                cout<<(char)221;
                cout<<endl;
                cout<<"           ";
                cout<<(char)219;
                cout<<"      o o o"<<endl;
                cout<<"           ";
                cout<<(char)219;
                cout<<"     o * * o"<<endl;
                cout<<"           ";
                cout<<(char)219;
                cout<<"     o  |  o"<<endl;
                cout<<"           ";
                cout<<(char)219;
                cout<<"      o o o"<<endl;
                cout<<"           ";
                cout<<(char)219;
                cout<<"        |"<<endl;
                cout<<"           ";
                cout<<(char)219;
                cout<<"        o"<<endl;
                cout<<"           ";
                cout<<(char)219;
                cout<<"     ooooooo"<<endl;
                cout<<"           ";
                cout<<(char)219;
                cout<<"     o  o  o"<<endl;
                cout<<"           ";
                cout<<(char)219;
                cout<<"        o"<<endl;
                cout<<"           ";
                cout<<(char)219;
                cout<<"        o"<<endl;
                cout<<"           ";
                cout<<(char)219;
                cout<<"        o"<<endl;
                cout<<"           ";
                cout<<(char)219;
                cout<<"      o   "<<endl;
                cout<<"           ";
                cout<<(char)219;
                cout<<"     o     "<<endl;
                cout<<"           ";
                cout<<(char)219;
                cout<<endl;
                cout<<"           ";
                cout<<(char)219;
                cout<<endl;
                cout<<"           ";
                cout<<(char)219;
                cout<<(char)219;
                cout<<(char)219;
                cout<<(char)219;
                cout<<(char)219;
                cout<<endl;
                cout<<endl<<"Nu ai ghicit!"<<endl;
            }
            if(nr_incercari_nereusite == MAXIM_INCERCARI)
            {
                gresit[liber] = litera;
                liber ++;
                system("cls");
                cout<<"           ";
                cout<<(char)220<<(char)220<<(char)220<<(char)220<<(char)220<<(char)220<<(char)220<<(char)220<<(char)220<<(char)220<<endl;
                cout<<"           ";
                cout<<(char)219;
                cout<<"        ";
                cout<<(char)221;
                cout<<endl;
                cout<<"           ";
                cout<<(char)219;
                cout<<"      o o o"<<endl;
                cout<<"           ";
                cout<<(char)219;
                cout<<"     o x x o"<<endl;
                cout<<"           ";
                cout<<(char)219;
                cout<<"     o  |  o"<<endl;
                cout<<"           ";
                cout<<(char)219;
                cout<<"      o o o"<<endl;
                cout<<"           ";
                cout<<(char)219;
                cout<<"        |"<<endl;
                cout<<"           ";
                cout<<(char)219;
                cout<<"        o"<<endl;
                cout<<"           ";
                cout<<(char)219;
                cout<<"     ooooooo"<<endl;
                cout<<"           ";
                cout<<(char)219;
                cout<<"     o  o  o"<<endl;
                cout<<"           ";
                cout<<(char)219;
                cout<<"        o"<<endl;
                cout<<"           ";
                cout<<(char)219;
                cout<<"        o"<<endl;
                cout<<"           ";
                cout<<(char)219;
                cout<<"        o"<<endl;
                cout<<"           ";
                cout<<(char)219;
                cout<<"      o   o"<<endl;
                cout<<"           ";
                cout<<(char)219;
                cout<<"     o     o"<<endl;
                cout<<"           ";
                cout<<(char)219;
                cout<<endl;
                cout<<"           ";
                cout<<(char)219;
                cout<<endl;
                cout<<"           ";
                cout<<(char)219;
                cout<<(char)219;
                cout<<(char)219;
                cout<<(char)219;
                cout<<(char)219;
                cout<<endl;
                cout<<endl<<"Nu ai ghicit!"<<endl;
            }
        }
        else
        {
            system("cls");
            cout<<endl<<"FELICITARI, AI GHICIT!!!"<<endl;
        }
        cout<<"Mai ai "<<MAXIM_INCERCARI - nr_incercari_nereusite;
        cout<<" incercari ramase."<<endl;
        if(literaa == unknown)
        {
            cout<<"AI REUSIT!"<<endl;
            cout<<"Cuvantul era: "<<literaa<<endl;
            break;
        }
    }
    if(nr_incercari_nereusite == MAXIM_INCERCARI)
    {
        cout<<"\nAI FOST SPANZURAT!"<<endl;
        cout<<"Cuvantul era: "<<literaa<<endl;
    }
    cin.ignore();
    cin.get();
    system("cls");
    meniu();
}

void joc::start_joc()
{
    int executaOptiuneAlegeDificultate = 0;
    int corect = 1;
    char op, op2;
    do
    {
        int dif;
        char buff[3];
        system("cls");
        meniu menu;
        op = menu.afisare_meniu();
        switch(op)
        {
        case 'A':
            if(executaOptiuneAlegeDificultate == 1)
                spanzuratoarea(dif);
            else
                cout<<"\n\t\tAlegeti mai intai un nivel de dificultate!";
            break;
        case 'I':
            cout<<"\n\t\t\t\tINSTRUCTIUNI"
                "\n\n\n\t\tTrebuie sa ghicesti un cuvant, sau mai multe, prin incercari succesive de litere. "
                "In\n\tmod clasic se juca pe o foaie de hartie impotriva unui prieten, dar aici poti juca impotriva\n\tcalculatorului, folosind dictionare din mai multe categorii. "
                "Dupa fiecare incercare, litera\n\tselectata se inlocuieste automat in interiorul cuvantului, sau in caz de esec se completeza\n\tdesenul. "
                "Daca gresesti de mai mult de 6 ori, calculatorul te spanzura.\n\n\t\tSucces!"<<endl;
            break;
        case 'D':
            cout<<endl;
            cout<<"\n\tAlegeti dificultatea: "<<endl;
            cout<<"\t\t\t1 -> usor\n\t\t\t2 -> mediu\n\t\t\t3 -> greu\n\t\t\t\t\t-->";
            fflush(stdin);
            cin.getline(buff, 3, '\n');
            if(atoi(buff) == 1)
                dif = 1;
            else
            {
                if(atoi(buff) == 2)
                    dif = 2;
                else
                {
                    if(atoi(buff) == 3)
                        dif = 3;
                    else
                    {
                        cout<<"\n\t\tOptiunea introdusa nu exista! Se revine la meniu!";
                        corect = 0;
                    }
                }
            }
            if(corect == 1)
                executaOptiuneAlegeDificultate = 1;
            break;
        case 'M':
            cout<<"\n\t\t\t\tMANUAL DE UTILIZARE"
                "\n\n\n\t\tPentru a incepe un joc nou, selectati JOC NOU. "
                "In momentul cand selectati JOC NOU,\n\tva aparea un mesaj: "
                "'Alegeti mai intai un nivel de dificultate'. "
                "Pentru a face acest lucru\n\tselectati DIFICULTATE, unde aveti posibilitatea de a alege un nivel de dificultate din cele\n\ttrei posibilitati. "
                "Dupa ce ati ales dificultatea, incepeti un JOC NOU. "
                "Deasemenea aveti\n\tposibilitateade a citi instructiunile jocului. "
                "Pentru a vedea date despre autorul acestui\n\tjoc selectati INFORMATII AUTOR. "
                "In momentul in care doriti sa iesiti din joc selectati\n\tIESIRE, unde tot odata aveti posibilitatea sa va razganditi."<<endl;
            break;
        case 'T':
            cout<<"\n\tInformatii autor:"
                "\n\t\t-Student: Adochitei Alexandru."
                "\n\t\t-An studiu: II"
                "\n\t\t-Specializare: Calculatoare."
                "\n\t\t-Grupa: 3121 A "<<endl;
            break;
        case 'X':
            bool boolD;
            boolD = true;
            while(boolD)
            {
                meniu2 menu2;
                op2 = menu2.afisare_meniu2();
                switch(op2)
                {
                case 'D':
                    exit(0);
                case 'N':
                    system("cls");
                    cout<<"\n Continuati sa jucati.";
                    boolD = false;
                }
            }
            break;
        default:
            cout<<"\n\n\tAlegere incorecta.";
            cout<<"\n\tApasati ENTER pentru a continua.";
            getchar();
            system("cls");
            meniu();
        }
        getch();
    }
    while(1);
}
