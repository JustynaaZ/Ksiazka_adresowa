#include <iostream>
#include <windows.h>
#include <fstream>
#include <vector>

using namespace std;


struct kontakt {
    int id=0;
    string imie="", nazwisko="", telefon="", email="", adres="";
};

struct uzytkownik {
    int idUzytkownika=0;
    string nazwaUzytkownika="", haslo="";
};


int pobierzKontakty(vector <kontakt> &osoby) {
    int iloscKontaktow = 0;
    string linia, id;
    fstream plik;
    plik.open("Adresaci.txt", ios::in);

    if (plik.good() == true) {
        while(getline(plik,linia)) {
            osoby.push_back(kontakt());
            int dlugoscLinii = linia.length()-1;
            int licznikSlupkow = 0;

            for (int i=0; i<dlugoscLinii; i++) {
                if (linia[i] == '|')
                    licznikSlupkow++;
                else if (linia[i] != '|' && licznikSlupkow == 0)
                    id = id + linia[i];
                else if (linia[i] != '|' && licznikSlupkow == 1)
                    osoby[iloscKontaktow].imie = osoby[iloscKontaktow].imie + linia[i];
                else if (linia[i] != '|' && licznikSlupkow == 2)
                    osoby[iloscKontaktow].nazwisko = osoby[iloscKontaktow].nazwisko + linia[i];
                else if (linia[i] != '|' && licznikSlupkow == 3)
                    osoby[iloscKontaktow].telefon = osoby[iloscKontaktow].telefon + linia[i];
                else if (linia[i] != '|' && licznikSlupkow == 4)
                    osoby[iloscKontaktow].email = osoby[iloscKontaktow].email + linia[i];
                else if (linia[i] != '|' && licznikSlupkow == 5)
                    osoby[iloscKontaktow].adres = osoby[iloscKontaktow].adres + linia[i];
            }
            osoby[iloscKontaktow].id = atoi(id.c_str());
            id = "";
            iloscKontaktow++;
        }
    }
    plik.close();
    return iloscKontaktow;
}


int wprowadzanieNowychDanych(vector <kontakt> &osoby, int iloscKontaktow) {
    system("cls");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
    cout << endl << "  *** WPROWADZANIE NOWEGO ADRESATA ***" << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
    osoby.push_back(kontakt());
    if (iloscKontaktow == 0)
        osoby[0].id = 1;
    else
        osoby[iloscKontaktow].id = osoby[iloscKontaktow-1].id + 1;

    cout << endl << "Imi\251: ";
    cin.sync();
    getline(cin, osoby[iloscKontaktow].imie);
    cout << "Nazwisko: ";
    cin.sync();
    getline(cin, osoby[iloscKontaktow].nazwisko);
    cout << "Nrumer telefonu: ";
    cin.sync();
    getline(cin, osoby[iloscKontaktow].telefon);
    cout << "E-mail: ";
    cin.sync();
    getline(cin, osoby[iloscKontaktow].email);
    cout << "Adres: ";
    cin.sync();
    getline(cin, osoby[iloscKontaktow].adres);

    fstream plik;
    plik.open("Adresaci.txt", ios::out | ios::app);

    if (plik.good() == true) {
        plik << osoby[iloscKontaktow].id << "|";
        plik << osoby[iloscKontaktow].imie << "|";
        plik << osoby[iloscKontaktow].nazwisko << "|";
        plik << osoby[iloscKontaktow].telefon << "|";
        plik << osoby[iloscKontaktow].email << "|";
        plik << osoby[iloscKontaktow].adres << "|" << endl;

        iloscKontaktow++;
        cout << endl << "Nowy kontakt zapisano poprawnie!" << endl;
        plik.close();

    } else
        cout << "B\210\245d zapisu. Spr\242buj ponownie." << endl;

    Sleep(2000);
    system("cls");
    return iloscKontaktow;
}


void wyswietlWszystkieKontakty(vector <kontakt> &osoby, int iloscKontaktow) {
    system("cls");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
    cout << endl << "  *** LISTA ADRESAT\340W ***" << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);

    for (int i = 0; i < iloscKontaktow; i++) {
        cout << endl;
        cout << "ID:       " << osoby[i].id << endl;
        cout << "Imi\251:     " << osoby[i].imie << endl;
        cout << "Nazwisko: " << osoby[i].nazwisko << endl;
        cout << "Telefon:  " << osoby[i].telefon << endl;
        cout << "E-mail:   " << osoby[i].email << endl;
        cout << "Adres:    " << osoby[i].adres << endl;
    }
    system("pause");
}


void szukajPoImieniu(vector <kontakt> &osoby, int iloscKontaktow) {
    system("cls");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
    cout << endl << "  *** SZUKAJ PO IMIENIU ***" << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);

    string szukaneImie;
    cout << endl << "Wprowadz imi\251: ";
    cin.sync();
    getline(cin, szukaneImie);

    int licznikPetli = 0;
    for (int i = 0; i < iloscKontaktow; i++) {
        if (osoby[i].imie != szukaneImie)
            licznikPetli++;
        else {
            cout << endl << osoby[i].id << endl;
            cout << osoby[i].imie << " " << osoby[i].nazwisko << endl;
            cout << "Telefon: " << osoby[i].telefon << endl;
            cout << "E-mail: " << osoby[i].email << endl;
            cout << "Adres: " << osoby[i].adres << endl;
        }
    }
    if (licznikPetli == iloscKontaktow) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
        cout << endl << "Osoba o takim imieniu nie znajduje si\251 w ksi\245\276ce adresowej" << endl << endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
    }
    system("pause");
}


void szukajPoNazwisku(vector <kontakt> &osoby, int iloscKontaktow) {
    system("cls");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
    cout << endl << "  *** SZUKAJ PO NAZWISKU ***" << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);

    string szukaneNazwisko;
    cout << endl << "Wprowad\253 nazwisko: ";
    cin.sync();
    getline(cin, szukaneNazwisko);

    int licznikPetli = 0;
    for (int i = 0; i < iloscKontaktow; i++) {
        if (osoby[i].nazwisko != szukaneNazwisko)
            licznikPetli++;
        else {
            cout << endl << osoby[i].id << endl;
            cout << osoby[i].imie << " " << osoby[i].nazwisko << endl;
            cout << "Telefon: " << osoby[i].telefon << endl;
            cout << "E-mail: " << osoby[i].email << endl;
            cout << "Adres: " << osoby[i].adres << endl;
        }
    }
    if (licznikPetli == iloscKontaktow) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
        cout << endl << "Osoba o takim nazwisku nie znajduje si\251 w ksi\245\276ce adresowej" << endl << endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
    }
    system("pause");
}


void zapiszDoPlikuTekstowego (vector <kontakt> &osoby, int iloscKontaktow) {
    DeleteFile("Adresaci.txt");
    fstream plik;

    plik.open("Adresaci.txt", ios::out | ios::app);
    if (plik.good() == true) {
        for (int i=0; i<iloscKontaktow; i++) {
            plik << osoby[i].id << "|";
            plik << osoby[i].imie << "|";
            plik << osoby[i].nazwisko << "|";
            plik << osoby[i].telefon << "|";
            plik << osoby[i].email << "|";
            plik << osoby[i].adres << "|" << endl;
        }
        plik.close();
    }
}


int usunKontakt(vector <kontakt> &osoby, int iloscKontaktow) {
    system("cls");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
    cout << endl << "  *** USUWANIE ADRESATA ***" << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);

    int wybraneID, licznikOsob = 0;
    char wybor;
    cout << endl << "Wprowad\215 ID adresata, kt\242rego chcesz usun\245\206: ";
    cin >> wybraneID;

    for(int i=0; i<iloscKontaktow; i++) {
        if (osoby[i].id == wybraneID) {
            cout << endl;
            cout << "Imi\251:     " << osoby[i].imie << endl;
            cout << "Nazwisko: " << osoby[i].nazwisko << endl;
            cout << "Telefon:  " << osoby[i].telefon << endl;
            cout << "E-mail:   " << osoby[i].email << endl;
            cout << "Adres:    " << osoby[i].adres << endl;

            cout << endl << "Usun\245\206 tego adresata? (t/n)" << endl;
            cin >> wybor;
            if (wybor == 't') {
                vector <kontakt> :: iterator itr;
                itr = osoby.begin() + licznikOsob;
                osoby.erase(itr);
                iloscKontaktow--;
                zapiszDoPlikuTekstowego (osoby, iloscKontaktow);
                cout << endl << "Adresat zosta\210 poprawnie usuni\251ty!" << endl << endl;
                Sleep(2000);
                break;
            } else if (wybor == 'n') {
                system("cls");
                break;
            }
        } else {
            licznikOsob++;
            if (licznikOsob == iloscKontaktow) {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
                cout << endl << "Osoba o takim ID nie znajduje si\251 w ksi\245\276ce adresowej" << endl << endl;
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
                system("pause");
            }
        }
    }
    return iloscKontaktow;
}


void edytujKontakt(vector <kontakt> &osoby, int iloscKontaktow) {
    system("cls");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
    cout << endl << "  *** EDYTOWANIE ADRESATA ***" << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);

    int wybraneID, licznikOsob = 0;
    char wybor;
    string imie, nazwisko, telefon, email, adres;

    cout << endl << "Wprowad\253 ID adresata, kt\242rego chcesz edytowa\206: ";
    cin >> wybraneID;

    for(int i=0; i<iloscKontaktow; i++) {
        if (osoby[i].id == wybraneID) {
            cout << endl << "Imi\251:     " << osoby[i].imie << endl;
            cout << "Nazwisko: " << osoby[i].nazwisko << endl;
            cout << "Telefon:  " << osoby[i].telefon << endl;
            cout << "E-mail:   " << osoby[i].email << endl;
            cout << "Adres:    " << osoby[i].adres << endl;

            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
            cout << endl << "   Co chcesz edytowa\206?" << endl;
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);

            cout << endl << "1. Imi\251" << endl;
            cout << "2. Nazwisko" << endl;
            cout << "3. Numer telefonu" << endl;
            cout << "4. Adres e-mail" << endl;
            cout << "5. Adres zamieszkania" << endl;
            cout << "6. Nic" << endl;
            cout << endl << "Tw\242j wyb\242r: ";
            cin >> wybor;

            if (wybor == '6') {
                system("cls");
                break;
            } else {
                if (wybor == '1') {
                    cout << "Wprowad\253 nowe imi\251: ";
                    cin >> imie;
                    osoby[i].imie = imie;
                }
                if (wybor == '2') {
                    cout << "Wprowad\253 nowe nazwisko: ";
                    cin >> nazwisko;
                    osoby[i].nazwisko = nazwisko;
                }
                if (wybor == '3') {
                    cout << "Wprowad\253 nowy numer telefonu: ";
                    cin >> telefon;
                    osoby[i].telefon = telefon;
                }
                if (wybor == '4') {
                    cout << "Wprowad\253 nowy adres e-mail: ";
                    cin >> email;
                    osoby[i].email = email;
                }
                if (wybor == '5') {
                    cout << "Wprowad\253 nowy adres zamieszkania: ";
                    cin >> adres;
                    osoby[i].adres = adres;
                }
                zapiszDoPlikuTekstowego (osoby, iloscKontaktow);
                cout << endl << "Nowe dane zosta\210y zapisane!";
                Sleep(2000);
                break;
            }
        } else {
            licznikOsob++;
            if (licznikOsob == iloscKontaktow) {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
                cout << endl << "Osoba o takim ID nie znajduje si\251 w ksi\245\276ce adresowej" << endl << endl;
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
                system("pause");
            }
        }
    }
}


int rejestracja (vector <uzytkownik> &uzytkownicy, int iloscUzytkownikow) {
    system("cls");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
    cout << endl << "  *** REJESTRACJA ***" << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);

    string nazwa, haslo;
    cout <<endl << "Podaj nazw\251 u\276ytkownika: ";
    cin >> nazwa;

    int i=0;
    while (i<iloscUzytkownikow) {
        if (uzytkownicy[i].nazwaUzytkownika == nazwa) {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
            cout << "Taki u\276ytkownik ju\276 istnieje" << endl;
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
            cout << "Podaj inn\245 nazw\251 u\276ytkownika: ";
            cin >> nazwa;
            i=0;
        } else
            i++;
    }
    cout << endl << "Podaj has\210o: ";
    cin >> haslo;

    uzytkownicy.push_back(uzytkownik());
    uzytkownicy[iloscUzytkownikow].nazwaUzytkownika = nazwa;
    uzytkownicy[iloscUzytkownikow].haslo = haslo;
    if (iloscUzytkownikow == 0)
        uzytkownicy[0].idUzytkownika = 1;
    else
        uzytkownicy[iloscUzytkownikow].idUzytkownika = uzytkownicy[iloscUzytkownikow-1].idUzytkownika + 1;

    fstream plik;
    plik.open("Uzytkownicy.txt", ios::out | ios::app);

    if (plik.good() == true) {
        plik << uzytkownicy[iloscUzytkownikow].idUzytkownika << "|";
        plik << uzytkownicy[iloscUzytkownikow].nazwaUzytkownika << "|";
        plik << uzytkownicy[iloscUzytkownikow].haslo << "|" << endl;

        iloscUzytkownikow++;
        plik.close();
    }
    cout << endl << "Konto zosta\210o za\210o\276one!" << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
    cout << "Teraz mo\276esz si\251 ZALOGOWA\217" << endl << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
    system("pause");

    return iloscUzytkownikow;
}


int pobierzUzytkownikow(vector <uzytkownik> &uzytkownicy) {
    int iloscUzytkownikow = 0;
    string linia, id;
    fstream plik;
    plik.open("Uzytkownicy.txt", ios::in);

    if (plik.good() == true) {
        while(getline(plik,linia)) {
            uzytkownicy.push_back(uzytkownik());
            int dlugoscLinii = linia.length()-1;
            int licznikSlupkow = 0;

            for (int i=0; i<dlugoscLinii; i++) {
                if (linia[i] == '|')
                    licznikSlupkow++;
                else if (linia[i] != '|' && licznikSlupkow == 0)
                    id = id + linia[i];
                else if (linia[i] != '|' && licznikSlupkow == 1)
                    uzytkownicy[iloscUzytkownikow].nazwaUzytkownika = uzytkownicy[iloscUzytkownikow].nazwaUzytkownika + linia[i];
                else if (linia[i] != '|' && licznikSlupkow == 2)
                    uzytkownicy[iloscUzytkownikow].haslo = uzytkownicy[iloscUzytkownikow].haslo + linia[i];
            }
            uzytkownicy[iloscUzytkownikow].idUzytkownika = atoi(id.c_str());
            id = "";
            iloscUzytkownikow++;
        }
    }
    plik.close();
    return iloscUzytkownikow;
}


int logowanie (vector <uzytkownik> &uzytkownicy, int iloscUzytkownikow) {
    system("cls");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
    cout << endl << "  *** LOGOWANIE ***" << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);

    string nazwa, haslo;
    cout << endl << "Podaj login: ";
    cin >> nazwa;

    int i = 0;
    while (i < iloscUzytkownikow) {
        if (uzytkownicy[i].nazwaUzytkownika == nazwa) {
            for (int proby=1; proby<4; proby++) {
                cout << "Podaj has\210o (pr\242ba nr " << proby << "): ";
                cin >> haslo;
                if (uzytkownicy[i].haslo == haslo) {
                    cout << endl << "Zalogowa\210e\230 si\251!" << endl;
                    Sleep(2000);
                    return uzytkownicy[i].idUzytkownika;
                }
            }
            cout << endl << "B\210\251dne has\210o!" << "\a" << endl;
            cout << "Poczekaj 10 sekund przed kolejn\245 prob\245." << endl;
            Sleep(10000);
            return 0;
        }
        i++;
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
    cout << "U\276ytkownik z takim loginem nie zosta\210 jeszcze zarejestrowany" << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
    Sleep(2000);
    return 0;
}


void zapiszHasloDoPliku (vector <uzytkownik> &uzytkownicy, int iloscUzytkownikow) {
    DeleteFile("Uzytkownicy.txt");
    fstream plik;

    plik.open("Uzytkownicy.txt", ios::out | ios::app);
    if (plik.good() == true) {
        for (int i=0; i<iloscUzytkownikow; i++) {
            plik << uzytkownicy[i].idUzytkownika << "|";
            plik << uzytkownicy[i].nazwaUzytkownika << "|";
            plik << uzytkownicy[i].haslo << "|" << endl;
        }
        plik.close();
    }
}


void zmianaHasla(vector <uzytkownik> &uzytkownicy, int iloscUzytkownikow, int idZalogowanegoUzytkownika) {
    system("cls");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
    cout << endl << "  *** ZMIANA HAS\235A ***" << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);

    string haslo;
    cout << endl << "Podaj nowe has\210o: ";
    cin >> haslo;

    for (int i=0; i<iloscUzytkownikow; i++) {
        if (uzytkownicy[i].idUzytkownika == idZalogowanegoUzytkownika) {
            uzytkownicy[i].haslo = haslo;
            zapiszHasloDoPliku(uzytkownicy, iloscUzytkownikow);
            cout << endl << "Has\210o zosta\210o zmienione!" << endl;
            Sleep(2000);
        }
    }
}


void wyswietlMenuGlowne() {
    system("cls");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
    cout << endl << "      KSI\244\275KA ADRESOWA" << endl;
    cout << "****************************" << endl << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
    cout << "1. Dodaj adresata" << endl;
    cout << "2. Lista wszystkich adresat\242w" << endl;
    cout << "3. Wyszukaj po imieniu" << endl;
    cout << "4. Wyszukaj po nazwisku" << endl;
    cout << "5. Usu\344 adresata" << endl;
    cout << "6. Edytuj adresata" << endl;
    cout << "7. Zmie\344 has\210o" << endl;
    cout << "8. Wyloguj si\251" << endl;
}


void wyswietlMenuLogowania() {
    system("cls");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
    cout << endl << "      KSI\244\275KA ADRESOWA" << endl;
    cout << "****************************" << endl << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
    cout << "1. Rejestracja" << endl;
    cout << "2. Logowanie" << endl;
    cout << "3. Wyj\230cie" << endl;
}


int main() {
    vector <kontakt> osoby;
    vector <uzytkownik> uzytkownicy;
    char wyborLogowanie;
    int idZalogowanegoUzytkownika = 0;
    int iloscUzytkownikow = pobierzUzytkownikow(uzytkownicy);
    int iloscKontaktow = pobierzKontakty(osoby);

    while(1) {
        if (idZalogowanegoUzytkownika == 0) {
            wyswietlMenuLogowania();
            cout << endl << "Tw\242j wyb\242r: ";
            cin >> wyborLogowanie;

            if (wyborLogowanie == '1')
                iloscUzytkownikow = rejestracja(uzytkownicy, iloscUzytkownikow);
            else if (wyborLogowanie == '2')
                idZalogowanegoUzytkownika = logowanie(uzytkownicy, iloscUzytkownikow);
            else if (wyborLogowanie == '3')
                exit(0);
        }

        else if (idZalogowanegoUzytkownika > 0) {
            char wybor;
            wyswietlMenuGlowne();
            cout << endl << "Tw\242j wyb\242r: ";
            cin >> wybor;

            if (wybor == '1')
                iloscKontaktow = wprowadzanieNowychDanych(osoby, iloscKontaktow);
            else if (wybor == '2')
                wyswietlWszystkieKontakty(osoby, iloscKontaktow);
            else if (wybor == '3')
                szukajPoImieniu(osoby, iloscKontaktow);
            else if (wybor == '4')
                szukajPoNazwisku(osoby, iloscKontaktow);
            else if (wybor == '5')
                iloscKontaktow = usunKontakt(osoby, iloscKontaktow);
            else if (wybor == '6')
                edytujKontakt(osoby, iloscKontaktow);
            else if (wybor == '7')
                zmianaHasla(uzytkownicy, iloscUzytkownikow, idZalogowanegoUzytkownika);
            else if (wybor == '8')
                idZalogowanegoUzytkownika = 0;
            else
                system("cls");
        }
    }
    return 0;
}

