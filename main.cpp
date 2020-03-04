#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <cstdlib>

typedef struct book
{

       char tytul[100], imie_aut[100], nazw_aut[100], kategoria[100], imie_wyp[100], nazw_wyp[100], inne[100];
       int ID, status;
       struct date
       {int dzien, miesiac, rok; }D;
       struct book* next;
       struct book* prev;
} book ;
book *head = NULL;
book *tail = NULL;
book *element = NULL;


//FUNKCJE
void menu();
void dodaj();
void dodaj2(book *wsk);
void wyswietlij();
void wyswietlOne();
void wyswietlTyt();
void wyswietlWyp();
void usun();   // naprawic bledy
void zmien();
int idfun();
void idNew();
int zmienStatus();
void zapisz();
void odczytaj();
void odczytaj2();
void freeFile();



int main()
{
    char option;

    while(option!= 'X')
    {
        menu();     fflush(stdin);     scanf("%c", &option);


        switch(option)          // poprawic, przy zmianie na char przestaje czesc dzialac)
        {
        case '1':            dodaj();            idNew();     break;
        case '2':            usun();             idNew();     break;
        case '3':            zmien();            idNew();     break;
        case '4':            zmienStatus();      idNew();     break;
        case '5':            wyswietlOne();      idNew();     break;
        case '6':            wyswietlTyt();      idNew();     break;
        case '7':            wyswietlWyp();      idNew();     break;
        case '8':            zapisz();           idNew();     break;
        case '9':            odczytaj2();         idNew();     break;
        case 'T':            wyswietlij();       idNew();     break;       //for testing
        case 'X' :           return 0;
        default:;
        }
        /*if(option !=( '1' || '2' || '3' || '4' || '5' || '6' || '7' || '8' || '9' || 'T' || 'X')) // wyskakuje nie tylko gdzie trzeba
            printf("\n\nOpcja ma byc liczba od 1 do 9 lub X, sproboj ponownie.\n\n");
        dodac pozniej*/
    }
    return 0;
}



void menu()
{
    printf("\n\n***MENU***\n");
    printf("1) Dodaj nowa ksiazke\n");
    printf("2) Usun ksiazke\n");
    printf("3) Edytuj dane ksiazki\n");
    printf("4) Zmien status ksiazki.\n");
    printf("5) Wyszukaj ksiazke\n");
    printf("6) Wyswietl baze po tytulach\n");
    printf("7) Wyswietl ksiazki wypozyczone\n");
    printf("8) Zapisz do pliku\n");
    printf("9) Odczytaj z pliku\n");
    printf("T) TEST - PRINT ALL FROM LIST\n");
    printf("X) Koniec pracy\n");
    printf("\n Wybierz opcje: ");
}

void dodaj()
{
    book *wsk;

    if(head==NULL) //jesli lista pusta
    {
        //printf("\nCASE i\n");
        head = (book*)malloc(sizeof(book));
        head->next = NULL;
        head->prev = NULL;
        tail = head;
        wsk = head;

    }
    else if(head!=NULL)
    {
        //printf("\nCASE ii\n");
        wsk = head;
        wsk = (book*)malloc(sizeof(book));
        while(wsk->next!=NULL)
        {
            wsk=wsk->next;
        }
        wsk->next = NULL;
        wsk->prev = tail;
        tail->next = wsk;
        tail = wsk;
    }


    wsk->ID = idfun();
    fflush(stdin);  printf("Podaj tytul: ");                                        scanf("%100[0-9a-zA-Z ]", wsk->tytul);

    fflush(stdin);  printf("Podaj imie autora: ");                                  scanf("%100[0-9a-zA-Z ]", wsk->imie_aut);
    fflush(stdin);  printf("Podaj nazwisko autora: ");                              scanf("%100[0-9a-zA-Z ]", wsk->nazw_aut);
    fflush(stdin);  printf("Podaj kategorie: ");                                    scanf("%100[0-9a-zA-Z ]", wsk->kategoria);

    printf("Podaj status ksiazki |1|-nie wypoz. |0|-wypoz.: ");
    char st;    fflush(stdin);  scanf("%c", &st);
    while((st!='1')&&(st!='0')){   printf("\nPodano nieprawidlowa opcje. Sproboj ponownie |1|-nie wypoz. |0|-wypoz.: "); fflush(stdin);  scanf("%c", &st); }
    if(st == '1')        wsk->status = 1;
    else if(st == '0')   wsk->status = 0;

    if(wsk->status == 0)
    {
        fflush(stdin);  printf("Podaj date wypozyczania. \nDzien: ");                   scanf("%d", &wsk->D.dzien);
        fflush(stdin);  printf("Miesiac: ");                                            scanf("%d", &wsk->D.miesiac);
        fflush(stdin);  printf("Rok: ");                                                scanf("%d", &wsk->D.rok);
        fflush(stdin);  printf("Podaj imie wypoz.: ");                                  scanf("%100[0-9a-zA-Z ]", wsk->imie_wyp);
        fflush(stdin);  printf("Podaj nazwisko wypoz.: ");                              scanf("%100[0-9a-zA-Z ]", wsk->nazw_wyp);
    }
    else ;
    fflush(stdin);  printf("Podaj dodatkowa informacje, |ENTER| jezeli nie ma: ");        scanf("%100[0-9a-zA-Z ]", wsk->inne);
    printf("\nChcesz dodac jeszcze ? |1=Tak| |2=Nie| : ");
    char op;  fflush(stdin);  scanf("%c", &op);
    while((op != '1') && (op != '2'))
    {
        printf("\nOpcja mozy byc tylko |1=Tak| lub |2=Nie|. sprobuj ponownie: ");
        fflush(stdin);  scanf("%c", &op);
    }
    switch(op)
    {
    case '1':        dodaj();        break;
    case '2':        break;
    default:;
    }
}

void wyswietlij()
{
    book *wsk;
    wsk = head;
    if(wsk == NULL)  printf("\nLista pusta");


    while(wsk != NULL)
    {
        printf("\n| ^\nv |\n");
        printf("\nNr indexu ksiazki: %d", wsk->ID);
        printf("\nTytul: %s", wsk->tytul);
        printf("\nStatus: %d", wsk->status);
        printf("\nAutor: %s %s", wsk->imie_aut, wsk->nazw_aut);
        printf("\nKategoria: %s", wsk->kategoria);
        printf("\nData wypozyczania %d/%d/%d",wsk->D.dzien,wsk->D.miesiac,wsk->D.rok);
        printf("\nWypozyczyl: %s %s", wsk->imie_wyp, wsk->nazw_wyp);
        printf("\nDodatkowa informacja: %s\n\n", wsk->inne);

        wsk=wsk->next;
    }

}
void usun()
{
    book *wsk;
    wsk = head;
    char delName[100];        int IDdel;
    if(head == NULL)
        printf("\nLista pusta.");
    else
    {
        printf("\nJezeli chcesz usuwac po ID wcisniej 1, po tytule - 2, powrot do menu - 3: ");
        char op; fflush(stdin); scanf("%c", &op);                                                        //some problem
        while((op != '1') && (op != '2') && (op != '3'))
        {
            printf("\n Wybrales nie istniejaca opcje. Sprobuj ponownie:  ");   //zrobic zabezpieczenie przed nieliczbami
            scanf("%d", &op);
        }
        switch(op)
            {
            case '1':

                fflush(stdin);      printf("\nPodaj ID: ");          scanf("%d", &IDdel);
                while(wsk!= NULL)
                {
                     if(wsk->ID == IDdel)
                        {
                            printf("\nUsuwam ksiazke. ");
                            if(tail->prev == tail->next) //poczatek
                            {
                                printf("\nCase i.i\n");
                                head = NULL;
                                free(tail);
                                wsk = wsk->next;
                            }
                            else if(wsk->prev == NULL) // 1 element
                            {
                                printf("\nCase i.iii\n");
                                head = wsk->next;
                                wsk->next->prev = NULL;
                                free(wsk);
                                wsk = wsk->next;
                            }
                            else if(wsk->prev!=NULL && wsk->next==NULL) // koniec
                            {
                                printf("\nCase i.ii\n");
                                wsk = tail->prev;
                                wsk->next = NULL;
                                free(tail);
                                tail = wsk;
                                wsk = wsk->next;
                            }
                            else // sriodek  -  error wlaca sie jak usuwam 1 element
                            {
                                printf("\nCase i.iv\n");
                                wsk->next->prev = wsk->prev;
                                wsk->prev->next = wsk->next;
                                free(wsk);
                                wsk = wsk->next;
                            }

                        }
                    else   {printf("  ->...");  wsk=wsk->next ;}

                }
                if(wsk==NULL)            printf("\nNie ma takiej ksiazki.\n");
                break;

            case '2':
                fflush(stdin);      printf("\nPodaj tytul: ");          scanf("%100[0-9a-zA-Z ]", &delName);
                while(wsk!=NULL)
                {
                    if(strcmp(delName,wsk->tytul)==0)
                    {
                        printf("\nUsuwam ksiazke. ");
                        if(tail->prev == tail->next) //poczatek
                        {
                                head = NULL;
                                free(tail);
                                wsk = wsk->next;
                        }
                        else if(wsk->prev!=NULL && wsk->next==NULL) // koniec
                        {
                            wsk = tail->prev;
                            wsk->next = NULL;
                            free(tail);
                            tail = wsk;
                            wsk = wsk->next;
                        }
                        else // sriodek
                        {
                            wsk->next->prev = wsk->prev;
                            wsk->prev->next = wsk->next;
                            free(wsk);
                        }

                    }
                    else   wsk=wsk->next ;

                }
                if(wsk==NULL)
                    printf("\nNie ma takiej ksiazki.");
                break;

            case '3':  break;
            default: ;
            }
            idNew();

        }
}

void zmien()
{
    book *wsk;
    element = (book*)malloc(sizeof(book));
    wsk = head;
    if(head == NULL)
        printf("\nLista pusta.");
    else
    {
        char newName[100]; int IDnew;
        printf("\nJezeli chcesz zmieniac po ID wcisniej 1, po tytule - 2, powrot do menu - 3: ");
        char op; fflush(stdin); scanf("%c", &op);
        while((op != '1') && (op != '2') && (op != '3'))
        {
            printf("\n Wybrales nie istniejaca opcje. Sprobuj ponownie:  ");
            scanf("%c", &op);
        }
        switch(op)
        {
        case '1':
                fflush(stdin);      printf("\nPodaj ID: ");          scanf("%d", &IDnew);
                while(wsk != NULL)
                {
                    if(wsk->ID == IDnew)
                    {
                        printf("\nZmieniamy dane ksiazke. ");  char tmp[100]="";


                            char t1[100]={'\0'}; fflush(stdin);  printf("Podaj nowy tytul: ");                                      scanf("%100[0-9a-zA-Z ]", &t1);
                            if(strlen(t1)>0)  strcpy(wsk->tytul, t1);
                            char t2[100]={'\0'}; fflush(stdin);  printf("Podaj imie autora: ");                                       scanf("%100[0-9a-zA-Z ]", &t2);
                            if(strlen(t2)>0)  strcpy(wsk->imie_aut, t2);
                            char t3[100]={'\0'};   fflush(stdin);  printf("Podaj nowe nazwisko autora: ");                              scanf("%100[0-9a-zA-Z ]", &t3);
                            if(strlen(t3)>0)  strcpy(wsk->nazw_aut, t3);
                            char t4[100]={'\0'};   fflush(stdin);  printf("Podaj nowa kategorie: ");                                    scanf("%100[0-9a-zA-Z ]", &t4);
                            if(strlen(t4)>0)  strcpy(wsk->kategoria, t4);
                            if(wsk->status == 0)
                            {
                                fflush(stdin);    printf("Podaj nowa date wypozyczania. \nDzien: ");                   scanf("%d", &wsk->D.dzien);
                                fflush(stdin);    printf("Miesiac: ");                                                 scanf("%d", &wsk->D.miesiac);
                                fflush(stdin);    printf("Rok: ");                                                     scanf("%d", &wsk->D.rok);

                                char t5[100]={'\0'};   fflush(stdin);  printf("Podaj nowe imie wypoz.: ");                                  scanf("%100[0-9a-zA-Z ]", &t5);
                                if(strlen(t5)>0)  strcpy(wsk->imie_wyp, t5);
                                char t6[100]={'\0'};   fflush(stdin);  printf("Podaj nowe nazwisko wypoz.: ");                              scanf("%100[0-9a-zA-Z ]", &t6);
                                if(strlen(t6)>0)  strcpy(wsk->nazw_wyp, t6);
                            }
                            char t7[100]={'\0'};   fflush(stdin);  printf("Podaj nowa dodatkowa informacje, |ENTER| jezeli nie ma: ");        scanf("%100[0-9a-zA-Z ]", &t7);
                            if(strlen(t7)>0)  strcpy(wsk->inne, t1);

                            wsk=wsk->next;
                            break;
                    }
                    else if(wsk->next == NULL)
                        {printf("\nNie ma takiej ksiazki."); wsk=wsk->next;}
                    else if( wsk!= NULL )
                        wsk=wsk->next;

                }

                break;

        case '2':
                fflush(stdin);      printf("\nPodaj tytul: ");
                char tytul[100];    scanf("%100[0-9a-zA-Z ]", &tytul);
                while(wsk != NULL)
                {
                    if(strcmp(tytul, wsk->tytul) == 0)
                    {
                        printf("\nZmieniamy dane ksiazke. ");  char tmp[100]="";


                            char t1[100]={'\0'}; fflush(stdin);  printf("Podaj nowy tytul: ");                                      scanf("%100[0-9a-zA-Z ]", &t1);
                            if(strlen(t1)>0)  strcpy(wsk->tytul, t1);
                            char t2[100]={'\0'}; fflush(stdin);  printf("Podaj imie autora: ");                                       scanf("%100[0-9a-zA-Z ]", &t2);
                            if(strlen(t2)>0)  strcpy(wsk->imie_aut, t2);
                            char t3[100]={'\0'};   fflush(stdin);  printf("Podaj nowe nazwisko autora: ");                              scanf("%100[0-9a-zA-Z ]", &t3);
                            if(strlen(t3)>0)  strcpy(wsk->nazw_aut, t3);
                            char t4[100]={'\0'};   fflush(stdin);  printf("Podaj nowa kategorie: ");                                    scanf("%100[0-9a-zA-Z ]", &t4);
                            if(strlen(t4)>0)  strcpy(wsk->kategoria, t4);
                            if(wsk->status == 0)
                            {
                                fflush(stdin);    printf("Podaj nowa date wypozyczania. \nDzien: ");                   scanf("%d", &wsk->D.dzien);
                                fflush(stdin);    printf("Miesiac: ");                                                 scanf("%d", &wsk->D.miesiac);
                                fflush(stdin);    printf("Rok: ");                                                     scanf("%d", &wsk->D.rok);

                                char t5[100]={'\0'};   fflush(stdin);  printf("Podaj nowe imie wypoz.: ");                                  scanf("%100[0-9a-zA-Z ]", &t5);
                                if(strlen(t5)>0)  strcpy(wsk->imie_wyp, t5);
                                char t6[100]={'\0'};   fflush(stdin);  printf("Podaj nowe nazwisko wypoz.: ");                              scanf("%100[0-9a-zA-Z ]", &t6);
                                if(strlen(t6)>0)  strcpy(wsk->nazw_wyp, t6);
                            }
                            char t7[100]={'\0'};   fflush(stdin);  printf("Podaj nowa dodatkowa informacje, |ENTER| jezeli nie ma: ");        scanf("%100[0-9a-zA-Z ]", &t7);
                            if(strlen(t7)>0)  strcpy(wsk->inne, t7);

                            wsk=wsk->next;
                            break;
                    }
                     else if(wsk->next == NULL)
                        {printf("\nNie ma takiej ksiazki."); wsk=wsk->next;}
                     else if( wsk!= NULL )
                        wsk=wsk->next;

                }

                break;

        case '3': break;
        default: ;
        }
    }
}

int idfun()
{
    book *wsk;
    wsk = head;
    int ID=1;

        while(wsk != NULL)
        {
            if(wsk->ID == ID)
            {
                ID++;
                //wsk = head;
            }

            wsk = wsk->next;
        }

    return ID;
}

void wyswietlOne()//TREZBA KOMUNIKAT
{
     book *wsk;
     wsk = head;
     printf("\nJezeli chcesz znalezc po ID -> |1|, po nazwisku -> |2| : ");
    char op; fflush(stdin); scanf("%c", &op);                                                        //some problem
    while((op != '1') && (op != '2'))
    {
        fflush(stdin);
        printf("\n Wybrales nie istniejaca opcje. Sprobuj ponownie(po ID -> |1|, po nazwisku wypoz. -> |2|):  ");
        scanf("%c", &op);
    }
    switch(op)
    {
    case '1':
        int ID;
        fflush(stdin);      printf("\nPodaj ID: ");          scanf("%d", &ID);
        while(wsk!=NULL)
        {
            if(wsk->ID == ID)
            {
                printf("\nNr indexu ksiazki: %d", wsk->ID);
                printf("\nTytul: %s", wsk->tytul);
                printf("\nAutor: %s %s", wsk->imie_aut, wsk->nazw_aut);
                printf("\nKategoria: %s", wsk->kategoria);
                printf("\nData wypozyczania %d/%d/%d",wsk->D.dzien,wsk->D.miesiac,wsk->D.rok);
                printf("\nWypozyczyl: %s %s", wsk->imie_wyp, wsk->nazw_wyp);
                printf("\nDodatkowa informacja: %s\n\n", wsk->inne);
                wsk = wsk->next;
                break;

            }
            else if(wsk->next == NULL)
                {printf("\nNie ma takiej ksiazki."); wsk=wsk->next;}
            else if(wsk != NULL)
                wsk=wsk->next;
        }
        break;
    case '2':
        char nazw[100];
        fflush(stdin);      printf("\nPodaj nazwisko: ");          scanf("%100[0-9a-zA-Z ]", &nazw);
        while(wsk!=NULL)
        {
            if(strcmp(nazw,wsk->nazw_wyp)==0)
            {
                printf("\nNr indexu ksiazki: %d", wsk->ID);
                printf("\nTytul: %s", wsk->tytul);
                printf("\nAutor: %s %s", wsk->imie_aut, wsk->nazw_aut);
                printf("\nKategoria: %s", wsk->kategoria);
                printf("\nData wypozyczania %d/%d/%d",wsk->D.dzien,wsk->D.miesiac,wsk->D.rok);
                printf("\nWypozyczyl: %s %s", wsk->imie_wyp, wsk->nazw_wyp);
                printf("\nDodatkowa informacja: %s\n\n", wsk->inne);
                wsk=wsk->next;
                break;
            }
            else if(wsk->next == NULL)
                {printf("\nNie ma takiej ksiazki."); wsk=wsk->next;}
            else if(wsk != NULL)
                wsk=wsk->next;
        }
        break;

    default: ;
    }
}

void wyswietlTyt()
{
    book *wsk;
    wsk = head;
    if(wsk == NULL) //lista pusta
        printf("\nLista pusta. ");
    else
    {
        printf("\nBAZA KSIAZEK: ");
        while(wsk != NULL)
        {
            printf("\nNr Indexu: %d \t Tytul: %s", wsk->ID, wsk->tytul);
            wsk = wsk->next;
        }
    }
}

int zmienStatus()
{
    book *wsk;
    wsk = head;
    printf("\nJezeli chcesz znalezc po ID -> |A|, po tytule -> |B| : ");
    char op; fflush(stdin); scanf("%c", &op);                                                        //some problem
    while((op != 'A') && (op  != 'B'))
    {
        fflush(stdin);
        printf("\n Wybrales nie istniejaca opcje. Sprobuj ponownie:  ");
        scanf("%c", &op);
    }
    switch(op)
    {
    case 'A':
        int ID;
        fflush(stdin);    printf("\nPodaj ID: ");     scanf("%d", &ID);
        while(wsk != NULL)
        {
            if(wsk->ID == ID)
            {

                if(wsk->status == 0)    //status == 0(wypoz)
                {
                    printf("\nObecny status ksiazki: wypoz. ");
                    printf("\nNr indexu ksiazki: %d", wsk->ID);
                    printf("\nTytul: %s", wsk->tytul);
                    printf("\nAutor: %s %s", wsk->imie_aut, wsk->nazw_aut);
                    printf("\nKategoria: %s", wsk->kategoria);
                    printf("\nData wypozyczania %d/%d/%d",wsk->D.dzien,wsk->D.miesiac,wsk->D.rok);
                    printf("\nWypozyczyl: %s %s", wsk->imie_wyp, wsk->nazw_wyp);
                    printf("\nDodatkowa informacja: %s\n\n", wsk->inne);

                    printf("\nZmienic status ksiazki na oddana? Tak->|1| , Nie->|2| : ");
                    char op1; fflush(stdin); scanf("%c", &op1);                                                        //some problem
                    while((op1 != '1') && (op1 != '2'))
                    {
                        fflush(stdin);
                        printf("\n Wybrales nie istniejaca opcje. Sprobuj ponownie:  ");   //zrobic zabezpieczenie przed nieliczbami
                        scanf("%c", &op1);
                    }
                    switch(op1)
                    {
                        case '1':
                                           //jak usunanc informacje ze struktury z posciegolnym
                            wsk->status = 1; //zmieniamy status z 0 na 1

                            wsk->D.dzien = 0;   wsk->D.miesiac = 0;     wsk->D.rok = 0;
                            strcpy(wsk->imie_wyp, "\0");    strcpy(wsk->nazw_wyp, "\0");    strcpy(wsk->inne, "\0");
                            //printf("\nTest* nowy status 1 = ? %d", wsk->status);

                            //printf("\nCheck***: ");
                            printf("\nObecny status ksiazki: nie wypoz. ");
                            printf("\nNr indexu ksiazki: %d", wsk->ID);
                            printf("\nTytul: %s", wsk->tytul);
                            printf("\nAutor: %s %s", wsk->imie_aut, wsk->nazw_aut);
                            printf("\nKategoria: %s", wsk->kategoria);
                            printf("\nData wypozyczania %d/%d/%d",wsk->D.dzien,wsk->D.miesiac,wsk->D.rok);
                            printf("\nWypozyczyl: %s %s", wsk->imie_wyp, wsk->nazw_wyp);
                            printf("\nDodatkowa informacja: %s\n\n", wsk->inne);
                            break;
                        case '2':
                            break;
                        default: ;

                    }
                }
                else //if (wsk->status == 1) //status == 1 (nie wypoz)
                {
                    printf("\nObecny status ksiazki: nie wypoz. ");

                    wsk->status = 0;
                    fflush(stdin);  printf("Podaj date wypozyczania. \nDzien: ");                   scanf("%d", &wsk->D.dzien);
                    fflush(stdin);  printf("Miesiac: ");                                            scanf("%d", &wsk->D.miesiac);
                    fflush(stdin);  printf("Rok: ");                                                scanf("%d", &wsk->D.rok);
                    fflush(stdin);  printf("Podaj imie wypoz.: ");                                  scanf("%100[0-9a-zA-Z ]", wsk->imie_wyp);
                    fflush(stdin);  printf("Podaj nazwisko wypoz.: ");                              scanf("%100[0-9a-zA-Z ]", wsk->nazw_wyp);
                    fflush(stdin);  printf("Podaj dodatkowa informacje, |ENTER| jezeli nie ma: ");        scanf("%100[0-9a-zA-Z ]", wsk->inne);
                }
                return 1;
            }
            else if(wsk->next == NULL)   {printf("\nNie ma takiej ksiazki."); wsk=wsk->next;}
            else if(wsk != NULL){ wsk = wsk->next; }
        }
        break;

    case 'B':
        char tytul[100];
        fflush(stdin);      printf("\nPodaj tytul: ");          scanf("%100[0-9a-zA-Z ]", &tytul);
        while(wsk != NULL)
        {
            if(strcmp(tytul,wsk->tytul)==0)
            {
                if(wsk->status == 0)    //status == 0( wypoz)
                {
                    printf("\nObecny status ksiazki: wypoz. ");
                    printf("\nNr indexu ksiazki: %d", wsk->ID);
                    printf("\nTytul: %s", wsk->tytul);
                    printf("\nAutor: %s %s", wsk->imie_aut, wsk->nazw_aut);
                    printf("\nKategoria: %s", wsk->kategoria);
                    printf("\nData wypozyczania %d/%d/%d",wsk->D.dzien,wsk->D.miesiac,wsk->D.rok);
                    printf("\nWypozyczyl: %s %s", wsk->imie_wyp, wsk->nazw_wyp);
                    printf("\nDodatkowa informacja: %s\n\n", wsk->inne);

                    printf("\nZmienic status ksiazki na oddana? Tak->|1| , Nie->|2| : ");
                    char op1; fflush(stdin); scanf("%c", &op1);                                                        //some problem
                    while((op1 != '1') && (op1 != '2'))
                    {
                        fflush(stdin);
                        printf("\n Wybrales nie istniejaca opcje. Sprobuj ponownie:  ");   //zrobic zabezpieczenie przed nieliczbami
                        scanf("%d", &op1);
                    }
                    switch(op1)
                    {
                        case '1':
                            wsk->status = 1;

                            wsk->D.dzien = 0;   wsk->D.miesiac = 0;     wsk->D.rok = 0;
                            strcpy(wsk->imie_wyp, "\0");    strcpy(wsk->nazw_wyp, "\0");    strcpy(wsk->inne, "\0");
                            //printf("\nTest* nowy status 1 = ? %d", wsk->status);

                            //printf("\nCheck  if changed status name oh wypz.***: ");
                            printf("\nObecny status ksiazki: nie wypoz. ");
                            printf("\nNr indexu ksiazki: %d", wsk->ID);
                            printf("\nTytul: %s", wsk->tytul);
                            printf("\nAutor: %s %s", wsk->imie_aut, wsk->nazw_aut);
                            printf("\nKategoria: %s", wsk->kategoria);
                            printf("\nData wypozyczania %d/%d/%d",wsk->D.dzien,wsk->D.miesiac,wsk->D.rok);
                            printf("\nWypozyczyl: %s %s", wsk->imie_wyp, wsk->nazw_wyp);
                            printf("\nDodatkowa informacja: %s\n\n", wsk->inne);
                            break;
                        case '2':
                            break;
                        default: ;

                    }
                }
                else //if(wsk->status == 1) //nie wypoz
                {
                    printf("\nObecny status ksiazki: nie wypoz. ");

                    wsk->status = 0; // zmieniam status
                    fflush(stdin);  printf("Podaj date wypozyczania. \nDzien: ");                   scanf("%d", &wsk->D.dzien);
                    fflush(stdin);  printf("Miesiac: ");                                            scanf("%d", &wsk->D.miesiac);
                    fflush(stdin);  printf("Rok: ");                                                scanf("%d", &wsk->D.rok);
                    fflush(stdin);  printf("Podaj imie wypoz.: ");                                  scanf("%100[0-9a-zA-Z ]", wsk->imie_wyp);
                    fflush(stdin);  printf("Podaj nazwisko wypoz.: ");                              scanf("%100[0-9a-zA-Z ]", wsk->nazw_wyp);
                    fflush(stdin);  printf("Podaj dodatkowa informacje, |ENTER| jezeli nie ma: ");  scanf("%100[0-9a-zA-Z ]", wsk->inne);//tu zmienic
                }
                return 1;
            }
            else if(wsk->next == NULL)   {printf("\nNie ma takiej ksiazki."); wsk=wsk->next;}
            else if(wsk != NULL){ wsk = wsk->next; }
        }

        break;

    }
    return 1;
}

void wyswietlWyp()
{
    book *wsk;
    wsk = head;
    if(wsk == NULL) //lista pusta
        printf("Lista pusta. ");
    else
    {
        printf("\nBAZA WYPOZYCZONYCH KSIAZEK:\n");
        while(wsk != NULL)
        {
            if(wsk->status == 0)
            {
                printf("\n| ^\nv |\n");
                printf("\nNr indexu ksiazki: %d", wsk->ID);
                printf("\nTytul: %s", wsk->tytul);
                printf("\nStatus: %d", wsk->status);
                printf("\nAutor: %s %s", wsk->imie_aut, wsk->nazw_aut);
                printf("\nKategoria: %s", wsk->kategoria);
                printf("\nData wypozyczania %d/%d/%d",wsk->D.dzien,wsk->D.miesiac,wsk->D.rok);
                printf("\nWypozyczyl: %s %s", wsk->imie_wyp, wsk->nazw_wyp);
                printf("\nDodatkowa informacja: %s\n\n", wsk->inne);
                wsk = wsk->next;
            }
            else {wsk = wsk->next; }
        }

    }
}
void zapisz()
{
    book *wsk = head;
    if( wsk == NULL )
        printf("Lista pusta. Nie mozna nic zapisac do pliku.");
    else
    {
        printf("Podaj nazwe pliku do zapisu |name.txt| : ");
        fflush(stdin);        char file[100];        scanf(" %s", &file);
        printf("\nTest1*\n");
        FILE *file_wsk = fopen( file, "w");
        if( file_wsk == NULL )
            printf("\nNie udalo sie otworzyc plik.");
        else
        {
            while( wsk != NULL)
            {


                fprintf(file_wsk, "\nNr indexu ksiazki: %d", wsk->ID);
                fprintf(file_wsk, "\nTytul: %s", wsk->tytul);
                fprintf(file_wsk, "\nStatus: %d", wsk->status);
                fprintf(file_wsk, "\nAutor: %s %s", wsk->imie_aut, wsk->nazw_aut);
                fprintf(file_wsk, "\nKategoria: %s", wsk->kategoria);
                fprintf(file_wsk, "\nData wypozyczania %d/%d/%d",wsk->D.dzien,wsk->D.miesiac,wsk->D.rok);
                fprintf(file_wsk, "\nWypozyczyl: %s %s", wsk->imie_wyp, wsk->nazw_wyp);
                fprintf(file_wsk, "\nDodatkowa informacja: %s\n\n", wsk->inne);

                wsk = wsk->next;
            }
            fclose(file_wsk);
            printf("Zapisano do pliku.");
        }
    }
}
void odczytaj2()
{
    printf("Podaj nazwe pliku do zapisu |name.txt| : ");
    fflush(stdin);    char name[100]="";    scanf(" %[0-9a-zA-Z\. ]", &name);
    FILE *fp = fopen(name , "w");
    if( fp == NULL )
    {
        printf("\nNie udalo sie otworzyc pliku.");
    }
    else
    {
        freeFile();// USUWAMY LISTE ISTNIEJACA DO TERAZ MOMENTU
        printf("\n freeFile -done\n");
        book *wsk; int nr;
        while(1)
        {
            printf("\n in while\n");
            switch(nr)
            {
                case 1:fscanf (fp, "%d%*c",      &wsk->ID);break;
                case 2:fscanf (fp, "%[^\n]%*c", &wsk->tytul);break;
                case 3:fscanf (fp, "%%d%*c",      &wsk->status);break;
                case 4:fscanf (fp, "%[^\n]%*c", &wsk->imie_aut);break;
                case 5:fscanf (fp, "%[^\n]%*c", &wsk->nazw_aut);break;
                case 6:fscanf (fp, "%[^\n]%*c", &wsk->kategoria);break;
                case 7:fscanf (fp, "%d%*c", &wsk->D.dzien);break;
                case 8:fscanf (fp, "%d%*c", &wsk->D.miesiac);break;
                case 9:fscanf (fp, "%d%*c", &wsk->D.rok);break;
                case 10:fscanf (fp, "%[^\n]%*c", &wsk->imie_wyp);break;
                case 11:fscanf (fp, "%[^\n]%*c", &wsk->nazw_wyp);break;

                default:;
            }
            nr++;
            if(nr==12)  nr=1;
            if(feof(fp))
               printf("EOF!!!!!!!!!!!!!!!!!!!!!!!!");// tu nie dziala
                //break;}
        }
    }
}


void odczytaj()
{
    printf("Podaj nazwe pliku do zapisu |name.txt| : ");
    fflush(stdin);    char name[100]="";    scanf(" %[0-9a-zA-Z\. ]", &name);
    FILE *fp = fopen(name , "w");
    if( fp == NULL )
    {
        printf("\nNie udalo sie otworzyc pliku.");
    }
    else
    {
        freeFile();// USUWAMY LISTE ISTNIEJACA DO TERAZ MOMENTU
        book *wsk;
        while(1)
        {

            if(feof(fp))
                break;
            fscanf (fp, "%d%*c",      &wsk->ID);   //%d
            fscanf (fp, "%[^\n]%*c", &wsk->tytul);
            fscanf (fp, "%%d%*c",      &wsk->status);
            fscanf (fp, "%[^\n]%*c", &wsk->imie_aut);
            fscanf (fp, "%[^\n]%*c", &wsk->nazw_aut);
            fscanf (fp, "%[^\n]%*c", &wsk->kategoria);
            fscanf (fp, "%d%*c", &wsk->D.dzien);
            fscanf (fp, "%d%*c", &wsk->D.miesiac);
            fscanf (fp, "%d%*c", &wsk->D.rok);
            fscanf (fp, "%[^\n]%*c", &wsk->imie_wyp);
                /*if(strcmp(wsk->imie_wyp, "") == 0)
                    strcpy(b.lender_name, "\0");    */
            fscanf (fp, "%[^\n]%*c", &wsk->nazw_wyp);
                /*if(strcmp(b.lender_surname, "brak") == 0)
                    strcpy(b.lender_surname, "\0");   */
            fscanf (fp, "%[^\n]%*c", &wsk->inne);
            /*if(strcmp(b.other, "brak danych") == 0)
                strcpy(b.other, "\0");      */

            if(feof(fp))
                break;

            wyswietlij();

            if(head==NULL) //jesli lista pusta
            {
                printf("\nCASE 1\n");
                head = (book*)malloc(sizeof(book));
                head->next = NULL;
                head->prev = NULL;
                tail = head;
                wsk = head;

            }
            else if(head!=NULL)
            {
                printf("\nCASE 2\n");
                wsk= head;
                wsk= (book*)malloc(sizeof(book));
                while(wsk->next!=NULL)
                {
                    wsk = wsk ->next;
                }
                printf("\n mamy element \n");
                wsk->next = NULL;
                wsk->prev = tail;
                tail->next = wsk;
                tail = wsk;
            }
            printf("\n mamy element utworzony\n");

            if(feof(fp))
                break;
        }
        printf("Odczytano pomyslnie.");
        wyswietlij();
        fclose(fp);
    }
}

void dodaj2(book *wsk)
{

    if(head==NULL) //jesli lista pusta
    {
        printf("\nCASE 1\n");
        head = (book*)malloc(sizeof(book));
        head->next = NULL;
        head->prev = NULL;
        tail = head;
        wsk = head;

    }
    else if(head!=NULL)
    {
        printf("\nCASE 2\n");
        element = head;
        element = (book*)malloc(sizeof(book));
        while(element->next!=NULL)
        {
            element=element->next;
        }
        printf("\n mamy element \n");
        element->next = NULL;
        element->prev = tail;
        tail->next = element;
        tail = element;
        wsk = element;
    }


    //wsk->ID = idfun();
}

void freeFile()
{//head=NULL; //WYCIEK PAMIECI ALE WYNIK TAKI SAM - USUWAMY STARA LISTE
    book *wsk;
    wsk = head;
    while(wsk != NULL)
    {
        if(head != NULL)
        {
            book *tail = head;
            if((*tail).prev == (*tail).next)
            {
                head = NULL;
                free(tail);
            }
            else
            {
                head = (*tail).next;
                (*head).prev = NULL;
                free(tail);
            }
        }
        wsk = wsk -> next;
    }
}

void idNew()
{
    book *wsk;
    wsk = head;
    int ID = 1;
    while(wsk != NULL)
    {
        wsk->ID = 0; // clean memory, i hope
        wsk->ID = ID;
        ID++;
        wsk = wsk->next;

    }
}
